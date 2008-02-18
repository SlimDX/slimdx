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

#include "GammaControlCapabilities.h"

namespace SlimDX
{
namespace DXGI
{ 	
	GammaControlCapabilities::GammaControlCapabilities( const DXGI_GAMMA_CONTROL_CAPABILITIES& native )
	{
		m_ScaleAndOffsetSupported = native.ScaleAndOffsetSupported ? true : false;
		m_MaxConvertedValue = native.MaxConvertedValue;
		m_MinConvertedValue = native.MinConvertedValue;
		m_ControlPointPositions = gcnew System::Collections::Generic::List<float>();
		for( UINT controlPointIndex = 0; controlPointIndex < native.NumGammaControlPoints; ++controlPointIndex )
			m_ControlPointPositions->Add( native.ControlPointPositions[ controlPointIndex ] );
	}

	bool GammaControlCapabilities::IsScaleAndOffsetSupported::get()
	{
		return m_ScaleAndOffsetSupported;
	}

	float GammaControlCapabilities::MaximumConvertedValue::get()
	{
		return m_MaxConvertedValue;
	}

	float GammaControlCapabilities::MinimumConvertedValue::get()
	{
		return m_MinConvertedValue;
	}

	System::Collections::ObjectModel::ReadOnlyCollection<float>^ GammaControlCapabilities::ControlPoints::get()
	{
		return gcnew System::Collections::ObjectModel::ReadOnlyCollection<float>( m_ControlPointPositions );
	}
}
}
