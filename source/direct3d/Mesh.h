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

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		[Flags]
		public enum class MeshFlags : Int32
		{
			Use32Bit = D3DXMESH_32BIT,
			DoNotClip = D3DXMESH_DONOTCLIP,
			Points = D3DXMESH_POINTS,
			RtPatches = D3DXMESH_RTPATCHES,
			NPatches = D3DXMESH_NPATCHES,
			VbSystemMem = D3DXMESH_VB_SYSTEMMEM,
			VbManaged = D3DXMESH_VB_MANAGED,
			VbWriteOnly = D3DXMESH_VB_WRITEONLY,
			VbDynamic = D3DXMESH_VB_DYNAMIC,
			VbSoftware = D3DXMESH_VB_SOFTWAREPROCESSING,
			IbSystemMem = D3DXMESH_IB_SYSTEMMEM,
			IbManaged = D3DXMESH_IB_MANAGED,
			IbWriteOnly = D3DXMESH_IB_WRITEONLY,
			IbDynamic = D3DXMESH_IB_DYNAMIC,
			IbSoftware = D3DXMESH_IB_SOFTWAREPROCESSING,

			VbShare = D3DXMESH_VB_SHARE,

			UseHardwareOnly = D3DXMESH_USEHWONLY,

			// Helper options
			SystemMem = D3DXMESH_SYSTEMMEM,
			Managed = D3DXMESH_MANAGED,
			WriteOnly = D3DXMESH_WRITEONLY,
			Dynamic = D3DXMESH_DYNAMIC,
			Software = D3DXMESH_SOFTWAREPROCESSING,
		};

		[Flags]
		public enum class TangentOptions : Int32
		{
			None = 0,
			WrapU = D3DXTANGENT_WRAP_U,
			WrapV = D3DXTANGENT_WRAP_V,
			WrapUV = D3DXTANGENT_WRAP_UV,
			DontNormalizePartials = D3DXTANGENT_DONT_NORMALIZE_PARTIALS,
			DontOrthogonalize = D3DXTANGENT_DONT_ORTHOGONALIZE,
			OrthogonalizeFromV = D3DXTANGENT_ORTHOGONALIZE_FROM_V,
			OrthogonalizeFromU = D3DXTANGENT_ORTHOGONALIZE_FROM_U,
			WeightByArea = D3DXTANGENT_WEIGHT_BY_AREA,
			WeightEqual = D3DXTANGENT_WEIGHT_EQUAL,
			WindCW = D3DXTANGENT_WIND_CW,
			CalculateNormals = D3DXTANGENT_CALCULATE_NORMALS,
			GenerateInPlace = D3DXTANGENT_GENERATE_IN_PLACE,
		};

		ref class Mesh;

		public ref class BaseMesh abstract : public DirectXObject
		{
		private:
			ID3DXBaseMesh* m_BaseMesh;

		protected:
			BaseMesh( ID3DXBaseMesh* baseMesh ) : m_BaseMesh( baseMesh )
			{ }

		internal:
			property ID3DXBaseMesh* BasePointer
			{
				ID3DXBaseMesh* get() { return m_BaseMesh; }
			}

		public:
			Mesh^ Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements  );

			void DrawSubset( int subset );
		};

		public ref class Mesh : public BaseMesh
		{
		private:
			ID3DXMesh* m_Mesh;

		internal:
			property ID3DXMesh* InternalPointer
			{
				ID3DXMesh* get() { return m_Mesh; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Mesh; }
				virtual void set( IUnknown* value ) override { m_Mesh = (ID3DXMesh*) value; }
			}

		public:
			Mesh( ID3DXMesh* mesh );
			
			static Mesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags );

			static Mesh^ FromFile( Device^ device, String^ fileName, MeshFlags flags );

			void ComputeTangentFrame( TangentOptions options );
		};
	}
}
