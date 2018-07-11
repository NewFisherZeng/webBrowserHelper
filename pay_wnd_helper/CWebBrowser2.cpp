// CWebBrowser2.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#include "CWebBrowser2.h"

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2

IMPLEMENT_DYNCREATE(CWebBrowser2, CWnd)

// CWebBrowser2 properties

// CWebBrowser2 operations

BOOL CWebBrowser2::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
	if (WM_RBUTTONDOWN == pMsg->message)
	{
		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}