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

#include "../math/Vector3.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D9
	{
		value class VertexElement;
		enum class VertexFormat;
		enum class Format;

		public ref class D3DX sealed
		{
		private:
			D3DX() { }

		public:
			literal int Default = D3DX_DEFAULT;
			literal int DefaultNonPowerOf2 = D3DX_DEFAULT_NONPOW2;
			literal int FromFile = D3DX_FROM_FILE;
			literal int FormatFromFile = D3DFMT_FROM_FILE;

			static int GetDeclarationVertexSize( array<VertexElement>^ elements, int stream );
			static int GetFVFVertexSize( VertexFormat fvf );

			static array<VertexElement>^ DeclaratorFromFVF( VertexFormat fvf );
			static VertexFormat FVFFromDeclarator( array<VertexElement>^ declarator );
			static array<VertexElement>^ GenerateOutputDeclaration( array<VertexElement>^ declaration );
			static int GetDeclarationLength( array<VertexElement>^ declaration );

			static Result GetRectanglePatchSize( float segmentCount, [Out] int% triangleCount, [Out] int% vertexCount );
			static Result GetTrianglePatchSize( float segmentCount, [Out] int% triangleCount, [Out] int% vertexCount );

			static Format MakeFourCC( System::Byte c1, System::Byte c2, System::Byte c3, System::Byte c4 );

			static bool DebugMute( bool mute );

			static array<int>^ OptimizeFaces( array<int>^ indices, int faceCount, int vertexCount );
			static array<int>^ OptimizeFaces( array<System::Int16>^ indices, int faceCount, int vertexCount );

			static array<int>^ OptimizeVertices( array<int>^ indices, int faceCount, int vertexCount );
			static array<int>^ OptimizeVertices( array<System::Int16>^ indices, int faceCount, int vertexCount );

			static bool CheckVersion( int d3dVersion, int d3dxVersion );

			static float FresnelTerm( float cosTheta, float refractionIndex );

			static array<Vector3>^ GetVectors( DataStream^ stream, int vertexCount, VertexFormat format );
			static array<Vector3>^ GetVectors( DataStream^ stream, int vertexCount, int stride );
		};
	}
}
