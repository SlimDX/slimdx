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

namespace SlimDX
{
	[System::Flags]
	public enum class Speakers : System::Int32
	{
		FrontLeft = SPEAKER_FRONT_LEFT,
		FrontRight = SPEAKER_FRONT_RIGHT,
		FrontCenter = SPEAKER_FRONT_CENTER,
		LowFrequency = SPEAKER_LOW_FREQUENCY,
		BackLeft = SPEAKER_BACK_LEFT,
		BackRight = SPEAKER_BACK_RIGHT,
		FrontLeftOfCenter = SPEAKER_FRONT_LEFT_OF_CENTER,
		FrontRightOfCenter = SPEAKER_FRONT_RIGHT_OF_CENTER,
		BackCenter = SPEAKER_BACK_CENTER,
		SideLeft = SPEAKER_SIDE_LEFT,
		SideRight = SPEAKER_SIDE_RIGHT,
		TopCenter = SPEAKER_TOP_CENTER,
		TopFrontLeft = SPEAKER_TOP_FRONT_LEFT,
		TopFrontCenter = SPEAKER_TOP_FRONT_CENTER,
		TopFrontRight = SPEAKER_TOP_FRONT_RIGHT,
		TopBackLeft = SPEAKER_TOP_BACK_LEFT,
		TopBackCenter = SPEAKER_TOP_BACK_CENTER,
		TopBackRight = SPEAKER_TOP_BACK_RIGHT,

		Reserved = SPEAKER_RESERVED,

#pragma warning(disable: 4369)
		All = SPEAKER_ALL,
#pragma warning(default: 4369)

		Mono = SPEAKER_MONO,
		Stereo = SPEAKER_STEREO,
		TwoPointOne = SPEAKER_2POINT1,
		Surround = SPEAKER_SURROUND,
		Quadrophonic = SPEAKER_QUAD,
		FourPointOne = SPEAKER_4POINT1,
		FivePointOne = SPEAKER_5POINT1,
		SevenPointOne = SPEAKER_7POINT1,
		FivePointOneSurround = SPEAKER_5POINT1_SURROUND,
		SevenPointOneSurround = SPEAKER_7POINT1_SURROUND,
	};
}