; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgTransfert
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ClipCxSrv.h"
LastPage=0

ClassCount=10
Class1=CClipCxSrvApp
Class2=CClipCxSrvDoc
Class3=CClipCxSrvView
Class4=CMainFrame

ResourceCount=11
Resource1=IDR_MENU_CONTEXT
Class5=CAboutDlg
Class6=FClipCxSrvEtatCxView
Class7=CClientSocket
Resource2=IDD_PROPTRANSFICHIER (English (U.S.))
Class8=CDialogPort
Resource3=IDR_FCLIPCXSRVETATCXVIEW_TMPL
Resource4=IDD_PROPPAGE_TRANS (English (U.S.))
Resource5=IDD_DIALOGBAR (English (U.S.))
Resource6=IDD_DIALOG_PORT
Resource7=IDD_ABOUTBOX
Resource8=IDD_DIALOG_PTRANSFIC
Resource9=IDD_FORMVIEW (English (U.S.))
Class9=CDlgPropTransFichier
Resource10=IDD_FCLIPCXSRVETATCXVIEW_FORM
Class10=CDlgTransfert
Resource11=IDR_MAINFRAME

[CLS:CClipCxSrvApp]
Type=0
HeaderFile=ClipCxSrv.h
ImplementationFile=ClipCxSrv.cpp
Filter=W
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CClipCxSrvApp

[CLS:CClipCxSrvDoc]
Type=0
HeaderFile=ClipCxSrvDoc.h
ImplementationFile=ClipCxSrvDoc.cpp
Filter=N
LastObject=CClipCxSrvDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CClipCxSrvView]
Type=0
HeaderFile=ClipCxSrvView.h
ImplementationFile=ClipCxSrvView.cpp
Filter=C
LastObject=CClipCxSrvView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=ClipCxSrv.cpp
ImplementationFile=ClipCxSrv.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=W
LastObject=CClientSocket
VirtualFilter=uq

[DLG:IDD_DIALOG_PORT]
Type=1
Class=CDialogPort
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_PORT,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECK1,button,1342242819

[CLS:CDialogPort]
Type=0
HeaderFile=DialogPort.h
ImplementationFile=DialogPort.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogPort

[MNU:IDR_MENU_CONTEXT]
Type=1
Class=?
Command1=ID_CONTEXT_OUVRIR
Command2=ID_FILE_NEW
Command3=ID_DECONNECTER
Command4=ID_FILE_CLOSE
CommandCount=4

[DLG:IDD_FCLIPCXSRVETATCXVIEW_FORM]
Type=1
Class=FClipCxSrvEtatCxView
ControlCount=2
Control1=IDC_STATIC,static,1342177283
Control2=IDC_EDIT_ETATCX,edit,1342257349

[CLS:FClipCxSrvEtatCxView]
Type=0
HeaderFile=FClipCxSrvEtatCxView.h
ImplementationFile=FClipCxSrvEtatCxView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=FClipCxSrvEtatCxView

[MNU:IDR_FCLIPCXSRVETATCXVIEW_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_DECONNECTER
Command3=ID_APP_EXIT
Command4=ID_PARAMETRER
Command5=ID_PARAM_FICHIER
Command6=ID_APP_ABOUT
CommandCount=6

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPTRANSFICHIER (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350631552
Control3=IDC_BUTTON_BROWSE,button,1342242816

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PTRANSFIC]
Type=1
Class=CDlgPropTransFichier
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_PARAMPATH,edit,1350631552
Control4=IDC_BUTTON_BROWSE,button,1342242816
Control5=IDC_CHECK_AUTOSAVE,button,1342242819
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgPropTransFichier]
Type=0
HeaderFile=DlgPropTransFichier.h
ImplementationFile=DlgPropTransFichier.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgPropTransFichier
VirtualFilter=dWC

[DLG:IDD_PROPPAGE_TRANS (English (U.S.))]
Type=1
Class=CDlgTransfert
ControlCount=2
Control1=IDC_PROGRESS1,msctls_progress32,1350565888
Control2=IDC_EDIT_NOMFICTRANS,edit,1342179328

[CLS:CDlgTransfert]
Type=0
HeaderFile=DlgTransfert.h
ImplementationFile=DlgTransfert.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgTransfert

