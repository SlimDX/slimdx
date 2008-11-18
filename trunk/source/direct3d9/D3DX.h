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

		/// <summary>
		/// Contains miscellaneous constants and methods for use with D3DX.
		/// </summary>
		public ref class D3DX sealed
		{
		private:
			D3DX() { }

		public:
			/// <summary>
			/// The value used to signify that the default value for a parameter should be used.
			/// </summary>
			literal int Default = D3DX_DEFAULT;

			/// <summary>
			/// The default value for non power-of-two textures.
			/// </summary>
			literal int DefaultNonPowerOf2 = D3DX_DEFAULT_NONPOW2;

			/// <summary>
			/// Indicates that the method should load from file.
			/// </summary>
			literal int FromFile = D3DX_FROM_FILE;

			/// <summary>
			/// Indicates that the method should format from file.
			/// </summary>
			literal int FormatFromFile = D3DFMT_FROM_FILE;

			/// <summary>
			/// 
			/// </summary>
			static int GetDeclarationVertexSize( array<VertexElement>^ elements, int stream );
			static int GetFVFVertexSize( VertexFormat fvf );

			/// <summary>
			/// Retrieves a declarator from a Flexible Vertex Format (FVF) code.
			/// </summary>
			static array<VertexElement>^ DeclaratorFromFVF( VertexFormat fvf );

			/// <summary>
			/// Retrieves a Flexible Vertex Format (FVF) code from a declarator.
			/// </summary>
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

			/// <summary>
			/// Verifies that the compiled version of D3DX matches the runtime version of D3DX.
			/// </summary>
			/// <returns><c>true</c> if the versions match; otherwise, <c>false</c>.</returns>
			static bool CheckVersion();

			static float FresnelTerm( float cosTheta, float refractionIndex );

			static array<Vector3>^ GetVectors( DataStream^ stream, int vertexCount, VertexFormat format );
			static array<Vector3>^ GetVectors( DataStream^ stream, int vertexCount, int stride );
		};
	}
}
