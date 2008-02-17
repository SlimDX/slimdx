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

#include <dxgi.h>

#include "GammaControl.h"

namespace SlimDX
{
namespace DXGI
{ 	
	GammaControl::GammaControl( const DXGI_GAMMA_CONTROL& native )
	{
		m_Scale = ColorRGB( native.Scale.Red, native.Scale.Green, native.Scale.Blue );
		m_Offset = ColorRGB( native.Offset.Red, native.Offset.Green, native.Offset.Blue );
		
		// 1025 is hard-coded by the DXGI API, there doesn't seem to be a constant for it.
		for( int controlPointIndex = 0; controlPointIndex < 1025; ++controlPointIndex )
			m_GammaCurve->Add( ColorRGB( native.GammaCurve[ controlPointIndex ].Red, native.GammaCurve[ controlPointIndex ].Green, native.GammaCurve[ controlPointIndex ].Blue ) );
	}
	
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
	
	ColorRGB GammaControl::Scale::get()
	{
		return m_Scale;
	}
	
	void GammaControl::Scale::set( ColorRGB value )
	{
		m_Scale = value;
	}
	
	ColorRGB GammaControl::Offset::get()
	{
		return m_Offset;
	}
	
	void GammaControl::Offset::set( ColorRGB value )
	{
		m_Offset = value;
	}

	ReadOnlyCollection<ColorRGB>^ GammaControl::ControlPoints::get()
	{
		return gcnew ReadOnlyCollection<ColorRGB>( m_GammaCurve );
	}
}
}
