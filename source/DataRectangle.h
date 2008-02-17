/*
* Copyright (c) 2007 SlimDX Group
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
	ref class DataStream;

	/// <remarks>
	/// A DataRectangle provides supporting information for a DataStream whose
	/// data is organized within two dimensions (a rectangle).
	/// </remarks>
	public value class DataRectangle
	{
	private:
		int m_Pitch;
		DataStream^ m_Data;

	internal:
		DataRectangle( int pitch, DataStream^ data );

	public:
		/// <summary>
		/// Gets the number of bytes of data between two consecutive (1D) rows of data.
		/// </summary>
		property int Pitch
		{
			int get();
		}

		/// <summary>
		/// Gets the DataStream containing the actual data bytes.
		/// </summary>
		property DataStream^ Data
		{
			DataStream^ get();
		}
	};
}

