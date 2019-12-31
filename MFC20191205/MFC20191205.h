
// MFC20191205.h: PROJECT_NAME 應用程式的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 在包含此檔案前先包含 'pch.h'"
#endif

#include "resource.h"		// 主要符號


// CMFC20191205App:
// 查看 MFC20191205.cpp 以了解此類別的實作
//

class CMFC20191205App : public CWinApp
{
public:
	CMFC20191205App();

// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 程式碼實作

	DECLARE_MESSAGE_MAP()
};

extern CMFC20191205App theApp;
