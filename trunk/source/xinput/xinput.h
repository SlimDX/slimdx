#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

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
