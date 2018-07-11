// WebDialog.cpp : implementation file
//

#include "WebDialog.h"


// CWebDialog dialog

IMPLEMENT_DYNAMIC(CWebDialog, CDialog)

CWebDialog::CWebDialog(const char* const pszUrl, const char* const pszWndName, CWnd* pParent /*=NULL*/)
	: CDialog(CWebDialog::IDD, pParent)
{
    m_pszUrl = pszUrl;
    m_pszWndName = pszWndName;
}

CWebDialog::~CWebDialog()
{
}

void CWebDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EXPLORER_WEB, m_WebBrowser);
}


BEGIN_MESSAGE_MAP(CWebDialog, CDialog)
    ON_WM_SIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

BOOL CWebDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetWindowText(m_pszWndName);
    SetWindowPos(NULL, 0, 0, m_nWidth, m_nHeight, SWP_NOZORDER);
    CenterWindow();
    m_WebBrowser.Navigate(m_pszUrl, NULL, NULL, NULL,  NULL);
    return TRUE;
}

void CWebDialog::SetSize(int nWidth, int nHeight)
{
    m_nHeight = nHeight;
    m_nWidth = nWidth;
}


// CWebDialog message handlers

void CWebDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    CWnd* pCtl = GetDlgItem(IDC_EXPLORER_WEB);
    if(nType != SIZE_MINIMIZED && NULL != pCtl) //判断是否为最小化
    {
        CRect rcWnd;
        GetClientRect(&rcWnd);
//         CRect rcBrowser;
//         rcBrowser.top = rcWnd.top + 5;
//         rcBrowser.bottom = rcWnd.bottom -5;
//         rcBrowser.left = rcWnd.left + 5;
//         rcBrowser.right = rcWnd.right - 5;

        m_WebBrowser.MoveWindow(rcWnd);//设置控件位置
    }
}

void CWebDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest != HTCAPTION)
	{
		CDialog::OnNcLButtonDown(nHitTest, point);
	}
}

void CWebDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if (nHitTest != HTCAPTION)
	{
		CDialog::OnNcMouseMove(nHitTest, point);
	}
}
