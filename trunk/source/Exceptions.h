#pragma once

using namespace System;
using namespace System::Runtime::Serialization;

namespace SlimDX
{
	public ref class DirectXException : public Exception
	{
	public:
		static property bool EnableExceptions;
		property int ErrorCode;

		static DirectXException()
		{
			EnableExceptions = true;
		}

		DirectXException() : Exception("A DirectX exception occurred.") {
			ErrorCode = E_FAIL;
		}
		DirectXException(String^ message) : Exception(message) {
			ErrorCode = E_FAIL;
		}
		DirectXException( int errorCode, String^ message ) : Exception( message )
		{
			ErrorCode = errorCode;
		}
		DirectXException( String^ message, Exception^ innerException ) : Exception( message, innerException )
		{ }

		DirectXException(SerializationInfo^ info, StreamingContext context) : Exception(info, context)
		{ }
	};

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

		inline GraphicsException^ GraphicsException::GetExceptionFromHResult( HRESULT hr )
		{
			switch( hr )
			{
			case D3DERR_WRONGTEXTUREFORMAT:
				return gcnew WrongTextureFormatException();
			case D3DERR_UNSUPPORTEDCOLOROPERATION:
				return gcnew UnsupportedColorOperationException();
			case D3DERR_UNSUPPORTEDCOLORARG:
				return gcnew UnsupportedColorArgumentException();
			case D3DERR_UNSUPPORTEDALPHAOPERATION:
				return gcnew UnsupportedAlphaOperationException();
			case D3DERR_UNSUPPORTEDALPHAARG:
				return gcnew UnsupportedAlphaArgumentException();
			case D3DERR_TOOMANYOPERATIONS:
				return gcnew TooManyOperationsException();
			case D3DERR_CONFLICTINGTEXTUREFILTER:
				return gcnew ConflictingTextureFilterException();
			case D3DERR_UNSUPPORTEDFACTORVALUE:
				return gcnew UnsupportedFactorValueException();
			case D3DERR_CONFLICTINGTEXTUREPALETTE:
				return gcnew ConflictingTexturePaletteException();
			case D3DERR_DRIVERINTERNALERROR:
				return gcnew DriverInternalErrorException();

			case D3DERR_NOTFOUND:
				return gcnew NotFoundException();
			case D3DERR_MOREDATA:
				return gcnew MoreDataException();
			case D3DERR_DEVICELOST:
				return gcnew DeviceLostException();
			case D3DERR_DEVICENOTRESET:
				return gcnew DeviceNotResetException();
			case D3DERR_NOTAVAILABLE:
				return gcnew NotAvailableException();
			case D3DERR_OUTOFVIDEOMEMORY:
				return gcnew OutOfVideoMemoryException();
			case D3DERR_INVALIDDEVICE:
				return gcnew InvalidDeviceException();
			case D3DERR_INVALIDCALL:
				return gcnew InvalidCallException();
			case D3DERR_DRIVERINVALIDCALL:
				return gcnew DriverInvalidCallException();
			case D3DERR_WASSTILLDRAWING:
				return gcnew WasStillDrawingException();

			default:
				return gcnew GraphicsException( E_FAIL, "A graphics exception occurred." );
			}
		}

		inline void GraphicsException::CheckHResult( HRESULT hr )
		{
			if( DirectXException::EnableExceptions && FAILED(hr) ) {
				GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( (hr) );
				ex->HResult = hr;
				throw ex;
			}

			SetLastError( hr );
		}
	}
}
