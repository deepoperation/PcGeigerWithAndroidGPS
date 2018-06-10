// LocalFile.cpp: CLocalFile �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CLocalFile::CLocalFile()
{
	OpenStatus	= FALSE;
}

CLocalFile::~CLocalFile()
{

}

BOOL CLocalFile::Open(CString name, UINT flags)
{
	
	if(OpenStatus == TRUE)
	{
		Close();
	}

	if(0 == m_file.Open(name, flags, NULL))
	{
		OpenStatus	= FALSE;
	}
	else
	{
		OpenStatus	= TRUE;
	}
	return(OpenStatus);
}

BOOL CLocalFile::Close()
{
	if(OpenStatus == FALSE)
	{
		// ���ɃN���[�Y���
		return(TRUE);
	}

	m_file.Close();
	OpenStatus	= FALSE;	// �N���[�Y���s�ł��N���[�Y�������̂Ƃ���

	return(TRUE);
}

BOOL CLocalFile::ReadLine(CString &str)
{
	if(OpenStatus == FALSE)
	{
		// �t�@�C�����I�[�v������Ă��Ȃ�
		return(FALSE);
	}
	return(m_file.ReadString(str));
}

BOOL CLocalFile::WriteString(CString str)
{
	if(OpenStatus == FALSE)
	{
		// �t�@�C�����I�[�v������Ă��Ȃ�
		return(FALSE);
	}	

	m_file.WriteString(str);

	return(TRUE);
}

DWORD CLocalFile::SeekToEnd()
{
	return(m_file.SeekToEnd());
}

BOOL CLocalFile::WriteLine(CString str)
{
	str += "\n";
	return(WriteString(str));
}


void CLocalFile::SeekToBegin()
{
	m_file.SeekToBegin();
	return;
}
