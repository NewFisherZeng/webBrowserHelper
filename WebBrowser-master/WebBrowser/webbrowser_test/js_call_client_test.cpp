#include "js_call_client_test.h"
void CppCall()
{
	MessageBox(NULL, L"您调用了CppCall", L"提示(C++)", 0);
}

JSCallClientTest::JSCallClientTest()
{
	_refNum = 1;
}
JSCallClientTest::~JSCallClientTest(void)
{
}
// IUnknown Methods

STDMETHODIMP JSCallClientTest::QueryInterface(REFIID iid, void**ppvObject)
{
	*ppvObject = NULL;
	if (iid == IID_IUnknown)	*ppvObject = this;
	else if (iid == IID_IDispatch)	*ppvObject = (IDispatch*)this;
	if (*ppvObject)
	{
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) JSCallClientTest::AddRef()
{
	return ::InterlockedIncrement(&_refNum);
}

STDMETHODIMP_(ULONG) JSCallClientTest::Release()
{
	::InterlockedDecrement(&_refNum);
	if (_refNum == 0)
	{
		delete this;
	}
	return _refNum;
}

// IDispatch Methods

HRESULT _stdcall JSCallClientTest::GetTypeInfoCount(
	unsigned int * pctinfo)
{
	return E_NOTIMPL;
}

HRESULT _stdcall JSCallClientTest::GetTypeInfo(
	unsigned int iTInfo,
	LCID lcid,
	ITypeInfo FAR* FAR* ppTInfo)
{
	return E_NOTIMPL;
}

HRESULT _stdcall JSCallClientTest::GetIDsOfNames(
	REFIID riid,
	OLECHAR FAR* FAR* rgszNames,
	unsigned int cNames,
	LCID lcid,
	DISPID FAR* rgDispId
	)
{
	if (lstrcmp(rgszNames[0], L"CppCall") == 0)
	{
		//网页调用window.external.CppCall时，会调用这个方法获取CppCall的ID
		*rgDispId = 100;
	}
	return S_OK;
}

HRESULT _stdcall JSCallClientTest::Invoke(
	DISPID dispIdMember,
	REFIID riid,
	LCID lcid,
	WORD wFlags,
	DISPPARAMS* pDispParams,
	VARIANT* pVarResult,
	EXCEPINFO* pExcepInfo,
	unsigned int* puArgErr
	)
{
	if (dispIdMember == 100)
	{
		//网页调用CppCall时，或根据获取到的ID调用Invoke方法
		CppCall();
	}
	return S_OK;
}