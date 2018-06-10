// BlackCatWithGPS.h : BLACKCATWITHGPS アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_)
#define AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSApp:
// このクラスの動作の定義に関しては BlackCatWithGPS.cpp ファイルを参照してください。
//

class CBlackCatWithGPSApp : public CWinApp
{
public:
	CBlackCatWithGPSApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBlackCatWithGPSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CBlackCatWithGPSApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_)
