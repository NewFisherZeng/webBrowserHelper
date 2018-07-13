#ifndef CALL_JS_TEST_H_
#define CALL_JS_TEST_H_
#include <OAIdl.h>
typedef void _stdcall JsFunction_Callback(LPVOID pParam);
class CallJsTest : public IDispatch{
private:
	long _refNum;
	JsFunction_Callback *m_pCallback;
	LPVOID m_pParam;
public:
	CallJsTest(JsFunction_Callback *pCallback, LPVOID pParam);
	~CallJsTest(void);
public:

	// IUnknown Methods

	STDMETHODIMP QueryInterface(REFIID iid, void**ppvObject);

	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IDispatch Methods

	HRESULT _stdcall GetTypeInfoCount(
		unsigned int * pctinfo);

	HRESULT _stdcall GetTypeInfo(
		unsigned int iTInfo,
		LCID lcid,
		ITypeInfo FAR* FAR* ppTInfo);

	HRESULT _stdcall GetIDsOfNames(
		REFIID riid,
		OLECHAR FAR* FAR* rgszNames,
		unsigned int cNames,
		LCID lcid,
		DISPID FAR* rgDispId
		);

	HRESULT _stdcall Invoke(
		DISPID dispIdMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS* pDispParams,
		VARIANT* pVarResult,
		EXCEPINFO* pExcepInfo,
		unsigned int* puArgErr
		);
};
#endif