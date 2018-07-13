#include "main_form.h"
#include "js_call_client_test.h"
#include "call_js_test.h"
MainForm::MainForm(HWND hwnd)
{
	hWnd = hwnd;
	pClientCall = new JSCallClientTest();
}

void _stdcall MainForm::button1_onclick(LPVOID pParam)
{
	MainForm *pMainForm = (MainForm*)pParam;
	MessageBox(pMainForm->hWnd, L"您点击了button1", L"提示(C++)", 0);
}

void MainForm::OnDocumentCompleted()
{
	VARIANT params[10];

	//获取window
	IDispatch *pHtmlWindow = GetHtmlWindow();

	//获取document
	CVariant document;
	params[0].vt = VT_BSTR;
	params[0].bstrVal = L"document";
	GetProperty(pHtmlWindow, L"document", &document);

	//获取button1
	CVariant button1;
	params[0].vt = VT_BSTR;
	params[0].bstrVal = L"button1";
	InvokeMethod(document.pdispVal, L"getElementById", &button1, params, 1);

	//处理button1的onclick事件
	params[0].vt = VT_DISPATCH;
	params[0].pdispVal = new CallJsTest(button1_onclick, this);
	SetProperty(button1.pdispVal, L"onclick", params);
}

HRESULT STDMETHODCALLTYPE MainForm::GetExternal(IDispatch **ppDispatch)
{
	//重写GetExternal返回一个ClientCall对象
	*ppDispatch = pClientCall;
	return S_OK;
}
