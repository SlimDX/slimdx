
struct Win32 {
};


// Define global
#define FAR
#define NEAR
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#define STDMETHODCALLTYPE __stdcall

#define LPUNKNOWN IUnknown *

// For DirectSound to avoid parsing of D3DCOLOR
#define DX_SHARED_DEFINES
#define LPWAVEFORMATEX WAVEFORMATEX *
typedef float D3DVALUE, *LPD3DVALUE;

// TYPE
#define DWORD int
#define LPDWORD DWORD *
#define LPLONG LONG *
#define PULONG LONG *
#define BYTE byte
#define LPBYTE byte *
#define LPVOID void *
#define PDWORD DWORD *
#define DWORD_PTR DWORD *
#define IStream void

// Used by D3D9
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

