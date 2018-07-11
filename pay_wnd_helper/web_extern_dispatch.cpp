#include "web_extern_dispatch.h"

// Hardcoded information for extending the Object Model   
// Typically this would be supplied through a TypeInfo  
// In this case the name "xxyyzz" maps to DISPID_Extend   
const   WCHAR pszExtend[10] = L"CppCall";
#define DISPID_Extend 100  



/*
* WebExternDispatch::WebExternDispatch
* WebExternDispatch::~WebExternDispatch
*
* Parameters (Constructor):
*  pSite           PCSite of the site we're in.
*  pUnkOuter       LPUNKNOWN to which we delegate.
*/

WebExternDispatch::WebExternDispatch(void)
{
	m_cRef = 0;
}

WebExternDispatch::~WebExternDispatch(void)
{
	ASSERT(m_cRef == 0);
}


/*
* WebExternDispatch::QueryInterface
* WebExternDispatch::AddRef
* WebExternDispatch::Release
*
* Purpose:
*  IUnknown members for WebExternDispatch object.
*/

STDMETHODIMP WebExternDispatch::QueryInterface(REFIID riid, void **ppv)
{
	*ppv = NULL;


	if (IID_IDispatch == riid)
	{
		*ppv = this;
	}

	if (NULL != *ppv)
	{
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

	return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) WebExternDispatch::AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) WebExternDispatch::Release(void)
{
	return --m_cRef;
}


//IDispatch  
STDMETHODIMP WebExternDispatch::GetTypeInfoCount(UINT* /*pctinfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP WebExternDispatch::GetTypeInfo(/* [in] */ UINT /*iTInfo*/,
	/* [in] */ LCID /*lcid*/,
	/* [out] */ ITypeInfo** /*ppTInfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP WebExternDispatch::GetIDsOfNames(
	/* [in] */ REFIID riid,
	/* [size_is][in] */ OLECHAR** rgszNames,
	/* [in] */ UINT cNames,
	/* [in] */ LCID lcid,
	/* [size_is][out] */ DISPID* rgDispId)
{
	HRESULT hr;
	UINT    i;

	// Assume some degree of success  
	hr = NOERROR;

	// Hardcoded mapping for this sample  
	// A more usual procedure would be to use a TypeInfo  
	for (i = 0; i < cNames; i++)
	{
		if (2 == CompareString(lcid, NORM_IGNOREWIDTH, (TCHAR*)pszExtend, 3, (TCHAR*)rgszNames[i], 3))
		{
			rgDispId[i] = DISPID_Extend;
		}
		else
		{
			// One or more are unknown so set the return code accordingly  
			hr = ResultFromScode(DISP_E_UNKNOWNNAME);
			rgDispId[i] = DISPID_UNKNOWN;
		}
	}
	return hr;
}

STDMETHODIMP WebExternDispatch::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID /*riid*/,
	/* [in] */ LCID /*lcid*/,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS* pDispParams,
	/* [out] */ VARIANT* pVarResult,
	/* [out] */ EXCEPINFO* /*pExcepInfo*/,
	/* [out] */ UINT* puArgErr)
{

	// For this sample we only support a Property Get on DISPID_Extend  
	// returning a BSTR with "Wibble" as the value  
	if (dispIdMember == DISPID_Extend)
	{
		MessageBoxA(NULL, "web call success", "test", MB_OK);
	}

	return S_OK;
}