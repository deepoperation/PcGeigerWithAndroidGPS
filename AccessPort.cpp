// AccessPort.cpp: CAccessPort �N���X�̃C���v�������e�[�V����
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
// �\�z/����
//////////////////////////////////////////////////////////////////////

CAccessPort::CAccessPort()
{
	// �|�[�g�I�[�v����Ԃ�������
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

	// �|�[�g���I�[�v�����n���h�����擾����
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

	// �ݒ�p�����[�^�̕ۑ�
	m_Port		= port;
	m_Speed		= atoi(speed);
	m_SpeedStr	= speed;
	
	GetCommState( m_ComHandle, &dcb );

	// BaudRate�ȊO�͌���Œ�l�Ƃ���
	dcb.BaudRate	= m_Speed;
	dcb.ByteSize	= 8;
	dcb.Parity		= NOPARITY;
	dcb.StopBits	= ONESTOPBIT;

	// �p�����[�^�ݒ�
	if(0 != SetCommState( m_ComHandle, &dcb ))
	{
		// �|�[�g�I�[�v����Ԑݒ�
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
	// �n���h���̃N���[�Y
	if(CloseHandle( m_ComHandle ) == 0)
	{
		// �N���[�Y���s
		return(FALSE);
	}
	else
	{
		// �|�[�g�N���[�Y��Ԑݒ�
		m_PortOpen	= FALSE;
		// �N���[�Y����
		return(TRUE);		
	}
}

INT CAccessPort::ReadNumber(void)
{
	if(m_PortOpen == FALSE)
	{
		return(FALSE);
	}
	
	// ��M�p�ϐ�
    DWORD	dwErrors;
    COMSTAT	ComStat;
    DWORD	dwCount;
    DWORD	dwRead = 0;
	UINT	flg = FALSE;
	CHAR	*pResp;
	
	if(0 == ClearCommError(m_ComHandle, &dwErrors, &ComStat))
	{
		// ���O���擾���s�������߃X���[�v��ɍĎ��s
		return 0;
	}
	dwCount=ComStat.cbInQue;		// ���T�C�Y���擾
	
	if(dwCount == 0)
	{
		return 0;
	}
	pResp = (CHAR *)malloc(dwCount + 1);	// 1�͖����̃k�������p
	if(0 == ReadFile(m_ComHandle, pResp, dwCount, &dwRead, NULL))
	{
		// �ǂݎ�莸�s�������߃X���[�v��ɍĎ��s
		free(pResp);
		return 0;
	}
	else
	{
	// �����������ߔ�����
		free(pResp);
		return(dwCount);
	}
}