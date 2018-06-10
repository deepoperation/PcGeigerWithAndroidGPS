// BlackCatWithGPSDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BlackCatWithGPS.h"
#include "BlackCatWithGPSDlg.h"
#include "Define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

UINT GPSThread(LPVOID parent){
	((CBlackCatWithGPSDlg *)parent)->GPSLoop();
	return 0;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
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
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSDlg �_�C�A���O

CBlackCatWithGPSDlg::CBlackCatWithGPSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlackCatWithGPSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlackCatWithGPSDlg)
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlackCatWithGPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlackCatWithGPSDlg)
	DDX_Control(pDX, IDC_START_BUTTON, m_StartButton);
	DDX_Control(pDX, IDC_FILESELECT_BUTTON, m_FileSelectButton);
	DDX_Control(pDX, IDC_COM_EDIT, m_ComEdit);
	DDX_Control(pDX, IDC_FILENAME_EDIT, m_FileNameEdit);
	DDX_Control(pDX, IDC_LOG_EDIT, m_LogEdit);
	DDX_Control(pDX, IDC_ANDROID_IP_EDIT, m_AndroidIPEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlackCatWithGPSDlg, CDialog)
	//{{AFX_MSG_MAP(CBlackCatWithGPSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILESELECT_BUTTON, OnFileselectButton)
	ON_BN_CLICKED(IDC_START_BUTTON, OnStartButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSDlg ���b�Z�[�W �n���h��

BOOL CBlackCatWithGPSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	CString addSpeedCombo[]	= {	"110", "300", "600", "1200", "2400", "4800", "9600",
							"14400", "19200", "38400", "57600", "115200", "128000"};
	// �X�s�[�h�ꗗ�̃R���{�{�b�N�X�ɒǉ�
	CComboBox* fileList=(CComboBox*)GetDlgItem(IDC_BAUD_COMBO);
	for(int i = 0; i < sizeof(addSpeedCombo)/sizeof(addSpeedCombo[0]) ; i++)
	{
		fileList->InsertString(-1,addSpeedCombo[i]);
	}
	fileList->SetCurSel(atoi(GetIniString(INI_SECTION_BASE, INI_ENTRY_BAUD, "11")));
	m_DisplayLogLine = 0;
	m_FileName = GetIniString(INI_SECTION_BASE, INI_ENTRY_LOGFILE, "C:\\GM10log.txt");
	m_FileNameEdit.SetWindowText(m_FileName);
	m_AndroidIPEdit.SetWindowText(GetIniString(INI_SECTION_BASE, INI_ENTRY_IPADDRESS, "192.168.1.1"));
	m_ComEdit.SetWindowText(GetIniString(INI_SECTION_BASE, INI_ENTRY_PORT, "1"));
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CBlackCatWithGPSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CBlackCatWithGPSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CBlackCatWithGPSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBlackCatWithGPSDlg::OnFileselectButton() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
		// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CFileDialog		*file;
	INT				selectRet;
	
	file = new CFileDialog(	TRUE,				// �t�@�C�����J��
							"log",				// �f�t�H���g�̊g���q
							"*.log",			// �f�t�H���g�̃t�@�C����
							OFN_CREATEPROMPT,	// �t�@�C�����Ȃ��ꍇ�m�F����
							"Log(*.log)|*.log|�S��(*.*)|*.*||" // �t�@�C���̃t�B���^
							);
	selectRet = file->DoModal();
	if(selectRet == IDOK)
	{
		m_FileName = file->GetPathName(); // �I���t�@�C�����擾
	}
	delete file;
	if(selectRet == IDCANCEL)
	{
		return;
	}
	// �I�[�v������
	m_FileNameEdit.SetWindowText(m_FileName);
}

void CBlackCatWithGPSDlg::OnStartButton() 
{
	CString tempStr;
	// COM�|�[�g�̃I�[�v������
	if(OpenComPort() == FALSE)
	{
		AfxGetMainWnd()->DestroyWindow();
		return;
	}
	if(OpenSocket() == FALSE)
	{
		AfxGetMainWnd()->DestroyWindow();
		return;
	}
	if(FileOpen() == FALSE)
	{
		AfxGetMainWnd()->DestroyWindow();
		return;
	}
	m_ComEdit.GetWindowText(tempStr);
	WritePrivateProfileString(INI_SECTION_BASE, INI_ENTRY_PORT, tempStr, GetCurDir()); 
	m_AndroidIPEdit.GetWindowText(tempStr);
	WritePrivateProfileString(INI_SECTION_BASE, INI_ENTRY_IPADDRESS, tempStr, GetCurDir());
	m_FileNameEdit.GetWindowText(tempStr);
	WritePrivateProfileString(INI_SECTION_BASE, INI_ENTRY_LOGFILE, tempStr, GetCurDir());
	CComboBox* fileList=(CComboBox*)GetDlgItem(IDC_BAUD_COMBO);
	int tempInt = fileList->GetCurSel();
	tempStr.Format("%d", tempInt);
	WritePrivateProfileString(INI_SECTION_BASE, INI_ENTRY_BAUD, tempStr, GetCurDir());
	AfxBeginThread(GPSThread, this);
	SetTimer(100, TIMER_INTERVAL, NULL);
	m_StartButton.EnableWindow(FALSE);
	m_FileSelectButton.EnableWindow(FALSE);
}

void CBlackCatWithGPSDlg::GPSLoop()
{
	char buf[256];
	CString logStr;
	CSingleLock	GPSSection(&m_GPSSection);
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		int n = recv(m_Sock, buf, sizeof(buf), 0);
		GPSSection.Lock();
		m_Location.Format("%s",buf);
		GPSSection.Unlock();
	}
}

void CBlackCatWithGPSDlg::OnOK()
{
		;
}

BOOL CBlackCatWithGPSDlg::OpenSocket()
{
	CString errStr;
	CString ipAddress;
	int err = WSAStartup(MAKEWORD(2,0), &m_wsaData);
	if (err != 0) {
		switch (err) {
			case WSASYSNOTREADY:
				errStr = "WSASYSNOTREADY";
				break;
			case WSAVERNOTSUPPORTED:
				errStr = "WSAVERNOTSUPPORTED";
				break;
			case WSAEINPROGRESS:
				errStr = "WSAEINPROGRESS";
				break;
			case WSAEPROCLIM:
				errStr = "WSAEPROCLIM";
				break;
			case WSAEFAULT:
				errStr = "WSAEFAULT";
				break;
		}
		AfxMessageBox("�\�P�b�g�쐬�G���[" + errStr, MB_OK);
		WSACleanup();
		return FALSE;
	}
	
	m_AndroidIPEdit.GetWindowText(ipAddress);
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	m_Server.sin_family = AF_INET;
	m_Server.sin_port = htons(52001);
	m_Server.sin_addr.S_un.S_addr = inet_addr(ipAddress);
	if(0 != connect(m_Sock, (struct sockaddr *)&m_Server, sizeof(m_Server)))
	{
		AfxMessageBox("�\�P�b�g�ڑ��G���[" + errStr, MB_OK);
		return FALSE;
	}
	return TRUE;
}


BOOL CBlackCatWithGPSDlg::OpenComPort()
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	INT		portNum;		// �|�[�g�ԍ�
	CHAR	*pTex;			// �ꎞ�e�L�X�g
	CString port;			// �|�[�g�̕����� 
	CString speed;			// �X�s�[�h�̕�����
	
	m_ComEdit.GetWindowText(port);
	if(port.GetLength() == 0)
	{
		// �ݒ�l�s��
		AfxMessageBox("�|�[�g������", MB_OK);
		return FALSE;
	}
	CComboBox* fileList=(CComboBox*)GetDlgItem(IDC_BAUD_COMBO);
	fileList->GetWindowText(speed);

	portNum		= atoi(port);
	pTex		= (CHAR *)malloc(port.GetLength() + 1);
	if(pTex == NULL)
	{
		// �ݒ�l�s��
		AfxMessageBox("���������������܂�", MB_OK);
		return FALSE;
	}
	
	_itoa(portNum, pTex, 10);
	
	if(port == "" || speed == "" || port != pTex)
	{
		// �ݒ�l�s��
		AfxMessageBox("�ݒ�l�s��", MB_OK);
		free(pTex);
		return FALSE;
	}
	free(pTex);

	port = "COM" + port;
	
	if(FALSE == m_AccessPort.OpenPort(port, speed))
	{
		AfxMessageBox("�|�[�g�I�[�v�����s", MB_OK);
		return FALSE;
	}
	return(TRUE);
}

// �f�B�X�v���C�Ƀ��O��\�����邽�߂̊֐�
// ��s�ÂĂяo���Ďg������
void CBlackCatWithGPSDlg::DisplayLog(CString str)
{
	INT			location;
	INT			deleteRet;
	CString		timeStr;
	CString		crlf = "\x0d\x0a";

	str.Replace('\r', ' ');
	str.Remove('\n');
	GetCurrentDateAndTimeString(timeStr);
	m_DisplayLog += timeStr + "," + str + crlf;
	m_DisplayLogLine += 1;
	
	if(m_DisplayLogLine >= DISPLAY_LOG_LINE_MAX)
	{
		// ���E�𒴂����̂łP�s���폜
		location = m_DisplayLog.Find("\n");
		if(location < 0)
		{
			// 
			AfxMessageBox("���O�o�͂ɕs����������܂���", MB_OK);
			return;
		}
		else
		{
			// �ŏ��̈�s���폜����̂ŃI�t�Z�b�g�͏��0�ɂȂ�B
			// location��0����͂��܂�̂Ō����n�_�܂ō폜����ɂ�
			// location + 1���K�v
			deleteRet = m_DisplayLog.Delete(0, location + 1);
			m_DisplayLogLine -= 1;
		}
	}
	// �V�����e�L�X�g��ݒ肷��
	m_LogEdit.SetWindowText(m_DisplayLog);
	// 
	m_LogEdit.LineScroll(DISPLAY_LOG_LINE_MAX, 0);
	// ���O�t�@�C���ɂ�������e��������
	m_LogFile.WriteString(timeStr + "," + str + "\n");
}

BOOL CBlackCatWithGPSDlg::FileOpen(void)
{
	CFileStatus		status;
	BOOL			openRet;
	INT				userRet;
	if(FALSE == CFile::GetStatus(m_FileName, status))
	{
		// �����t�@�C���Ȃ�
		openRet = m_LogFile.Open(m_FileName, CFile::modeCreate | CFile::modeReadWrite);	// �I�[�v������
	}
	else
	{
		// �����t�@�C������
		userRet = AfxMessageBox("�t�@�C�������݂��܂�\n�㏑�����܂����H\n��������I������ƒǋL���[�h�ɂȂ�܂�", MB_YESNO);
		
		if(userRet == IDYES)
		{
			// �㏑�����[�h�ŃI�[�v������
			openRet = m_LogFile.Open(m_FileName, CFile::modeCreate | CFile::modeReadWrite);
		}
		else
		{
			// �㏑�������ɃI�[�v������
			openRet = m_LogFile.Open(m_FileName, CFile::modeNoTruncate | CFile::modeReadWrite);	// �I�[�v������
		}
	}

	if(openRet == 0)
	{
		// �I�[�v�����s
		m_FileName = "";
		m_FileNameEdit.SetWindowText("");
		// �I�[�v�����s
		AfxMessageBox("�t�@�C���I�[�v���Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	else
	{
		CString	str;
		m_LogFile.SeekToEnd();		// �I�[�Ɉړ����Ă���
		return TRUE;
	}
}

void CBlackCatWithGPSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	SetTimer(100, TIMER_INTERVAL, NULL);
	INT num = m_AccessPort.ReadNumber();
	CString tempStr;
	tempStr.Format("%d", num);
	CSingleLock	GPSSection(&m_GPSSection);
	GPSSection.Lock();
	DisplayLog(tempStr + "," + m_Location);
	GPSSection.Unlock();	
}
