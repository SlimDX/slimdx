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
	namespace DirectSound
	{
		/// <summary>Defines error result codes that are returned by DirectSound functions.</summary>
		public ref class ResultCode sealed
		{
		private:
			ResultCode();

		public:
			property static Result NoVirtualization
			{
				Result get();
			};

			property static Result AccessDenied
			{
				Result get();
			};

			property static Result Allocated
			{
				Result get();
			};

			property static Result AlreadyInitialized
			{
				Result get();
			};

			property static Result BadFormat
			{
				Result get();
			};

			property static Result BadSendBufferGuid
			{
				Result get();
			};

			property static Result BufferLost
			{
				Result get();
			};

			property static Result BufferTooSmall
			{
				Result get();
			};

			property static Result ControlUnavailable
			{
				Result get();
			};

			property static Result DirectSound8Required
			{
				Result get();
			};

			property static Result EffectsUnavailable
			{
				Result get();
			};

			property static Result Generic
			{
				Result get();
			};

			property static Result InvalidCall
			{
				Result get();
			};

			property static Result InvalidParameter
			{
				Result get();
			};

			property static Result NoAggregation
			{
				Result get();
			};

			property static Result NoDriver
			{
				Result get();
			};

			property static Result NoInterface
			{
				Result get();
			};

			property static Result ObjectNotFound
			{
				Result get();
			};

			property static Result OtherApplicationHasPriority
			{
				Result get();
			};

			property static Result PriorityLevelNeeded
			{
				Result get();
			};

			property static Result SendLoop
			{
				Result get();
			};

			property static Result Uninitialized
			{
				Result get();
			};

			property static Result Unsupported
			{
				Result get();
			};
		};
	}
}