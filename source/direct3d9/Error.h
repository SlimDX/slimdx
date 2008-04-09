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

#include "../Result.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		/// <summary>Defines error result codes that are returned by Direct3D 9 functions.</summary>
		public ref class Error sealed
		{
		private:
			Error();
			
		public:
			/// <summary>
			/// Occurs when a method succeeds but mipmaps could not be automatically generated.
			/// </summary>
			property static Result NoneButNoAutomaticGeneration
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when two set render states conflict with each other.
			/// </summary>
			property static Result ConflictingRenderState
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when two set texture filters conflict with each other.
			/// </summary>
			property static Result ConflictingTextureFilter
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when two texture palettes conflict with each other.
			/// </summary>
			property static Result ConflictingTexturePalette
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when a device is lost.
			/// </summary>
			property static Result DeviceLost
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when a lost yet resettable device has not yet been reset.
			/// </summary>
			property static Result DeviceNotReset
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when a driver internal error is thrown.
			/// </summary>
			property static Result DriverInternalError
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when an invalid method call is made. This is usually do to an invalid parameter.
			/// </summary>
			property static Result InvalidCall
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when a requested device type is invalid.
			/// </summary>
			property static Result InvalidDevice
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when there is more data availabe than the specified buffer can hold.
			/// </summary>
			property static Result MoreData
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the queried technique.
			/// </summary>
			property static Result NotAvailable
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the requested item cannot be found.
			/// </summary>
			property static Result NotFound
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the driver runs out of video memory.
			/// </summary>
			property static Result OutOfVideoMemory
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when more texture-filtering operations are requested than the device can support.
			/// </summary>
			property static Result TooManyOperations
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the requested alpha blending argument.
			/// </summary>
			property static Result UnsupportedAlphaArgument
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the requested alpha blending operation.
			/// </summary>
			property static Result UnsupportedAlphaOperation
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device not support the requested color blending argument.
			/// </summary>
			property static Result UnsupportedColorArgument
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the requested color blending operation.
			/// </summary>
			property static Result UnsupportedColorOperation
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the requested texture factor value.
			/// </summary>
			property static Result UnsupportedFactorValue
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the device does not support the requested texture filter.
			/// </summary>
			property static Result UnsupportedTextureFilter
			{
				Result get();
			};
		
			/// <summary>
			/// Occurs when a previous draw operation has not yet completed at the time of a new draw call.
			/// </summary>
			property static Result WasStillDrawing
			{
				Result get();
			};
			
			/// <summary>
			/// Occurs when the pixel format for a texture is invalid.
			/// </summary>
			property static Result WrongTextureFormat
			{
				Result get();
			};
		};
	}
}