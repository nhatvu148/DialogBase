
// BasicControlDlg.h : header file
//

#pragma once


// CBasicControlDlg dialog
class CBasicControlDlg : public CDialogEx
{
	// Construction
public:
	CBasicControlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICCONTROL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio4();
protected:
	CEdit edit_val_1_;
	CEdit edit_val_2_;
	CEdit edit_result_;
	CButton btn_cal_;
	int rad_plus_;
	int rad_minus_;
	int rad_multiply_;
	int rad_divide_;
public:
	afx_msg void OnBnClickedBtnCal();
};
