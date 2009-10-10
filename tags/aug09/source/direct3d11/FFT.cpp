#include "stdafx.h"
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

#include <d3d11.h>
#include <d3dx11.h>

#include "UnorderedAccessView11.h"

#include "FFT.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	float FFT::ForwardScale::get()
	{
		return InternalPointer->GetForwardScale();
	}

	void FFT::ForwardScale::set( float value )
	{
		InternalPointer->SetForwardScale( value );
	}

	float FFT::InverseScale::get()
	{
		return InternalPointer->GetInverseScale();
	}

	void FFT::InverseScale::set( float value )
	{
		InternalPointer->SetInverseScale( value );
	}

	void FFT::AttachBuffersAndPrecompute( array<UnorderedAccessView^>^ tempBuffers, array<UnorderedAccessView^>^ precomputeBuffers )
	{
		ID3D11UnorderedAccessView* nativeTempBuffers[D3DX11_FFT_MAX_TEMP_BUFFERS];
		int numTempBuffers = 0;
		ID3D11UnorderedAccessView* nativePrecomputeBuffers[D3DX11_FFT_MAX_PRECOMPUTE_BUFFERS];
		int numPrecomputeBuffers = 0;

		if ( tempBuffers != nullptr || tempBuffers->Length > 0 )
		{
			for ( int i = 0; i < tempBuffers->Length; ++i )
				nativeTempBuffers[ i ] = tempBuffers[ i ] == nullptr ? NULL : tempBuffers[ i ]->InternalPointer;
			numTempBuffers = tempBuffers->Length;
		}

		if ( precomputeBuffers != nullptr || precomputeBuffers->Length > 0 )
		{
			for ( int i = 0; i < precomputeBuffers->Length; ++i )
				nativePrecomputeBuffers[ i ] = precomputeBuffers[ i ] == nullptr ? NULL : precomputeBuffers[ i ]->InternalPointer;
			numPrecomputeBuffers = precomputeBuffers->Length;
		}

		InternalPointer->AttachBuffersAndPrecompute( numTempBuffers, nativeTempBuffers, numPrecomputeBuffers, nativePrecomputeBuffers );
	}

	void FFT::ForwardTransform( UnorderedAccessView^ input, UnorderedAccessView^ output )
	{
		if ( output == nullptr )
		{
			throw gcnew System::ArgumentNullException( "output" );
		}

		ID3D11UnorderedAccessView* inputBuffer = input == nullptr ? NULL : input->InternalPointer;
		ID3D11UnorderedAccessView* outputBuffer = output->InternalPointer;

		InternalPointer->ForwardTransform( inputBuffer, &outputBuffer );
	}

	UnorderedAccessView^ FFT::ForwardTransform( UnorderedAccessView^ input )
	{
		ID3D11UnorderedAccessView* inputBuffer = input == nullptr ? NULL : input->InternalPointer;
		ID3D11UnorderedAccessView* outputBuffer = NULL;

		InternalPointer->ForwardTransform( inputBuffer, &outputBuffer );

		return UnorderedAccessView::FromPointer( outputBuffer );
	}

	void FFT::InverseTransform( UnorderedAccessView^ input, UnorderedAccessView^ output )
	{
		if ( output == nullptr )
		{
			throw gcnew System::ArgumentNullException( "output" );
		}

		ID3D11UnorderedAccessView* inputBuffer = input == nullptr ? NULL : input->InternalPointer;
		ID3D11UnorderedAccessView* outputBuffer = output->InternalPointer;

		InternalPointer->InverseTransform( inputBuffer, &outputBuffer );
	}

	UnorderedAccessView^ FFT::InverseTransform( UnorderedAccessView^ input )
	{
		ID3D11UnorderedAccessView* inputBuffer = input == nullptr ? NULL : input->InternalPointer;
		ID3D11UnorderedAccessView* outputBuffer = NULL;

		InternalPointer->InverseTransform( inputBuffer, &outputBuffer );

		return UnorderedAccessView::FromPointer( outputBuffer );
	}
}
}
