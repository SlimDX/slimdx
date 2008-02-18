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
	value class Matrix;

	namespace Direct3D9
	{
		value class VertexElement;
		enum class VertexFormat;

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public ref class BoneCombination
		{
		internal:
			D3DXBONECOMBINATION ToUnmanaged();
			static BoneCombination^ FromUnmanaged( const D3DXBONECOMBINATION &bone );

		public:
			property int AttributeId;
			property int FaceStart;
			property int FaceCount;
			property int VertexStart;
			property int VertexCount;
			property array<int>^ BoneIds;
		};

		public ref class SkinInfo : public ComObject
		{
			COMOBJECT(ID3DXSkinInfo);

		internal:
			SkinInfo( ID3DXSkinInfo* skinInfo );

		public:
			SkinInfo( System::IntPtr pointer );
			SkinInfo( int vertexCount, array<VertexElement>^ vertexDeclaration, int boneCount );
			SkinInfo( BaseMesh^ mesh, int boneCount, array<BoneCombination^>^ boneCombinationTable );
			SkinInfo( int vertexCount, VertexFormat fvf, int boneCount );
			virtual ~SkinInfo() { Destruct(); }

			SkinInfo^ Clone();

			Mesh^ ConvertToBlendedMesh( Mesh^ mesh, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap, [Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable );
			Mesh^ ConvertToBlendedMesh( Mesh^ mesh, [Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable );

			Mesh^ ConvertToIndexedBlendedMesh( Mesh^ mesh, int paletteSize, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap, [Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable );
			Mesh^ ConvertToIndexedBlendedMesh( Mesh^ mesh, int paletteSize, [Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable );

			int FindBoneVertexInfluenceIndex( int bone, int vertex );

			void GetBoneInfluence( int bone, [Out] array<int>^% vertices, [Out] array<float>^% weights );
			void SetBoneInfluence( int bone, array<int>^ vertices, array<float>^ weights );

			System::String^ GetBoneName( int bone );
			void SetBoneName( int bone, System::String^ name );

			void GetBoneVertexInfluence( int bone, int influence, [Out] float% weight, [Out] int% vertex );
			void SetBoneVertexInfluence( int bone, int influence, float weight );

			Matrix GetBoneOffsetMatrix( int bone );
			void SetBoneOffsetMatrix( int bone, Matrix transform );

			array<VertexElement>^ GetDeclaration();
			void SetDeclaration( array<VertexElement>^ declaration );

			int GetMaxFaceInfluences( IndexBuffer^ indexBuffer, int faceCount );
			int GetBoneInfluenceCount( int bone );

			void Remap( array<int>^ remapData );

			void UpdateSkinnedMesh( Matrix boneTransform, Matrix boneInvTranspose, DataStream^ source, DataStream^ destination );

			property int MaximumVertexInfluences { int get(); }
			property int BoneCount { int get(); }

			property float MinimumBoneInfluence
			{
				float get();
				void set( float value );
			}

			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get();
				void set( SlimDX::Direct3D9::VertexFormat format );
			}
		};
	}
}
