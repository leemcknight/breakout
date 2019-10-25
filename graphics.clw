; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraphicsView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "graphics.h"
LastPage=0

ClassCount=5
Class1=CGraphicsApp
Class2=CGraphicsDoc
Class3=CGraphicsView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CGraphicsApp]
Type=0
HeaderFile=graphics.h
ImplementationFile=graphics.cpp
Filter=N

[CLS:CGraphicsDoc]
Type=0
HeaderFile=graphicsDoc.h
ImplementationFile=graphicsDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_FILE_NEW

[CLS:CGraphicsView]
Type=0
HeaderFile=graphicsView.h
ImplementationFile=graphicsView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CGraphicsView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_FILE_NEW




[CLS:CAboutDlg]
Type=0
HeaderFile=graphics.cpp
ImplementationFile=graphics.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

