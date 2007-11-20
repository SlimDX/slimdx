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
		ref class BaseMesh;
		ref class Mesh;
		ref class VertexBuffer;
		ref class IndexBuffer;
		ref class BufferWrapper;

		ref class StreamShim : System::Runtime::InteropServices::ComTypes::IStream
		{
		private:
			Stream^ m_WrappedStream;

			long long position;
			void SetSizeToPosition();

		public:
			StreamShim( Stream^ stream );

			virtual void Clone( [Out] System::Runtime::InteropServices::ComTypes::IStream^% ppstm );
			virtual void Commit( int grfCommitFlags );
			virtual void CopyTo( System::Runtime::InteropServices::ComTypes::IStream^ pstm, long long cb, IntPtr pcbRead, IntPtr pcbWritten );
			virtual void LockRegion( long long libOffset, long long cb, int dwLockType );
			virtual void Read( [Out] array<unsigned char>^ pv, int cb, IntPtr pcbRead );
			virtual void Revert();
			virtual void Seek( long long dlibMove, int dwOrigin, IntPtr plibNewPosition );
			virtual void SetSize( long long libNewSize );
			virtual void Stat( [Out] System::Runtime::InteropServices::ComTypes::STATSTG% pstatstg, int grfStatFlag );
			virtual void UnlockRegion( long long libOffset, long long cb, int dwLockType );
			virtual void Write( array<unsigned char>^ pv, int cb, IntPtr pcbWritten );
		};

		public enum class MeshSimplification : Int32
		{
			Vertex = D3DXMESHSIMP_VERTEX,
			Face = D3DXMESHSIMP_FACE
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class AttributeWeights
		{
		public:
			property float Position;
			property float Boundary;
			property float Normal;
			property float Diffuse;
			property float Specular;
			property float TextureCoordinate1;
			property float TextureCoordinate2;
			property float TextureCoordinate3;
			property float TextureCoordinate4;
			property float TextureCoordinate5;
			property float TextureCoordinate6;
			property float TextureCoordinate7;
			property float TextureCoordinate8;
			property float Tangent;
			property float Binormal;
		};

		public ref class ProgressiveMesh : public BaseMesh
		{
		internal:
			ProgressiveMesh( ID3DXPMesh* mesh ) : BaseMesh( mesh ) { }

			property ID3DXPMesh* MeshPointer
			{
				ID3DXPMesh* get() { return static_cast<ID3DXPMesh*>( m_Pointer ); }
			}

		public:
			ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights, 
				array<float>^ vertexWeights, int minimumValue, MeshSimplification options );
			ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights, 
				int minimumValue, MeshSimplification options );
			ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, int minimumValue, MeshSimplification options );
			virtual ~ProgressiveMesh() { }

			static ProgressiveMesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags, 
				[Out] BufferWrapper^% materials, [Out] BufferWrapper^% effects, [Out] int% materialCount );

			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags flags, array<VertexElement>^ vertexDeclaration );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat format );

			void GenerateVertexHistory( array<int>^ vertexHistory );
			array<int>^ GetAdjacency();
		
			Mesh^ Optimize( MeshOptimizeFlags flags );
			Mesh^ Optimize( MeshOptimizeFlags flags, [Out] array<int>^% adjacencyOut );
			Mesh^ Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] BufferWrapper^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] BufferWrapper^% vertexRemap );

			void OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags );
			void OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap );

			void Save( Stream^ stream, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects );
			void SetFaceCount( int faceCount );
			void SetVertexCount( int vertexCount );

			void TrimFaces( int newFaceMinimum, int newFaceMaximum );
			void TrimFaces( int newFaceMinimum, int newFaceMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void TrimVertices( int newVertexMinimum, int newVertexMaximum );
			void TrimVertices( int newVertexMinimum, int newVertexMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );

			property int MaximumFaceCount { int get(); }
			property int MaximumVertexCount { int get(); }
			property int MinimumFaceCount { int get(); }
			property int MinimumVertexCount { int get(); }
		};

		public ref class SimplificationMesh : DirectXObject<ID3DXSPMesh>
		{
		internal:
			SimplificationMesh( ID3DXSPMesh *mesh ) : DirectXObject( mesh ) { }

		public:
			SimplificationMesh( Mesh^ mesh, array<int>^% adjacency, array<AttributeWeights>^ vertexAttributeWeights, array<float>^ vertexWeights );
			SimplificationMesh( Mesh^ mesh, array<int>^% adjacency, array<AttributeWeights>^ vertexAttributeWeights );
			SimplificationMesh( Mesh^ mesh, array<int>^% adjacency, array<float>^ vertexWeights );
			SimplificationMesh( Mesh^ mesh, array<int>^% adjacency );
			virtual ~SimplificationMesh() { Destruct(); }
			DXOBJECT_FUNCTIONS;

			Mesh^ Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% adjacencyOut, [Out] array<int>^% vertexRemap );
			Mesh^ Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% adjacencyOut );
			Mesh^ Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration );

			Mesh^ Clone( Device^ device, MeshFlags options, VertexFormat fvf, [Out] array<int>^% adjacencyOut, [Out] array<int>^% vertexRemap );
			Mesh^ Clone( Device^ device, MeshFlags options, VertexFormat fvf, [Out] array<int>^% adjacencyOut );
			Mesh^ Clone( Device^ device, MeshFlags options, VertexFormat fvf );

			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap, [Out] array<float>^% errorsByFace );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration );

			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, VertexFormat fvf, [Out] array<int>^% vertexRemap, [Out] array<float>^% errorsByFace );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, VertexFormat fvf, [Out] array<int>^% vertexRemap );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags options, VertexFormat fvf );

			array<VertexElement>^ GetDeclaration();
			Device^ GetDevice();

			array<AttributeWeights>^ GetVertexAttributeWeights();
			array<float>^ GetVertexWeights();

			void ReduceFaces( int faces );
			void ReduceVertices( int vertices );

			property VertexFormat VertexFormat { SlimDX::Direct3D9::VertexFormat get(); }
			property int MaximumFaceCount { int get(); }
			property int MaximumVertexCount { int get(); }
			property int FaceCount { int get(); }
			property int VertexCount { int get(); }
			property MeshFlags CreationOptions { MeshFlags get(); }
		};
	}
}