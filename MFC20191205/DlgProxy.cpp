
// DlgProxy.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFC20191205.h"
#include "DlgProxy.h"
#include "MFC20191205Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC20191205DlgAutoProxy

IMPLEMENT_DYNCREATE(CMFC20191205DlgAutoProxy, CCmdTarget)

CMFC20191205DlgAutoProxy::CMFC20191205DlgAutoProxy()
{
	EnableAutomation();

	// 若要保持應用程式執行的時間與自動化一樣長
	//	建構函式必須呼叫 AfxOleLockApp。
	AfxOleLockApp();

	// 經由應用程式主視窗指標，取得對對話方塊的存取。
	// 將 Proxy 的內部指標設定為指向對話方塊，
	// 並設定指向此 Proxy 的
	// 對話方塊返回指標。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMFC20191205Dlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFC20191205Dlg)))
		{
			m_pDialog = reinterpret_cast<CMFC20191205Dlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFC20191205DlgAutoProxy::~CMFC20191205DlgAutoProxy()
{
	// 若要在使用 Automation 建立了所有物件之後結束應用程式，
	//	 解構函式必須呼叫 AfxOleUnlockApp。
	// 此外，這會摧毀主對話方塊
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMFC20191205DlgAutoProxy::OnFinalRelease()
{
	// 當釋放 Automation 物件最後的參考時，
	// 會呼叫 OnFinalRelease。基底類別會自動
	// 刪除物件。呼叫基底類別前，請先加入您物件所需的額外清除 (Cleanup)
	// 程式碼。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFC20191205DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFC20191205DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 備註: 我們新增了對 IID_IMFC20191205 的支援以支援型別安全繫結
//  以便從 VBA 支援類型安全繫結。此 IID 必須與 .IDL 檔中，
// 附加至分配介面 (Dispinterface) 的 GUID 相符。

// {737f7a32-b182-4536-a806-b169b2d88698}
static const IID IID_IMFC20191205 =
{0x737f7a32,0xb182,0x4536,{0xa8,0x06,0xb1,0x69,0xb2,0xd8,0x86,0x98}};

BEGIN_INTERFACE_MAP(CMFC20191205DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFC20191205DlgAutoProxy, IID_IMFC20191205, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 的巨集會在此專案的 pch.h 中定義
// {3a3acb96-e12a-4537-8b82-937e4f86ad2b}
IMPLEMENT_OLECREATE2(CMFC20191205DlgAutoProxy, "MFC20191205.Application", 0x3a3acb96,0xe12a,0x4537,0x8b,0x82,0x93,0x7e,0x4f,0x86,0xad,0x2b)


// CMFC20191205DlgAutoProxy 訊息處理常式
