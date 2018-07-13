#ifndef JS_CALL_CLIENT_TEST_H_
#define JS_CALL_CLIENT_TEST_H_
#include <OAIdl.h>

class JSCallClientTest :public IDispatch
{
	long _refNum;
public:
	JSCallClientTest();
	~JSCallClientTest(void);
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