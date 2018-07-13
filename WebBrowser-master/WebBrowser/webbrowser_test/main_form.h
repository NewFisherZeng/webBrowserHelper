#ifndef MAIN_FORM_H_
#define MAIN_FORM_H_
#include "WebBrowser.h"
class JSCallClientTest;
class MainForm : public CWebBrowserBase
{
	HWND hWnd;
	JSCallClientTest *pClientCall;
public:
	MainForm(HWND hwnd);
	virtual HWND GetHWND(){ return hWnd; }

	static void _stdcall button1_onclick(LPVOID pParam);

	virtual void OnDocumentCompleted() override;

	virtual HRESULT STDMETHODCALLTYPE GetExternal(IDispatch **ppDispatch) override;
};

#endif