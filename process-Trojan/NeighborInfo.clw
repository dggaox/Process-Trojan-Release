; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNeighborInfoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "neighborinfo.h"
LastPage=0

ClassCount=4
Class1=CMessSocket
Class2=CNeighborInfoApp
Class3=CAboutDlg
Class4=CNeighborInfoDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_NEIGHBORINFO_DIALOG
Resource3=CG_IDR_POPUP_NEIGHBOR_INFO_DLG

[CLS:CMessSocket]
Type=0
BaseClass=CSocket
HeaderFile=MessSocket.h
ImplementationFile=MessSocket.cpp

[CLS:CNeighborInfoApp]
Type=0
BaseClass=CWinApp
HeaderFile=NeighborInfo.h
ImplementationFile=NeighborInfo.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=NeighborInfoDlg.cpp
ImplementationFile=NeighborInfoDlg.cpp

[CLS:CNeighborInfoDlg]
Type=0
BaseClass=CDialog
HeaderFile=NeighborInfoDlg.h
ImplementationFile=NeighborInfoDlg.cpp
LastObject=IDC_BUTTON5
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NEIGHBORINFO_DIALOG]
Type=1
Class=CNeighborInfoDlg
ControlCount=13
Control1=IDOK,button,1342242816
Control2=IDC_BEGINSCAN,button,1342242817
Control3=IDC_STOPSCAN,button,1342242816
Control4=IDC_LISTINFOR,SysListView32,1350631424
Control5=IDC_MYHELP,button,1342242816
Control6=IDC_EMPTY,button,1342242816
Control7=IDC_IP,edit,1350631552
Control8=IDC_BUTTON2,button,1342242816
Control9=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control10=IDC_BUTTON3,button,1342242816
Control11=IDC_BUTTON4,button,1342242816
Control12=IDC_LISTPROCSS,SysListView32,1350631424
Control13=IDC_BUTTON5,button,1342242816

[MNU:CG_IDR_POPUP_NEIGHBOR_INFO_DLG]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=IDC_BUTTON3
Command5=IDC_BUTTON2
CommandCount=5

