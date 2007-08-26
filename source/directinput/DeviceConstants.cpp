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
#include <windows.h>
#include <dinput.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "DirectInput.h"
#include "Device.h"
#include "InputException.h"
#include "DeviceConstants.h"

namespace SlimDX
{
namespace DirectInput
{
	int AnyControl::Button( int button )
	{
		return DIBUTTON_ANY( button );
	}

	int JoystickObjects::Button( int button )
	{
		return DIJOFS_BUTTON( button );
	}

	int JoystickObjects::Slider( int slider )
	{
		return DIJOFS_SLIDER( slider );
	}

	int JoystickObjects::PointOfView( int pov )
	{
		return DIJOFS_POV( pov );
	}

	int DeviceConstantConverter::KeysToDIK( Keys key )
	{
		switch( key )
		{
		case Keys::D0:
			return DIK_0;
			break;

		case Keys::D1:
			return DIK_1;
			break;

		case Keys::D2:
			return DIK_2;
			break;

		case Keys::D3:
			return DIK_3;
			break;

		case Keys::D4:
			return DIK_4;
			break;

		case Keys::D5:
			return DIK_5;
			break;

		case Keys::D6:
			return DIK_6;
			break;

		case Keys::D7:
			return DIK_7;
			break;

		case Keys::D8:
			return DIK_8;
			break;

		case Keys::D9:
			return DIK_9;
			break;

		case Keys::A:
			return DIK_A;
			break;

		case Keys::B:
			return DIK_B;
			break;

		case Keys::C:
			return DIK_C;
			break;

		case Keys::D:
			return DIK_D;
			break;

		case Keys::E:
			return DIK_E;
			break;

		case Keys::F:
			return DIK_F;
			break;

		case Keys::G:
			return DIK_G;
			break;

		case Keys::H:
			return DIK_H;
			break;

		case Keys::I:
			return DIK_I;
			break;

		case Keys::J:
			return DIK_J;
			break;

		case Keys::K:
			return DIK_K;
			break;

		case Keys::L:
			return DIK_L;
			break;

		case Keys::M:
			return DIK_M;
			break;

		case Keys::N:
			return DIK_N;
			break;

		case Keys::O:
			return DIK_O;
			break;

		case Keys::P:
			return DIK_P;
			break;

		case Keys::Q:
			return DIK_Q;
			break;

		case Keys::R:
			return DIK_R;
			break;

		case Keys::S:
			return DIK_S;
			break;

		case Keys::T:
			return DIK_T;
			break;

		case Keys::U:
			return DIK_U;
			break;

		case Keys::V:
			return DIK_V;
			break;

		case Keys::W:
			return DIK_W;
			break;

		case Keys::X:
			return DIK_X;
			break;

		case Keys::Y:
			return DIK_Y;
			break;

		case Keys::Z:
			return DIK_Z;
			break;

		case Keys::AbntC1:
			return DIK_ABNT_C1;
			break;

		case Keys::AbntC2:
			return DIK_ABNT_C2;
			break;

		case Keys::Apostrophe:
			return DIK_APOSTROPHE;
			break;

		case Keys::Applications:
			return DIK_APPS;
			break;

		case Keys::At:
			return DIK_AT;
			break;

		case Keys::Ax:
			return DIK_AX;
			break;

		case Keys::BackSpace:
			return DIK_BACKSPACE;
			break;

		case Keys::BackSlash:
			return DIK_BACKSLASH;
			break;

		case Keys::Calculator:
			return DIK_CALCULATOR;
			break;

		case Keys::CapsLock:
			return DIK_CAPSLOCK;
			break;

		case Keys::Colon:
			return DIK_COLON;
			break;

		case Keys::Comma:
			return DIK_COMMA;
			break;

		case Keys::Convert:
			return DIK_CONVERT;
			break;

		case Keys::Delete:
			return DIK_DELETE;
			break;

		case Keys::DownArrow:
			return DIK_DOWNARROW;
			break;

		case Keys::End:
			return DIK_END;
			break;

		case Keys::Equals:
			return DIK_EQUALS;
			break;

		case Keys::Escape:
			return DIK_ESCAPE;
			break;

		case Keys::F1:
			return DIK_F1;
			break;

		case Keys::F2:
			return DIK_F2;
			break;

		case Keys::F3:
			return DIK_F3;
			break;

		case Keys::F4:
			return DIK_F4;
			break;

		case Keys::F5:
			return DIK_F5;
			break;

		case Keys::F6:
			return DIK_F6;
			break;

		case Keys::F7:
			return DIK_F7;
			break;

		case Keys::F8:
			return DIK_F8;
			break;

		case Keys::F9:
			return DIK_F9;
			break;

		case Keys::F10:
			return DIK_F10;
			break;

		case Keys::F11:
			return DIK_F11;
			break;

		case Keys::F12:
			return DIK_F12;
			break;

		case Keys::F13:
			return DIK_F13;
			break;

		case Keys::F14:
			return DIK_F14;
			break;

		case Keys::F15:
			return DIK_F15;
			break;

		case Keys::Grave:
			return DIK_GRAVE;
			break;

		case Keys::Home:
			return DIK_HOME;
			break;

		case Keys::Insert:
			return DIK_INSERT;
			break;

		case Keys::Kana:
			return DIK_KANA;
			break;

		case Keys::Kanji:
			return DIK_KANJI;
			break;

		case Keys::LeftBracket:
			return DIK_LBRACKET;
			break;

		case Keys::LeftControl:
			return DIK_LCONTROL;
			break;

		case Keys::LeftArrow:
			return DIK_LEFTARROW;
			break;

		case Keys::LeftAlt:
			return DIK_LMENU;
			break;

		case Keys::LeftShift:
			return DIK_LSHIFT;
			break;

		case Keys::LeftWindowsKey:
			return DIK_LWIN;
			break;

		case Keys::Mail:
			return DIK_MAIL;
			break;

		case Keys::MediaSelect:
			return DIK_MEDIASELECT;
			break;

		case Keys::MediaStop:
			return DIK_MEDIASTOP;
			break;

		case Keys::Minus:
			return DIK_MINUS;
			break;

		case Keys::Mute:
			return DIK_MUTE;
			break;

		case Keys::MyComputer:
			return DIK_MYCOMPUTER;
			break;

		case Keys::NextTrack:
			return DIK_NEXTTRACK;
			break;

		case Keys::NoConvert:
			return DIK_NOCONVERT;
			break;

		case Keys::NumLock:
			return DIK_NUMLOCK;
			break;

		case Keys::NumPad0:
			return DIK_NUMPAD0;
			break;

		case Keys::NumPad1:
			return DIK_NUMPAD1;
			break;

		case Keys::NumPad2:
			return DIK_NUMPAD2;
			break;

		case Keys::NumPad3:
			return DIK_NUMPAD3;
			break;

		case Keys::NumPad4:
			return DIK_NUMPAD4;
			break;

		case Keys::NumPad5:
			return DIK_NUMPAD5;
			break;

		case Keys::NumPad6:
			return DIK_NUMPAD6;
			break;

		case Keys::NumPad7:
			return DIK_NUMPAD7;
			break;

		case Keys::NumPad8:
			return DIK_NUMPAD8;
			break;

		case Keys::NumPad9:
			return DIK_NUMPAD9;
			break;

		case Keys::NumPadComma:
			return DIK_NUMPADCOMMA;
			break;

		case Keys::NumPadEnter:
			return DIK_NUMPADENTER;
			break;

		case Keys::NumPadMinus:
			return DIK_NUMPADMINUS;
			break;

		case Keys::NumPadPeriod:
			return DIK_NUMPADPERIOD;
			break;

		case Keys::NumPadPlus:
			return DIK_NUMPADPLUS;
			break;

		case Keys::NumPadSlash:
			return DIK_NUMPADSLASH;
			break;

		case Keys::NumPadStar:
			return DIK_NUMPADSTAR;
			break;

		case Keys::OEM102:
			return DIK_OEM_102;
			break;

		case Keys::PageDown:
			return DIK_NEXT;
			break;

		case Keys::PageUp:
			return DIK_PRIOR;
			break;

		case Keys::Pause:
			return DIK_PAUSE;
			break;

		case Keys::Period:
			return DIK_PERIOD;
			break;

		case Keys::PlayPause:
			return DIK_PLAYPAUSE;
			break;

		case Keys::Power:
			return DIK_POWER;
			break;

		case Keys::PreviousTrack:
			return DIK_PREVTRACK;
			break;

		case Keys::RightBracket:
			return DIK_RBRACKET;
			break;

		case Keys::RightControl:
			return DIK_RCONTROL;
			break;

		case Keys::Return:
			return DIK_RETURN;
			break;

		case Keys::RightArrow:
			return DIK_RIGHTARROW;
			break;

		case Keys::RightAlt:
			return DIK_RMENU;
			break;

		case Keys::RightShift:
			return DIK_RSHIFT;
			break;

		case Keys::RightWindowsKey:
			return DIK_RWIN;
			break;

		case Keys::ScrollLock:
			return DIK_SCROLL;
			break;

		case Keys::Semicolon:
			return DIK_SEMICOLON;
			break;

		case Keys::Slash:
			return DIK_SLASH;
			break;

		case Keys::Sleep:
			return DIK_SLEEP;
			break;

		case Keys::Space:
			return DIK_SPACE;
			break;

		case Keys::Stop:
			return DIK_STOP;
			break;

		case Keys::PrintScreen:
			return DIK_SYSRQ;
			break;

		case Keys::Tab:
			return DIK_TAB;
			break;

		case Keys::Underline:
			return DIK_UNDERLINE;
			break;

		case Keys::Unlabeled:
			return DIK_UNLABELED;
			break;

		case Keys::UpArrow:
			return DIK_UPARROW;
			break;

		case Keys::VolumeDown:
			return DIK_VOLUMEDOWN;
			break;

		case Keys::VolumeUp:
			return DIK_VOLUMEUP;
			break;

		case Keys::Wake:
			return DIK_WAKE;
			break;

		case Keys::WebBack:
			return DIK_WEBBACK;
			break;

		case Keys::WebFavorites:
			return DIK_WEBFAVORITES;
			break;

		case Keys::WebForward:
			return DIK_WEBFORWARD;
			break;

		case Keys::WebHome:
			return DIK_WEBHOME;
			break;

		case Keys::WebSearch:
			return DIK_WEBSEARCH;
			break;
			
		case Keys::WebStop:
			return DIK_WEBSTOP;
			break;

		case Keys::Yen:
			return DIK_YEN;
			break;
		}

		throw gcnew ArgumentException( "The specified key does not exist." );
	}

	int DeviceConstantConverter::KeysToDIKEYBOARD( Keys key )
	{
		switch( key )
		{
		case Keys::D0:
			return DIKEYBOARD_0;
			break;

		case Keys::D1:
			return DIKEYBOARD_1;
			break;

		case Keys::D2:
			return DIKEYBOARD_2;
			break;

		case Keys::D3:
			return DIKEYBOARD_3;
			break;

		case Keys::D4:
			return DIKEYBOARD_4;
			break;

		case Keys::D5:
			return DIKEYBOARD_5;
			break;

		case Keys::D6:
			return DIKEYBOARD_6;
			break;

		case Keys::D7:
			return DIKEYBOARD_7;
			break;

		case Keys::D8:
			return DIKEYBOARD_8;
			break;

		case Keys::D9:
			return DIKEYBOARD_9;
			break;

		case Keys::A:
			return DIKEYBOARD_A;
			break;

		case Keys::B:
			return DIKEYBOARD_B;
			break;

		case Keys::C:
			return DIKEYBOARD_C;
			break;

		case Keys::D:
			return DIKEYBOARD_D;
			break;

		case Keys::E:
			return DIKEYBOARD_E;
			break;

		case Keys::F:
			return DIKEYBOARD_F;
			break;

		case Keys::G:
			return DIKEYBOARD_G;
			break;

		case Keys::H:
			return DIKEYBOARD_H;
			break;

		case Keys::I:
			return DIKEYBOARD_I;
			break;

		case Keys::J:
			return DIKEYBOARD_J;
			break;

		case Keys::K:
			return DIKEYBOARD_K;
			break;

		case Keys::L:
			return DIKEYBOARD_L;
			break;

		case Keys::M:
			return DIKEYBOARD_M;
			break;

		case Keys::N:
			return DIKEYBOARD_N;
			break;

		case Keys::O:
			return DIKEYBOARD_O;
			break;

		case Keys::P:
			return DIKEYBOARD_P;
			break;

		case Keys::Q:
			return DIKEYBOARD_Q;
			break;

		case Keys::R:
			return DIKEYBOARD_R;
			break;

		case Keys::S:
			return DIKEYBOARD_S;
			break;

		case Keys::T:
			return DIKEYBOARD_T;
			break;

		case Keys::U:
			return DIKEYBOARD_U;
			break;

		case Keys::V:
			return DIKEYBOARD_V;
			break;

		case Keys::W:
			return DIKEYBOARD_W;
			break;

		case Keys::X:
			return DIKEYBOARD_X;
			break;

		case Keys::Y:
			return DIKEYBOARD_Y;
			break;

		case Keys::Z:
			return DIKEYBOARD_Z;
			break;

		case Keys::AbntC1:
			return DIKEYBOARD_ABNT_C1;
			break;

		case Keys::AbntC2:
			return DIKEYBOARD_ABNT_C2;
			break;

		case Keys::Apostrophe:
			return DIKEYBOARD_APOSTROPHE;
			break;

		case Keys::Applications:
			return DIKEYBOARD_APPS;
			break;

		case Keys::At:
			return DIKEYBOARD_AT;
			break;

		case Keys::Ax:
			return DIKEYBOARD_AX;
			break;

		case Keys::BackSpace:
			return DIKEYBOARD_BACK;
			break;

		case Keys::BackSlash:
			return DIKEYBOARD_BACKSLASH;
			break;

		case Keys::Calculator:
			return DIKEYBOARD_CALCULATOR;
			break;

		case Keys::CapsLock:
			return DIKEYBOARD_CAPITAL;
			break;

		case Keys::Colon:
			return DIKEYBOARD_COLON;
			break;

		case Keys::Comma:
			return DIKEYBOARD_COMMA;
			break;

		case Keys::Convert:
			return DIKEYBOARD_CONVERT;
			break;

		case Keys::Delete:
			return DIKEYBOARD_DELETE;
			break;

		case Keys::DownArrow:
			return DIKEYBOARD_DOWN;
			break;

		case Keys::End:
			return DIKEYBOARD_END;
			break;

		case Keys::Equals:
			return DIKEYBOARD_EQUALS;
			break;

		case Keys::Escape:
			return DIKEYBOARD_ESCAPE;
			break;

		case Keys::F1:
			return DIKEYBOARD_F1;
			break;

		case Keys::F2:
			return DIKEYBOARD_F2;
			break;

		case Keys::F3:
			return DIKEYBOARD_F3;
			break;

		case Keys::F4:
			return DIKEYBOARD_F4;
			break;

		case Keys::F5:
			return DIKEYBOARD_F5;
			break;

		case Keys::F6:
			return DIKEYBOARD_F6;
			break;

		case Keys::F7:
			return DIKEYBOARD_F7;
			break;

		case Keys::F8:
			return DIKEYBOARD_F8;
			break;

		case Keys::F9:
			return DIKEYBOARD_F9;
			break;

		case Keys::F10:
			return DIKEYBOARD_F10;
			break;

		case Keys::F11:
			return DIKEYBOARD_F11;
			break;

		case Keys::F12:
			return DIKEYBOARD_F12;
			break;

		case Keys::F13:
			return DIKEYBOARD_F13;
			break;

		case Keys::F14:
			return DIKEYBOARD_F14;
			break;

		case Keys::F15:
			return DIKEYBOARD_F15;
			break;

		case Keys::Grave:
			return DIKEYBOARD_GRAVE;
			break;

		case Keys::Home:
			return DIKEYBOARD_HOME;
			break;

		case Keys::Insert:
			return DIKEYBOARD_INSERT;
			break;

		case Keys::Kana:
			return DIKEYBOARD_KANA;
			break;

		case Keys::Kanji:
			return DIKEYBOARD_KANJI;
			break;

		case Keys::LeftBracket:
			return DIKEYBOARD_LBRACKET;
			break;

		case Keys::LeftControl:
			return DIKEYBOARD_LCONTROL;
			break;

		case Keys::LeftArrow:
			return DIKEYBOARD_LEFT;
			break;

		case Keys::LeftAlt:
			return DIKEYBOARD_LMENU;
			break;

		case Keys::LeftShift:
			return DIKEYBOARD_LSHIFT;
			break;

		case Keys::LeftWindowsKey:
			return DIKEYBOARD_LWIN;
			break;

		case Keys::Mail:
			return DIKEYBOARD_MAIL;
			break;

		case Keys::MediaSelect:
			return DIKEYBOARD_MEDIASELECT;
			break;

		case Keys::MediaStop:
			return DIKEYBOARD_MEDIASTOP;
			break;

		case Keys::Minus:
			return DIKEYBOARD_MINUS;
			break;

		case Keys::Mute:
			return DIKEYBOARD_MUTE;
			break;

		case Keys::MyComputer:
			return DIKEYBOARD_MYCOMPUTER;
			break;

		case Keys::NextTrack:
			return DIKEYBOARD_NEXTTRACK;
			break;

		case Keys::NoConvert:
			return DIKEYBOARD_NOCONVERT;
			break;

		case Keys::NumLock:
			return DIKEYBOARD_NUMLOCK;
			break;

		case Keys::NumPad0:
			return DIKEYBOARD_NUMPAD0;
			break;

		case Keys::NumPad1:
			return DIKEYBOARD_NUMPAD1;
			break;

		case Keys::NumPad2:
			return DIKEYBOARD_NUMPAD2;
			break;

		case Keys::NumPad3:
			return DIKEYBOARD_NUMPAD3;
			break;

		case Keys::NumPad4:
			return DIKEYBOARD_NUMPAD4;
			break;

		case Keys::NumPad5:
			return DIKEYBOARD_NUMPAD5;
			break;

		case Keys::NumPad6:
			return DIKEYBOARD_NUMPAD6;
			break;

		case Keys::NumPad7:
			return DIKEYBOARD_NUMPAD7;
			break;

		case Keys::NumPad8:
			return DIKEYBOARD_NUMPAD8;
			break;

		case Keys::NumPad9:
			return DIKEYBOARD_NUMPAD9;
			break;

		case Keys::NumPadComma:
			return DIKEYBOARD_NUMPADCOMMA;
			break;

		case Keys::NumPadEnter:
			return DIKEYBOARD_NUMPADENTER;
			break;

		case Keys::NumPadMinus:
			return DIKEYBOARD_SUBTRACT;
			break;

		case Keys::NumPadPeriod:
			return DIKEYBOARD_DECIMAL;
			break;

		case Keys::NumPadPlus:
			return DIKEYBOARD_ADD;
			break;

		case Keys::NumPadSlash:
			return DIKEYBOARD_DIVIDE;
			break;

		case Keys::NumPadStar:
			return DIKEYBOARD_MULTIPLY;
			break;

		case Keys::OEM102:
			return DIKEYBOARD_OEM_102;
			break;

		case Keys::PageDown:
			return DIKEYBOARD_NEXT;
			break;

		case Keys::PageUp:
			return DIKEYBOARD_PRIOR;
			break;

		case Keys::Pause:
			return DIKEYBOARD_PAUSE;
			break;

		case Keys::Period:
			return DIKEYBOARD_PERIOD;
			break;

		case Keys::PlayPause:
			return DIKEYBOARD_PLAYPAUSE;
			break;

		case Keys::Power:
			return DIKEYBOARD_POWER;
			break;

		case Keys::PreviousTrack:
			return DIKEYBOARD_PREVTRACK;
			break;

		case Keys::RightBracket:
			return DIKEYBOARD_RBRACKET;
			break;

		case Keys::RightControl:
			return DIKEYBOARD_RCONTROL;
			break;

		case Keys::Return:
			return DIKEYBOARD_RETURN;
			break;

		case Keys::RightArrow:
			return DIKEYBOARD_RIGHT;
			break;

		case Keys::RightAlt:
			return DIKEYBOARD_RMENU;
			break;

		case Keys::RightShift:
			return DIKEYBOARD_RSHIFT;
			break;

		case Keys::RightWindowsKey:
			return DIKEYBOARD_RWIN;
			break;

		case Keys::ScrollLock:
			return DIKEYBOARD_SCROLL;
			break;

		case Keys::Semicolon:
			return DIKEYBOARD_SEMICOLON;
			break;

		case Keys::Slash:
			return DIKEYBOARD_SLASH;
			break;

		case Keys::Sleep:
			return DIKEYBOARD_SLEEP;
			break;

		case Keys::Space:
			return DIKEYBOARD_SPACE;
			break;

		case Keys::Stop:
			return DIKEYBOARD_STOP;
			break;

		case Keys::PrintScreen:
			return DIKEYBOARD_SYSRQ;
			break;

		case Keys::Tab:
			return DIKEYBOARD_TAB;
			break;

		case Keys::Underline:
			return DIKEYBOARD_UNDERLINE;
			break;

		case Keys::Unlabeled:
			return DIKEYBOARD_UNLABELED;
			break;

		case Keys::UpArrow:
			return DIKEYBOARD_UP;
			break;

		case Keys::VolumeDown:
			return DIKEYBOARD_VOLUMEDOWN;
			break;

		case Keys::VolumeUp:
			return DIKEYBOARD_VOLUMEUP;
			break;

		case Keys::Wake:
			return DIKEYBOARD_WAKE;
			break;

		case Keys::WebBack:
			return DIKEYBOARD_WEBBACK;
			break;

		case Keys::WebFavorites:
			return DIKEYBOARD_WEBFAVORITES;
			break;

		case Keys::WebForward:
			return DIKEYBOARD_WEBFORWARD;
			break;

		case Keys::WebHome:
			return DIKEYBOARD_WEBHOME;
			break;

		case Keys::WebSearch:
			return DIKEYBOARD_WEBSEARCH;
			break;
			
		case Keys::WebStop:
			return DIKEYBOARD_WEBSTOP;
			break;

		case Keys::Yen:
			return DIKEYBOARD_YEN;
			break;
		}

		throw gcnew ArgumentException( "The specified key does not exist." );
	}

	int DeviceConstantConverter::MouseToDIMOFS( MouseObjects mouse )
	{
		switch( mouse )
		{
		case MouseObjects::Button1:
			return DIMOFS_BUTTON0;
			break;

		case MouseObjects::Button2:
			return DIMOFS_BUTTON1;
			break;

		case MouseObjects::Button3:
			return DIMOFS_BUTTON2;
			break;

		case MouseObjects::Button4:
			return DIMOFS_BUTTON3;
			break;

		case MouseObjects::Button5:
			return DIMOFS_BUTTON4;
			break;

		case MouseObjects::Button6:
			return DIMOFS_BUTTON5;
			break;

		case MouseObjects::Button7:
			return DIMOFS_BUTTON6;
			break;

		case MouseObjects::Button8:
			return DIMOFS_BUTTON7;
			break;

		case MouseObjects::XAxis:
			return DIMOFS_X;
			break;

		case MouseObjects::YAxis:
			return DIMOFS_Y;
			break;

		case MouseObjects::ZAxis:
			return DIMOFS_Z;
			break;
		}

		throw gcnew ArgumentException( "The specified mouse object does not exist." );
	}

	int DeviceConstantConverter::MouseToDIMOUSE( MouseObjects mouse )
	{
		switch( mouse )
		{
		case MouseObjects::Button1:
			return DIMOUSE_BUTTON0;
			break;

		case MouseObjects::Button2:
			return DIMOUSE_BUTTON1;
			break;

		case MouseObjects::Button3:
			return DIMOUSE_BUTTON2;
			break;

		case MouseObjects::Button4:
			return DIMOUSE_BUTTON3;
			break;

		case MouseObjects::Button5:
			return DIMOUSE_BUTTON4;
			break;

		case MouseObjects::Button6:
			return DIMOUSE_BUTTON5;
			break;

		case MouseObjects::Button7:
			return DIMOUSE_BUTTON6;
			break;

		case MouseObjects::Button8:
			return DIMOUSE_BUTTON7;
			break;

		case MouseObjects::XAxis:
			return DIMOUSE_XAXIS;
			break;

		case MouseObjects::YAxis:
			return DIMOUSE_YAXIS;
			break;

		case MouseObjects::ZAxis:
			return DIMOUSE_WHEEL;
			break;
		}

		throw gcnew ArgumentException( "The specified mouse object does not exist." );
	}
}
}