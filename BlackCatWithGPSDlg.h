// BlackCatWithGPSDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_)
#define AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_

#include <afxmt.h>
#include "AccessPort.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "LocalFile.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSDlg �_�C�A���O

class CBlackCatWithGPSDlg : public CDialog
{
// �\�z
public:
	CBlackCatWithGPSDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
	void GPSLoop();
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBlackCatWithGPSDlg)
	enum { IDD = IDD_BLACKCATWITHGPS_DIALOG };
	CButton	m_StartButton;
	CButton	m_FileSelectButton;
	CEdit	m_ComEdit;
	CEdit	m_FileNameEdit;
	CEdit	m_LogEdit;
	CEdit	m_AndroidIPEdit;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlackCatWithGPSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CBlackCatWithGPSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileselectButton();
	afx_msg void OnStartButton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL				OpenSocket();
	void				DisplayLog(CString str);
	BOOL				FileOpen(void);
	struct sockaddr_in	m_Server;
	SOCKET				m_Sock;
	WSADATA				m_wsaData;
	virtual void		OnOK();
	BOOL				OpenComPort();
	CAccessPort			m_AccessPort;
	CString				m_DisplayLog;
	UINT				m_DisplayLogLine;
	CLocalFile			m_LogFile;
	CString				m_FileName;
	CString				m_Location;
	CCriticalSection	m_GPSSection;	// GPS�f�[�^�Z�N�V����
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_)
