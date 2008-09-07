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

#include "../ComObject.h"

#include "Enums.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace DXGI
	{
		ref class Surface;
		value class FrameStatistics;
		value class GammaControl;
		value class GammaControlCapabilities;
		value class ModeDescription;
		value class OutputDescription;
		
		/// <summary>
		/// Represents the output of an adapter (such as a monitor).
		/// </summary>
		public ref class Output : public ComObject
		{
			COMOBJECT(IDXGIOutput, Output);
		
		public:
			/// <summary>
			/// Gets the output's description.
			/// </summary>
			property OutputDescription Description
			{
				OutputDescription get();
			}
			
			/// <summary>
			/// Gets statistics about recent frames.
			/// </summary>
			property DXGI::FrameStatistics FrameStatistics
			{
				DXGI::FrameStatistics get();
			}
			
			/// <summary>
			/// Gets a description of the output's gamma-control capabilities.
			/// </summary>
			property DXGI::GammaControlCapabilities GammaControlCapabilities
			{
				DXGI::GammaControlCapabilities get();
			}
			
			/// <summary>
			/// Constructs a new instance of the <see cref="Output"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIOutput pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static Output^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Gets a list of display modes matching certain specifications.
			/// </summary>
			/// <param name="format">The display mode color format.</param>
			/// <param name="flags">Flags indicating how the display mode scanline order and scaling.</param>
			/// <returns>A list of matching display mode descriptions. The list is null if an error occured.</returns>
			System::Collections::ObjectModel::ReadOnlyCollection<ModeDescription>^ GetDisplayModeList( Format format, DisplayModeEnumerationFlags flags );
			
			/// <summary>
			/// Gets the display mode that best matches the requested mode.
			/// </summary>
			/// <param name="device">The device interface. If this parameter is null, only
			/// modes whose format matches the specified mode will be returned; otherwise, only those
			/// formats that are supported for scan-out by the device are returned.</param>
			/// <param name="modeToMatch">The description of the display mode to match.</param>
			/// <param name="result">Receives the best-matching display mode.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result GetClosestMatchingMode( ComObject^ device, ModeDescription modeToMatch, [Out] ModeDescription %result );
			
			/// <summary>
			/// Sets gamma control information.
			/// </summary>
			/// <param name="control">The gamma control information.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result SetGammaControl( GammaControl control );
			
			/// <summary>
			/// Changes the current display surface to the specified surface.
			/// </summary>
			/// <param name="surface">The new display surface.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result SetDisplaySurface( Surface^ surface );
			
			/// <summary>
			/// Copies the display surface content to the specified destination surface.
			/// </summary>
			/// <param name="surface">The destination surface.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result CopyDisplaySurfaceTo( Surface^ surface );
			
			/// <summary>
			/// Takes ownership of an output.
			/// </summary>
			/// <param name="device">The device interface.</param>
			/// <param name="exclusive">If true, ownership is exclusive.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result TakeOwnership( ComObject^ device, bool exclusive );
			
			/// <summary>
			/// Releases ownership of an output.
			/// </summary>
			void ReleaseOwnership();
			
			/// <summary>
			/// Halts the current thread until a vertical blank occurs.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result WaitForVerticalBlank();
			
			/// <summary>
			/// Converts the value of the object to its equivalent string representation.
			/// </summary>
			/// <returns>The string representation of the value of this instance.</returns>
			virtual System::String^ ToString() override;
		};
	}
};