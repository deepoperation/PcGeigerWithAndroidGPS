// BlackCatWithGPSDlg.h : ヘッダー ファイル
//

#if !defined(AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_)
#define AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_

#include <afxmt.h>
#include "AccessPort.h"	// ClassView によって追加されました。
#include "LocalFile.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSDlg ダイアログ

class CBlackCatWithGPSDlg : public CDialog
{
// 構築
public:
	CBlackCatWithGPSDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	void GPSLoop();
// ダイアログ データ
	//{{AFX_DATA(CBlackCatWithGPSDlg)
	enum { IDD = IDD_BLACKCATWITHGPS_DIALOG };
	CButton	m_StartButton;
	CButton	m_FileSelectButton;
	CEdit	m_ComEdit;
	CEdit	m_FileNameEdit;
	CEdit	m_LogEdit;
	CEdit	m_AndroidIPEdit;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBlackCatWithGPSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
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
	CCriticalSection	m_GPSSection;	// GPSデータセクション
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BLACKCATWITHGPSDLG_H__D6A8CC89_C0E1_497E_B834_C3B6D01EE1B1__INCLUDED_)
