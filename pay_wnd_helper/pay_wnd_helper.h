#ifndef PAY_WND_HELPER_H_
#define PAY_WND_HELPER_H_
#include "base/singleton.h"
class WebExternDispatch;
class CCustomOccManager;
class PayWndHelper : public yy::Singleton<PayWndHelper> {
public:
	bool InitPayWndSupport();
	bool ShowPayWnd(const std::string& pay_url);
	void OpenUrl(const std::string& url);
	WebExternDispatch* GetExternDispatch() { return m_dispatch; }
	~PayWndHelper();
private:
	bool m_init = false;
	WebExternDispatch* m_dispatch = nullptr;
};
#endif // !PAY_WND_HELPER_H_
