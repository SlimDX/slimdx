/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

using namespace System;

#include <d3d9.h>
#include "../ErrorCode.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class D3DErrorCode : ErrorCode
		{
		public:
			literal int WrongTextureFormat = D3DERR_WRONGTEXTUREFORMAT;
			literal int UnsupportedColorOperation = D3DERR_UNSUPPORTEDCOLOROPERATION;
			literal int UnsupportedColorArgument = D3DERR_UNSUPPORTEDCOLORARG;
			literal int UnsupportedAlphaOperation = D3DERR_UNSUPPORTEDALPHAOPERATION;
			literal int UnsupportedAlphaArgument = D3DERR_UNSUPPORTEDALPHAARG;
			literal int TooManyOperations = D3DERR_TOOMANYOPERATIONS;
			literal int ConflictingTextureFilter = D3DERR_CONFLICTINGTEXTUREFILTER;
			literal int UnsupportedFactorValue = D3DERR_UNSUPPORTEDFACTORVALUE;
			literal int ConflictingRenderState = D3DERR_CONFLICTINGRENDERSTATE;
			literal int UnsupportedTextureFilter = D3DERR_UNSUPPORTEDTEXTUREFILTER;
			literal int ConflictingTexturePalette = D3DERR_CONFLICTINGTEXTUREPALETTE;
			literal int DriverInternalError = D3DERR_DRIVERINTERNALERROR;

			literal int NotFound = D3DERR_NOTFOUND;
			literal int MoreData = D3DERR_MOREDATA;
			literal int DeviceLost = D3DERR_DEVICELOST;
			literal int DeviceNotReset = D3DERR_DEVICENOTRESET;
			literal int NotAvailable = D3DERR_NOTAVAILABLE;
			literal int OutOfVideoMemory = D3DERR_OUTOFVIDEOMEMORY;
			literal int InvalidDevice = D3DERR_INVALIDDEVICE;
			literal int InvalidCall = D3DERR_INVALIDCALL;
			literal int DriverInvalidCall = D3DERR_DRIVERINVALIDCALL;
			literal int WasStillDrawing = D3DERR_WASSTILLDRAWING;
			literal int NoAutoGen = D3DOK_NOAUTOGEN;
		};

		public ref class D3DXFileErrorCode : ErrorCode
		{
		public:
			literal int BadObject = D3DXFERR_BADOBJECT;
			literal int BadValue = D3DXFERR_BADVALUE;
			literal int BadType = D3DXFERR_BADTYPE;
			literal int NotFound = D3DXFERR_NOTFOUND;
			literal int NotDoneYet = D3DXFERR_NOTDONEYET;
			literal int FileNotFound = D3DXFERR_FILENOTFOUND;
			literal int ResourceNotFound = D3DXFERR_RESOURCENOTFOUND;
			literal int BadResource = D3DXFERR_BADRESOURCE;
			literal int BadFileType = D3DXFERR_BADFILETYPE;
			literal int BadFileVersion = D3DXFERR_BADFILEVERSION;
			literal int BadFileFloatSize = D3DXFERR_BADFILEFLOATSIZE;
			literal int BadFile = D3DXFERR_BADFILE;
			literal int ParseError = D3DXFERR_PARSEERROR;
			literal int BadArraySize = D3DXFERR_BADARRAYSIZE;
			literal int BadDataReference = D3DXFERR_BADDATAREFERENCE;
			literal int NoMoreObjects = D3DXFERR_NOMOREOBJECTS;
			literal int NoMoreData = D3DXFERR_NOMOREDATA;
			literal int BadCacheFile = D3DXFERR_BADCACHEFILE;
		};

		public ref class D3DXErrorCode : ErrorCode
		{
		public:
			literal int CannotModifyIndexBuffer = D3DXERR_CANNOTMODIFYINDEXBUFFER;
			literal int InvalidMesh = D3DXERR_INVALIDMESH;
			literal int CannotAttributeSort = D3DXERR_CANNOTATTRSORT;
			literal int SkinningNotSupported = D3DXERR_SKINNINGNOTSUPPORTED;
			literal int TooManyInfluences = D3DXERR_TOOMANYINFLUENCES;
			literal int InvalidData = D3DXERR_INVALIDDATA;
			literal int MeshHasNoData = D3DXERR_LOADEDMESHASNODATA;
			literal int DuplicatNamedFragment = D3DXERR_DUPLICATENAMEDFRAGMENT;
			literal int CannotRemoveLastItem = D3DXERR_CANNOTREMOVELASTITEM;
		};
	}
}