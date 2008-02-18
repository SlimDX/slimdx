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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class BaseMesh;
		ref class Mesh;
		ref class VertexBuffer;
		ref class IndexBuffer;

		ref class StreamShim : System::Runtime::InteropServices::ComTypes::IStream
		{
		private:
			System::IO::Stream^ m_WrappedStream;

			long long position;
			void SetSizeToPosition();

		public:
			StreamShim( System::IO::Stream^ stream );

			virtual void Clone( [Out] System::Runtime::InteropServices::ComTypes::IStream^% ppstm );
			virtual void Commit( int grfCommitFlags );
			virtual void CopyTo( System::Runtime::InteropServices::ComTypes::IStream^ pstm, long long cb, System::IntPtr pcbRead, System::IntPtr pcbWritten );
			virtual void LockRegion( long long libOffset, long long cb, int dwLockType );
			virtual void Read( [Out] array<unsigned char>^ pv, int cb, System::IntPtr pcbRead );
			virtual void Revert();
			virtual void Seek( long long dlibMove, int dwOrigin, System::IntPtr plibNewPosition );
			virtual void SetSize( long long libNewSize );
			virtual void Stat( [Out] System::Runtime::InteropServices::ComTypes::STATSTG% pstatstg, int grfStatFlag );
			virtual void UnlockRegion( long long libOffset, long long cb, int dwLockType );
			virtual void Write( array<unsigned char>^ pv, int cb, System::IntPtr pcbWritten );
		};

		public ref class ProgressiveMesh : public BaseMesh
		{
		private:
			array<ExtendedMaterial>^ materials;
			array<EffectInstance>^ effects;

		internal:
			ProgressiveMesh( ID3DXPMesh* mesh ) : BaseMesh( mesh ) { }

			property ID3DXPMesh* MeshPointer
			{
				ID3DXPMesh* get() { return static_cast<ID3DXPMesh*>( InternalPointer ); }
			}

		public:
			ProgressiveMesh( System::IntPtr pointer );
			ProgressiveMesh( Mesh^ mesh, array<AttributeWeights>^ attributeWeights, array<float>^ vertexWeights, int minimumValue, MeshSimplification options );
			ProgressiveMesh( Mesh^ mesh, array<AttributeWeights>^ attributeWeights, int minimumValue, MeshSimplification options );
			ProgressiveMesh( Mesh^ mesh, int minimumValue, MeshSimplification options );
			virtual ~ProgressiveMesh() { }

			static ProgressiveMesh^ FromStream( Device^ device, System::IO::Stream^ stream, MeshFlags flags );
			static void ToStream( ProgressiveMesh^ mesh, System::IO::Stream^ stream );

			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags flags, array<VertexElement>^ vertexDeclaration );
			ProgressiveMesh^ CloneProgressive( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat format );

			void GenerateVertexHistory( array<int>^ vertexHistory );
			array<int>^ GetAdjacency();
		
			Mesh^ Optimize( MeshOptimizeFlags flags );
			Mesh^ Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );

			void OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags );
			void OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap );

			void SetFaceCount( int faceCount );
			void SetVertexCount( int vertexCount );

			void TrimFaces( int newFaceMinimum, int newFaceMaximum );
			void TrimFaces( int newFaceMinimum, int newFaceMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void TrimVertices( int newVertexMinimum, int newVertexMaximum );
			void TrimVertices( int newVertexMinimum, int newVertexMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );

			array<ExtendedMaterial>^ GetMaterials() { return materials; }
			void SetMaterials( array<ExtendedMaterial>^ value ) { materials = value; }

			array<EffectInstance>^ GetEffects() { return effects; }
			void SetEffects( array<EffectInstance>^ value ) { effects = value; }

			property int MaximumFaceCount { int get(); }
			property int MaximumVertexCount { int get(); }
			property int MinimumFaceCount { int get(); }
			property int MinimumVertexCount { int get(); }
		};

		public ref class SimplificationMesh : ComObject
		{
			COMOBJECT(ID3DXSPMesh);

		internal:
			SimplificationMesh( ID3DXSPMesh *mesh ) { Construct(mesh); }

		public:
			SimplificationMesh( System::IntPtr pointer );
			SimplificationMesh( Mesh^ mesh, array<AttributeWeights>^ vertexAttributeWeights, array<float>^ vertexWeights );
			SimplificationMesh( Mesh^ mesh, array<AttributeWeights>^ vertexAttributeWeights );
			SimplificationMesh( Mesh^ mesh, array<float>^ vertexWeights );
			SimplificationMesh( Mesh^ mesh );
			virtual ~SimplificationMesh() { Destruct(); }

			Mesh^ Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap );
			Mesh^ Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration );

			Mesh^ Clone( Device^ device, MeshFlags options, VertexFormat fvf, [Out] array<int>^% vertexRemap );
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