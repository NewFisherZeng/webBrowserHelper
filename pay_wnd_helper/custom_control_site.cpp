
//#include "StdAfx.h"
#include "custom_control_site.h"
#include "pay_wnd_helper.h"
#include "web_extern_dispatch.h"
BEGIN_INTERFACE_MAP(CustomControlSite, COleControlSite)

	INTERFACE_PART(CustomControlSite, IID_IDocHostUIHandler, DocHostUIHandler)

END_INTERFACE_MAP()

CustomControlSite::CustomControlSite(COleControlContainer*pCtrl) :COleControlSite(pCtrl) {

}

ULONG CustomControlSite::XDocHostUIHandler::AddRef()
{
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return pThis->ExternalAddRef();
}

ULONG CustomControlSite::XDocHostUIHandler::Release() {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return pThis->ExternalRelease();
}


HRESULT CustomControlSite::XDocHostUIHandler::QueryInterface(REFIID riid, void** ppvObj) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}


HRESULT CustomControlSite::XDocHostUIHandler::GetHostInfo(DOCHOSTUIINFO* pInfo) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
	pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER;
	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;
	return S_OK;
}

HRESULT CustomControlSite::XDocHostUIHandler::ShowUI(
	DWORD dwID,
	IOleInPlaceActiveObject* /*pActiveObject*/,
	IOleCommandTarget* pCommandTarget,
	IOleInPlaceFrame* /*pFrame*/,
	IOleInPlaceUIWindow* /*pDoc*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return S_OK;
}

HRESULT CustomControlSite::XDocHostUIHandler::HideUI(void) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return S_OK;
}

HRESULT CustomControlSite::XDocHostUIHandler::UpdateUI(void) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return S_OK;
}

HRESULT CustomControlSite::XDocHostUIHandler::EnableModeless(BOOL /*fEnable*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

HRESULT CustomControlSite::XDocHostUIHandler::OnDocWindowActivate(BOOL /*fActivate*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

HRESULT CustomControlSite::XDocHostUIHandler::OnFrameWindowActivate(BOOL /*fActivate*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

HRESULT CustomControlSite::XDocHostUIHandler::ResizeBorder(
	LPCRECT /*prcBorder*/,
	IOleInPlaceUIWindow* /*pUIWindow*/,
	BOOL /*fRameWindow*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

HRESULT CustomControlSite::XDocHostUIHandler::ShowContextMenu(
	DWORD /*dwID*/,
	POINT* pptPosition,
	IUnknown* /*pCommandTarget*/,
	IDispatch* /*pDispatchObjectHit*/) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return S_OK; // We've shown our own context menu. MSHTML.DLL will no longer try to show its own.
}

HRESULT CustomControlSite::XDocHostUIHandler::TranslateAccelerator(
	/* [in] */ LPMSG lpMsg,
	/* [in] */ const GUID __RPC_FAR* pguidCmdGroup,
	/* [in] */ DWORD nCmdID) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		//disable F5
		if (lpMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_F5) < 0) {
			return S_OK;
		}
	if (GetKeyState(VK_CONTROL) & 0x8000) {
		// disable ctrl + O
		if (lpMsg->message == WM_KEYDOWN && GetAsyncKeyState(0x4F) < 0)
		{
			return S_OK;
		}
		//disable ctrl + p
		if (lpMsg->message == WM_KEYDOWN && GetAsyncKeyState(0x50) < 0)
		{
			return S_OK;
		}
		//disable ctrl + N
		if (lpMsg->message == WM_KEYDOWN && GetAsyncKeyState(0x4E) < 0)
		{
			return S_OK;
		}
	}
	//disable back space
	if(lpMsg->wParam == VK_BACK)	{
		return S_OK;
	}

	return S_FALSE;
}

HRESULT CustomControlSite::XDocHostUIHandler::GetOptionKeyPath(BSTR* pbstrKey, DWORD) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

STDMETHODIMP CustomControlSite::XDocHostUIHandler::GetDropTarget(
	/* [in] */ IDropTarget __RPC_FAR* pDropTarget,
	/* [out] */ IDropTarget __RPC_FAR*__RPC_FAR* ppDropTarget) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

STDMETHODIMP CustomControlSite::XDocHostUIHandler::GetExternal(
	/* [out] */ IDispatch __RPC_FAR*__RPC_FAR* ppDispatch) {
	// return the IDispatch we have for extending the object Model
	*ppDispatch = PayWndHelper::GetSingleton()->GetExternDispatch();
	return S_OK;
}

STDMETHODIMP CustomControlSite::XDocHostUIHandler::TranslateUrl(
	/* [in] */ DWORD dwTranslate,
	/* [in] */ OLECHAR __RPC_FAR *pchURLIn,
	/* [out] */ OLECHAR __RPC_FAR*__RPC_FAR* ppchURLOut) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

STDMETHODIMP CustomControlSite::XDocHostUIHandler::FilterDataObject(
	/* [in] */ IDataObject __RPC_FAR* pDO,
	/* [out] */ IDataObject __RPC_FAR*__RPC_FAR* ppDORet) {
	METHOD_PROLOGUE(CustomControlSite, DocHostUIHandler)
		return E_NOTIMPL;
}

CustomControlSite::~CustomControlSite(void) {
}

CCustomOccManager::CCustomOccManager() {
}

COleControlSite* CCustomOccManager::CreateSite(COleControlContainer* pCtrlCont) {
	CustomControlSite *pSite = new CustomControlSite(pCtrlCont);
	return pSite;
}