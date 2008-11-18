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

#include <dxgi.h>

#include "GammaControl.h"

using namespace System::Collections::ObjectModel;

namespace SlimDX
{
namespace DXGI
{ 	
	/*GammaControl::GammaControl( const DXGI_GAMMA_CONTROL& native )
	{
		m_Scale = Color3( native.Scale.Red, native.Scale.Green, native.Scale.Blue );
		m_Offset = Color3( native.Offset.Red, native.Offset.Green, native.Offset.Blue );
		
		// 1025 is hard-coded by the DXGI API, there doesn't seem to be a constant for it.
		for( int controlPointIndex = 0; controlPointIndex < 1025; ++controlPointIndex )
			m_GammaCurve->Add( Color3( native.GammaCurve[ controlPointIndex ].Red, native.GammaCurve[ controlPointIndex ].Green, native.GammaCurve[ controlPointIndex ].Blue ) );
	}*/
	
	DXGI_GAMMA_CONTROL GammaControl::CreateNativeVersion()
	{
		DXGI_GAMMA_CONTROL native;
		native.Scale.Red = m_Scale.Red;
		native.Scale.Green = m_Scale.Green;
		native.Scale.Blue = m_Scale.Blue;
		native.Offset.Red = m_Offset.Red;
		native.Offset.Green = m_Offset.Green;
		native.Offset.Blue = m_Offset.Blue;
		
		// 1025 is hard-coded by the DXGI API, there doesn't seem to be a constant for it.
		for( int controlPointIndex = 0; controlPointIndex < 1025; ++controlPointIndex )
		{
			native.GammaCurve[ controlPointIndex ].Red = m_GammaCurve[ controlPointIndex ].Red;
			native.GammaCurve[ controlPointIndex ].Green = m_GammaCurve[ controlPointIndex ].Green;
			native.GammaCurve[ controlPointIndex ].Blue = m_GammaCurve[ controlPointIndex ].Blue;
		}
		
		return native;	
	}
	
	Color3 GammaControl::Scale::get()
	{
		return m_Scale;
	}
	
	void GammaControl::Scale::set( Color3 value )
	{
		m_Scale = value;
	}
	
	Color3 GammaControl::Offset::get()
	{
		return m_Offset;
	}
	
	void GammaControl::Offset::set( Color3 value )
	{
		m_Offset = value;
	}

	ReadOnlyCollection<Color3>^ GammaControl::ControlPoints::get()
	{
		return gcnew ReadOnlyCollection<Color3>( m_GammaCurve );
	}

	bool GammaControl::operator == ( GammaControl left, GammaControl right )
	{
		return GammaControl::Equals( left, right );
	}

	bool GammaControl::operator != ( GammaControl left, GammaControl right )
	{
		return !GammaControl::Equals( left, right );
	}

	int GammaControl::GetHashCode()
	{
		return m_Scale.GetHashCode() + m_Offset.GetHashCode() + m_GammaCurve->GetHashCode();
	}

	bool GammaControl::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<GammaControl>( value ) );
	}

	bool GammaControl::Equals( GammaControl value )
	{
		return ( m_Scale == value.m_Scale && m_Offset == value.m_Offset && m_GammaCurve == value.m_GammaCurve );
	}

	bool GammaControl::Equals( GammaControl% value1, GammaControl% value2 )
	{
		return ( value1.m_Scale == value2.m_Scale && value1.m_Offset == value2.m_Offset && value1.m_GammaCurve == value2.m_GammaCurve );
	}
}
}
