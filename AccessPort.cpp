// AccessPort.cpp: CAccessPort クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AccessPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAccessPort::CAccessPort()
{
	// ポートオープン状態を初期化
	m_PortOpen = FALSE;
}

CAccessPort::~CAccessPort()
{

}

BOOL CAccessPort::OpenPort(CString port, CString speed)
{
	
	BOOL	result = FALSE;
	DCB		dcb;
	
	if(m_PortOpen == TRUE)
	{
		ClosePort();
	}

	// ポートをオープンしハンドルを取得する
	m_ComHandle = CreateFile(
        "\\\\.\\" + port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
		OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
	
	if(m_ComHandle == INVALID_HANDLE_VALUE)
	{
		return(result);
	}

	// 設定パラメータの保存
	m_Port		= port;
	m_Speed		= atoi(speed);
	m_SpeedStr	= speed;
	
	GetCommState( m_ComHandle, &dcb );

	// BaudRate以外は現状固定値とする
	dcb.BaudRate	= m_Speed;
	dcb.ByteSize	= 8;
	dcb.Parity		= NOPARITY;
	dcb.StopBits	= ONESTOPBIT;

	// パラメータ設定
	if(0 != SetCommState( m_ComHandle, &dcb ))
	{
		// ポートオープン状態設定
		m_PortOpen	= TRUE;
		result		= TRUE;
	}
	else
	{
		DWORD	a;
		a = GetLastError();
		ClosePort();
	}
	
	return(result);

}

BOOL CAccessPort::ClosePort()
{
	// ハンドルのクローズ
	if(CloseHandle( m_ComHandle ) == 0)
	{
		// クローズ失敗
		return(FALSE);
	}
	else
	{
		// ポートクローズ状態設定
		m_PortOpen	= FALSE;
		// クローズ成功
		return(TRUE);		
	}
}

INT CAccessPort::ReadNumber(void)
{
	if(m_PortOpen == FALSE)
	{
		return(FALSE);
	}
	
	// 受信用変数
    DWORD	dwErrors;
    COMSTAT	ComStat;
    DWORD	dwCount;
    DWORD	dwRead = 0;
	UINT	flg = FALSE;
	CHAR	*pResp;
	
	if(0 == ClearCommError(m_ComHandle, &dwErrors, &ComStat))
	{
		// 事前情報取得失敗したためスリープ後に再実行
		return 0;
	}
	dwCount=ComStat.cbInQue;		// 情報サイズを取得
	
	if(dwCount == 0)
	{
		return 0;
	}
	pResp = (CHAR *)malloc(dwCount + 1);	// 1は末尾のヌル文字用
	if(0 == ReadFile(m_ComHandle, pResp, dwCount, &dwRead, NULL))
	{
		// 読み取り失敗したためスリープ後に再実行
		free(pResp);
		return 0;
	}
	else
	{
	// 成功したため抜ける
		free(pResp);
		return(dwCount);
	}
}