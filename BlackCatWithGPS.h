// BlackCatWithGPS.h : BLACKCATWITHGPS �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_)
#define AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CBlackCatWithGPSApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� BlackCatWithGPS.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CBlackCatWithGPSApp : public CWinApp
{
public:
	CBlackCatWithGPSApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlackCatWithGPSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CBlackCatWithGPSApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLACKCATWITHGPS_H__F077BC70_0C29_4C91_9E1F_75527C3D7632__INCLUDED_)
