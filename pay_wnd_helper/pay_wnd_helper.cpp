#include "pay_wnd_helper.h"
#include <atlhost.h>
#include "WebDialog.h"
#include "web_extern_dispatch.h"
#include "custom_control_site.h"
bool PayWndHelper::InitPayWndSupport() {
	if (AfxWinInit(GetModuleHandle(NULL), NULL, GetCommandLine(), 0) == FALSE) {
			return false;
		}

		if (S_OK != OleInitialize(0) || !AtlAxWinInit())
			return false;
	AfxEnableControlContainer(new CCustomOccManager);
	m_dispatch = new WebExternDispatch;
	m_init = true;
	return true;
}

PayWndHelper::~PayWndHelper() {
	if (m_dispatch) {
		delete m_dispatch;
	}
}

bool PayWndHelper::ShowPayWnd(const std::string& pay_url) {
	if (!m_init) {
		return false;
	}
	CWebDialog WebDlg(pay_url.c_str(), "Buy", CWnd::FromHandle(GetActiveWindow()));
	WebDlg.SetSize(1600, 900);
	WebDlg.DoModal();
	return true;
}
void PayWndHelper::OpenUrl(const std::string& url) {
	HINSTANCE result = ::ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
	if ((int)result <= HINSTANCE_ERROR)
		result = ::ShellExecute(NULL, NULL, "iexplore.exe", url.c_str(), NULL, SW_SHOW);
}
