#include "call_js_test.h"

CallJsTest::CallJsTest(JsFunction_Callback *pCallback, LPVOID pParam)
{
	_refNum = 1;
	m_pCallback = pCallback;
	m_pParam = pParam;
}
CallJsTest::~CallJsTest(void)
{
}

	// IUnknown Methods

STDMETHODIMP CallJsTest::QueryInterface(REFIID iid, void**ppvObject)
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

STDMETHODIMP_(ULONG) CallJsTest::AddRef()
{
	return ::InterlockedIncrement(&_refNum);
}

STDMETHODIMP_(ULONG) CallJsTest::Release()
{
	::InterlockedDecrement(&_refNum);
	if (_refNum == 0)
	{
		delete this;
	}
	return _refNum;
}

// IDispatch Methods

HRESULT _stdcall CallJsTest::GetTypeInfoCount(
	unsigned int * pctinfo)
{
	return E_NOTIMPL;
}

HRESULT _stdcall CallJsTest::GetTypeInfo(
	unsigned int iTInfo,
	LCID lcid,
	ITypeInfo FAR* FAR* ppTInfo)
{
	return E_NOTIMPL;
}

HRESULT _stdcall CallJsTest::GetIDsOfNames(
	REFIID riid,
	OLECHAR FAR* FAR* rgszNames,
	unsigned int cNames,
	LCID lcid,
	DISPID FAR* rgDispId
	)
{
	//���˷ѽ���ǣ���ҳ���ú�����call����ʱ��û�е���GetIDsOfNames��ȡcall��ID������ֱ�ӵ���Invoke
	return E_NOTIMPL;
}

HRESULT _stdcall CallJsTest::Invoke(
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
	m_pCallback(m_pParam);
	return S_OK;
}