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
		public ref class Error sealed
		{
			private:
				Error();
				
			public:
				property static Result NoneButNoAutomaticGeneration
				{
					Result get();
				};
				
				property static Result ConflictingRenderState
				{
					Result get();
				};
				
				property static Result ConflictingTextureFilter
				{
					Result get();
				};
				
				property static Result ConflictingTexturePalette
				{
					Result get();
				};
				
				property static Result DeviceLost
				{
					Result get();
				};
				
				property static Result DeviceNotReset
				{
					Result get();
				};
				
				property static Result DriverInternalError
				{
					Result get();
				};
				
				property static Result DriverInvalidCall
				{
					Result get();
				};
				
				property static Result InvalidCall
				{
					Result get();
				};
				
				property static Result InvalidDevice
				{
					Result get();
				};
				
				property static Result MoreData
				{
					Result get();
				};
				
				property static Result NotAvailable
				{
					Result get();
				};
				
				property static Result NotFound
				{
					Result get();
				};
				
				property static Result OutOfVideoMemory
				{
					Result get();
				};
				
				property static Result TooManyOperations
				{
					Result get();
				};
				
				property static Result UnsupportedAlphaArgument
				{
					Result get();
				};
				
				property static Result UnsupportedAlphaOperation
				{
					Result get();
				};
				
				property static Result UnsupportedColorArgument
				{
					Result get();
				};
				
				property static Result UnsupportedColorOperation
				{
					Result get();
				};
				
				property static Result UnsupportedFactorValue
				{
					Result get();
				};
				
				property static Result UnsupportedTextureFilter
				{
					Result get();
				};
			
				property static Result WasStillDrawing
				{
					Result get();
				};
				
				property static Result WrongTextureFormat
				{
					Result get();
				};
		};
	}
}