// BlackCatWithGPSDlg.cpp : インプリメンテーション ファイル
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
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

UINT GPSThread(LPVOID parent){
	((CBlackCatWithGPSDlg *)parent)->GPSLoop();
	return 0;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
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
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSDlg ダイアログ

CBlackCatWithGPSDlg::CBlackCatWithGPSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlackCatWithGPSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlackCatWithGPSDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
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
// CBlackCatWithGPSDlg メッセージ ハンドラ

BOOL CBlackCatWithGPSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
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

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	CString addSpeedCombo[]	= {	"110", "300", "600", "1200", "2400", "4800", "9600",
							"14400", "19200", "38400", "57600", "115200", "128000"};
	// スピード一覧のコンボボックスに追加
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
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
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

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CBlackCatWithGPSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CBlackCatWithGPSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBlackCatWithGPSDlg::OnFileselectButton() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
		// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog		*file;
	INT				selectRet;
	
	file = new CFileDialog(	TRUE,				// ファイルを開く
							"log",				// デフォルトの拡張子
							"*.log",			// デフォルトのファイル名
							OFN_CREATEPROMPT,	// ファイルがない場合確認する
							"Log(*.log)|*.log|全て(*.*)|*.*||" // ファイルのフィルタ
							);
	selectRet = file->DoModal();
	if(selectRet == IDOK)
	{
		m_FileName = file->GetPathName(); // 選択ファイル名取得
	}
	delete file;
	if(selectRet == IDCANCEL)
	{
		return;
	}
	// オープン成功
	m_FileNameEdit.SetWindowText(m_FileName);
}

void CBlackCatWithGPSDlg::OnStartButton() 
{
	CString tempStr;
	// COMポートのオープン処理
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
		AfxMessageBox("ソケット作成エラー" + errStr, MB_OK);
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
		AfxMessageBox("ソケット接続エラー" + errStr, MB_OK);
		return FALSE;
	}
	return TRUE;
}


BOOL CBlackCatWithGPSDlg::OpenComPort()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	INT		portNum;		// ポート番号
	CHAR	*pTex;			// 一時テキスト
	CString port;			// ポートの文字列 
	CString speed;			// スピードの文字列
	
	m_ComEdit.GetWindowText(port);
	if(port.GetLength() == 0)
	{
		// 設定値不正
		AfxMessageBox("ポート未入力", MB_OK);
		return FALSE;
	}
	CComboBox* fileList=(CComboBox*)GetDlgItem(IDC_BAUD_COMBO);
	fileList->GetWindowText(speed);

	portNum		= atoi(port);
	pTex		= (CHAR *)malloc(port.GetLength() + 1);
	if(pTex == NULL)
	{
		// 設定値不正
		AfxMessageBox("文字数が多すぎます", MB_OK);
		return FALSE;
	}
	
	_itoa(portNum, pTex, 10);
	
	if(port == "" || speed == "" || port != pTex)
	{
		// 設定値不正
		AfxMessageBox("設定値不正", MB_OK);
		free(pTex);
		return FALSE;
	}
	free(pTex);

	port = "COM" + port;
	
	if(FALSE == m_AccessPort.OpenPort(port, speed))
	{
		AfxMessageBox("ポートオープン失敗", MB_OK);
		return FALSE;
	}
	return(TRUE);
}

// ディスプレイにログを表示するための関数
// 一行づつ呼び出して使うこと
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
		// 限界を超えたので１行分削除
		location = m_DisplayLog.Find("\n");
		if(location < 0)
		{
			// 
			AfxMessageBox("ログ出力に不具合が発生しました", MB_OK);
			return;
		}
		else
		{
			// 最初の一行を削除するのでオフセットは常に0になる。
			// locationは0からはじまるので検索地点まで削除するには
			// location + 1が必要
			deleteRet = m_DisplayLog.Delete(0, location + 1);
			m_DisplayLogLine -= 1;
		}
	}
	// 新しいテキストを設定する
	m_LogEdit.SetWindowText(m_DisplayLog);
	// 
	m_LogEdit.LineScroll(DISPLAY_LOG_LINE_MAX, 0);
	// ログファイルにも同一内容書き込み
	m_LogFile.WriteString(timeStr + "," + str + "\n");
}

BOOL CBlackCatWithGPSDlg::FileOpen(void)
{
	CFileStatus		status;
	BOOL			openRet;
	INT				userRet;
	if(FALSE == CFile::GetStatus(m_FileName, status))
	{
		// 同名ファイルなし
		openRet = m_LogFile.Open(m_FileName, CFile::modeCreate | CFile::modeReadWrite);	// オープンする
	}
	else
	{
		// 同名ファイルあり
		userRet = AfxMessageBox("ファイルが存在します\n上書きしますか？\nいいえを選択すると追記モードになります", MB_YESNO);
		
		if(userRet == IDYES)
		{
			// 上書きモードでオープンする
			openRet = m_LogFile.Open(m_FileName, CFile::modeCreate | CFile::modeReadWrite);
		}
		else
		{
			// 上書きせずにオープンする
			openRet = m_LogFile.Open(m_FileName, CFile::modeNoTruncate | CFile::modeReadWrite);	// オープンする
		}
	}

	if(openRet == 0)
	{
		// オープン失敗
		m_FileName = "";
		m_FileNameEdit.SetWindowText("");
		// オープン失敗
		AfxMessageBox("ファイルオープンに失敗しました", MB_OK);
		return FALSE;
	}
	else
	{
		CString	str;
		m_LogFile.SeekToEnd();		// 終端に移動しておく
		return TRUE;
	}
}

void CBlackCatWithGPSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	SetTimer(100, TIMER_INTERVAL, NULL);
	INT num = m_AccessPort.ReadNumber();
	CString tempStr;
	tempStr.Format("%d", num);
	CSingleLock	GPSSection(&m_GPSSection);
	GPSSection.Lock();
	DisplayLog(tempStr + "," + m_Location);
	GPSSection.Unlock();	
}
