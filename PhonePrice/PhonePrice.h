// PhonePrice.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPhonePriceApp:
// �йش����ʵ�֣������ PhonePrice.cpp
//

class CPhonePriceApp : public CWinApp
{
public:
	CPhonePriceApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPhonePriceApp theApp;