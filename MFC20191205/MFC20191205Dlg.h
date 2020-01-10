
// MFC20191205Dlg.h: 標頭檔
//

#pragma once

class CMFC20191205DlgAutoProxy;


// CMFC20191205Dlg 對話方塊
class CMFC20191205Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFC20191205Dlg);
	friend class CMFC20191205DlgAutoProxy;

// 建構
public:
	CMFC20191205Dlg(CWnd* pParent = nullptr);	// 標準建構函式
	virtual ~CMFC20191205Dlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC20191205_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	CMFC20191205DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	//CEdit m_edit;
	//CEdit m_edit;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnSelchangeCombo2();

	afx_msg void OnEnChangeEdit1();
	CEdit m_editCtrl;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> m_editctrl_v;
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnUpdateEdit6();


	afx_msg void OnEnChangeEdit5();
	CEdit Y_EDIT;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> Y_Show;
	afx_msg void OnEnChangeEdit2();
	CEdit Z_edit;
	afx_msg void OnEnChangeEdit3();
	CStringT<wchar_t, StrTraitMFC<wchar_t>> Z_Show;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton5();
	CEdit plate_Z_edit;
	afx_msg void OnEnChangeEdit7();
	CStringT<wchar_t, StrTraitMFC<wchar_t>> plat_Z_show;
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CButton Lights_switch;
	afx_msg void OnBnClickedCheck1();
	CEdit Moving_TImes;
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedCheck2();
	CButton Stream_ONnOff;
	CStatic picpicpic;
	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedButton13();
	CString z_step;
	afx_msg void OnEnChangeEdit10();

	int exposure_time;
	afx_msg void OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit11();
	CString Exposure_time;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
