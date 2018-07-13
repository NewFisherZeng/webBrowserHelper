#include "stdafx.h"
#include "resource.h"
#include "WebBrowser.h"
#include <string>
#include "base/path_helper.h"
#include "webbrowser_test/call_js_test.h"
#include "webbrowser_test/js_call_client_test.h"
#include "webbrowser_test/main_form.h"
using namespace std;

INT_PTR CALLBACK DlgProc(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);

HWND hMainForm;
HINSTANCE hCurrentInstance;
CWebBrowserBase *pBrowser;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int ShowCmd)
{
	wstring sPath = GetAppPath();;
	INITCOMMONCONTROLSEX icc;
	MSG msg;
	BOOL bRet;
	HACCEL hAccel;
	HICON hAppIcon;

	hCurrentInstance=hInstance;

	//��ʼ���ؼ�
	icc.dwSize=sizeof(icc);
	icc.dwICC=ICC_BAR_CLASSES|ICC_COOL_CLASSES;
	InitCommonControlsEx(&icc);

	//���ô���ͼ��
	hAppIcon=LoadIcon(hInstance,(LPCTSTR)IDI_APP);
	if(hAppIcon) SendMessage(hMainForm,WM_SETICON,ICON_BIG,(LPARAM)hAppIcon);

	//��ʾ����
	hMainForm = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_MAINFORM),NULL,DlgProc);
	pBrowser = new MainForm(hMainForm);
	ShowWindow(hMainForm,SW_SHOW);

	pBrowser->OpenWebBrowser();
	wstring sUrl = sPath + L"\\test.htm";
	VARIANT url;
	url.vt = VT_LPWSTR;
	url.bstrVal = (BSTR)sUrl.c_str();
	pBrowser->OpenURL(&url);

	RECT rect;
	GetClientRect(hMainForm, &rect);
	rect.top += 100;
	pBrowser->SetWebRect(&rect);

	//���ؼ��ټ�
	hAccel=LoadAccelerators(hInstance,(LPCTSTR)IDR_ACCELERATOR);

	//��Ϣѭ��
	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			break;
		}
		else
		{
			if (!IsDialogMessage(hMainForm, &msg) && 
				!TranslateAccelerator(hMainForm, hAccel,&msg)
				) 
			{ 
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		} 
	} 
	return 0;
}

INT_PTR CALLBACK DlgProc(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case WM_INITDIALOG:
		{
			return TRUE;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return TRUE;
		}
	case WM_COMMAND:
		{
			int wmId, wmEvent;
			wmId = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			switch(wmId)
			{
			case IDC_BUTTON1:
				{
					VARIANT params[10];
					VARIANT ret;
					//��ȡҳ��window
					IDispatch *pHtmlWindow = pBrowser->GetHtmlWindow();
					//ҳ��ȫ�ֺ���Testʵ������window��Test������
					CWebBrowserBase::InvokeMethod(pHtmlWindow, L"Test", &ret, params, 0);

					break;
				}
			case IDC_BUTTON2:
				{
					VARIANT params[10];
					VARIANT ret;
					//��ȡҳ��window
					IDispatch *pHtmlWindow = pBrowser->GetHtmlWindow();
					//��ȡglobalObject
					CVariant globalObject;
					params[0].vt = VT_BSTR;
					params[0].bstrVal = L"globalObject";
					CWebBrowserBase::GetProperty(pHtmlWindow, L"globalObject", &globalObject);
					//����globalObject.Test
					CWebBrowserBase::InvokeMethod(globalObject.pdispVal, L"Test", &ret, params, 0);
					break;
				}
			}
			return TRUE;
		}
	case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hDlg, &rect);
			rect.top += 100;
			pBrowser->SetWebRect(&rect);

			return TRUE;
		}
	}
	return 0;
}