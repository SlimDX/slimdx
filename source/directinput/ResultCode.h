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

#include "../Result.h"

namespace SlimDX
{
	namespace DirectInput
	{
		public ref class ResultCode sealed
		{
		private:
			ResultCode();
				
		public:
			property static Result Acquired
			{
				Result get();
			};

			property static Result AlreadyInitialized
			{
				Result get();
			};

			property static Result BadDriverVersion
			{
				Result get();
			};

			property static Result BetaDirectInputVersion
			{
				Result get();
			};

			property static Result BufferOverflow
			{
				Result get();
			};

			property static Result DeviceFull
			{
				Result get();
			};

			property static Result DeviceNotRegistered
			{
				Result get();
			};

			property static Result DownloadSkipped
			{
				Result get();
			};

			property static Result EffectPlaying
			{
				Result get();
			};

			property static Result EffectRestarted
			{
				Result get();
			};

			property static Result Failure
			{
				Result get();
			};

			property static Result Generic
			{
				Result get();
			};

			property static Result HandleExists
			{
				Result get();
			};

			property static Result HasEffects
			{
				Result get();
			};

			property static Result IncompleteEffect
			{
				Result get();
			};

			property static Result InputLost
			{
				Result get();
			};

			property static Result InvalidParameter
			{
				Result get();
			};

			property static Result MapFileFail
			{
				Result get();
			};

			property static Result MoreData
			{
				Result get();
			};

			property static Result NoAggregation
			{
				Result get();
			};

			property static Result NoEffect
			{
				Result get();
			};

			property static Result NoInterface
			{
				Result get();
			};

			property static Result NotAcquired
			{
				Result get();
			};

			property static Result NotAttached
			{
				Result get();
			};

			property static Result NotBuffered
			{
				Result get();
			};

			property static Result NotDownloaded
			{
				Result get();
			};

			property static Result NotExclusivelyAcquired
			{
				Result get();
			};

			property static Result NotFound
			{
				Result get();
			};

			property static Result NotInitialized
			{
				Result get();
			};

			property static Result ObjectNotFound
			{
				Result get();
			};

			property static Result OldDirectInputVersion
			{
				Result get();
			};

			property static Result OtherApplicationHasPriority
			{
				Result get();
			};

			property static Result OutOfMemory
			{
				Result get();
			};

			property static Result PolledDevice
			{
				Result get();
			};

			property static Result PropertyHasNoEffect
			{
				Result get();
			};

			property static Result ReadOnly
			{
				Result get();
			};

			property static Result ReportFull
			{
				Result get();
			};

			property static Result SettingsNotSaved
			{
				Result get();
			};

			property static Result Success
			{
				Result get();
			};

			property static Result Truncated
			{
				Result get();
			};

			property static Result TruncatedAndRestarted
			{
				Result get();
			};

			property static Result Unplugged
			{
				Result get();
			};

			property static Result Unsupported
			{
				Result get();
			};

			property static Result WriteProtect
			{
				Result get();
			};
		};
	}
}
