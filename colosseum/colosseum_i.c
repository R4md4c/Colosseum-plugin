

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Jul 01 17:52:49 2011
 */
/* Compiler settings for .\colosseum.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_colosseumLib,0xEAB0C469,0xFB77,0x4B34,0x91,0x2F,0xB4,0xF0,0xF3,0x98,0xEB,0xF8);


MIDL_DEFINE_GUID(IID, DIID__Dcolosseum,0xE8B8A0AD,0x761C,0x4631,0x88,0xCF,0xD5,0xD2,0xDD,0xEA,0xEE,0x79);


MIDL_DEFINE_GUID(IID, DIID__DcolosseumEvents,0xE9D4851E,0x590E,0x4C56,0x9C,0xEF,0x9E,0xC4,0x95,0x96,0x1E,0xDD);


MIDL_DEFINE_GUID(CLSID, CLSID_colosseum,0x70217189,0x66E8,0x4874,0x9F,0xD2,0x53,0x52,0xFD,0xF4,0x67,0x34);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



