
struct Win32 {
};

// ------------------------------------------------------------------------
// Win32 API
// ------------------------------------------------------------------------

// Define global calling conventions
#define FAR
#define NEAR
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#define STDMETHODCALLTYPE __stdcall

#define STDAPI HRESULT WINAPI
#define STDAPI_(ret) ret WINAPI

#define FALSE 0
#define TRUE 1

#define EXTERN_C extern "C"

#define __RPCNDR_H_VERSION__ 1
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#define __SAL_H_FULL_VER 140050727

// ------------------------------------------------------------------------
// COM IUnknown
// ------------------------------------------------------------------------
#define STDMETHOD(method) virtual HRESULT __stdcall method
#define STDMETHOD_(type,method) virtual type __stdcall method

#define __DEFINE_GUID__(value)
#define DEFINE_IID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)
#define DEFINE_CLSID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)
#define DEFINE_GUID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)

#define MIDL_INTERFACE(guid) interface __DEFINE_GUID__(guid)
#define DECLARE_INTERFACE(name) interface name
#define DECLARE_INTERFACE_(name,parent) interface name : public parent
#define D2D1_DECLARE_INTERFACE(guid) __DEFINE_GUID__(guid)
#define DWRITE_DECLARE_INTERFACE(guid) __DEFINE_GUID__(guid)
#define DECLSPEC_UUID(guid) __DEFINE_GUID__(guid)
#define DECLSPEC_NOVTABLE

#define PURE =0
#define THIS_
#define THIS void
#define __field_ecount_opt(x)
#define DEFINE_ENUM_FLAG_OPERATORS(x)

#define MAKE_HRESULT(sev,fac,code) ( ((sev)<<31) | ((fac)<<16) | (code) )

// ------------------------------------------------------------------------
// Global types
// ------------------------------------------------------------------------
#define __reserved
#define CONST const

#define VOID void

#define CHAR char
#define WCHAR wchar_t
#define TCHAR wchar_t
#define UCHAR unsigned char

#define WORD short
#define SHORT short
#define INT16 short
#define USHORT unsigned short
#define UINT16 unsigned short

#define DWORD int
#define INT32 int
#define INT int
#define LONG int
#define UINT32 unsigned int
#define UINT unsigned int
#define ULONG unsigned int

#define FLOAT float
#define DOUBLE double

#define BYTE byte
#define INT8 byte
#define UINT8 unsigned byte

#define LONGLONG __int64
#define ULONGLONG unsigned __int64
#define UINT64 unsigned __int64
#define LARGE_INTEGER __int64

#define WPARAM unsigned int *
#define LPARAM unsigned int *
#define LRESULT unsigned int *

#define HANDLE void *
#define HMODULE void *
#define HMODULE void *
#define HINSTANCE void *
#define HTASK void *
#define HKEY void *
#define HDESK void *
#define HMF void *
#define HEMF void *
#define HPEN void *
#define HRSRC void *
#define HSTR void *
#define HWINSTA void *
#define HKL void *
#define HGDIOBJ void *

#define HWND void *
#define HMENU void *
#define HACCEL void *
#define HBRUSH void *
#define HFONT void *
#define HDC void *
#define HICON void *
#define HRGN void *

#define HFILE int

#define LPBYTE byte *
#define LPWORD WORD *
#define LPDWORD DWORD *
#define PWORD WORD *
#define PDWORD DWORD *
#define DWORD_PTR DWORD *
#define LPLONG LONG *
#define PULONG ULONG *

#define USHORT_PTR unsigned short *
#define SHORT_PTR int *

#define UINT_PTR unsigned int *
#define INT_PTR int *

#define UCHAR_PTR unsigned char *
#define CHAR_PTR char *

#define LPVOID void *
#define PVOID void *
#define LPCVOID const void *
#define PCVOID void *

#define LPSTR char *
#define PSTR char *
#define LPCSTR const char *
#define PCSTR const char *

#define LPWSTR wchar_t *
#define PWSTR wchar_t *
#define PCWSTR const wchar_t *
#define LPTSTR wchar_t *
#define PTSTR wchar_t *
#define PCTSTR const wchar_t *
#define LPCWSTR const wchar_t *
#define LPCTSTR const wchar_t *

#define LPHANDLE HANDLE *
#define DECLARE_HANDLE(name)

#define PRECTL RECT *
#define LPRECTL RECT *
#define LPRECT RECT *

#define PPOINT POINT *
#define LPPOINT POINT *
#define PPOINTL POINT *

#define PSIZE SIZE *
#define LPSIZE SIZE *
#define PSIZEL SIZE *
#define LPSIZEL SIZE *

#define PPALETTEENTRY PALETTEENTRY
#define LPPALETTEENTRY PALETTEENTRY

#define FILETIME __int64

#define IID GUID
#define CLSID GUID

#define REFGUID GUID *
#define REFIID IID *
#define REFCLSID CLSID *

#define LUID __int64

#define IStream void

#define LPUNKNOWN IUnknown *

// ------------------------------------------------------------------------
// DirectX API specific
// ------------------------------------------------------------------------

// Direct2D  / DirectWrite
#define LF_FACESIZE 32

// Direct3D 10 & 11
#define D3D11_NO_HELPERS 1
#define D3D10_NO_HELPERS 1

// For DirectSound to avoid parsing of D3DCOLOR
#define DX_SHARED_DEFINES
#define LPWAVEFORMATEX WAVEFORMATEX *
typedef float D3DVALUE, *LPD3DVALUE;

#define _WAVEFORMATEX_
#define _WAVEFORMATEXTENSIBLE_

// Used by D3D9

// D3D9
#define D3DVECTOR_DEFINED
#define D3DCOLORVALUE_DEFINED
#define D3DRECT_DEFINED
#define D3DMATRIX_DEFINED
#define D3DVECTOR_DEFINED
//#define MAX_FVF_DECL_SIZE 65
#define WOW64_ENUM_WORKAROUND
#define D3DXFX_LARGEADDRESS_HANDLE

#define HMONITOR void *

// DWrite macros
#define DWRITE_EXPORT WINAPI
#define DEFINE_ENUM_FLAG_OPERATORS(x)

// D3D9
typedef struct _RGNDATAHEADER {
  DWORD dwSize;
  DWORD iType;
  DWORD nCount;
  DWORD nRgnSize;
  RECT  rcBound;
} RGNDATAHEADER, *PRGNDATAHEADER;

typedef struct tagPALETTEENTRY {
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
} PALETTEENTRY;

typedef void * RGNDATA;

//// Used by D3D9
//typedef struct _RGNDATA {
//  RGNDATAHEADER rdh;
//  char          Buffer[1];
//} RGNDATA, *PRGNDATA;

// Used by D3D9/D3D10 Font
typedef struct TEXTMETRICW {
  LONG  tmHeight;
  LONG  tmAscent;
  LONG  tmDescent;
  LONG  tmInternalLeading;
  LONG  tmExternalLeading;
  LONG  tmAveCharWidth;
  LONG  tmMaxCharWidth;
  LONG  tmWeight;
  LONG  tmOverhang;
  LONG  tmDigitizedAspectX;
  LONG  tmDigitizedAspectY;
  WCHAR tmFirstChar;
  WCHAR tmLastChar;
  WCHAR tmDefaultChar;
  WCHAR tmBreakChar;
  BYTE  tmItalic;
  BYTE  tmUnderlined;
  BYTE  tmStruckOut;
  BYTE  tmPitchAndFamily;
  BYTE  tmCharSet;
} TEXTMETRICW;

typedef struct TEXTMETRICA {
  LONG  tmHeight;
  LONG  tmAscent;
  LONG  tmDescent;
  LONG  tmInternalLeading;
  LONG  tmExternalLeading;
  LONG  tmAveCharWidth;
  LONG  tmMaxCharWidth;
  LONG  tmWeight;
  LONG  tmOverhang;
  LONG  tmDigitizedAspectX;
  LONG  tmDigitizedAspectY;
  CHAR tmFirstChar;
  CHAR tmLastChar;
  CHAR tmDefaultChar;
  CHAR tmBreakChar;
  BYTE  tmItalic;
  BYTE  tmUnderlined;
  BYTE  tmStruckOut;
  BYTE  tmPitchAndFamily;
  BYTE  tmCharSet;
} TEXTMETRICA;

// Used by DirectWrite
typedef struct LOGFONTW {
  LONG  lfHeight;
  LONG  lfWidth;
  LONG  lfEscapement;
  LONG  lfOrientation;
  LONG  lfWeight;
  BYTE  lfItalic;
  BYTE  lfUnderline;
  BYTE  lfStrikeOut;
  BYTE  lfCharSet;
  BYTE  lfOutPrecision;
  BYTE  lfClipPrecision;
  BYTE  lfQuality;
  BYTE  lfPitchAndFamily;
  WCHAR lfFaceName[LF_FACESIZE];
} LOGFONTW;

