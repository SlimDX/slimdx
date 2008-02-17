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
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

#include "../math/ColorRGB.h"

namespace SlimDX
{
	namespace DXGI
	{
		/// <remarks>
		/// Describes gamma control settings.
		/// </remarks>
		public value class GammaControl
		{
			ColorRGB m_Scale;
			ColorRGB m_Offset;
			List<ColorRGB>^ m_GammaCurve;

		internal:
			GammaControl( const DXGI_GAMMA_CONTROL& native );

		public:
			/// <summary>
			/// Gets or sets a scaling factor applied to gamma RGB values.
			/// </summary>
			property ColorRGB Scale
			{
				ColorRGB get();
				void set( ColorRGB value );
			}
			
			/// <summary>
			/// Gets or sets an offset applied to gamma RGB values.
			/// </summary>
			property ColorRGB Offset
			{
				ColorRGB get();
				void set( ColorRGB value );
			}
			
			/// <summary>
			/// Gets the list of RGB control points defining the gamma curve.
			/// </summary>
			property ReadOnlyCollection<ColorRGB>^ ControlPoints
			{
				ReadOnlyCollection<ColorRGB>^ get();
			}
		};
	}
};