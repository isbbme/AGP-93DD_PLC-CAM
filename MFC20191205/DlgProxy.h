
// DlgProxy.h: 標頭檔
//

#pragma once

class CMFC20191205Dlg;


// CMFC20191205DlgAutoProxy 命令目標

class CMFC20191205DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFC20191205DlgAutoProxy)

	CMFC20191205DlgAutoProxy();           // 動態建立所使用的保護建構函式

// 屬性
public:
	CMFC20191205Dlg* m_pDialog;

// 作業
public:

// 覆寫
	public:
	virtual void OnFinalRelease();

// 程式碼實作
protected:
	virtual ~CMFC20191205DlgAutoProxy();

	// 產生的訊息對應函式

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFC20191205DlgAutoProxy)

	// 產生的 OLE 分派對應函式

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

