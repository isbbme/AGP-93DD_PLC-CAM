

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for MFC20191205.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __MFC20191205_h_h__
#define __MFC20191205_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMFC20191205_FWD_DEFINED__
#define __IMFC20191205_FWD_DEFINED__
typedef interface IMFC20191205 IMFC20191205;

#endif 	/* __IMFC20191205_FWD_DEFINED__ */


#ifndef __MFC20191205_FWD_DEFINED__
#define __MFC20191205_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFC20191205 MFC20191205;
#else
typedef struct MFC20191205 MFC20191205;
#endif /* __cplusplus */

#endif 	/* __MFC20191205_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFC20191205_LIBRARY_DEFINED__
#define __MFC20191205_LIBRARY_DEFINED__

/* library MFC20191205 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFC20191205;

#ifndef __IMFC20191205_DISPINTERFACE_DEFINED__
#define __IMFC20191205_DISPINTERFACE_DEFINED__

/* dispinterface IMFC20191205 */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFC20191205;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("737f7a32-b182-4536-a806-b169b2d88698")
    IMFC20191205 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFC20191205Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFC20191205 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFC20191205 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFC20191205 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFC20191205 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFC20191205 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFC20191205 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFC20191205 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMFC20191205Vtbl;

    interface IMFC20191205
    {
        CONST_VTBL struct IMFC20191205Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFC20191205_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFC20191205_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFC20191205_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFC20191205_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFC20191205_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFC20191205_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFC20191205_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFC20191205_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MFC20191205;

#ifdef __cplusplus

class DECLSPEC_UUID("3a3acb96-e12a-4537-8b82-937e4f86ad2b")
MFC20191205;
#endif
#endif /* __MFC20191205_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


