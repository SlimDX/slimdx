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

#ifdef WRAP_XAPO

#include "RegistrationProperties.h"
#include "../WaveFormat.h"
#include "LockParameter.h"
#include "BufferParameter.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace XAPO
	{
		public interface struct IAudioProcessor
		{
			virtual int CalculateInputFrames( int outputFrameCount ) = 0;
			virtual int CalculateOutputFrames( int inputFrameCount ) = 0;
			virtual Result Initialize( DataStream^ data ) = 0;
			virtual bool IsInputFormatSupported( WaveFormat^ outputFormat, WaveFormat^ requestedInputFormat, [Out] WaveFormat^% supportedInputFormat ) = 0;
			virtual bool IsOutputFormatSupported( WaveFormat^ inputFormat, WaveFormat^ requestedOutputFormat, [Out] WaveFormat^% supportedOutputFormat ) = 0;
			virtual Result LockForProcess( array<LockParameter>^ inputParameters, array<LockParameter>^ outputParameters ) = 0;
			virtual void Process( array<BufferParameter^>^ inputParameters, array<BufferParameter^>^ outputParameters, bool isEnabled ) = 0;
			virtual void Reset() = 0;
			virtual void UnlockForProcess() = 0;

			virtual property RegistrationProperties^ RegistrationProperties
			{
				SlimDX::XAPO::RegistrationProperties^ get();
			}
		};
	}
}

#endif