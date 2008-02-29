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

#include "../math/Matrix.h"
#include "../math/Ray.h"

#include "XFile.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class SkinInfo;

		public value class ExtendedMaterial : System::IEquatable<ExtendedMaterial>
		{
		internal:
			static D3DXMATERIAL ToUnmanaged( ExtendedMaterial material );
			static ExtendedMaterial FromUnmanaged( const D3DXMATERIAL &material );
			static array<ExtendedMaterial>^ FromBuffer( ID3DXBuffer* buffer, unsigned int count );

		public:
			property Material MaterialD3D;
			property System::String^ TextureFileName;

			static bool operator == ( ExtendedMaterial left, ExtendedMaterial right );
			static bool operator != ( ExtendedMaterial left, ExtendedMaterial right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ExtendedMaterial other );
			static bool Equals( ExtendedMaterial% value1, ExtendedMaterial% value2 );
		};

		public value class EffectDefault : System::IEquatable<EffectDefault>
		{
		public:
			property System::String^ ParameterName;
			property EffectDefaultType Type;
			property DataStream^ Value;

			static bool operator == ( EffectDefault left, EffectDefault right );
			static bool operator != ( EffectDefault left, EffectDefault right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( EffectDefault other );
			static bool Equals( EffectDefault% value1, EffectDefault% value2 );
		};

		public value class EffectInstance : System::IEquatable<EffectInstance>
		{
		internal:
			static EffectInstance FromUnmanaged( const D3DXEFFECTINSTANCE &effect );
			static D3DXEFFECTINSTANCE ToUnmanaged( EffectInstance effect );
			static array<EffectInstance>^ FromBuffer( ID3DXBuffer* buffer, unsigned int count );

		public:
			property System::String^ EffectFileName;
			property array<EffectDefault>^ Defaults;

			static bool operator == ( EffectInstance left, EffectInstance right );
			static bool operator != ( EffectInstance left, EffectInstance right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( EffectInstance other );
			static bool Equals( EffectInstance% value1, EffectInstance% value2 );
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class AttributeRange : System::IEquatable<AttributeRange>
		{
		public:
			property int AttribId;
			property int FaceStart;
			property int FaceCount;
			property int VertexStart;
			property int VertexCount;

			static bool operator == ( AttributeRange left, AttributeRange right );
			static bool operator != ( AttributeRange left, AttributeRange right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( AttributeRange other );
			static bool Equals( AttributeRange% value1, AttributeRange% value2 );
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class GlyphMetricsFloat : System::IEquatable<GlyphMetricsFloat>
		{
		public:
			property float BlackBoxX;
			property float BlackBoxY;
			property System::Drawing::PointF GlyphOrigin;
			property float CellIncX;
			property float CellIncY;

			static bool operator == ( GlyphMetricsFloat left, GlyphMetricsFloat right );
			static bool operator != ( GlyphMetricsFloat left, GlyphMetricsFloat right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( GlyphMetricsFloat other );
			static bool Equals( GlyphMetricsFloat% value1, GlyphMetricsFloat% value2 );
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class AttributeWeights : System::IEquatable<AttributeWeights>
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

			static bool operator == ( AttributeWeights left, AttributeWeights right );
			static bool operator != ( AttributeWeights left, AttributeWeights right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( AttributeWeights other );
			static bool Equals( AttributeWeights% value1, AttributeWeights% value2 );
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class IntersectInformation : System::IEquatable<IntersectInformation>
		{
		public:
			property int FaceIndex;
			property float U;
			property float V;
			property float Distance;

			static bool operator == ( IntersectInformation left, IntersectInformation right );
			static bool operator != ( IntersectInformation left, IntersectInformation right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( IntersectInformation other );
			static bool Equals( IntersectInformation% value1, IntersectInformation% value2 );
		};

		ref class Mesh;
		ref class VertexBuffer;
		ref class IndexBuffer;
		enum class VertexFormat;

		public ref class BaseMesh abstract : public ComObject
		{
			COMOBJECT_BASE(ID3DXBaseMesh);

		protected:
			BaseMesh() { }

		public:
			Mesh^ Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements );
			Mesh^ Clone( Device^ device, MeshFlags flags, VertexFormat fvf );

			property Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}

			IndexBuffer^ GetIndexBuffer();
			VertexBuffer^ GetVertexBuffer();
			array<VertexElement>^ GetDeclaration();
			array<AttributeRange>^ GetAttributeTable();

			DataStream^ LockIndexBuffer( LockFlags flags );
			Result UnlockIndexBuffer();

			DataStream^ LockVertexBuffer( LockFlags flags );
			Result UnlockVertexBuffer();

			array<int>^ GenerateAdjacency( float epsilon );
			array<int>^ ConvertAdjacencyToPointReps( array<int>^ adjacency );
			array<int>^ ConvertPointRepsToAdjacency( array<int>^ pointReps );
			Result UpdateSemantics( array<VertexElement>^ elements );

			Result DrawSubset( int subset );

			IndexBuffer^ ConvertSubsetToSingleStrip( int attributeId, MeshFlags options, [Out] int% indexCount );
			IndexBuffer^ ConvertSubsetToStrips( int attributeId, MeshFlags options, [Out] int% indexCount, [Out] array<int>^% stripLengths );

			bool Intersects( Ray ray, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits );
			bool Intersects( Ray ray, [Out] float% distance );
			bool Intersects( Ray ray );

			bool IntersectsSubset( Ray ray, int attributeId, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits );
			bool IntersectsSubset( Ray ray, int attributeId, [Out] float% distance );
			bool IntersectsSubset( Ray ray, int attributeId );

			property int FaceCount { int get(); }
			property int VertexCount { int get(); }
			property VertexFormat VertexFormat { SlimDX::Direct3D9::VertexFormat get(); }
			property int BytesPerVertex { int get(); }
			property MeshFlags CreationOptions { MeshFlags get(); }
		};

		public ref class Mesh : public BaseMesh
		{
			COMOBJECT(ID3DXMesh, Mesh);

		private:
			array<int>^ adjacency;
			array<ExtendedMaterial>^ materials;
			array<EffectInstance>^ effects;
			SkinInfo^ skinInfo;			

		internal:
			void SetAdjacency( DWORD *adjacency );

		public:
			Mesh( SlimDX::Direct3D9::Device^ device, int faceCount, int vertexCount, MeshFlags options, array<VertexElement>^ vertexDeclaration );
			Mesh( SlimDX::Direct3D9::Device^ device, int faceCount, int vertexCount, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf );
			virtual ~Mesh() { }
			static Mesh^ FromPointer( System::IntPtr pointer );

			static Mesh^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, MeshFlags flags );
			static Mesh^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, MeshFlags flags );
			static Mesh^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, MeshFlags flags );
			static Mesh^ FromXFile( SlimDX::Direct3D9::Device^ device, XFileData^ xfile, MeshFlags flags );

			static Result ToXFile( Mesh^ mesh, System::String^ fileName, XFileFormat format, System::Runtime::InteropServices::CharSet charSet );
			static Result ToXFile( Mesh^ mesh, System::String^ fileName, XFileFormat format );

			static Mesh^ CreateBox( SlimDX::Direct3D9::Device^ device, float width, float height, float depth );
			static Mesh^ CreateCylinder( SlimDX::Direct3D9::Device^ device, float radius1, float radius2, float length, int slices, int stacks );
			static Mesh^ CreateSphere( SlimDX::Direct3D9::Device^ device, float radius, int slices, int stacks );
			static Mesh^ CreateTeapot( SlimDX::Direct3D9::Device^ device );
			static Mesh^ CreateTorus( SlimDX::Direct3D9::Device^ device, float innerRadius, float outerRadius, int sides, int rings );

			static Mesh^ CreateText( SlimDX::Direct3D9::Device^ device, System::Drawing::Font^ font, System::String^ text, float deviation, float extrusion, [Out] array<GlyphMetricsFloat>^% glyphMetrics );
			static Mesh^ CreateText( SlimDX::Direct3D9::Device^ device, System::Drawing::Font^ font, System::String^ text, float deviation, float extrusion );

			static Mesh^ Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms, array<Matrix>^ textureTransforms, array<VertexElement>^ vertexDeclaration );
			static Mesh^ Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms, array<Matrix>^ textureTransforms );
			static Mesh^ Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options );

			static Mesh^ Simplify( Mesh^ mesh, array<AttributeWeights>^ attributeWeights, array<float>^ vertexWeights, int minimumValue, MeshSimplification options );
			static Mesh^ Simplify( Mesh^ mesh, array<AttributeWeights>^ attributeWeights, int minimumValue, MeshSimplification options );
			static Mesh^ Simplify( Mesh^ mesh, int minimumValue, MeshSimplification options );

			DataStream^ LockAttributeBuffer( LockFlags flags );
			Result UnlockAttributeBuffer();
			Result SetAttributeTable( array<AttributeRange>^ table );

			Result OptimizeInPlace( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Result OptimizeInPlace( MeshOptimizeFlags flags );

			Mesh^ Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags );

			Mesh^ Clean( CleanType type, [Out] System::String^% errorsAndWarnings );
			Mesh^ Clean( CleanType type );
			
			Result ComputeNormals();
			Result ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap );
			Result ComputeTangentFrame( TangentOptions options );

			Mesh^ ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
				int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
				int normalOutIndex, TangentOptions options, float partialEdgeThreshold,
				float singularPointThreshold, float normalEdgeThreshold, [Out] array<int>^% vertexMapping );

			Mesh^ ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
				int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
				int normalOutIndex, TangentOptions options, float partialEdgeThreshold,
				float singularPointThreshold, float normalEdgeThreshold );

			array<ExtendedMaterial>^ GetMaterials() { return materials; }
			void SetMaterials( array<ExtendedMaterial>^ value ) { materials = value; }

			array<EffectInstance>^ GetEffects() { return effects; }
			void SetEffects( array<EffectInstance>^ value ) { effects = value; }

			void SetAdjacency( array<int>^ adjacency ) { this->adjacency = adjacency; }
			array<int>^ GetAdjacency() { return adjacency; }

			property SkinInfo^ SkinInfo
			{ 
				SlimDX::Direct3D9::SkinInfo^ get() { return skinInfo; }
				void set( SlimDX::Direct3D9::SkinInfo^ value ) { skinInfo = value; }
			}
		};
	}
}
