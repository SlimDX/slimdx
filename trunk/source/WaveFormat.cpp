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

#include <xaudio2.h>

#include "Utilities.h"
#include "WaveFormat.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	std::auto_ptr<WAVEFORMATEX> WaveFormat::ToUnmanaged( WaveFormat^ format )
	{
		array<Byte>^ bytes = format->GetBytes();
		pin_ptr<Byte> pinnedBytes = &bytes[0];

		BYTE *result = new BYTE[bytes->Length];
		memcpy( result, pinnedBytes, bytes->Length * sizeof( BYTE ) );

		return std::auto_ptr<WAVEFORMATEX>( reinterpret_cast<WAVEFORMATEX*>( result ) );
	}

	WaveFormat^ WaveFormat::FromUnmanaged( const WAVEFORMATEX &format )
	{
		WaveFormat^ result = gcnew WaveFormat();

		result->FormatTag = static_cast<WaveFormatTag>( format.wFormatTag );
		result->AverageBytesPerSecond = format.nAvgBytesPerSec;
		result->BitsPerSample = format.wBitsPerSample;
		result->BlockAlignment = format.nBlockAlign;
		result->Channels = format.nChannels;
		result->SamplesPerSecond = format.nSamplesPerSec;
		result->Size = format.cbSize;

		return result;
	}

	array<Byte>^ WaveFormat::GetBytes()
	{
		List<Byte>^ result = gcnew List<Byte>();

#if _MSC_VER < 1500
#pragma message( "This code's broken on VS 2005. I don't know how to fix it yet." )
#else
		result->AddRange( BitConverter::GetBytes( static_cast<short>( FormatTag ) ) );
		result->AddRange( BitConverter::GetBytes( Channels ) );
		result->AddRange( BitConverter::GetBytes( SamplesPerSecond ) );
		result->AddRange( BitConverter::GetBytes( AverageBytesPerSecond ) );
		result->AddRange( BitConverter::GetBytes( BlockAlignment ) );
		result->AddRange( BitConverter::GetBytes( BitsPerSample ) );
		result->AddRange( BitConverter::GetBytes( Size ) );
#endif

		return result->ToArray();
	}

	WaveFormat^ WaveFormat::Clone()
	{
		WaveFormat^ result = gcnew WaveFormat();

		result->AverageBytesPerSecond = AverageBytesPerSecond;
		result->BitsPerSample = BitsPerSample;
		result->BlockAlignment = BlockAlignment;
		result->Channels = Channels;
		result->SamplesPerSecond = SamplesPerSecond;

		return result;
	}

	bool WaveFormat::operator == ( WaveFormat^ left, WaveFormat^ right )
	{
		if( ReferenceEquals( left, nullptr ) )
			return ReferenceEquals( right, nullptr );

		return WaveFormat::Equals( left, right );
	}

	bool WaveFormat::operator != ( WaveFormat^ left, WaveFormat^ right )
	{
		return !( left == right );
	}

	int WaveFormat::GetHashCode()
	{		
		return FormatTag.GetHashCode() + Channels.GetHashCode() +
			SamplesPerSecond.GetHashCode() + AverageBytesPerSecond.GetHashCode() +
			BlockAlignment.GetHashCode() + BitsPerSample.GetHashCode();
	}

	bool WaveFormat::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<WaveFormat^>( value ) );
	}

	bool WaveFormat::Equals( WaveFormat^ value )
	{
		if( value == nullptr )
			return false;

		if( ReferenceEquals( this, value ) )
			return true;

		return ( FormatTag == value->FormatTag &&
			Channels == value->Channels && SamplesPerSecond == value->SamplesPerSecond &&
			AverageBytesPerSecond == value->AverageBytesPerSecond && BlockAlignment == value->BlockAlignment &&
			BitsPerSample == value->BitsPerSample );
	}

	bool WaveFormat::Equals( WaveFormat^ value1, WaveFormat^ value2 )
	{
		return value1->Equals( value2 );
	}
}