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

#include "../ComObject.h"
#include "../Utilities.h"

#include "DirectInput.h"
//#include "DirectInputErrorHandler.h"

#include "Device.h"
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

	int DeviceConstantConverter::KeyToDIK( Key key )
	{
		switch( key )
		{
		case Key::D0:
			return DIK_0;
			break;

		case Key::D1:
			return DIK_1;
			break;

		case Key::D2:
			return DIK_2;
			break;

		case Key::D3:
			return DIK_3;
			break;

		case Key::D4:
			return DIK_4;
			break;

		case Key::D5:
			return DIK_5;
			break;

		case Key::D6:
			return DIK_6;
			break;

		case Key::D7:
			return DIK_7;
			break;

		case Key::D8:
			return DIK_8;
			break;

		case Key::D9:
			return DIK_9;
			break;

		case Key::A:
			return DIK_A;
			break;

		case Key::B:
			return DIK_B;
			break;

		case Key::C:
			return DIK_C;
			break;

		case Key::D:
			return DIK_D;
			break;

		case Key::E:
			return DIK_E;
			break;

		case Key::F:
			return DIK_F;
			break;

		case Key::G:
			return DIK_G;
			break;

		case Key::H:
			return DIK_H;
			break;

		case Key::I:
			return DIK_I;
			break;

		case Key::J:
			return DIK_J;
			break;

		case Key::K:
			return DIK_K;
			break;

		case Key::L:
			return DIK_L;
			break;

		case Key::M:
			return DIK_M;
			break;

		case Key::N:
			return DIK_N;
			break;

		case Key::O:
			return DIK_O;
			break;

		case Key::P:
			return DIK_P;
			break;

		case Key::Q:
			return DIK_Q;
			break;

		case Key::R:
			return DIK_R;
			break;

		case Key::S:
			return DIK_S;
			break;

		case Key::T:
			return DIK_T;
			break;

		case Key::U:
			return DIK_U;
			break;

		case Key::V:
			return DIK_V;
			break;

		case Key::W:
			return DIK_W;
			break;

		case Key::X:
			return DIK_X;
			break;

		case Key::Y:
			return DIK_Y;
			break;

		case Key::Z:
			return DIK_Z;
			break;

		case Key::AbntC1:
			return DIK_ABNT_C1;
			break;

		case Key::AbntC2:
			return DIK_ABNT_C2;
			break;

		case Key::Apostrophe:
			return DIK_APOSTROPHE;
			break;

		case Key::Applications:
			return DIK_APPS;
			break;

		case Key::AT:
			return DIK_AT;
			break;

		case Key::AX:
			return DIK_AX;
			break;

		case Key::Backspace:
			return DIK_BACKSPACE;
			break;

		case Key::Backslash:
			return DIK_BACKSLASH;
			break;

		case Key::Calculator:
			return DIK_CALCULATOR;
			break;

		case Key::CapsLock:
			return DIK_CAPSLOCK;
			break;

		case Key::Colon:
			return DIK_COLON;
			break;

		case Key::Comma:
			return DIK_COMMA;
			break;

		case Key::Convert:
			return DIK_CONVERT;
			break;

		case Key::Delete:
			return DIK_DELETE;
			break;

		case Key::DownArrow:
			return DIK_DOWNARROW;
			break;

		case Key::End:
			return DIK_END;
			break;

		case Key::Equals:
			return DIK_EQUALS;
			break;

		case Key::Escape:
			return DIK_ESCAPE;
			break;

		case Key::F1:
			return DIK_F1;
			break;

		case Key::F2:
			return DIK_F2;
			break;

		case Key::F3:
			return DIK_F3;
			break;

		case Key::F4:
			return DIK_F4;
			break;

		case Key::F5:
			return DIK_F5;
			break;

		case Key::F6:
			return DIK_F6;
			break;

		case Key::F7:
			return DIK_F7;
			break;

		case Key::F8:
			return DIK_F8;
			break;

		case Key::F9:
			return DIK_F9;
			break;

		case Key::F10:
			return DIK_F10;
			break;

		case Key::F11:
			return DIK_F11;
			break;

		case Key::F12:
			return DIK_F12;
			break;

		case Key::F13:
			return DIK_F13;
			break;

		case Key::F14:
			return DIK_F14;
			break;

		case Key::F15:
			return DIK_F15;
			break;

		case Key::Grave:
			return DIK_GRAVE;
			break;

		case Key::Home:
			return DIK_HOME;
			break;

		case Key::Insert:
			return DIK_INSERT;
			break;

		case Key::Kana:
			return DIK_KANA;
			break;

		case Key::Kanji:
			return DIK_KANJI;
			break;

		case Key::LeftBracket:
			return DIK_LBRACKET;
			break;

		case Key::LeftControl:
			return DIK_LCONTROL;
			break;

		case Key::LeftArrow:
			return DIK_LEFTARROW;
			break;

		case Key::LeftAlt:
			return DIK_LMENU;
			break;

		case Key::LeftShift:
			return DIK_LSHIFT;
			break;

		case Key::LeftWindowsKey:
			return DIK_LWIN;
			break;

		case Key::Mail:
			return DIK_MAIL;
			break;

		case Key::MediaSelect:
			return DIK_MEDIASELECT;
			break;

		case Key::MediaStop:
			return DIK_MEDIASTOP;
			break;

		case Key::Minus:
			return DIK_MINUS;
			break;

		case Key::Mute:
			return DIK_MUTE;
			break;

		case Key::MyComputer:
			return DIK_MYCOMPUTER;
			break;

		case Key::NextTrack:
			return DIK_NEXTTRACK;
			break;

		case Key::NoConvert:
			return DIK_NOCONVERT;
			break;

		case Key::NumberLock:
			return DIK_NUMLOCK;
			break;

		case Key::NumberPad0:
			return DIK_NUMPAD0;
			break;

		case Key::NumberPad1:
			return DIK_NUMPAD1;
			break;

		case Key::NumberPad2:
			return DIK_NUMPAD2;
			break;

		case Key::NumberPad3:
			return DIK_NUMPAD3;
			break;

		case Key::NumberPad4:
			return DIK_NUMPAD4;
			break;

		case Key::NumberPad5:
			return DIK_NUMPAD5;
			break;

		case Key::NumberPad6:
			return DIK_NUMPAD6;
			break;

		case Key::NumberPad7:
			return DIK_NUMPAD7;
			break;

		case Key::NumberPad8:
			return DIK_NUMPAD8;
			break;

		case Key::NumberPad9:
			return DIK_NUMPAD9;
			break;

		case Key::NumberPadEquals:
			return DIK_NUMPADEQUALS;

		case Key::WebRefresh:
			return DIK_WEBREFRESH;

		case Key::NumberPadComma:
			return DIK_NUMPADCOMMA;
			break;

		case Key::NumberPadEnter:
			return DIK_NUMPADENTER;
			break;

		case Key::NumberPadMinus:
			return DIK_NUMPADMINUS;
			break;

		case Key::NumberPadPeriod:
			return DIK_NUMPADPERIOD;
			break;

		case Key::NumberPadPlus:
			return DIK_NUMPADPLUS;
			break;

		case Key::NumberPadSlash:
			return DIK_NUMPADSLASH;
			break;

		case Key::NumberPadStar:
			return DIK_NUMPADSTAR;
			break;

		case Key::Oem102:
			return DIK_OEM_102;
			break;

		case Key::PageDown:
			return DIK_NEXT;
			break;

		case Key::PageUp:
			return DIK_PRIOR;
			break;

		case Key::Pause:
			return DIK_PAUSE;
			break;

		case Key::Period:
			return DIK_PERIOD;
			break;

		case Key::PlayPause:
			return DIK_PLAYPAUSE;
			break;

		case Key::Power:
			return DIK_POWER;
			break;

		case Key::PreviousTrack:
			return DIK_PREVTRACK;
			break;

		case Key::RightBracket:
			return DIK_RBRACKET;
			break;

		case Key::RightControl:
			return DIK_RCONTROL;
			break;

		case Key::Return:
			return DIK_RETURN;
			break;

		case Key::RightArrow:
			return DIK_RIGHTARROW;
			break;

		case Key::RightAlt:
			return DIK_RMENU;
			break;

		case Key::RightShift:
			return DIK_RSHIFT;
			break;

		case Key::RightWindowsKey:
			return DIK_RWIN;
			break;

		case Key::ScrollLock:
			return DIK_SCROLL;
			break;

		case Key::Semicolon:
			return DIK_SEMICOLON;
			break;

		case Key::Slash:
			return DIK_SLASH;
			break;

		case Key::Sleep:
			return DIK_SLEEP;
			break;

		case Key::Space:
			return DIK_SPACE;
			break;

		case Key::Stop:
			return DIK_STOP;
			break;

		case Key::PrintScreen:
			return DIK_SYSRQ;
			break;

		case Key::Tab:
			return DIK_TAB;
			break;

		case Key::Underline:
			return DIK_UNDERLINE;
			break;

		case Key::Unlabeled:
			return DIK_UNLABELED;
			break;

		case Key::UpArrow:
			return DIK_UPARROW;
			break;

		case Key::VolumeDown:
			return DIK_VOLUMEDOWN;
			break;

		case Key::VolumeUp:
			return DIK_VOLUMEUP;
			break;

		case Key::Wake:
			return DIK_WAKE;
			break;

		case Key::WebBack:
			return DIK_WEBBACK;
			break;

		case Key::WebFavorites:
			return DIK_WEBFAVORITES;
			break;

		case Key::WebForward:
			return DIK_WEBFORWARD;
			break;

		case Key::WebHome:
			return DIK_WEBHOME;
			break;

		case Key::WebSearch:
			return DIK_WEBSEARCH;
			break;
			
		case Key::WebStop:
			return DIK_WEBSTOP;
			break;

		case Key::Yen:
			return DIK_YEN;
			break;
		}

		throw gcnew ArgumentException( "The specified key does not exist." );
	}

	/* Unused.
	int DeviceConstantConverter::KeyToDIKEYBOARD( Key key )
	{
		switch( key )
		{
		case Key::D0:
			return DIKEYBOARD_0;
			break;

		case Key::D1:
			return DIKEYBOARD_1;
			break;

		case Key::D2:
			return DIKEYBOARD_2;
			break;

		case Key::D3:
			return DIKEYBOARD_3;
			break;

		case Key::D4:
			return DIKEYBOARD_4;
			break;

		case Key::D5:
			return DIKEYBOARD_5;
			break;

		case Key::D6:
			return DIKEYBOARD_6;
			break;

		case Key::D7:
			return DIKEYBOARD_7;
			break;

		case Key::D8:
			return DIKEYBOARD_8;
			break;

		case Key::D9:
			return DIKEYBOARD_9;
			break;

		case Key::A:
			return DIKEYBOARD_A;
			break;

		case Key::B:
			return DIKEYBOARD_B;
			break;

		case Key::C:
			return DIKEYBOARD_C;
			break;

		case Key::D:
			return DIKEYBOARD_D;
			break;

		case Key::E:
			return DIKEYBOARD_E;
			break;

		case Key::F:
			return DIKEYBOARD_F;
			break;

		case Key::G:
			return DIKEYBOARD_G;
			break;

		case Key::H:
			return DIKEYBOARD_H;
			break;

		case Key::I:
			return DIKEYBOARD_I;
			break;

		case Key::J:
			return DIKEYBOARD_J;
			break;

		case Key::K:
			return DIKEYBOARD_K;
			break;

		case Key::L:
			return DIKEYBOARD_L;
			break;

		case Key::M:
			return DIKEYBOARD_M;
			break;

		case Key::N:
			return DIKEYBOARD_N;
			break;

		case Key::O:
			return DIKEYBOARD_O;
			break;

		case Key::P:
			return DIKEYBOARD_P;
			break;

		case Key::Q:
			return DIKEYBOARD_Q;
			break;

		case Key::R:
			return DIKEYBOARD_R;
			break;

		case Key::S:
			return DIKEYBOARD_S;
			break;

		case Key::T:
			return DIKEYBOARD_T;
			break;

		case Key::U:
			return DIKEYBOARD_U;
			break;

		case Key::V:
			return DIKEYBOARD_V;
			break;

		case Key::W:
			return DIKEYBOARD_W;
			break;

		case Key::X:
			return DIKEYBOARD_X;
			break;

		case Key::Y:
			return DIKEYBOARD_Y;
			break;

		case Key::Z:
			return DIKEYBOARD_Z;
			break;

		case Key::AbntC1:
			return DIKEYBOARD_ABNT_C1;
			break;

		case Key::AbntC2:
			return DIKEYBOARD_ABNT_C2;
			break;

		case Key::Apostrophe:
			return DIKEYBOARD_APOSTROPHE;
			break;

		case Key::Applications:
			return DIKEYBOARD_APPS;
			break;

		case Key::AT:
			return DIKEYBOARD_AT;
			break;

		case Key::AX:
			return DIKEYBOARD_AX;
			break;

		case Key::Backspace:
			return DIKEYBOARD_BACK;
			break;

		case Key::Backslash:
			return DIKEYBOARD_BACKSLASH;
			break;

		case Key::Calculator:
			return DIKEYBOARD_CALCULATOR;
			break;

		case Key::CapsLock:
			return DIKEYBOARD_CAPITAL;
			break;

		case Key::Colon:
			return DIKEYBOARD_COLON;
			break;

		case Key::Comma:
			return DIKEYBOARD_COMMA;
			break;

		case Key::Convert:
			return DIKEYBOARD_CONVERT;
			break;

		case Key::Delete:
			return DIKEYBOARD_DELETE;
			break;

		case Key::DownArrow:
			return DIKEYBOARD_DOWN;
			break;

		case Key::End:
			return DIKEYBOARD_END;
			break;

		case Key::Equals:
			return DIKEYBOARD_EQUALS;
			break;

		case Key::Escape:
			return DIKEYBOARD_ESCAPE;
			break;

		case Key::F1:
			return DIKEYBOARD_F1;
			break;

		case Key::F2:
			return DIKEYBOARD_F2;
			break;

		case Key::F3:
			return DIKEYBOARD_F3;
			break;

		case Key::F4:
			return DIKEYBOARD_F4;
			break;

		case Key::F5:
			return DIKEYBOARD_F5;
			break;

		case Key::F6:
			return DIKEYBOARD_F6;
			break;

		case Key::F7:
			return DIKEYBOARD_F7;
			break;

		case Key::F8:
			return DIKEYBOARD_F8;
			break;

		case Key::F9:
			return DIKEYBOARD_F9;
			break;

		case Key::F10:
			return DIKEYBOARD_F10;
			break;

		case Key::F11:
			return DIKEYBOARD_F11;
			break;

		case Key::F12:
			return DIKEYBOARD_F12;
			break;

		case Key::F13:
			return DIKEYBOARD_F13;
			break;

		case Key::F14:
			return DIKEYBOARD_F14;
			break;

		case Key::F15:
			return DIKEYBOARD_F15;
			break;

		case Key::Grave:
			return DIKEYBOARD_GRAVE;
			break;

		case Key::Home:
			return DIKEYBOARD_HOME;
			break;

		case Key::Insert:
			return DIKEYBOARD_INSERT;
			break;

		case Key::Kana:
			return DIKEYBOARD_KANA;
			break;

		case Key::Kanji:
			return DIKEYBOARD_KANJI;
			break;

		case Key::LeftBracket:
			return DIKEYBOARD_LBRACKET;
			break;

		case Key::LeftControl:
			return DIKEYBOARD_LCONTROL;
			break;

		case Key::LeftArrow:
			return DIKEYBOARD_LEFT;
			break;

		case Key::LeftAlt:
			return DIKEYBOARD_LMENU;
			break;

		case Key::LeftShift:
			return DIKEYBOARD_LSHIFT;
			break;

		case Key::LeftWindowsKey:
			return DIKEYBOARD_LWIN;
			break;

		case Key::Mail:
			return DIKEYBOARD_MAIL;
			break;

		case Key::MediaSelect:
			return DIKEYBOARD_MEDIASELECT;
			break;

		case Key::MediaStop:
			return DIKEYBOARD_MEDIASTOP;
			break;

		case Key::Minus:
			return DIKEYBOARD_MINUS;
			break;

		case Key::Mute:
			return DIKEYBOARD_MUTE;
			break;

		case Key::MyComputer:
			return DIKEYBOARD_MYCOMPUTER;
			break;

		case Key::NextTrack:
			return DIKEYBOARD_NEXTTRACK;
			break;

		case Key::NoConvert:
			return DIKEYBOARD_NOCONVERT;
			break;

		case Key::NumberLock:
			return DIKEYBOARD_NUMLOCK;
			break;

		case Key::NumberPad0:
			return DIKEYBOARD_NUMPAD0;
			break;

		case Key::NumberPad1:
			return DIKEYBOARD_NUMPAD1;
			break;

		case Key::NumberPad2:
			return DIKEYBOARD_NUMPAD2;
			break;

		case Key::NumberPad3:
			return DIKEYBOARD_NUMPAD3;
			break;

		case Key::NumberPad4:
			return DIKEYBOARD_NUMPAD4;
			break;

		case Key::NumberPad5:
			return DIKEYBOARD_NUMPAD5;
			break;

		case Key::NumberPad6:
			return DIKEYBOARD_NUMPAD6;
			break;

		case Key::NumberPad7:
			return DIKEYBOARD_NUMPAD7;
			break;

		case Key::NumberPad8:
			return DIKEYBOARD_NUMPAD8;
			break;

		case Key::NumberPad9:
			return DIKEYBOARD_NUMPAD9;
			break;

		case Key::NumberPadComma:
			return DIKEYBOARD_NUMPADCOMMA;
			break;

		case Key::NumberPadEnter:
			return DIKEYBOARD_NUMPADENTER;
			break;

		case Key::NumberPadMinus:
			return DIKEYBOARD_SUBTRACT;
			break;

		case Key::NumberPadPeriod:
			return DIKEYBOARD_DECIMAL;
			break;

		case Key::NumberPadPlus:
			return DIKEYBOARD_ADD;
			break;

		case Key::NumberPadSlash:
			return DIKEYBOARD_DIVIDE;
			break;

		case Key::NumberPadEquals:
			return DIKEYBOARD_NUMPADEQUALS;

		case Key::WebRefresh:
			return DIKEYBOARD_WEBREFRESH;

		case Key::NumberPadStar:
			return DIKEYBOARD_MULTIPLY;
			break;

		case Key::Oem102:
			return DIKEYBOARD_OEM_102;
			break;

		case Key::PageDown:
			return DIKEYBOARD_NEXT;
			break;

		case Key::PageUp:
			return DIKEYBOARD_PRIOR;
			break;

		case Key::Pause:
			return DIKEYBOARD_PAUSE;
			break;

		case Key::Period:
			return DIKEYBOARD_PERIOD;
			break;

		case Key::PlayPause:
			return DIKEYBOARD_PLAYPAUSE;
			break;

		case Key::Power:
			return DIKEYBOARD_POWER;
			break;

		case Key::PreviousTrack:
			return DIKEYBOARD_PREVTRACK;
			break;

		case Key::RightBracket:
			return DIKEYBOARD_RBRACKET;
			break;

		case Key::RightControl:
			return DIKEYBOARD_RCONTROL;
			break;

		case Key::Return:
			return DIKEYBOARD_RETURN;
			break;

		case Key::RightArrow:
			return DIKEYBOARD_RIGHT;
			break;

		case Key::RightAlt:
			return DIKEYBOARD_RMENU;
			break;

		case Key::RightShift:
			return DIKEYBOARD_RSHIFT;
			break;

		case Key::RightWindowsKey:
			return DIKEYBOARD_RWIN;
			break;

		case Key::ScrollLock:
			return DIKEYBOARD_SCROLL;
			break;

		case Key::Semicolon:
			return DIKEYBOARD_SEMICOLON;
			break;

		case Key::Slash:
			return DIKEYBOARD_SLASH;
			break;

		case Key::Sleep:
			return DIKEYBOARD_SLEEP;
			break;

		case Key::Space:
			return DIKEYBOARD_SPACE;
			break;

		case Key::Stop:
			return DIKEYBOARD_STOP;
			break;

		case Key::PrintScreen:
			return DIKEYBOARD_SYSRQ;
			break;

		case Key::Tab:
			return DIKEYBOARD_TAB;
			break;

		case Key::Underline:
			return DIKEYBOARD_UNDERLINE;
			break;

		case Key::Unlabeled:
			return DIKEYBOARD_UNLABELED;
			break;

		case Key::UpArrow:
			return DIKEYBOARD_UP;
			break;

		case Key::VolumeDown:
			return DIKEYBOARD_VOLUMEDOWN;
			break;

		case Key::VolumeUp:
			return DIKEYBOARD_VOLUMEUP;
			break;

		case Key::Wake:
			return DIKEYBOARD_WAKE;
			break;

		case Key::WebBack:
			return DIKEYBOARD_WEBBACK;
			break;

		case Key::WebFavorites:
			return DIKEYBOARD_WEBFAVORITES;
			break;

		case Key::WebForward:
			return DIKEYBOARD_WEBFORWARD;
			break;

		case Key::WebHome:
			return DIKEYBOARD_WEBHOME;
			break;

		case Key::WebSearch:
			return DIKEYBOARD_WEBSEARCH;
			break;
			
		case Key::WebStop:
			return DIKEYBOARD_WEBSTOP;
			break;

		case Key::Yen:
			return DIKEYBOARD_YEN;
			break;
		}

		throw gcnew ArgumentException( "The specified key does not exist." );
	}
	*/

	/* Unused.
	int DeviceConstantConverter::MouseToDIMOFS( MouseObject mouse )
	{
		switch( mouse )
		{
		case MouseObject::Button1:
			return DIMOFS_BUTTON0;
			break;

		case MouseObject::Button2:
			return DIMOFS_BUTTON1;
			break;

		case MouseObject::Button3:
			return DIMOFS_BUTTON2;
			break;

		case MouseObject::Button4:
			return DIMOFS_BUTTON3;
			break;

		case MouseObject::Button5:
			return DIMOFS_BUTTON4;
			break;

		case MouseObject::Button6:
			return DIMOFS_BUTTON5;
			break;

		case MouseObject::Button7:
			return DIMOFS_BUTTON6;
			break;

		case MouseObject::Button8:
			return DIMOFS_BUTTON7;
			break;

		case MouseObject::XAxis:
			return DIMOFS_X;
			break;

		case MouseObject::YAxis:
			return DIMOFS_Y;
			break;

		case MouseObject::ZAxis:
			return DIMOFS_Z;
			break;
		}

		throw gcnew ArgumentException( "The specified mouse object does not exist." );
	}
	*/

	/* Unused.
	int DeviceConstantConverter::MouseToDIMOUSE( MouseObject mouse )
	{
		switch( mouse )
		{
		case MouseObject::Button1:
			return DIMOUSE_BUTTON0;
			break;

		case MouseObject::Button2:
			return DIMOUSE_BUTTON1;
			break;

		case MouseObject::Button3:
			return DIMOUSE_BUTTON2;
			break;

		case MouseObject::Button4:
			return DIMOUSE_BUTTON3;
			break;

		case MouseObject::Button5:
			return DIMOUSE_BUTTON4;
			break;

		case MouseObject::Button6:
			return DIMOUSE_BUTTON5;
			break;

		case MouseObject::Button7:
			return DIMOUSE_BUTTON6;
			break;

		case MouseObject::Button8:
			return DIMOUSE_BUTTON7;
			break;

		case MouseObject::XAxis:
			return DIMOUSE_XAXIS;
			break;

		case MouseObject::YAxis:
			return DIMOUSE_YAXIS;
			break;

		case MouseObject::ZAxis:
			return DIMOUSE_WHEEL;
			break;
		}

		throw gcnew ArgumentException( "The specified mouse object does not exist." );
	}
	*/
}
}