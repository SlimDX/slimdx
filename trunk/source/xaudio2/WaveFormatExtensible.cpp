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

#include "../Utilities.h"

#include "WaveFormatExtensible.h"

namespace SlimDX
{
namespace XAudio2
{
	WAVEFORMATEXTENSIBLE WaveFormatExtensible::ToUnmanaged()
	{
		WAVEFORMATEXTENSIBLE result;

		result.dwChannelMask = static_cast<DWORD>( ChannelMask );
		result.Format = Format.ToUnmanaged();
		result.Samples.wSamplesPerBlock = static_cast<WORD>( Samples );
		result.SubFormat = Utilities::ConvertManagedGuid( SubFormat );

		return result;
	}

	WaveFormatExtensible::WaveFormatExtensible( const WAVEFORMATEXTENSIBLE &format )
	{
		ChannelMask = static_cast<Speakers>( format.dwChannelMask );
		Format = WaveFormatExtended::FromUnmanaged( format.Format );
		Samples = format.Samples.wSamplesPerBlock;
		SubFormat = Utilities::ConvertNativeGuid( format.SubFormat );
	}

	WaveFormatExtensible^ WaveFormatExtensible::Clone()
	{
		WaveFormatExtensible^ result = gcnew WaveFormatExtensible();

		result->Format = Format;
		result->Samples = Samples;
		result->ChannelMask = ChannelMask;
		result->SubFormat = SubFormat;

		return result;
	}

	bool WaveFormatExtensible::operator == ( WaveFormatExtensible^ left, WaveFormatExtensible^ right )
	{
		if( ReferenceEquals( left, nullptr ) )
			return ReferenceEquals( right, nullptr );

		return WaveFormatExtensible::Equals( left, right );
	}

	bool WaveFormatExtensible::operator != ( WaveFormatExtensible^ left, WaveFormatExtensible^ right )
	{
		return !( left == right );
	}

	int WaveFormatExtensible::GetHashCode()
	{		
		return Format.GetHashCode() + Samples.GetHashCode() +
			ChannelMask.GetHashCode() + SubFormat.GetHashCode();
	}

	bool WaveFormatExtensible::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<WaveFormatExtensible^>( value ) );
	}

	bool WaveFormatExtensible::Equals( WaveFormatExtensible^ value )
	{
		if( value == nullptr )
			return false;

		if( ReferenceEquals( this, value ) )
			return true;

		return ( Format == value->Format &&
			Samples == value->Samples && ChannelMask == value->ChannelMask &&
			SubFormat == value->SubFormat );
	}

	bool WaveFormatExtensible::Equals( WaveFormatExtensible^ value1, WaveFormatExtensible^ value2 )
	{
		return value1->Equals( value2 );
	}
}
}