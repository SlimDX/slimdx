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
#pragma once

namespace SlimDX
{
	namespace DXGI
	{
		/// <remarks>
		/// Describes gamma control capabilities.
		/// </remarks>
		public value class GammaControlCapabilities
		{
			bool m_ScaleAndOffsetSupported;
			float m_MaxConvertedValue;
			float m_MinConvertedValue;
			System::Collections::Generic::List<float>^ m_ControlPointPositions;
		
		internal:
			GammaControlCapabilities( const DXGI_GAMMA_CONTROL_CAPABILITIES& native );

		public:
			/// <summary>
			/// Gets a value indicating whether gamma scale and offset transformation is supported.
			/// </summary>
			property bool IsScaleAndOffsetSupported
			{
				bool get();
			}

			/// <summary>
			/// Gets a value indicating the maximum range of the curve control point positions.
			/// </summary>
			property float MaximumConvertedValue
			{
				float get();
			}

			/// <summary>
			/// Gets a value indicating the minimum range of the curve control point positions.
			/// </summary>
			property float MinimumConvertedValue
			{
				float get();
			}

			/// <summary>
			/// Gets the list of curve control point positions.
			/// </summary>
			property System::Collections::ObjectModel::ReadOnlyCollection<float>^ ControlPoints
			{
				System::Collections::ObjectModel::ReadOnlyCollection<float>^ get();
			}
		};
	}
};