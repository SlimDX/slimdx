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
#include "DirectInputErrorHandler.h"

#include "Device.h"

namespace SlimDX
{
namespace DirectInput
{
	generic<typename DataFormat>
	BufferedData<DataFormat>::BufferedData( const DIDEVICEOBJECTDATA &objectData )
	{
		Type^ type = DataFormat::typeid;

		if( type == KeyboardState::typeid )
		{
			KeyboardState^ result = gcnew KeyboardState();
			if( objectData.dwData )
				result->keys[objectData.dwOfs] = true;
			else
				result->keys[objectData.dwOfs] = false;
			data = reinterpret_cast<DataFormat>( result );
		}
		else if( type == MouseState::typeid )
		{
			MouseState^ result = gcnew MouseState( 0, 0, 0 );
			if( objectData.dwOfs == DIMOFS_BUTTON0 )
			{
				if( objectData.dwData )
					result->buttons[0] = true;
				else
					result->buttons[0] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON1 )
			{
				if( objectData.dwData )
					result->buttons[1] = true;
				else
					result->buttons[1] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON2 )
			{
				if( objectData.dwData )
					result->buttons[2] = true;
				else
					result->buttons[2] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON3 )
			{
				if( objectData.dwData )
					result->buttons[3] = true;
				else
					result->buttons[3] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON4 )
			{
				if( objectData.dwData )
					result->buttons[4] = true;
				else
					result->buttons[4] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON5 )
			{
				if( objectData.dwData )
					result->buttons[5] = true;
				else
					result->buttons[5] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON6 )
			{
				if( objectData.dwData )
					result->buttons[6] = true;
				else
					result->buttons[6] = false;
			}
			else if( objectData.dwOfs == DIMOFS_BUTTON7 )
			{
				if( objectData.dwData )
					result->buttons[7] = true;
				else
					result->buttons[7] = false;
			}
			else if( objectData.dwOfs == DIMOFS_X )
				result->x = objectData.dwData;
			else if( objectData.dwOfs == DIMOFS_Y )
				result->y = objectData.dwData;
			else if( objectData.dwOfs == DIMOFS_Z )
				result->z = objectData.dwData;

			data = reinterpret_cast<DataFormat>( result );
		}
		else if( type == JoystickState::typeid )
		{
			JoystickState^ result = gcnew JoystickState();

			if( objectData.dwOfs == DIJOFS_RX )
				result->rx = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_RY )
				result->ry = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_RZ )
				result->rz = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_X )
				result->x = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_Y )
				result->y = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_Z )
				result->z = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_SLIDER( 0 ) )
				result->sliders[0] = objectData.dwData;
			else if( objectData.dwOfs == DIJOFS_SLIDER( 1 ) )
				result->sliders[1] = objectData.dwData;
			else
			{
				bool found = false;
				for( int i = 0; i < 4; i++ )
				{
					if( objectData.dwOfs == DIJOFS_POV( i ) )
					{
						result->povs[i] = objectData.dwData;
						found = true;
						break;
					}
				}

				if( !found )
				{
					for( int i = 0; i < 128; i++ )
					{
						if( objectData.dwOfs == DIJOFS_BUTTON( i ) )
						{
							if( objectData.dwData )
								result->buttons[i] = true;
							else
								result->buttons[i] = false;
							break;
						}
					}
				}
			}
		}
		else
		{
			array<FieldInfo^>^ fields = type->GetFields();
			for each( FieldInfo^ field in fields )
			{
				int o = Marshal::OffsetOf( type, field->Name ).ToInt32();
				if( o == objectData.dwOfs )
				{
					field->SetValue( data, objectData.dwData );
					break;
				}
			}
		}

		timeStamp = objectData.dwTimeStamp;
		sequence = objectData.dwSequence;
		if( objectData.uAppData == NULL )
			appData = nullptr;
		else
		{
			GCHandle handle = GCHandle::FromIntPtr( static_cast<IntPtr>( static_cast<UIntPtr>( objectData.uAppData ).ToPointer() ) );
			appData = handle.Target;
			handle.Free();
		}
	}

	generic<typename DataFormat>
	BufferedData<DataFormat>::BufferedData()
	{
	}

	generic<typename DataFormat>
	BufferedData<DataFormat>::BufferedData( DataFormat data ) : data( data )
	{
	}

	generic<typename DataFormat>
	BufferedDataCollection<DataFormat>::BufferedDataCollection()
	{
		list = gcnew List<BufferedData<DataFormat>^>();
	}

	generic<typename DataFormat>
	void BufferedDataCollection<DataFormat>::Add( BufferedData<DataFormat>^ data )
	{
		list->Add( data );
	}
}
}