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
	MessageBox(pMainForm->hWnd, L"�������button1", L"��ʾ(C++)", 0);
}

void MainForm::OnDocumentCompleted()
{
	VARIANT params[10];

	//��ȡwindow
	IDispatch *pHtmlWindow = GetHtmlWindow();

	//��ȡdocument
	CVariant document;
	params[0].vt = VT_BSTR;
	params[0].bstrVal = L"document";
	GetProperty(pHtmlWindow, L"document", &document);

	//��ȡbutton1
	CVariant button1;
	params[0].vt = VT_BSTR;
	params[0].bstrVal = L"button1";
	InvokeMethod(document.pdispVal, L"getElementById", &button1, params, 1);

	//����button1��onclick�¼�
	params[0].vt = VT_DISPATCH;
	params[0].pdispVal = new CallJsTest(button1_onclick, this);
	SetProperty(button1.pdispVal, L"onclick", params);
}

HRESULT STDMETHODCALLTYPE MainForm::GetExternal(IDispatch **ppDispatch)
{
	//��дGetExternal����һ��ClientCall����
	*ppDispatch = pClientCall;
	return S_OK;
}
