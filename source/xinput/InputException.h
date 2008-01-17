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

#include "../Exceptions.h"
#include "../Configuration.h"

namespace SlimDX
{
	namespace XInput
	{
		[Serializable]
		public ref class InputException : public DirectXException
		{
		private:
			static InputException()
			{
				LastError =	ERROR_SUCCESS;
			}

		protected:
			InputException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

		public:
			InputException() : DirectXException(E_FAIL, "An XInput exception occurred.")
			{ }

			InputException(String^ message) : DirectXException(E_FAIL, message)
			{ }

			InputException( int errorCode, String^ message ) : DirectXException( errorCode, message )
			{ }

			InputException( String^ message, Exception^ innerException ) : DirectXException( message, innerException )
			{ }

			static property int LastError;

		internal:
			static void CheckResult(UInt32 result)
			{
				if(result != ERROR_SUCCESS && result != ERROR_EMPTY)
				{
					if( Configuration::EnableExceptions )
					{
						if(result == ERROR_DEVICE_NOT_CONNECTED)
							throw gcnew InputException(ERROR_DEVICE_NOT_CONNECTED, "Device not connected. If this is a wireless device it may not yet be powered on.");
						else
							throw gcnew InputException(result, "An XInput exception occured.");
					}
					else
						SetLastError(result);
				}

				LastError = result;
			}
		};
	}
}