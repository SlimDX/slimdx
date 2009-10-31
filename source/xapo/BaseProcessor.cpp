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
#include "stdafx.h"

#include "../ComObject.h"
#include "../DataStream.h"
#include "../stack_array.h"

const IID IID_CXAPOBase = __uuidof(IXAPO);

#include "BaseProcessor.h"

using namespace System;
using namespace SlimDX::Multimedia;

namespace SlimDX
{
namespace XAPO
{
	BaseProcessor::BaseProcessor( SlimDX::XAPO::RegistrationProperties properties )
	{
		XAPO_REGISTRATION_PROPERTIES props = properties.ToUnmanaged();

		Construct( new XAPOBaseImpl( this, &props ) );
	}

	int BaseProcessor::CalculateInputFrames( int outputFrameCount )
	{
		return InternalPointer->CalcInputFrames( outputFrameCount );
	}

	int BaseProcessor::CalculateOutputFrames( int inputFrameCount )
	{
		return InternalPointer->CalcOutputFrames( inputFrameCount );
	}

	Result BaseProcessor::Initialize( DataStream^ data )
	{
		HRESULT hr = InternalPointer->Initialize( data->PositionPointer, static_cast<UINT32>( data->RemainingLength ) );
		return Result( hr );
	}

	bool BaseProcessor::IsInputFormatSupported( SlimDX::Multimedia::WaveFormat^ outputFormat, SlimDX::Multimedia::WaveFormat^ requestedInputFormat, [Out] SlimDX::Multimedia::WaveFormat^% supportedInputFormat )
	{
		auto_array<WAVEFORMATEX> output = WaveFormat::ToUnmanaged( outputFormat );
		auto_array<WAVEFORMATEX> input = WaveFormat::ToUnmanaged( requestedInputFormat );
		WAVEFORMATEX *supported = NULL;

		HRESULT hr = InternalPointer->IsInputFormatSupported( output.get(), input.get(), &supported );
		supportedInputFormat = WaveFormat::FromUnmanaged( *supported );
		return hr == S_OK;
	}

	bool BaseProcessor::IsOutputFormatSupported( SlimDX::Multimedia::WaveFormat^ inputFormat, SlimDX::Multimedia::WaveFormat^ requestedOutputFormat, [Out] SlimDX::Multimedia::WaveFormat^% supportedOutputFormat )
	{
		auto_array<WAVEFORMATEX> input = WaveFormat::ToUnmanaged( inputFormat );
		auto_array<WAVEFORMATEX> output = WaveFormat::ToUnmanaged( requestedOutputFormat );
		WAVEFORMATEX *supported = NULL;

		HRESULT hr = InternalPointer->IsOutputFormatSupported( input.get(), output.get(), &supported );
		supportedOutputFormat = WaveFormat::FromUnmanaged( *supported );
		return hr == S_OK;
	}

	Result BaseProcessor::LockForProcess( array<LockParameter>^ inputParameters, array<LockParameter>^ outputParameters )
	{
		stack_array<XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS> input = stackalloc( XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS, inputParameters->Length );
		stack_array<XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS> output = stackalloc( XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS, outputParameters->Length );

		for( int i = 0; i < inputParameters->Length; i++ )
		{
			XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS p;
			p.pFormat = WaveFormat::ToUnmanaged( inputParameters[i].Format ).release();
			p.MaxFrameCount = inputParameters[i].MaxFrameCount;

			input[i] = p;
		}

		for( int i = 0; i < outputParameters->Length; i++ )
		{
			XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS p;
			p.pFormat = WaveFormat::ToUnmanaged( outputParameters[i].Format ).release();
			p.MaxFrameCount = outputParameters[i].MaxFrameCount;

			output[i] = p;
		}

		HRESULT hr = InternalPointer->LockForProcess( inputParameters->Length, &input[0], outputParameters->Length, &output[0] );
		return Result( hr );
	}

	void BaseProcessor::Reset()
	{
		InternalPointer->Reset();
	}

	void BaseProcessor::UnlockForProcess()
	{
		InternalPointer->UnlockForProcess();
	}

	void BaseProcessor::ProcessThru( DataStream^ inputBuffer, array<float>^ outputBuffer, int frameCount, int inputChannelCount, int outputChannelCount, bool mixWithDestination )
	{
		pin_ptr<float> pinnedOutput = &outputBuffer[0];
		ImplPointer->ProcessThru( inputBuffer->PositionPointer, pinnedOutput, frameCount, static_cast<WORD>( inputChannelCount ), static_cast<WORD>( outputChannelCount ), mixWithDestination );
	}

	Result BaseProcessor::ValidateFormatDefault( SlimDX::Multimedia::WaveFormat^ format )
	{
		auto_array<WAVEFORMATEX> wave = WaveFormat::ToUnmanaged( format );
		HRESULT hr = ImplPointer->ValidateFormatDefault( wave.get(), FALSE );

		return Result( hr );
	}

	Result BaseProcessor::ValidateFormatPair( SlimDX::Multimedia::WaveFormat^ supportedFormat, SlimDX::Multimedia::WaveFormat^ requestedFormat )
	{
		auto_array<WAVEFORMATEX> supported = WaveFormat::ToUnmanaged( supportedFormat );
		auto_array<WAVEFORMATEX> requested = WaveFormat::ToUnmanaged( requestedFormat );

		HRESULT hr = ImplPointer->ValidateFormatPair( supported.get(), requested.get(), FALSE );
		return Result( hr );
	}

	SlimDX::XAPO::RegistrationProperties BaseProcessor::RegistrationProperties::get()
	{
		return SlimDX::XAPO::RegistrationProperties::FromUnmanaged( *ImplPointer->GetRegistrationPropertiesInternal() );
	}

	bool BaseProcessor::IsLocked::get()
	{
		return ImplPointer->IsLocked() > 0;
	}

	XAPOBaseImpl::XAPOBaseImpl( BaseProcessor^ processor, XAPO_REGISTRATION_PROPERTIES *pRegProperties )
		: CXAPOBase( pRegProperties )
	{
		m_processor = processor;
	}

	void XAPOBaseImpl::Process( UINT32 InputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS *pInputProcessParameters, UINT32 OutputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS *pOutputProcessParameters, BOOL IsEnabled )
	{
		try
		{
			array<BufferParameter>^ input = gcnew array<BufferParameter>( InputProcessParameterCount );
			for( int i = 0; i < input->Length; i++ )
			{
				BufferParameter p;
				p.Buffer = IntPtr( pInputProcessParameters[i].pBuffer );
				p.Flags = static_cast<BufferFlags>( pInputProcessParameters[i].BufferFlags );
				p.ValidFrameCount = pInputProcessParameters[i].ValidFrameCount;

				input[i] = p;
			}

			array<BufferParameter>^ output = gcnew array<BufferParameter>( OutputProcessParameterCount );
			for( int i = 0; i < output->Length; i++ )
			{
				BufferParameter p;
				p.Buffer = IntPtr( pOutputProcessParameters[i].pBuffer );
				p.Flags = static_cast<BufferFlags>( pOutputProcessParameters[i].BufferFlags );
				p.ValidFrameCount = pOutputProcessParameters[i].ValidFrameCount;

				output[i] = p;
			}

			m_processor->Process( input, output, IsEnabled > 0 );
		}
		catch(...)
		{
		}
	}
}
}