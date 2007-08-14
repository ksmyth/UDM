/*
Copyright (c) Vanderbilt University, 2000-2001
ALL RIGHTS RESERVED
Vanderbilt University disclaims all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall Vanderbilt University be liable for
any special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
*/

#ifndef MGA_CORECOLLECTION_H
#define MGA_CORECOLLECTION_H

#include <vector>

template<class ITFTYPE, class OBJTYPE>
struct CopyItfFromObj
{
	static HRESULT copy(ITFTYPE **p, OBJTYPE *const*q)
	{
		ASSERT( p != NULL && q != NULL && *q != NULL );
		if( *p != NULL )
			COMRETURN(E_POINTER);

		return (*q)->QueryInterface(__uuidof(ITFTYPE), (void**)p);
	}

	static void init(ITFTYPE **p)
	{
		ASSERT( p != NULL );

		*p = NULL;
	}

	static void destroy(ITFTYPE **p)
	{
		ASSERT( p != NULL );

		if( *p )
		{
			(*p)->Release();
			*p = NULL;
		}
	}
};

template<class ITFTYPE>
struct CopyItfFromItf
{
	static HRESULT copy(ITFTYPE **p, ITFTYPE *const*q)
	{
		ASSERT( p != NULL && q != NULL && *q != NULL );

		if( *p != NULL )
			COMRETURN(E_POINTER);

		(*p = *q)->AddRef();

		return S_OK;
	}

	static void init(ITFTYPE **p)
	{
		ASSERT( p != NULL );

		*p = NULL;
	}

	static void destroy(ITFTYPE **p)
	{
		ASSERT( p != NULL );

		if( *p )
		{
			(*p)->Release();
			*p = NULL;
		}
	}
};

template<class OBJTYPE>
struct CopyDispVariantFromObj
{
	static HRESULT copy(VARIANT *p, OBJTYPE *const*q)
	{
		ASSERT( p != NULL && q != NULL && *q != NULL );

		if( p->vt != VT_EMPTY )
			COMRETURN(E_POINTER);

		HRESULT hr = (*q)->QueryInterface(IID_IDispatch, (void**)&p->pdispVal);
		if( SUCCEEDED(hr) )
			p->vt = VT_DISPATCH;

		return hr;
	}

	static void init(VARIANT *p) { VariantInit(p); }
	static void destroy(VARIANT *p) { VariantClear(p); }
};

template<class ITFTYPE>
struct CopyDispVariantFromItf
{
	static HRESULT copy(VARIANT *p, ITFTYPE **q)
	{
		ASSERT( p != NULL && q != NULL && *q != NULL );

		if( p->vt != VT_EMPTY )
			COMRETURN(E_POINTER);

		HRESULT hr = (*q)->QueryInterface(IID_IDispatch, (void**)&p->pdispVal);
		if( SUCCEEDED(hr) )
			p->vt = VT_DISPATCH;

		return hr;
	}

	static void init(VARIANT *p) { VariantInit(p); }
	static void destroy(VARIANT *p) { VariantClear(p); }
};

template<class COLLTYPE, class OBJTYPE>
class ATL_NO_VTABLE CComEnumDispVariantOnObjColl :
	public CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT,
	VARIANT, CopyDispVariantFromObj<OBJTYPE>,
	COLLTYPE>
{
};

template<class COLLTYPE, class ITFTYPE>
class ATL_NO_VTABLE CComEnumDispVariantOnItfColl :
	public CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT,
	VARIANT, CopyDispVariantFromItf<ITFTYPE>, COLLTYPE>
{
};

template<class COLLITF, class COLLTYPE, class ITFTYPE, class OBJTYPE>
class ATL_NO_VTABLE CCoreCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ICollectionOnSTLImpl<
	IDispatchImpl<COLLITF, &__uuidof(COLLITF)>,
	COLLTYPE, ITFTYPE*, CopyItfFromItf<ITFTYPE>,
	CComEnumDispVariantOnItfColl<COLLTYPE, ITFTYPE> >,
	public ISupportErrorInfoImpl<&__uuidof(COLLITF)>
{
public:
	typedef CCoreCollection<COLLITF, COLLTYPE, ITFTYPE, OBJTYPE> CLASS;
	typedef COLLTYPE::iterator ITERTYPE;
	typedef CopyItfFromObj<ITFTYPE, OBJTYPE> FILL_COPYTYPE;
	typedef CopyItfFromItf<ITFTYPE> GETALL_COPYTYPE;

	~CCoreCollection()
	{
		while( !m_coll.empty() )
		{
			FILL_COPYTYPE::destroy(&m_coll.front());
			m_coll.pop_front();
		}
	}

BEGIN_COM_MAP(CLASS)
	COM_INTERFACE_ENTRY(COLLITF)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	COLLTYPE &GetCollection() { return m_coll; }

	STDMETHODIMP raw_GetAll(ULONG requested, ITFTYPE **p, ULONG *provided)
	{
		CHECK_OUT(provided);

		ITERTYPE i = m_coll.begin();
		ITERTYPE e = m_coll.end();
		ULONG copied = 0;
		HRESULT hr = S_OK;

		while( i != e && copied < requested )
		{
			ASSERT( *(p+copied) == NULL );
			hr = GETALL_COPYTYPE::copy(p+copied, &*i);
			if( FAILED(hr) )
				break;

			++copied;
			++i;
		}

		if( FAILED(hr) || i != e || copied != requested )
		{
			while( copied > 0 )
			{
				GETALL_COPYTYPE::destroy(p+copied);
				--copied;
			}

			if( SUCCEEDED(hr) )
				hr = E_GETALL;
		}

		*provided = copied;

		if( FAILED(hr) )
			SetErrorInfo(hr);

		return hr;
	}

	template<class ITERTYPE2>
	void Fill(ITERTYPE2 i, ITERTYPE2 e)
	{
		while( i != e )
		{
			ITFTYPE *o = NULL;
			COMTHROW( FILL_COPYTYPE::copy(&o, &*i) );
			m_coll.push_front(o);
			++i;
		}
	}

	void Add(OBJTYPE *i)
	{
		ASSERT( i != NULL );

		ITFTYPE *o = NULL;
		COMTHROW( FILL_COPYTYPE::copy(&o, &i) );
		m_coll.push_front(o);
	}
};

//typedef CComObject< CCoreCollection<IMetaObjects, slist<IMetaObject*>, 
//	IMetaObject, CMetaStaticObject> > CMetaStaticObjects;

//typedef CComObject< CCoreCollection<IMetaAttributes, slist<IMetaAttribute*>,
//	IMetaAttribute, CMetaStaticAttribute> > CMetaStaticAttributes;

template<class COLLITF, class ITFTYPE>
void GetAll(COLLITF *coll, vector< CComObjPtr<ITFTYPE> > &ret)
{
	ASSERT( coll != NULL );
	ASSERT( ret.empty() );

	long count = 0;
	COMTHROW( coll->get_Count(&count) );
	ASSERT( count >= 0 );

	ret.clear();
	ret.insert(ret.begin(), count, NULL);

	unsigned long provided = 0;
	COMTHROW( coll->GetAll((unsigned long)count, (ITFTYPE**)ret.begin(), &provided) );
	ASSERT( count == provided );
}

#endif//MGA_CORECOLLECTION_H
