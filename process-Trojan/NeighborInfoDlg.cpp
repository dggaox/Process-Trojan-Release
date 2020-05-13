// NeighborInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeighborInfo.h"
#include "NeighborInfoDlg.h"
#include "resource.h"
#include "TLHELP32.H"
#include "psapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NBTSTATPORT 137		//nbtstat name port
#define OWNERPORT	4321

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//--------------------------------var-------------------------------
BYTE bs[50]=
{0x0,0x00,0x0,0x10,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x43,0x4b,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x0,0x0,0x21,0x0,0x1};
HANDLE wait_handle;
UINT NbtstatThread(LPVOID param);



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeighborInfoDlg dialog

CNeighborInfoDlg::CNeighborInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeighborInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNeighborInfoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNeighborInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNeighborInfoDlg)
	DDX_Control(pDX, IDC_LISTPROCSS, m_ListProcess);
	DDX_Control(pDX, IDC_IPADDRESS1, m_123);
	DDX_Control(pDX, IDC_LISTINFOR, m_ListView);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNeighborInfoDlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CNeighborInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEGINSCAN, OnBeginScan)
	ON_BN_CLICKED(IDC_STOPSCAN, OnStopScan)
	ON_BN_CLICKED(IDC_MYHELP, OnMyHelp)
	ON_BN_CLICKED(IDC_EMPTY, OnEmpty)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeighborInfoDlg message handlers

BOOL CNeighborInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	wait_handle=CreateEvent(NULL,true,false,"receive data");
	GetDlgItem(IDC_STOPSCAN)->EnableWindow(false);

	DWORD dwStyle=GetWindowLong(m_ListView.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_ListView.GetSafeHwnd(),GWL_STYLE,dwStyle);
	SetWindowLong(m_ListProcess.GetSafeHwnd(),GWL_STYLE,dwStyle);

	//��ʼ����ͼ�б�1
    m_ListView.InsertColumn(3,"MAC��ַ",LVCFMT_LEFT,127);
	m_ListView.InsertColumn(2,"����",LVCFMT_LEFT,127);
	m_ListView.InsertColumn(1,"������",LVCFMT_LEFT,128);
	m_ListView.InsertColumn(0,"IP��ַ",LVCFMT_LEFT,128); 
	m_ListView.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_ListView.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	//��ʼ����ͼ�б�2
	m_ListProcess.InsertColumn(0,"����",LVCFMT_LEFT,127);
	m_ListProcess.InsertColumn(1,"ID",LVCFMT_LEFT,127);
	m_ListProcess.InsertColumn(2,"������",LVCFMT_LEFT,128);
	m_ListProcess.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_ListProcess.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);


	//��ʼ���˿�
	if(AfxSocketInit(NULL)==FALSE)
	{
		AfxMessageBox("Error Init Socket");
	}
	m_socket.Init(this);
	if(m_socket.Create(OWNERPORT,SOCK_DGRAM)==FALSE)
	{
		AfxMessageBox("Socket Create Error");
	}
    
	//���ü�ʱ��
	SetTimer(0,100,NULL);

	m_bStop=FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNeighborInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNeighborInfoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNeighborInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNeighborInfoDlg::OnBeginScan() 
{
	GetDlgItem(IDC_BEGINSCAN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOPSCAN)->EnableWindow(TRUE);

	//��ʼɨ��
	AfxBeginThread(NbtstatThread,(LPVOID)this,THREAD_PRIORITY_NORMAL);
}

void CNeighborInfoDlg::OnStopScan() 
{
	// TODO: Add your control notification handler code here
	m_bStop=TRUE;
}

void CNeighborInfoDlg::ReceiveMessage()
{
	BYTE Buf[500];
	static CString strOldIP;
	CString str,strIP,strHost,strHex,strMac,Host,Group;
	UINT dport;
	m_socket.ReceiveFrom(Buf,500,strIP,dport,0);

	if(strIP==(char)NULL||strIP==strOldIP)return;
	strOldIP=strIP;

	//ip
	int index=m_ListView.InsertItem(0,strIP);

	strHost="";
	strHex="";
	Host="\\";
	
	int tem=0,num=0;
	bool bAdd=true;

	for(int i=0;i<500;i++)
	{
		if(i%50==0)
			TRACE("\n");
		TRACE("%c",Buf[i]);
	}

	//nbtstatǰ���57���ֽ���
	for(i=57;i<500;i++) //57-72
	{
		//end
		if(Buf[i]==0xcc)
			break; 
		
		if(Buf[i]==0x20)
			bAdd=false;
		if(bAdd)
		{
			str.Format("%c",Buf[i]);
			if(Buf[i]>=' ')strHost+=str;

			str.Format("%02x.",Buf[i]);
			strHex+=str;
		}

		if((++tem)%18==0)
		{
            bAdd=true; 
			strHost.TrimRight((char)NULL);
			if(strHost=="")
			{
   				strMac.Delete(17,strMac.GetLength()-17);
				m_ListView.SetItem(index,3,LVIF_TEXT,strMac, 0, 0, 0,0);
				break;
			}

			if(num==0&&strHost!="")
			{
				m_ListView.SetItem(index,2,LVIF_TEXT,strHost, 0, 0, 0,0);
				Host=strHost;
				num++;
			}
			else
			{
				if(Host!=strHost&&num==1&&strHost!="")
				{
					m_ListView.SetItem(index,1,LVIF_TEXT,strHost, 0, 0, 0,0);
					Group=strHost;
				    num++;
				}

			}
			strMac=strHex;
			strHost="";
	    	strHex="";
		}
	}
	SetEvent(wait_handle);
}

void CNeighborInfoDlg::OnMyHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog dlg(IDD_ABOUTBOX);
	dlg.DoModal();
	
}

//--------------------------nbtstat�߳�----------------------
UINT NbtstatThread(LPVOID param)
{
	CNeighborInfoDlg * dlg=(CNeighborInfoDlg *)param;

	BYTE begin[4],end[4];
	begin[0]=192;
	begin[1]=168;
	begin[2]=1;
	begin[3]=100;
	end[0]=192;
	end[1]=168;
	end[2]=1;
	end[3]=200;

	CString ip;
	do
	{
		if(dlg->m_bStop)
		{
			AfxMessageBox("��ֹɨ��!");
			dlg->GetDlgItem(IDC_STOPSCAN)->EnableWindow(false);
	        dlg->GetDlgItem(IDC_BEGINSCAN)->EnableWindow(true);
			dlg->m_bStop=FALSE;
			return 1;
		}

		ip.Format("%d.%d.%d.%d",begin[0],begin[1],begin[2],begin[3]);
		if(begin[3]!=0&&begin[2]!=0)
			dlg->m_socket.SendTo((void*)bs,50,NBTSTATPORT,ip,0);
		
 		WaitForSingleObject(wait_handle,100);
		ResetEvent(wait_handle);
		
		//=============================================
		if(begin[2]<=end[2])
		{
		   if(begin[3]<end[3])
			   begin[3]++;
		   else if(begin[2]<end[2]&&begin[3]<255)
			   begin[3]++;
		   else if(begin[2]<end[2]&&begin[3]==255)
		   {
			   begin[3]=0;
			   begin[2]++;
		   }
		}
		else 
			break;
		if(begin[3]>=end[3]&&begin[2]>=end[2])
			break;
	}while(begin[2]<=255&&begin[3]<=255);

	dlg->GetDlgItem(IDC_STOPSCAN)->EnableWindow(false);
	dlg->GetDlgItem(IDC_BEGINSCAN)->EnableWindow(true);
	return 0;
}
//-----------------------------------------------------------

void CNeighborInfoDlg::OnEmpty() 
{
	m_ListView.DeleteAllItems();
}

void CNeighborInfoDlg::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_NEIGHBOR_INFO_DLG));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CNeighborInfoDlg::OnButton2() 
{
	POSITION pos = m_ListView.GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = m_ListView.GetNextSelectedItem(pos);
		CString strUserinfo;
		strUserinfo.Format("IP��ַ:%s",
			m_ListView.GetItemText(nItem,0));
		GetDlgItem(IDC_IP)->SetWindowText(strUserinfo);
	}	
}

void CNeighborInfoDlg::OnButton3() 
{
	POSITION pos = m_ListView.GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = m_ListView.GetNextSelectedItem(pos);
		CString   strIP;
		strIP.Format("%s",m_ListView.GetItemText(nItem,0));
		DWORD   dwIP;   
		dwIP   =   inet_addr(strIP);   
		unsigned   char   *pIP   =   (unsigned   char*)&dwIP;   
	    m_123.SetAddress(*pIP,   *(pIP+1),   *(pIP+2),   *(pIP+3));
	}	
}

void CNeighborInfoDlg::OnButton4() 
{
	m_ListProcess.DeleteAllItems();
	HANDLE toolhelp=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//ʹ�ñ������KERNEL32.LIB���ӿ�
	if(toolhelp==NULL)
	{
		AfxMessageBox("ɨ�����ʧ�ܣ���");
	}
	m_ListProcess.SetRedraw(FALSE);
	PROCESSENTRY32 processinfo;
	int i=0;
	CString str;
	BOOL start=Process32First(toolhelp,&processinfo);
	while(start)
	{
		m_ListProcess.InsertItem(i,"");
		m_ListProcess.SetItemText(i,0,processinfo.szExeFile);
		str.Format("%08x",processinfo.th32ProcessID);
		m_ListProcess.SetItemText(i,1,str);
		str.Format("%08x",processinfo.th32ParentProcessID);
		m_ListProcess.SetItemText(i,2,str);
		start=Process32Next(toolhelp,&processinfo);
		i++;
	}
	m_ListProcess.SetRedraw(TRUE);
	
}

//���ҽ���
DWORD CNeighborInfoDlg::FindProcess(char *strProcessName)
{
    DWORD aProcesses[1024], cbNeeded, cbMNeeded;
    HMODULE hMods[1024];
    HANDLE hProcess;
    char szProcessName[MAX_PATH];

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))  
	{
		return 0;
	}
    for(int i=0; i< (int) (cbNeeded / sizeof(DWORD)); i++)
    {
        hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
        EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
        GetModuleFileNameEx( hProcess, hMods[0], szProcessName,sizeof(szProcessName));
        
        if(strstr(szProcessName, strProcessName))
        {
            return(aProcesses[i]);
        }
    }
    return 0;
}

//��ɱ����
void CNeighborInfoDlg::KillProcess()
{
	HANDLE hYourTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, FindProcess("gamemd.exe"));
	if(hYourTargetProcess == NULL)
	{
		return;
	}
	GetDebugPriv();//���Ȩ��
	TerminateProcess(hYourTargetProcess,0);
    MessageBox("û�г�ү�������ֹ���к쾯��Ϸ-.-","����",MB_ICONEXCLAMATION|MB_OK); 
    return;
}

//���Ȩ��
BOOL CNeighborInfoDlg::GetDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
    {
		return FALSE;
    }
	if (!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&sedebugnameValue))
	{
		CloseHandle( hToken );
		return FALSE;
	}
	
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	if (!AdjustTokenPrivileges( hToken, FALSE,&tkp,sizeof tkp, NULL,NULL))
    {
        CloseHandle( hToken );
        return FALSE;
    }
    return TRUE;
}

void CNeighborInfoDlg::OnButton5() 
{
   KillProcess();	
}

void CNeighborInfoDlg::OnTimer(UINT nIDEvent) 
{
    KillProcess();	
	CDialog::OnTimer(nIDEvent);
}
