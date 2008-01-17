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
#include <dxerr.h>

namespace SlimDX
{
	namespace Direct3D9
	{
		[Serializable]
		public ref class GraphicsException : public SlimDX::DirectXException
		{
		private:
			static GraphicsException()
			{
				LastError = S_OK;

				EnableForDeviceState = true;
				EnableForStillDrawing = true;
			}

		protected:
			GraphicsException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }
			
		public:

			GraphicsException() : DirectXException(E_FAIL, "A Direct3D exception occurred.")
			{ }
			GraphicsException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			GraphicsException(int errorCode ) : DirectXException( errorCode, gcnew String( DXGetErrorDescription( errorCode ) ) )
			{ }
			GraphicsException(int errorCode, String^ message) : DirectXException( errorCode, message )
			{ }
			GraphicsException(String^ message, Exception^ innerException) : DirectXException( message, innerException )
			{ }

			static property int LastError;

			static property bool EnableForDeviceState;
			static property bool EnableForStillDrawing;

			static GraphicsException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue );
		};

#define DEFINE_GRAPHICS_EXCEPTION( ExName, ErrorCode ) \
	[Serializable] \
	public ref class ExName ## Exception : public GraphicsException \
	{ \
	protected: \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : GraphicsException(info, context) { }\
	public: \
		ExName ## Exception () : GraphicsException( ErrorCode ) { } \
		ExName ## Exception ( String^ message ) : GraphicsException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : GraphicsException( message, innerException ) { } \
	}

#define DEFINE_CUSTOM_GRAPHICS_EXCEPTION( ExName, ErrorCode, Message ) \
	[Serializable] \
	public ref class ExName ## Exception : public GraphicsException \
	{ \
	protected: \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : GraphicsException(info, context) { }\
	public: \
		ExName ## Exception () : GraphicsException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : GraphicsException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : GraphicsException( message, innerException ) { } \
	}

		DEFINE_GRAPHICS_EXCEPTION( WrongTextureFormat, D3DERR_WRONGTEXTUREFORMAT );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedColorOperation, D3DERR_UNSUPPORTEDCOLOROPERATION );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedColorArgument, D3DERR_UNSUPPORTEDCOLORARG );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedAlphaOperation, D3DERR_UNSUPPORTEDALPHAOPERATION );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedAlphaArgument, D3DERR_UNSUPPORTEDALPHAARG );
		DEFINE_GRAPHICS_EXCEPTION( TooManyOperations, D3DERR_TOOMANYOPERATIONS );
		DEFINE_GRAPHICS_EXCEPTION( ConflictingTextureFilter, D3DERR_CONFLICTINGTEXTUREFILTER );
		DEFINE_GRAPHICS_EXCEPTION( UnsupportedFactorValue, D3DERR_UNSUPPORTEDFACTORVALUE );
		DEFINE_GRAPHICS_EXCEPTION( ConflictingTexturePalette, D3DERR_CONFLICTINGTEXTUREPALETTE );
		DEFINE_GRAPHICS_EXCEPTION( DriverInternalError, D3DERR_DRIVERINTERNALERROR );
		DEFINE_GRAPHICS_EXCEPTION( NotFound, D3DERR_NOTFOUND );
		DEFINE_GRAPHICS_EXCEPTION( MoreData, D3DERR_MOREDATA );
		DEFINE_GRAPHICS_EXCEPTION( DeviceLost, D3DERR_DEVICELOST );
		DEFINE_GRAPHICS_EXCEPTION( DeviceNotReset, D3DERR_DEVICENOTRESET );
		DEFINE_GRAPHICS_EXCEPTION( NotAvailable, D3DERR_NOTAVAILABLE );
		DEFINE_GRAPHICS_EXCEPTION( OutOfVideoMemory, D3DERR_OUTOFVIDEOMEMORY );
		DEFINE_GRAPHICS_EXCEPTION( InvalidDevice, D3DERR_INVALIDDEVICE );
		DEFINE_GRAPHICS_EXCEPTION( InvalidCall, D3DERR_INVALIDCALL );
		DEFINE_GRAPHICS_EXCEPTION( DriverInvalidCall, D3DERR_DRIVERINVALIDCALL );
		DEFINE_GRAPHICS_EXCEPTION( WasStillDrawing, D3DERR_WASSTILLDRAWING );

		DEFINE_GRAPHICS_EXCEPTION( CannotModifyIndexBuffer, D3DXERR_CANNOTMODIFYINDEXBUFFER );
		DEFINE_GRAPHICS_EXCEPTION( InvalidMesh, D3DXERR_INVALIDMESH );
		DEFINE_GRAPHICS_EXCEPTION( CannotAttributeSort, D3DXERR_CANNOTATTRSORT );
		DEFINE_GRAPHICS_EXCEPTION( SkinningNotSupported, D3DXERR_SKINNINGNOTSUPPORTED );
		DEFINE_GRAPHICS_EXCEPTION( TooManyInfluences, D3DXERR_TOOMANYINFLUENCES );
		DEFINE_GRAPHICS_EXCEPTION( InvalidData, D3DXERR_INVALIDDATA );
		DEFINE_GRAPHICS_EXCEPTION( LoadedMeshHasNoData, D3DXERR_LOADEDMESHASNODATA );
		DEFINE_GRAPHICS_EXCEPTION( DuplicateNamedFragment, D3DXERR_DUPLICATENAMEDFRAGMENT );
		DEFINE_GRAPHICS_EXCEPTION( CannotRemoveLastItem, D3DXERR_CANNOTREMOVELASTITEM );

		DEFINE_GRAPHICS_EXCEPTION( BadObject, D3DXFERR_BADOBJECT );
		DEFINE_GRAPHICS_EXCEPTION( BadValue, D3DXFERR_BADVALUE );
		DEFINE_GRAPHICS_EXCEPTION( BadType, D3DXFERR_BADTYPE );
		DEFINE_GRAPHICS_EXCEPTION( XNotFound, D3DXFERR_NOTFOUND );
		DEFINE_GRAPHICS_EXCEPTION( NotDoneYet, D3DXFERR_NOTDONEYET );
		DEFINE_GRAPHICS_EXCEPTION( FileNotFound, D3DXFERR_FILENOTFOUND );
		DEFINE_GRAPHICS_EXCEPTION( ResourceNotFound, D3DXFERR_RESOURCENOTFOUND );
		DEFINE_GRAPHICS_EXCEPTION( BadResource, D3DXFERR_BADRESOURCE );
		DEFINE_GRAPHICS_EXCEPTION( BadFileType, D3DXFERR_BADFILETYPE );
		DEFINE_GRAPHICS_EXCEPTION( BadFileVersion, D3DXFERR_BADFILEVERSION );
		DEFINE_GRAPHICS_EXCEPTION( BadFileFloatSize, D3DXFERR_BADFILEFLOATSIZE );
		DEFINE_GRAPHICS_EXCEPTION( BadFile, D3DXFERR_BADFILE );
		DEFINE_GRAPHICS_EXCEPTION( ParseError, D3DXFERR_PARSEERROR );
		DEFINE_GRAPHICS_EXCEPTION( BadArraySize, D3DXFERR_BADARRAYSIZE );
		DEFINE_GRAPHICS_EXCEPTION( BadDataReference, D3DXFERR_BADDATAREFERENCE );
		DEFINE_GRAPHICS_EXCEPTION( NoMoreObjects, D3DXFERR_NOMOREOBJECTS );
		DEFINE_GRAPHICS_EXCEPTION( NoMoreData, D3DXFERR_NOMOREDATA );
		DEFINE_GRAPHICS_EXCEPTION( BadCacheFile, D3DXFERR_BADCACHEFILE );

		DEFINE_CUSTOM_GRAPHICS_EXCEPTION( OutOfMemory, E_OUTOFMEMORY, "Out of memory." );

		DEFINE_CUSTOM_GRAPHICS_EXCEPTION( Direct3D9NotFound, E_FAIL, "Direct3D 9 not found." );
		DEFINE_CUSTOM_GRAPHICS_EXCEPTION( Direct3DX9NotFound, E_FAIL, "Direct3DX 9 not found." );
		DEFINE_CUSTOM_GRAPHICS_EXCEPTION( Direct3DNotInitialized, E_FAIL, "Direct3D not initialized." );

		inline GraphicsException^ GraphicsException::GetExceptionFromHResult( HRESULT hr )
		{
			GraphicsException^ ex;

#			define GENERATE_EXCEPTION(errCase, type) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

#			define GENERATE_EXCEPTION_IF(errCase, type, condition) \
			case errCase:\
				if(condition)\
					ex = gcnew type ## Exception ();\
				else\
					return nullptr;\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION_IF(D3DERR_DEVICELOST, DeviceLost, GraphicsException::EnableForDeviceState);
			GENERATE_EXCEPTION_IF(D3DERR_DEVICENOTRESET, DeviceNotReset, GraphicsException::EnableForDeviceState);
			GENERATE_EXCEPTION_IF(D3DERR_WASSTILLDRAWING, WasStillDrawing, GraphicsException::EnableForStillDrawing);

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
			GENERATE_EXCEPTION(D3DERR_NOTAVAILABLE, NotAvailable);
			GENERATE_EXCEPTION(D3DERR_OUTOFVIDEOMEMORY,OutOfVideoMemory);
			GENERATE_EXCEPTION(D3DERR_INVALIDDEVICE,InvalidDevice);
			GENERATE_EXCEPTION(D3DERR_INVALIDCALL,InvalidCall);
			GENERATE_EXCEPTION(D3DERR_DRIVERINVALIDCALL,DriverInvalidCall);

			GENERATE_EXCEPTION(D3DXERR_CANNOTMODIFYINDEXBUFFER, CannotModifyIndexBuffer);
			GENERATE_EXCEPTION(D3DXERR_INVALIDMESH, InvalidMesh);
			GENERATE_EXCEPTION(D3DXERR_CANNOTATTRSORT, CannotAttributeSort);
			GENERATE_EXCEPTION(D3DXERR_SKINNINGNOTSUPPORTED, SkinningNotSupported);
			GENERATE_EXCEPTION(D3DXERR_TOOMANYINFLUENCES, TooManyInfluences);
			GENERATE_EXCEPTION(D3DXERR_INVALIDDATA, InvalidData);
			GENERATE_EXCEPTION(D3DXERR_LOADEDMESHASNODATA, LoadedMeshHasNoData);
			GENERATE_EXCEPTION(D3DXERR_DUPLICATENAMEDFRAGMENT, DuplicateNamedFragment);
			GENERATE_EXCEPTION(D3DXERR_CANNOTREMOVELASTITEM, CannotRemoveLastItem);

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
				ex = gcnew GraphicsException( "A graphics exception occurred." );
			}

			ex->HResult = hr;
			return ex;
		}

		inline void GraphicsException::CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue )
		{
			GraphicsException::LastError = hr;
			if( Configuration::EnableExceptions && FAILED(hr) )
			{
				GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( (hr) );
				//don't throw if an exception wasn't returned for some reason (e.g. it's part of a disabled subset)
				if( ex != nullptr )
				{
					if( dataKey != nullptr )
						ex->Data->Add( dataKey, dataValue );
					throw ex;
				}
			}
		}

		inline void GraphicsException::CheckHResult( HRESULT hr )
		{
			GraphicsException::CheckHResult( hr, nullptr, nullptr );
		}
	}
}
