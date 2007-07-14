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
#include "Utils.h"
#include "DirectXObject.h"

namespace SlimDX
{
	void Utils::ReportNotDisposed( DirectXBase^ obj )
	{
		String^ message = String::Format( "Object of type {0} not disposed.", obj->GetType()->ToString() );
		//Debug::WriteLine( message );
	}
	
	void Utils::MarkDisposed( bool %disposed, Object^ obj )
	{
		if( disposed )
			throw gcnew ObjectDisposedException( obj->GetType()->ToString() );

		disposed = true;
		GC::SuppressFinalize( obj );
	}

	/// <summary>
	/// Function to convert a GDI+ rectangle to a standard RECT.
	/// </summary>
	/// <param name="rect">Rectangle to convert.</param>
	/// <param name="outrect">Output rectangle.</param>
	void Utils::ConvertRect(Drawing::Rectangle rect, RECT *outrect)
	{
		if (outrect == NULL)
			throw gcnew ArgumentNullException("outrect");

		outrect->left = rect.Left;
		outrect->top = rect.Top;
		outrect->right = rect.Right;
		outrect->bottom = rect.Bottom;
	}

	/// <summary>
	/// Function to convert a standard RECT to a GDI+ rectangle.
	/// </summary>
	/// <param name="rect">RECT to convert.</param>
	/// <returns>A GDI+ rectangle structure.</returns>
	Drawing::Rectangle Utils::ConvertRect(RECT rect)
	{
		return Drawing::Rectangle(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}

	array<Byte>^ Utils::ReadStream( Stream^ stream, int readLength )
	{
		if( stream == nullptr )
			throw gcnew ArgumentNullException( "stream" );
		if( !stream->CanRead )
			throw gcnew NotSupportedException();

		if( readLength == 0 )
			readLength = (int) ( stream->Length - stream->Position );
		if( readLength < 0 )
			throw gcnew ArgumentOutOfRangeException( "readLength" );
		if( readLength == 0 )
			return gcnew array<Byte>( 0 );

		array<Byte>^ buffer = gcnew array<Byte>( readLength ); 
		int bytesRead = 0;

		while( bytesRead < readLength )
		{
			bytesRead += stream->Read( buffer, bytesRead, readLength - bytesRead );
		}

		return buffer;
	}
}