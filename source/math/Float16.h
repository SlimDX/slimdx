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

//using namespace System;
//using namespace System::Globalization;
//using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class Float16
	{
	private:
		System::UInt16 m_Value;

		static Float16()
		{
			Float16::Epsilon = 0.0004887581f;
			Float16::MaxValue = 65504.0f;
			Float16::MinValue = 6.103516E-05f;
		}

	public:
		literal int PrecisionDigits = 3;
		literal int MantissaBits = 11;
		literal int MaximumDecimalExponent = 4;
		literal int MaximumBinaryExponent = 15;
		literal int MinimumDecimalExponent = -4;
		literal int MinimumBinaryExponent = -12;
		literal int ExponentRadix = 2;
		literal int AdditionRounding = 1;
		static initonly float Epsilon;
		static initonly float MaxValue;
		static initonly float MinValue;

		Float16( float value );

		static array<float>^ ConvertToFloat( array<Float16>^ values );
		static array<Float16>^ ConvertToFloat16( array<float>^ values );

		static explicit operator Float16( float value );
		static operator float( Float16 value );

		static bool operator == ( Float16 left, Float16 right );
		static bool operator != ( Float16 left, Float16 right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Float16 other );
		static bool Equals( Float16% value1, Float16% value2 );
	};
}