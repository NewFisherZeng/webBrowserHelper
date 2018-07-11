#pragma once
#include "cwebbrowser2.h"

#define IDD_DIALOG_WEB                  132
#define IDC_EXPLORER_WEB                1017

// CWebDialog dialog

class CWebDialog : public CDialog
{
	DECLARE_DYNAMIC(CWebDialog)

public:
	CWebDialog(const char* const pszUrl = NULL
        , const char* const pszWndName = NULL
        , CWnd* pParent = NULL);   // standard constructor

	virtual ~CWebDialog();

    virtual BOOL OnInitDialog();
    void SetSize(int nWidth, int nHeight);

// Dialog Data
	enum { IDD = IDD_DIALOG_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
    CWebBrowser2 m_WebBrowser;
    const char* m_pszUrl;
    const char* m_pszWndName;
    int m_nWidth;
    int m_nHeight;
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
