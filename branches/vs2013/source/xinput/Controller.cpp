/*
* Copyright (c) 2007-2014 SlimDX Group
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
#include "stdafx.h"

#include "../Utilities.h"

#include "Controller.h"
#include "XInputException.h"
#include "ResultCodeXI.h"

using namespace System;

namespace SlimDX
{
namespace XInput
{
	Controller::Controller( UserIndex userIndex )
	{
		m_UserIndex = static_cast<System::UInt32>( userIndex );
	}
	
	bool Controller::IsConnected::get()
	{
		XINPUT_STATE state;
		UInt32 result = XInputGetState( m_UserIndex, &state );

		if( result == ERROR_DEVICE_NOT_CONNECTED )
			return false;
		return true;
	}
	
	State Controller::GetState()
	{
		XINPUT_STATE state;
		if( RECORD_XINPUT( ConvertError( XInputGetState( m_UserIndex, &state ) ) ).IsFailure )
			return State();
	
		return State( state ); 
	}
	
	Result Controller::SetVibration( Vibration vibration )
	{
		XINPUT_VIBRATION nativeVibration = vibration.CreateNativeVersion();
		return RECORD_XINPUT( ConvertError( XInputSetState( m_UserIndex, &nativeVibration ) ) );
	}
	
	int Controller::ConvertError( int errorCode )
	{
		return HRESULT_FROM_WIN32( errorCode );
	}
}
}
