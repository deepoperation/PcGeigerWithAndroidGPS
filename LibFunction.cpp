#include "stdafx.h"
#include <direct.h>
#include "Define.h"

CString GetIniString(CString Section, CString Key, CString Default)
{
	DWORD	Len;
	CString	Str;
	CString Dir;
	CHAR	Buf[GET_BUFFER_SIZE];
	
	Dir = GetCurDir() + "\\" + INI_FILE_NAME;
	Len = GetPrivateProfileString(Section, Key, Default, Buf, sizeof(Buf), GetCurDir());
	if(Len > 0)
	{
		Str = Buf;
	}
	return Str;
}

void GetCurrentTimeString(CString &str)
{
	CHAR	timestring[255];

	SYSTEMTIME	stime;
	
	GetLocalTime(&stime);
	sprintf(timestring,"%02d:%02d:%02d:%03d\0", stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
	str += timestring;
}

void GetCurrentDateAndTimeString(CString &str)
{
	CHAR	timestring[255];

	SYSTEMTIME	stime;
	
	GetLocalTime(&stime);
	sprintf(timestring,"%04d/%02d/%02d,%02d:%02d:%02d:%d\0", stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
	str += timestring;
}

// スレッドを立ててワーニングを表示するための関数
void DisplayWarning(void	*par)
{
	CString	*str = (CString *)par;
	
	AfxMessageBox(*str, MB_OK);
	delete	par;
}

CString	GetCurDir()
{
	CString Path = "";
	CHAR	Buf[FILE_PATH_MAX];

	Path += _getdcwd(_getdrive(), Buf, sizeof(Buf));
	Path += "\\";
	Path += INI_FILE_NAME;
	return Path;
}
