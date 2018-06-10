// LocalFile.h: CLocalFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALFILE_H__156D1B97_4C35_49DD_A5EB_FB8644597612__INCLUDED_)
#define AFX_LOCALFILE_H__156D1B97_4C35_49DD_A5EB_FB8644597612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLocalFile  
{
public:
	void SeekToBegin();
	BOOL WriteLine(CString str);
	DWORD SeekToEnd();
	BOOL WriteString(CString str);
	BOOL ReadLine(CString &str);
	BOOL Close();
	BOOL Open(CString name, UINT flags);
	CLocalFile();
	virtual ~CLocalFile();

protected:
	CStdioFile m_file;
	BOOL OpenStatus;
};

#endif // !defined(AFX_LOCALFILE_H__156D1B97_4C35_49DD_A5EB_FB8644597612__INCLUDED_)
