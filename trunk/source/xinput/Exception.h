#pragma once

#include "../Exceptions.h"

namespace SlimDX {
	namespace XInput {
		public ref class XInputException : public DirectXException
		{
		public:
			XInputException() : DirectXException(E_FAIL, "A XInput exception occurred.")
			{ }
			XInputException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			XInputException( int errorCode, String^ message ) : DirectXException( errorCode, message )
			{ }
			XInputException( String^ message, Exception^ innerException ) : DirectXException( message, innerException )
			{ }
			XInputException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }
		internal:
			static void CheckResult(UInt32 result) {
				if(result != ERROR_SUCCESS && result != ERROR_EMPTY) {
					if(DirectXException::EnableExceptions) {
						if(result == ERROR_DEVICE_NOT_CONNECTED)
							throw gcnew XInputException(ERROR_DEVICE_NOT_CONNECTED, "Device not connected. If this is a wireless device it may not yet be powered on.");
						else
							throw gcnew XInputException(result, "A XInput exception occured.");
					} else
						SetLastError(result);
				}
			}
		};
	}
}