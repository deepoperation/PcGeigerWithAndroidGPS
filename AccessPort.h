// AccessPort.h: CAccessPort クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSPORT_H__B22A841C_7640_4626_8F25_DD32EB2D6B5F__INCLUDED_)
#define AFX_ACCESSPORT_H__B22A841C_7640_4626_8F25_DD32EB2D6B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAccessPort  
{
public:
	BOOL ClosePort();
	BOOL OpenPort(CString port, CString speed);
	INT  ReadNumber(void);
	CAccessPort();
	virtual ~CAccessPort();

protected:
	DWORD		m_Speed;
	CString		m_SpeedStr;
	CString		m_Port;
	BOOL		m_PortOpen;
	HANDLE		m_ComHandle;
};

#endif // !defined(AFX_ACCESSPORT_H__B22A841C_7640_4626_8F25_DD32EB2D6B5F__INCLUDED_)
