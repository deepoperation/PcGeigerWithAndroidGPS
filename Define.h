//一般的な定義はこのファイルに入れる
#if !defined(___DEFINE_H___)
#define ___DEFINE_H___

#define DISPLAY_LOG_LINE_MAX 100

// Iniファイル関係の設定
#define	INI_SECTION_BASE	"SectionBase"

#define	INI_ENTRY_IPADDRESS	"EntryIPAddress"
#define	INI_ENTRY_LOGFILE	"EntryLogFile"
#define	INI_ENTRY_PORT		"EntryPort"

#define	INI_FILE_NAME		"BlackCatWithGps.ini"

#define FILE_PATH_MAX		512

#define	GET_BUFFER_SIZE		1025
#define	TIMER_INTERVAL		60000

CString GetIniString(CString Section, CString Key, CString Default = "");
void GetCurrentTimeString(CString &str);
void GetCurrentDateAndTimeString(CString &str);
void DisplayWarning(void	*par);
CString	GetCurDir();

#endif	// ___DEFINE_H___