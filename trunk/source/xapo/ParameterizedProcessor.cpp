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
const IID IID_CXAPOParametersBase = __uuidof(IXAPOParameters);

#include "ParameterizedProcessor.h"

using namespace System;
using namespace SlimDX::Multimedia;

namespace SlimDX
{
namespace XAPO
{
	ParameterizedProcessor::ParameterizedProcessor( SlimDX::XAPO::RegistrationProperties properties, DataStream^ parameterBlocks, int blockSize, bool producer )
	{
		XAPO_REGISTRATION_PROPERTIES props = properties.ToUnmanaged();

		Construct( static_cast<IXAPOParameters*>( new XAPOParametersImpl( this, &props, reinterpret_cast<BYTE*>( parameterBlocks->PositionPointer ), blockSize, producer ) ) );
	}

	IntPtr ParameterizedProcessor::BeginProcess()
	{
		return IntPtr( ParamPointer->BeginProcess() );
	}

	void ParameterizedProcessor::EndProcess()
	{
		ParamPointer->EndProcess();
	}

	void ParameterizedProcessor::OnSetParameters( DataStream^ parameters )
	{
		SLIMDX_UNREFERENCED_PARAMETER( parameters );
	}

	void ParameterizedProcessor::GetParameters( DataStream^ parameters )
	{
		ParamPointer->GetParameters( parameters->PositionPointer, static_cast<UINT32>( parameters->RemainingLength ) );
	}

	void ParameterizedProcessor::SetParameters( DataStream^ parameters )
	{
		ParamPointer->SetParameters( parameters->PositionPointer, static_cast<UINT32>( parameters->RemainingLength ) );
	}

	bool ParameterizedProcessor::ParametersChanged::get()
	{
		return ParamPointer->ParametersChanged() > 0;
	}

	XAPOParametersImpl::XAPOParametersImpl( ParameterizedProcessor^ processor, XAPO_REGISTRATION_PROPERTIES *pRegProperties, BYTE *pParameterBlocks, UINT32 uParameterBlockByteSize, BOOL fProducer )
		: CXAPOParametersBase( pRegProperties, pParameterBlocks, uParameterBlockByteSize, fProducer )
	{
		m_processor = processor;
	}

	void XAPOParametersImpl::OnSetParameters( const void *pParameters, UINT32 ParameterByteSize )
	{
		m_processor->OnSetParameters( gcnew DataStream( pParameters, ParameterByteSize, true, false ) );
	}

	void XAPOParametersImpl::Process( UINT32 InputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS *pInputProcessParameters, UINT32 OutputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS *pOutputProcessParameters, BOOL IsEnabled )
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