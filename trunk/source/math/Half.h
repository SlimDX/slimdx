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
	/// <summary>
	/// A half precision (16 bit) floating point value.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class Half
	{
	private:
		System::UInt16 m_Value;

		static Half()
		{
			Half::Epsilon = 0.0004887581f;
			Half::MaxValue = 65504.0f;
			Half::MinValue = 6.103516E-05f;
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

		Half( float value );

		static array<float>^ ConvertToFloat( array<Half>^ values );
		static array<Half>^ ConvertToHalf( array<float>^ values );

		static explicit operator Half( float value );
		static operator float( Half value );

		static bool operator == ( Half left, Half right );
		static bool operator != ( Half left, Half right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Half other );
		static bool Equals( Half% value1, Half% value2 );
	};
}