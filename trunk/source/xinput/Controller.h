/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include "../Result.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace XInput
	{
		public ref class Controller
		{
		private:
			System::UInt32 m_UserIndex;
			
			static int ConvertError( int errorCode );
			
		public:
			/// <summary>
			/// Gets a value indicating whether or not the controller is connected.
			/// </summary>
			property bool IsConnected
			{
				bool get();
			}
			
			property System::Guid SoundRenderGuid
			{
				System::Guid get();
			}

			property System::Guid SoundCaptureGuid
			{
				System::Guid get();
			}
			
			Controller( UserIndex userIndex );
			
			BatteryInformation GetBatteryInformation( BatteryDeviceType battery );
			Capabilities GetCapabilities( DeviceQueryType device );
			State GetState();
			
			Result GetKeystroke( DeviceQueryType flag, [Out] Keystroke% keystroke );
						
			Result SetVibration( Vibration vibration );

			
			static void SetReporting( bool value );
		};
	}
}