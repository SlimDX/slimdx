/*
* Copyright (c) 2007-2009 SlimDX Group
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
	namespace Direct2D
	{
		public ref class ResultCode sealed
		{
		private:
			ResultCode();
			
		public:
			property static Result BadNumber
			{
				Result get();
			};

			property static Result DisplayFormatNotSupported
			{
				Result get();
			};

			property static Result DisplayStateInvalid
			{
				Result get();
			};

			property static Result Failure
			{
				Result get();
			};

			property static Result IncompatibleBrushTypes
			{
				Result get();
			};

			property static Result InsufficientBuffer
			{
				Result get();
			};

			property static Result NotInitialized
			{
				Result get();
			};

			property static Result InternalError
			{
				Result get();
			};

			property static Result InvalidCall
			{
				Result get();
			};

			property static Result LayerAlreadyInUse
			{
				Result get();
			};

			property static Result MaxTextureSizeExceeded
			{
				Result get();
			};

			property static Result NoHardwareDevice
			{
				Result get();
			};

			property static Result PopCallDidNotMatchPush
			{
				Result get();
			};

			property static Result PushPopUnbalanced
			{
				Result get();
			};

			property static Result RecreateTarget
			{
				Result get();
			};

			property static Result RenderTargetHasLayerOrClippingRectangle
			{
				Result get();
			};

			property static Result ScannerFailed
			{
				Result get();
			};

			property static Result ScreenAccessDenied
			{
				Result get();
			};

			property static Result ShaderCompileFailed
			{
				Result get();
			};

			property static Result Success
			{
				Result get();
			};

			property static Result TargetNotGdiCompatible
			{
				Result get();
			};

			property static Result TextEffectIsWrongType
			{
				Result get();
			};

			property static Result TextRendererNotReleased
			{
				Result get();
			};

			property static Result TooManyShaderElements
			{
				Result get();
			};

			property static Result UnsupportedOperation
			{
				Result get();
			};

			property static Result UnsupportedVersion
			{
				Result get();
			};

			property static Result Win32Error
			{
				Result get();
			};

			property static Result WrongFactory
			{
				Result get();
			};

			property static Result WrongRenderTarget
			{
				Result get();
			};

			property static Result WrongState
			{
				Result get();
			};

			property static Result ZeroVector
			{
				Result get();
			};
		};
	}
}