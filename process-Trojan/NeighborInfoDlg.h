// NeighborInfoDlg.h : header file
//

#if !defined(AFX_NEIGHBORINFODLG_H__62DB6683_C7A0_4019_A9C5_E45277A7BFEA__INCLUDED_)
#define AFX_NEIGHBORINFODLG_H__62DB6683_C7A0_4019_A9C5_E45277A7BFEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNeighborInfoDlg dialog
#include "MessSocket.h"

class CNeighborInfoDlg : public CDialog
{
// Construction
public:
	CNeighborInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNeighborInfoDlg)
	enum { IDD = IDD_NEIGHBORINFO_DIALOG };
	CListCtrl	m_ListProcess;
	CIPAddressCtrl	m_123;
	CListCtrl	m_ListView;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeighborInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	//BYTE m_bStartAddress[4],m_bEndAddress[4];
	CMessSocket m_socket;
	BOOL m_bStop;
	void ReceiveMessage();
	DWORD FindProcess(char *strProcessName);//查找进程
	void KillProcess();//杀掉进程
	BOOL GetDebugPriv();//提高权限
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNeighborInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBeginScan();
	afx_msg void OnStopScan();
	afx_msg void OnMyHelp();
	afx_msg void OnEmpty();
	afx_msg void OnButton2();
    afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEIGHBORINFODLG_H__62DB6683_C7A0_4019_A9C5_E45277A7BFEA__INCLUDED_)
