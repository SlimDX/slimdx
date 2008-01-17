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

#include "XFile.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class SkinInfo;

		[Flags]
		public enum class MeshFlags : Int32
		{
			Use32Bit = D3DXMESH_32BIT,
			DoNotClip = D3DXMESH_DONOTCLIP,
			Points = D3DXMESH_POINTS,
			RTPatches = D3DXMESH_RTPATCHES,
			NPatches = D3DXMESH_NPATCHES,
			VertexBufferSystemMemory = D3DXMESH_VB_SYSTEMMEM,
			VertexBufferManaged = D3DXMESH_VB_MANAGED,
			VertexBufferWriteOnly = D3DXMESH_VB_WRITEONLY,
			VertexBufferDynamic = D3DXMESH_VB_DYNAMIC,
			VertexBufferSoftware = D3DXMESH_VB_SOFTWAREPROCESSING,
			IndexBufferSystemMemory = D3DXMESH_IB_SYSTEMMEM,
			IndexBufferManaged = D3DXMESH_IB_MANAGED,
			IndexBufferbWriteOnly = D3DXMESH_IB_WRITEONLY,
			IndexBufferDynamic = D3DXMESH_IB_DYNAMIC,
			IndexBufferSoftware = D3DXMESH_IB_SOFTWAREPROCESSING,

			VertexBufferShare = D3DXMESH_VB_SHARE,

			UseHardwareOnly = D3DXMESH_USEHWONLY,

			// Helper options
			SystemMemory = D3DXMESH_SYSTEMMEM,
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

		public enum class EffectDefaultType : Int32
		{
			String = D3DXEDT_STRING,
			Floats = D3DXEDT_FLOATS,
			Dword = D3DXEDT_DWORD,
		};

		[Flags]
		public enum class MeshOptimizeFlags : Int32
		{
			Compact = D3DXMESHOPT_COMPACT,
			AttributeSort = D3DXMESHOPT_ATTRSORT,
			VertexCache = D3DXMESHOPT_VERTEXCACHE,
			StripReorder = D3DXMESHOPT_STRIPREORDER,
			IgnoreVertices = D3DXMESHOPT_IGNOREVERTS,
			DoNotSplit = D3DXMESHOPT_DONOTSPLIT,
			DeviceIndependent = D3DXMESHOPT_DEVICEINDEPENDENT,
		};

		[Flags]
		public enum class CleanType : Int32
		{
			BackFacing = D3DXCLEAN_BACKFACING,
			BowTies = D3DXCLEAN_BOWTIES,
			Skinning = D3DXCLEAN_SKINNING,
			Optimization = D3DXCLEAN_OPTIMIZATION,
			Simplification = D3DXCLEAN_SIMPLIFICATION
		};

		public enum class MeshSimplification : Int32
		{
			Vertex = D3DXMESHSIMP_VERTEX,
			Face = D3DXMESHSIMP_FACE
		};

		public value class ExtendedMaterial
		{
		internal:
			static D3DXMATERIAL ToUnmanaged( ExtendedMaterial material );
			static ExtendedMaterial FromUnmanaged( const D3DXMATERIAL &material );
			static array<ExtendedMaterial>^ FromBuffer( ID3DXBuffer* buffer, unsigned int count );

		public:
			property Material MaterialD3D;
			property String^ TextureFilename;
		};

		public value class EffectDefault
		{
		public:
			property String^ ParameterName;
			property EffectDefaultType Type;
			property DataStream^ Value;
		};

		public value class EffectInstance
		{
		internal:
			static EffectInstance FromUnmanaged( const D3DXEFFECTINSTANCE &effect );
			static D3DXEFFECTINSTANCE ToUnmanaged( EffectInstance effect );
			static array<EffectInstance>^ FromBuffer( ID3DXBuffer* buffer, unsigned int count );

		public:
			property String^ EffectFilename;
			property array<EffectDefault>^ Defaults;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class AttributeRange
		{
		public:
			property int AttribId;
			property int FaceStart;
			property int FaceCount;
			property int VertexStart;
			property int VertexCount;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class GlyphMetricsFloat
		{
		public:
			property float BlackBoxX;
			property float BlackBoxY;
			property PointF GlyphOrigin;
			property float CellIncX;
			property float CellIncY;
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

		[StructLayout(LayoutKind::Sequential)]
		public value class IntersectInformation
		{
		public:
			property int FaceIndex;
			property float U;
			property float V;
			property float Distance;
		};

		ref class Mesh;
		ref class VertexBuffer;
		ref class IndexBuffer;
		enum class VertexFormat;

		public ref class BaseMesh abstract : public BaseObject
		{
			DXOBJECT(ID3DXBaseMesh);

		protected:
			BaseMesh() { }
			BaseMesh( ID3DXBaseMesh* baseMesh ) { Construct(baseMesh); }

		public:
			BaseMesh( IntPtr pointer );
			Mesh^ Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements );
			Mesh^ Clone( Device^ device, MeshFlags flags, VertexFormat fvf );
			virtual ~BaseMesh() { Destruct(); }

			Device^ GetDevice();
			IndexBuffer^ GetIndexBuffer();
			VertexBuffer^ GetVertexBuffer();
			array<VertexElement>^ GetDeclaration();
			array<AttributeRange>^ GetAttributeTable();

			DataStream^ LockIndexBuffer( LockFlags flags );
			void UnlockIndexBuffer();

			DataStream^ LockVertexBuffer( LockFlags flags );
			void UnlockVertexBuffer();

			array<int>^ GenerateAdjacency( float epsilon );
			array<int>^ ConvertAdjacencyToPointReps( array<int>^ adjacency );
			array<int>^ ConvertPointRepsToAdjacency( array<int>^ adjacency );
			void UpdateSemantics( array<VertexElement>^ elements );

			void DrawSubset( int subset );

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
		internal:
			Mesh( ID3DXMesh* mesh );
			property ID3DXMesh* MeshPointer
			{
				ID3DXMesh* get() { return static_cast<ID3DXMesh*>( InternalPointer ); }
			}

		public:
			Mesh( IntPtr pointer );
			Mesh( Device^ device, int faceCount, int vertexCount, MeshFlags options, array<VertexElement>^ vertexDecl );
			Mesh( Device^ device, int faceCount, int vertexCount, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf );
			virtual ~Mesh() { }
			
			static Mesh^ FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<int>^% adjacency, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials );
			static Mesh^ FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags );

			static Mesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<int>^% adjacency, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials );
			static Mesh^ FromStream( Device^ device, Stream^ stream, MeshFlags flags );

			static Mesh^ FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<int>^% adjacency, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials );
			static Mesh^ FromFile( Device^ device, String^ fileName, MeshFlags flags );

			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<int>^% adjacency, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags );

			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<int>^% adjacency, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances, [Out] SkinInfo^% skinInfo );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances, [Out] SkinInfo^% skinInfo );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] SkinInfo^% skinInfo );
			static Mesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] SkinInfo^% skinInfo );

			static Mesh^ CreateBox( Device^ device, float width, float height, float depth, [Out] array<int>^% adjacency );
			static Mesh^ CreateBox( Device^ device, float width, float height, float depth );

			static Mesh^ CreateCylinder( Device^ device, float radius1, float radius2, float length, int slices, int stacks, [Out] array<int>^% adjacency );
			static Mesh^ CreateCylinder( Device^ device, float radius1, float radius2, float length, int slices, int stacks );

			static Mesh^ CreateSphere( Device^ device, float radius, int slices, int stacks, [Out] array<int>^% adjacency );
			static Mesh^ CreateSphere( Device^ device, float radius, int slices, int stacks );

			static Mesh^ CreateTeapot( Device^ device, [Out] array<int>^% adjacency );
			static Mesh^ CreateTeapot( Device^ device );

			static Mesh^ CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion, [Out] array<int>^% adjacency, [Out] array<GlyphMetricsFloat>^% glyphMetrics );
			static Mesh^ CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion, [Out] array<int>^% adjacency );
			static Mesh^ CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion );

			static Mesh^ CreateTorus( Device^ device, float innerRadius, float outerRadius, int sides, int rings, [Out] array<int>^% adjacency );
			static Mesh^ CreateTorus( Device^ device, float innerRadius, float outerRadius, int sides, int rings );

			static Mesh^ Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, 
				array<Matrix>^ geometryTransforms, array<Matrix>^ textureTransforms, 
				array<VertexElement>^ vertexDeclaration );

			static Mesh^ Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, 
				array<Matrix>^ geometryTransforms, array<Matrix>^ textureTransforms );

			static Mesh^ Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options );

			static Mesh^ Simplify( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights, 
				array<float>^ vertexWeights, int minimumValue, MeshSimplification options );

			static Mesh^ Simplify( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights, 
				int minimumValue, MeshSimplification options );

			static Mesh^ Simplify( Mesh^ mesh, array<int>^ adjacency, int minimumValue, MeshSimplification options );

			DataStream^ LockAttributeBuffer( LockFlags flags );
			void UnlockAttributeBuffer();
			void SetAttributeTable( array<AttributeRange>^ table );

			void OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut );
			void OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn );

			void OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			void OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut );
			void OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn );

			Mesh^ Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut );
			Mesh^ Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn );

			Mesh^ Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap );
			Mesh^ Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut );
			Mesh^ Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn );

			Mesh^ Clean( CleanType type, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] String^% errorsAndWarnings );
			Mesh^ Clean( CleanType type, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut );
			Mesh^ Clean( CleanType type, array<int>^ adjacencyIn );

			Mesh^ Clean( CleanType type, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] String^% errorsAndWarnings );
			Mesh^ Clean( CleanType type, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut );
			Mesh^ Clean( CleanType type, IntPtr adjacencyIn );
			
			void ComputeNormals( array<int>^ adjacency );
			void ComputeNormals();
			void ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap, array<int>^ adjacency );
			void ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap );
			void ComputeTangentFrame( TangentOptions options );

			Mesh^ ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
				int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
				int normalOutIndex, TangentOptions options, array<int>^ adjacency, float partialEdgeThreshold,
				float singularPointThreshold, float normalEdgeThreshold, [Out] array<int>^% vertexMapping );

			Mesh^ ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
				int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
				int normalOutIndex, TangentOptions options, array<int>^ adjacency, float partialEdgeThreshold,
				float singularPointThreshold, float normalEdgeThreshold );

			Mesh^ ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
				int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
				int normalOutIndex, TangentOptions options, float partialEdgeThreshold,
				float singularPointThreshold, float normalEdgeThreshold );

			void Save( String^ fileName, array<int>^ adjacency, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects, XFileFormat format, CharSet charSet );
			void Save( String^ fileName, array<int>^ adjacency, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects, XFileFormat format );
		};
	}
}
