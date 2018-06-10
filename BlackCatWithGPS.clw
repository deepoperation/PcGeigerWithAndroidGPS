; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CBlackCatWithGPSDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BlackCatWithGPS.h"

ClassCount=3
Class1=CBlackCatWithGPSApp
Class2=CBlackCatWithGPSDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BLACKCATWITHGPS_DIALOG

[CLS:CBlackCatWithGPSApp]
Type=0
HeaderFile=BlackCatWithGPS.h
ImplementationFile=BlackCatWithGPS.cpp
Filter=N

[CLS:CBlackCatWithGPSDlg]
Type=0
HeaderFile=BlackCatWithGPSDlg.h
ImplementationFile=BlackCatWithGPSDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CBlackCatWithGPSDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=BlackCatWithGPSDlg.h
ImplementationFile=BlackCatWithGPSDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BLACKCATWITHGPS_DIALOG]
Type=1
Class=CBlackCatWithGPSDlg
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FILENAME_EDIT,edit,1350633600
Control3=IDC_FILESELECT_BUTTON,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BAUD_COMBO,combobox,1344340227
Control6=IDC_STATIC,static,1342308352
Control7=IDC_COM_EDIT,edit,1350639746
Control8=IDC_COM_SPIN,msctls_updown32,1342177334
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ANDROID_IP_EDIT,edit,1350631552
Control11=IDC_START_BUTTON,button,1342242816
Control12=IDC_LOG_EDIT,edit,1353779268

