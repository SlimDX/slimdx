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
	namespace Direct3D9
	{
		value class VertexElement;
		enum class VertexFormat;
		enum class Format;

		public ref class D3DX
		{
		public:
			literal int Default = D3DX_DEFAULT;
			literal int DefaultNonPowerOf2 = D3DX_DEFAULT_NONPOW2;
			literal int FromFile = D3DX_FROM_FILE;
			literal int FormatFromFile = D3DFMT_FROM_FILE;

			static int GetDeclarationVertexSize( array<VertexElement>^ elements, int stream );
			static int GetFVFVertexSize( VertexFormat fvf );

			static Format MakeFourCC( Byte c1, Byte c2, Byte c3, Byte c4 );

			static bool DebugMute( bool mute );
		};
	}
}
