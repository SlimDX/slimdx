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
	value class Matrix;

	namespace Direct3D9
	{
		value class VertexElement;
		enum class VertexFormat;

		public ref class BoneCombination sealed
		{
		public:
			property int AttribId;
			property int FaceStart;
			property int FaceCount;
			property int VertexStart;
			property int VertexCount;
			property array<int>^ BoneIds;
		};

		public ref class SkinInfo sealed : public DirectXObject<ID3DXSkinInfo>
		{
		public:
			SkinInfo( ID3DXSkinInfo* skinInfo );
			SkinInfo( int numVertices, array<VertexElement>^ vertexDecl, int numBones );
			SkinInfo( int numVertices, VertexFormat fvf, int numBones );
			~SkinInfo() { Destruct(); }

			int FindBoneVertexInfluenceIndex( int bone, int vertex );

			void GetBoneInfluence( int bone, [Out] array<int>^% vertices, [Out] array<int>^% weights );
			void SetBoneInfluence( int bone, array<int>^ vertices, array<int>^ weights );

			String^ GetBoneName( int bone );
			void SetBoneName( int bone, String^ name );

			void GetBoneVertexInfluence( int bone, int influence, [Out] float% weight, [Out] int% vertex );
			void SetBoneVertexInfluence( int bone, int influence, float weight );

			Matrix GetBoneOffsetMatrix( int bone );
			void SetBoneOffsetMatrix( int bone, Matrix transform );

			void Remap( array<int>^ remapData );
			//void UpdateSkinnedMesh( Matrix boneTransform, Matrix boneTransformInverseTranspose, 

			property int MinBoneInfluence
			{
				int get();
				void set( int minimum );
			}

			property int MaxVertexInfluence
			{
				int get();
			}

			property int BoneCount
			{
				int get();
			}

			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get();
				void set( SlimDX::Direct3D9::VertexFormat format );
			}
		};
	}
}
