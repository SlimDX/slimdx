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
using namespace System::Runtime::InteropServices;

#include "../DirectXObject.h"

namespace SlimDX {
	namespace XInput {
		[StructLayout(LayoutKind::Sequential)]
		public value class Vibration {
		public:
			UInt16 LeftMotorSpeed;
			UInt16 RightMotorSpeed;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class GamePad {
		public:
			UInt16 wButtons;
			Byte bLeftTrigger;
			Byte bRightTrigger;
			Int16 sThumbLX;
			Int16 sThumbLY;
			Int16 sThumbRX;
			Int16 sThumbRY;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class KeyStroke {
		public:
			UInt16 VirtualKey;
			Char Unicode;
			UInt16 Flags;
			Byte UserIndex;
			Byte HidCode;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class State {
		public:
			UInt32 PacketNumber;
			GamePad Gamepad;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class Capabilities {
		public:
			Byte Type;
			Byte SubType;
			UInt16 Flags;
			GamePad Gamepad;
			Vibration Vibration;
		};

		public enum class Flags : Int32 {
			GamePad = XINPUT_FLAG_GAMEPAD
		};

		public ref class Controller {
		public:
			Controller();
			void GetState(UInt32 userIndex, State% currentState);
			void SetState(UInt32 userIndex, Vibration% vibration);
			void GetCapabilities(UInt32 userIndex, Flags flag, Capabilities% capabilities);
			void GetDirectSoundAudioDeviceGuids(UInt32 userIndex, Guid% soundRenderGuid, Guid% soundCaptureGuid);
			void GetKeystroke(UInt32 userIndex, Flags flag, KeyStroke% keystroke);
		};
	}
}