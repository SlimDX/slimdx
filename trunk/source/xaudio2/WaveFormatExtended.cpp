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

#include "WaveFormatExtended.h"

namespace SlimDX
{
namespace XAudio2
{
	WAVEFORMATEX WaveFormatExtended::ToUnmanaged()
	{
		WAVEFORMATEX result;

		result.wFormatTag = static_cast<WORD>( FormatTag );
		result.cbSize = Size;
		result.nAvgBytesPerSec = AverageBytesPerSecond;
		result.nBlockAlign = BlockAlignment;
		result.nChannels = Channels;
		result.nSamplesPerSec = SamplesPerSecond;
		result.wBitsPerSample = BitsPerSample;

		return result;
	}

	WaveFormatExtended WaveFormatExtended::FromUnmanaged( const WAVEFORMATEX &format )
	{
		WaveFormatExtended result;

		result.FormatTag = static_cast<WaveFormatTag>( format.wFormatTag );
		result.Size = format.cbSize;
		result.AverageBytesPerSecond = format.nAvgBytesPerSec;
		result.BlockAlignment = format.nBlockAlign;
		result.Channels = format.nChannels;
		result.SamplesPerSecond = format.nSamplesPerSec;
		result.BitsPerSample = format.wBitsPerSample;

		return result;
	}

	bool WaveFormatExtended::operator == ( WaveFormatExtended left, WaveFormatExtended right )
	{
		return WaveFormatExtended::Equals( left, right );
	}

	bool WaveFormatExtended::operator != ( WaveFormatExtended left, WaveFormatExtended right )
	{
		return !WaveFormatExtended::Equals( left, right );
	}

	int WaveFormatExtended::GetHashCode()
	{
		return FormatTag.GetHashCode() + Channels.GetHashCode() + SamplesPerSecond.GetHashCode() +
			AverageBytesPerSecond.GetHashCode() + BlockAlignment.GetHashCode() + BitsPerSample.GetHashCode() +
			Size.GetHashCode();
	}

	bool WaveFormatExtended::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<WaveFormatExtended>( value ) );
	}

	bool WaveFormatExtended::Equals( WaveFormatExtended value )
	{
		return ( FormatTag == value.FormatTag && Channels == value.Channels && 
			SamplesPerSecond == value.SamplesPerSecond && AverageBytesPerSecond == value.AverageBytesPerSecond &&
			BlockAlignment == value.BlockAlignment && BitsPerSample == value.BitsPerSample &&
			Size == value.Size );
	}

	bool WaveFormatExtended::Equals( WaveFormatExtended% value1, WaveFormatExtended% value2 )
	{
		return ( value1.FormatTag == value2.FormatTag && value1.Channels == value2.Channels && 
			value1.SamplesPerSecond == value2.SamplesPerSecond && value1.AverageBytesPerSecond == value2.AverageBytesPerSecond &&
			value1.BlockAlignment == value2.BlockAlignment && value1.BitsPerSample == value2.BitsPerSample &&
			value1.Size == value2.Size );
	}
}
}