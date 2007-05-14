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
using namespace System::Runtime::Serialization;

#include "../Exceptions.h"

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class GraphicsException : public DirectXException
		{
		public:
			GraphicsException() : DirectXException(E_FAIL, "A Direct3D exception occurred.")
			{ }
			GraphicsException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			GraphicsException( int errorCode, String^ message ) : DirectXException( errorCode, message )
			{ }
			GraphicsException( String^ message, Exception^ innerException ) : DirectXException( message, innerException )
			{ }
			GraphicsException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

			static GraphicsException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
		};

#define DEFINE_GRAPHICS_EXCEPTION( ExName, ErrorCode, Message ) \
	public ref class ExName ## Exception : public GraphicsException \
	{ \
		public: \
		ExName ## Exception () : GraphicsException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : GraphicsException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : GraphicsException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : GraphicsException(info, context) { }\
	}

		DEFINE_GRAPHICS_EXCEPTION( WrongTextureFormat, D3DERR_WRONGTEXTUREFORMAT, "Wrong texture format." );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedColorOperation, D3DERR_UNSUPPORTEDCOLOROPERATION, "Unsupported color operation." );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedColorArgument, D3DERR_UNSUPPORTEDCOLORARG, "Unsupported color argument." );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedAlphaOperation, D3DERR_UNSUPPORTEDALPHAOPERATION, "Unsupported alpha operation." );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedAlphaArgument, D3DERR_UNSUPPORTEDALPHAARG, "Unsupported alpha argument." );
		DEFINE_GRAPHICS_EXCEPTION( TooManyOperations, D3DERR_TOOMANYOPERATIONS, "Too many operations." );
		DEFINE_GRAPHICS_EXCEPTION( ConflictingTextureFilter, D3DERR_CONFLICTINGTEXTUREFILTER, "Conflicting texture filter." );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedFactorValue, D3DERR_UNSUPPORTEDFACTORVALUE, "Unsupported factor value." );
		DEFINE_GRAPHICS_EXCEPTION( ConflictingTexturePalette, D3DERR_CONFLICTINGTEXTUREPALETTE, "Conflicting texture palette." );
		DEFINE_GRAPHICS_EXCEPTION( DriverInternalError, D3DERR_DRIVERINTERNALERROR, "Driver internal error." );
		DEFINE_GRAPHICS_EXCEPTION( NotFound, D3DERR_NOTFOUND, "Not found." );
		DEFINE_GRAPHICS_EXCEPTION( MoreData, D3DERR_MOREDATA, "More data." );
		DEFINE_GRAPHICS_EXCEPTION( DeviceLost, D3DERR_DEVICELOST, "Device lost." );
		DEFINE_GRAPHICS_EXCEPTION( DeviceNotReset, D3DERR_DEVICENOTRESET, "Device not reset." );
		DEFINE_GRAPHICS_EXCEPTION( NotAvailable, D3DERR_NOTAVAILABLE, "Not available." );
		DEFINE_GRAPHICS_EXCEPTION( OutOfVideoMemory, D3DERR_OUTOFVIDEOMEMORY, "Out of video memory." );
		DEFINE_GRAPHICS_EXCEPTION( InvalidDevice, D3DERR_INVALIDDEVICE, "Invalid device." );
		DEFINE_GRAPHICS_EXCEPTION( InvalidCall, D3DERR_INVALIDCALL, "Invalid call." );
		DEFINE_GRAPHICS_EXCEPTION( DriverInvalidCall, D3DERR_DRIVERINVALIDCALL, "Driver invalid call." );
		DEFINE_GRAPHICS_EXCEPTION( WasStillDrawing, D3DERR_WASSTILLDRAWING, "Was still drawing." );

		DEFINE_GRAPHICS_EXCEPTION( BadObject, D3DXFERR_BADOBJECT, "Bad object." );
		DEFINE_GRAPHICS_EXCEPTION( BadValue, D3DXFERR_BADVALUE, "Bad value." );
		DEFINE_GRAPHICS_EXCEPTION( BadType, D3DXFERR_BADTYPE, "Bad type." );
		DEFINE_GRAPHICS_EXCEPTION( XNotFound, D3DXFERR_NOTFOUND, "Not found." );
		DEFINE_GRAPHICS_EXCEPTION( NotDoneYet, D3DXFERR_NOTDONEYET, "Not done yet." );
		DEFINE_GRAPHICS_EXCEPTION( FileNotFound, D3DXFERR_FILENOTFOUND, "File not found." );
		DEFINE_GRAPHICS_EXCEPTION( ResourceNotFound, D3DXFERR_RESOURCENOTFOUND, "Resource not found." );
		DEFINE_GRAPHICS_EXCEPTION( BadResource, D3DXFERR_BADRESOURCE, "Bad resource." );
		DEFINE_GRAPHICS_EXCEPTION( BadFileType, D3DXFERR_BADFILETYPE, "Bad file type." );
		DEFINE_GRAPHICS_EXCEPTION( BadFileVersion, D3DXFERR_BADFILEVERSION, "Bad file version." );
		DEFINE_GRAPHICS_EXCEPTION( BadFileFloatSize, D3DXFERR_BADFILEFLOATSIZE, "Bad file float size." );
		DEFINE_GRAPHICS_EXCEPTION( BadFile, D3DXFERR_BADFILE, "Bad file." );
		DEFINE_GRAPHICS_EXCEPTION( ParseError, D3DXFERR_PARSEERROR, "Parse error." );
		DEFINE_GRAPHICS_EXCEPTION( BadArraySize, D3DXFERR_BADARRAYSIZE, "Bad array size." );
		DEFINE_GRAPHICS_EXCEPTION( BadDataReference, D3DXFERR_BADDATAREFERENCE, "Bad data reference." );
		DEFINE_GRAPHICS_EXCEPTION( NoMoreObjects, D3DXFERR_NOMOREOBJECTS, "No more objects." );
		DEFINE_GRAPHICS_EXCEPTION( NoMoreData, D3DXFERR_NOMOREDATA, "No more data." );
		DEFINE_GRAPHICS_EXCEPTION( BadCacheFile, D3DXFERR_BADCACHEFILE, "Bad cache file." );

		DEFINE_GRAPHICS_EXCEPTION( OutOfMemory, E_OUTOFMEMORY, "Out of memory." );

		inline GraphicsException^ GraphicsException::GetExceptionFromHResult( HRESULT hr )
		{
			GraphicsException^ ex;

#			define GENERATE_EXCEPTION(errCase, type) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION(D3DERR_WRONGTEXTUREFORMAT, WrongTextureFormat);
			GENERATE_EXCEPTION(D3DERR_UNSUPPORTEDCOLOROPERATION, UnsupportedColorOperation);
			GENERATE_EXCEPTION(D3DERR_UNSUPPORTEDCOLORARG, UnsupportedColorArgument);
			GENERATE_EXCEPTION(D3DERR_UNSUPPORTEDALPHAOPERATION, UnsupportedAlphaOperation);
			GENERATE_EXCEPTION(D3DERR_UNSUPPORTEDALPHAARG, UnsupportedAlphaArgument);
			GENERATE_EXCEPTION(D3DERR_TOOMANYOPERATIONS, TooManyOperations);
			GENERATE_EXCEPTION(D3DERR_CONFLICTINGTEXTUREFILTER, ConflictingTextureFilter);
			GENERATE_EXCEPTION(D3DERR_UNSUPPORTEDFACTORVALUE, UnsupportedFactorValue);
			GENERATE_EXCEPTION(D3DERR_CONFLICTINGTEXTUREPALETTE, ConflictingTexturePalette);
			GENERATE_EXCEPTION(D3DERR_DRIVERINTERNALERROR, DriverInternalError);

			GENERATE_EXCEPTION(D3DERR_NOTFOUND, NotFound);
			GENERATE_EXCEPTION(D3DERR_MOREDATA, MoreData);
			GENERATE_EXCEPTION(D3DERR_DEVICELOST, DeviceLost);
			GENERATE_EXCEPTION(D3DERR_DEVICENOTRESET, DeviceNotReset);
			GENERATE_EXCEPTION(D3DERR_NOTAVAILABLE, NotAvailable);
			GENERATE_EXCEPTION(D3DERR_OUTOFVIDEOMEMORY,OutOfVideoMemory);
			GENERATE_EXCEPTION(D3DERR_INVALIDDEVICE,InvalidDevice);
			GENERATE_EXCEPTION(D3DERR_INVALIDCALL,InvalidCall);
			GENERATE_EXCEPTION(D3DERR_DRIVERINVALIDCALL,DriverInvalidCall);
			GENERATE_EXCEPTION(D3DERR_WASSTILLDRAWING,WasStillDrawing);

			GENERATE_EXCEPTION(D3DXFERR_BADOBJECT, BadObject);
			GENERATE_EXCEPTION(D3DXFERR_BADVALUE, BadValue);
			GENERATE_EXCEPTION(D3DXFERR_BADTYPE, BadType);
			GENERATE_EXCEPTION(D3DXFERR_NOTFOUND, NotFound);
			GENERATE_EXCEPTION(D3DXFERR_NOTDONEYET, NotDoneYet);
			GENERATE_EXCEPTION(D3DXFERR_FILENOTFOUND, FileNotFound);
			GENERATE_EXCEPTION(D3DXFERR_RESOURCENOTFOUND, ResourceNotFound);
			GENERATE_EXCEPTION(D3DXFERR_BADRESOURCE, BadResource);
			GENERATE_EXCEPTION(D3DXFERR_BADFILETYPE, BadFileType);
			GENERATE_EXCEPTION(D3DXFERR_BADFILEVERSION, BadFileVersion);
			GENERATE_EXCEPTION(D3DXFERR_BADFILEFLOATSIZE, BadFileFloatSize);
			GENERATE_EXCEPTION(D3DXFERR_BADFILE, BadFile);
			GENERATE_EXCEPTION(D3DXFERR_PARSEERROR, ParseError);
			GENERATE_EXCEPTION(D3DXFERR_BADARRAYSIZE, BadArraySize);
			GENERATE_EXCEPTION(D3DXFERR_BADDATAREFERENCE, BadDataReference);
			GENERATE_EXCEPTION(D3DXFERR_NOMOREOBJECTS, NoMoreObjects);
			GENERATE_EXCEPTION(D3DXFERR_NOMOREDATA, NoMoreData);
			GENERATE_EXCEPTION(D3DXFERR_BADCACHEFILE, BadCacheFile);

			GENERATE_EXCEPTION(E_OUTOFMEMORY, OutOfMemory);

			default:
				ex = gcnew GraphicsException( E_FAIL, "A graphics exception occurred." );
			}

			ex->HResult = hr;
			return ex;
		}

		inline void GraphicsException::CheckHResult( HRESULT hr )
		{
			if( DirectXException::EnableExceptions && FAILED(hr) )
				throw GraphicsException::GetExceptionFromHResult( (hr) );

			SetLastError( hr );
		}
	}
}
