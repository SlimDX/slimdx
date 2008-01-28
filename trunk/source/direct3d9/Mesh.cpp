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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"

#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "SkinInfo.h"

namespace SlimDX
{
namespace Direct3D9
{
	//Utility function to convert from D3D color to SlimDX color. Can't put it in ColorValue because
	//that thing is shared between D3D 9 and D3D 10.
	ColorValue ConvertColor( const D3DCOLORVALUE& color )
	{
		ColorValue cv;
		cv.Red = color.r;
		cv.Green = color.g;
		cv.Blue = color.b;
		cv.Alpha = color.a;

		return cv;
	}

	D3DCOLORVALUE ConvertColor( ColorValue color )
	{
		D3DCOLORVALUE cv;
		cv.r = color.Red;
		cv.g = color.Green;
		cv.b = color.Blue;
		cv.a = color.Alpha;

		return cv;
	}

	D3DXMATERIAL ExtendedMaterial::ToUnmanaged( ExtendedMaterial material )
	{
		D3DXMATERIAL result;
		if( !String::IsNullOrEmpty( material.TextureFileName ) )
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( material.TextureFileName );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];
			result.pTextureFilename = reinterpret_cast<LPSTR>( pinnedName );
		}
		else
			result.pTextureFilename = NULL;

		result.MatD3D.Ambient = ConvertColor( material.MaterialD3D.Ambient );
		result.MatD3D.Diffuse = ConvertColor( material.MaterialD3D.Diffuse );
		result.MatD3D.Specular = ConvertColor( material.MaterialD3D.Specular );
		result.MatD3D.Emissive = ConvertColor( material.MaterialD3D.Emissive );
		result.MatD3D.Power = material.MaterialD3D.Power;

		return result;
	}

	ExtendedMaterial ExtendedMaterial::FromUnmanaged( const D3DXMATERIAL &material )
	{
		ExtendedMaterial result;
		Material mat;
		mat.Diffuse = ConvertColor( material.MatD3D.Diffuse );
		mat.Ambient = ConvertColor( material.MatD3D.Ambient );
		mat.Specular = ConvertColor( material.MatD3D.Specular );
		mat.Emissive = ConvertColor( material.MatD3D.Emissive );
		mat.Power = material.MatD3D.Power;
		result.MaterialD3D = mat;
		result.TextureFileName = gcnew String( material.pTextureFilename );

		return result;
	}

	array<ExtendedMaterial>^ ExtendedMaterial::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXMATERIAL* source  = reinterpret_cast<const D3DXMATERIAL*>( buffer->GetBufferPointer() );

		array<ExtendedMaterial>^ destination = gcnew array<ExtendedMaterial>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			Material m;
			m.Diffuse = ConvertColor( source[i].MatD3D.Diffuse );
			m.Ambient = ConvertColor( source[i].MatD3D.Ambient );
			m.Specular = ConvertColor( source[i].MatD3D.Specular );
			m.Emissive = ConvertColor( source[i].MatD3D.Emissive );
			m.Power = source[i].MatD3D.Power;
			destination[i].MaterialD3D = m;
			destination[i].TextureFileName = gcnew String( source[i].pTextureFilename );
		}

		return destination;
	}

	EffectInstance EffectInstance::FromUnmanaged( const D3DXEFFECTINSTANCE &effect )
	{
		EffectInstance result;

		result.EffectFileName = gcnew String( effect.pEffectFilename );
		result.Defaults = gcnew array<EffectDefault>( effect.NumDefaults );

		for( unsigned int i = 0; i < effect.NumDefaults; i++ )
		{
			result.Defaults[i].ParameterName = gcnew String( effect.pDefaults[i].pParamName );
			result.Defaults[i].Type = static_cast<EffectDefaultType>( effect.pDefaults[i].Type );
			result.Defaults[i].Value = gcnew DataStream( effect.pDefaults[i].pValue, effect.pDefaults[i].NumBytes, true, false, true );
		}

		return result;
	}

	D3DXEFFECTINSTANCE EffectInstance::ToUnmanaged( EffectInstance effect )
	{
		D3DXEFFECTINSTANCE result;
		int count = effect.Defaults->Length;
		result.NumDefaults = count;
		result.pDefaults = new D3DXEFFECTDEFAULT[count];

		if( String::IsNullOrEmpty( effect.EffectFileName ) )
			result.pEffectFilename = NULL;
		else
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.EffectFileName );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];
			result.pEffectFilename = reinterpret_cast<LPSTR>( pinnedName );
		}		

		for( int i = 0; i < effect.Defaults->Length; i++ )
		{
			array<unsigned char>^ nameBytes2 = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.Defaults[i].ParameterName );
			pin_ptr<unsigned char> pinnedName2 = &nameBytes2[0];

			result.pDefaults[i].pParamName = reinterpret_cast<LPSTR>( pinnedName2 );
			result.pDefaults[i].Type = static_cast<D3DXEFFECTDEFAULTTYPE>( effect.Defaults[i].Type );
			result.pDefaults[i].NumBytes = static_cast<DWORD>( effect.Defaults[i].Value->Length );
			result.pDefaults[i].pValue = effect.Defaults[i].Value->RawPointer;
		}

		return result;
	}

	array<EffectInstance>^ EffectInstance::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXEFFECTINSTANCE* source  = reinterpret_cast<const D3DXEFFECTINSTANCE*>( buffer->GetBufferPointer() );

		array<EffectInstance>^ destination = gcnew array<EffectInstance>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			destination[i].EffectFileName = gcnew String( source[i].pEffectFilename );
			destination[i].Defaults = gcnew array<EffectDefault>( source[i].NumDefaults );
			for( unsigned int x = 0; x < source[i].NumDefaults; ++x )
			{
				destination[i].Defaults[x].ParameterName = gcnew String( source[i].pDefaults[x].pParamName );
				destination[i].Defaults[x].Type = static_cast<EffectDefaultType>( source[i].pDefaults[x].Type );
				destination[i].Defaults[x].Value = gcnew DataStream( source[i].pDefaults[x].pValue, source[i].pDefaults[x].NumBytes, true, false, true );
			}
		}

		return destination;
	}

	BaseMesh::BaseMesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &elements[0];

		HRESULT hr = InternalPointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = InternalPointer->CloneMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( fvf ), 
			device->InternalPointer, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	void BaseMesh::DrawSubset( int subset )
	{
		HRESULT hr = InternalPointer->DrawSubset( subset );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	Device^ BaseMesh::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	IndexBuffer^ BaseMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;
		HRESULT hr = InternalPointer->GetIndexBuffer( &ib );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew IndexBuffer( ib );
	}

	VertexBuffer^ BaseMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = InternalPointer->GetVertexBuffer( &vb );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexBuffer( vb );
	}

	array<VertexElement>^ BaseMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];
		HRESULT hr = InternalPointer->GetDeclaration( elementBuffer );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		// Apparently the returned decl does not include an End element. This is bizarre and confusing,
		// not to mention completely unexpected. We patch it up here.
		int count = D3DXGetDeclLength( elementBuffer ) + 1;
		array<VertexElement>^ elements = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		memcpy( pinnedElements, elementBuffer, count * sizeof(D3DVERTEXELEMENT9) );
		elements[count - 1] = VertexElement::VertexDeclarationEnd;

		return elements;
	}

	array<AttributeRange>^ BaseMesh::GetAttributeTable()
	{
		DWORD count = 0;
		HRESULT hr = InternalPointer->GetAttributeTable( NULL, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) || count == 0 )
			return nullptr;

		array<AttributeRange>^ attribTable = gcnew array<AttributeRange>( count );
		pin_ptr<AttributeRange> pinnedTable = &attribTable[0];
		hr = InternalPointer->GetAttributeTable( reinterpret_cast<D3DXATTRIBUTERANGE*>( pinnedTable ), &count );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return attribTable;
	}

	DataStream^ BaseMesh::LockIndexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = InternalPointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = 6 * FaceCount;
		if( (CreationOptions & MeshFlags::Use32Bit) == MeshFlags::Use32Bit )
			size *= 2;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockIndexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockIndexBuffer();
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	DataStream^ BaseMesh::LockVertexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = InternalPointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = BytesPerVertex * VertexCount;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockVertexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockVertexBuffer();
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	array<int>^ BaseMesh::GenerateAdjacency( float epsilon )
	{
		// allocate the array to write the adjacency into
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = InternalPointer->GenerateAdjacency( epsilon, reinterpret_cast<DWORD*>( pinnedAdj ) );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	array<int>^ BaseMesh::ConvertAdjacencyToPointReps( array<int>^ adjacency )
	{
		array<int>^ points = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = InternalPointer->ConvertAdjacencyToPointReps( reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedPoints ) );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return points;
	}

	array<int>^ BaseMesh::ConvertPointRepsToAdjacency( array<int>^ points )
	{
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = InternalPointer->ConvertPointRepsToAdjacency( reinterpret_cast<const DWORD*>( pinnedPoints ),
			reinterpret_cast<DWORD*>( pinnedAdj ) );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	void BaseMesh::UpdateSemantics( array<VertexElement>^ elements )
	{
		pin_ptr<VertexElement> pinnedElements = &elements[0];

		HRESULT hr = InternalPointer->UpdateSemantics( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	IndexBuffer^ BaseMesh::ConvertSubsetToSingleStrip( int attributeId, MeshFlags options, [Out] int% indexCount )
	{
		IDirect3DIndexBuffer9 *result;
		DWORD count;

		HRESULT hr = D3DXConvertMeshSubsetToSingleStrip( InternalPointer, attributeId, static_cast<DWORD>( options ),
			&result, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			indexCount = 0;
			return nullptr;
		}

		indexCount = count;
		return gcnew IndexBuffer( result );
	}

	IndexBuffer^ BaseMesh::ConvertSubsetToStrips( int attributeId, MeshFlags options, [Out] int% indexCount,
		[Out] array<int>^% stripLengths )
	{
		IDirect3DIndexBuffer9 *result;
		ID3DXBuffer *buffer;
		DWORD numIndices;
		DWORD numStrips;

		HRESULT hr = D3DXConvertMeshSubsetToStrips( InternalPointer, attributeId, static_cast<DWORD>( options ),
			&result, &numIndices, &buffer, &numStrips );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			indexCount = 0;
			stripLengths = nullptr;
			return nullptr;
		}

		indexCount = numIndices;
		stripLengths = ( gcnew DataStream( buffer ) )->ReadRange<int>( numStrips );
		return gcnew IndexBuffer( result );
	}

	bool BaseMesh::Intersects( Ray ray, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits )
	{
		ID3DXBuffer *allHits;
		BOOL result;
		FLOAT dist;
		DWORD count;
		DWORD face;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, &face, NULL, NULL, &dist, &allHits, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			hits = nullptr;
			faceIndex = 0;
			distance = 0;
			return false;
		}

		faceIndex = face;
		distance = dist;

		hits = ( gcnew DataStream( allHits ) )->ReadRange<IntersectInformation>( count );

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::Intersects( Ray ray, [Out] float% distance )
	{
		BOOL result;
		FLOAT dist;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, &dist, NULL, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			distance = 0;
			return false;
		}

		distance = dist;
		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::Intersects( Ray ray )
	{
		BOOL result;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, NULL, NULL, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return false;

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits )
	{
		ID3DXBuffer *allHits;
		BOOL result;
		FLOAT dist;
		DWORD count;
		DWORD face;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, &face, NULL, NULL, &dist, &allHits, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			hits = nullptr;
			faceIndex = 0;
			distance = 0;
			return false;
		}

		faceIndex = face;
		distance = dist;
		hits = ( gcnew DataStream( allHits ) )->ReadRange<IntersectInformation>( count );

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId, [Out] float% distance )
	{
		BOOL result;
		FLOAT dist;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, &dist, NULL, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			distance = 0;
			return false;
		}

		distance = dist;
		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId )
	{
		BOOL result;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, NULL, NULL, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return false;

		if( result )
			return true;
		else
			return false;
	}

	int BaseMesh::FaceCount::get()
	{
		return InternalPointer->GetNumFaces();
	}

	int BaseMesh::VertexCount::get()
	{
		return InternalPointer->GetNumVertices();
	}

	SlimDX::Direct3D9::VertexFormat BaseMesh::VertexFormat::get()
	{
		return static_cast<SlimDX::Direct3D9::VertexFormat>( InternalPointer->GetFVF() );
	}

	int BaseMesh::BytesPerVertex::get()
	{
		return InternalPointer->GetNumBytesPerVertex();
	}

	MeshFlags BaseMesh::CreationOptions::get()
	{
		return static_cast<MeshFlags>( InternalPointer->GetOptions() );
	}

	void Mesh::SetAdjacency( DWORD *adj )
	{
		if( adj == NULL )
			adjacency = nullptr;
		else
		{
			adjacency = gcnew array<int>( FaceCount * 3 );
			for( int i = 0; i < FaceCount * 3; i++ )
				adjacency[i] = adj[i];
		}
	}

	Mesh::Mesh( ID3DXMesh* mesh ) : BaseMesh( mesh )
	{
	}

	Mesh::Mesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh* mesh;
		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];

		HRESULT hr = D3DXCreateMesh( numFaces, numVertices, static_cast<DWORD>( options ),
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), device->InternalPointer, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception();

		Construct(mesh);
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = D3DXCreateMeshFVF( numFaces, numVertices, static_cast<DWORD>( options ), 
			static_cast<DWORD>( fvf ), device->InternalPointer, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception();

		Construct(mesh);
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		Mesh^ result = gcnew Mesh( mesh );

		result->SetAdjacency( ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 ) );
		result->SetMaterials( ExtendedMaterial::FromBuffer( materialBuffer, materialCount ) );

		// figure out how many effect instances there are, and get them out of the buffer
		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		result->SetEffects( EffectInstance::FromBuffer( instanceBuffer, instanceCount ) );

		materialBuffer->Release();
		instanceBuffer->Release();

		return result;
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		Mesh^ result = gcnew Mesh( mesh );

		result->SetAdjacency( ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 ) );
		result->SetMaterials( ExtendedMaterial::FromBuffer( materialBuffer, materialCount ) );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		result->SetEffects( EffectInstance::FromBuffer( instanceBuffer, instanceCount ) );

		materialBuffer->Release();
		instanceBuffer->Release();

		return result;
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &skin, &mesh );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		Mesh^ result = gcnew Mesh( mesh );

		result->SetAdjacency( ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 ) );
		result->SetMaterials( ExtendedMaterial::FromBuffer( materialBuffer, materialCount ) );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		result->SetEffects( EffectInstance::FromBuffer( instanceBuffer, instanceCount ) );

		materialBuffer->Release();
		instanceBuffer->Release();

		result->SkinInfo = gcnew SlimDX::Direct3D9::SkinInfo( skin );

		return result;
	}

	void Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( MeshPointer, static_cast<DWORD>( options ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	Mesh^ Mesh::CreateBox( Device^ device, float width, float height, float depth )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateBox( device->InternalPointer, width, height, depth, &result, &adj );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateCylinder( Device^ device, float radius1, float radius2, float length, int slices, int stacks )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateCylinder( device->InternalPointer, radius1, radius2, length, slices, stacks, &result, &adj );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateSphere( Device^ device, float radius, int slices, int stacks )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateSphere( device->InternalPointer, radius, slices, stacks, &result, &adj );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateTeapot( Device^ device )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTeapot( device->InternalPointer, &result, &adj );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateTorus( Device^ device, float innerRadius, float outerRadius, int sides, int rings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTorus( device->InternalPointer, innerRadius, outerRadius, sides, rings, &result, &adj );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion, [Out] array<GlyphMetricsFloat>^% glyphMetrics )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		glyphMetrics = gcnew array<GlyphMetricsFloat>( text->Length );

		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );
		pin_ptr<GlyphMetricsFloat> pinnedMetrics = &glyphMetrics[0];

		HDC hdc = CreateCompatibleDC( NULL );
		HFONT newFont;
		HFONT oldFont;
		if( hdc == NULL )
			throw gcnew OutOfMemoryException();

		newFont = static_cast<HFONT>( font->ToHfont().ToPointer() );
		oldFont = static_cast<HFONT>( SelectObject( hdc, newFont ) );		

		HRESULT hr = D3DXCreateText( device->InternalPointer, hdc, reinterpret_cast<LPCWSTR>( pinnedText ),
			deviation, extrusion, &result, &adj, reinterpret_cast<LPGLYPHMETRICSFLOAT>( pinnedMetrics ) );
		Direct3D9ErrorHandler::TestForFailure( hr );

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( FAILED( hr ) )
		{
			glyphMetrics = nullptr;
			return nullptr;
		}

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );

		HDC hdc = CreateCompatibleDC( NULL );
		HFONT newFont;
		HFONT oldFont;
		if( hdc == NULL )
			throw gcnew OutOfMemoryException();

		newFont = static_cast<HFONT>( font->ToHfont().ToPointer() );
		oldFont = static_cast<HFONT>( SelectObject( hdc, newFont ) );		

		HRESULT hr = D3DXCreateText( device->InternalPointer, hdc, reinterpret_cast<LPCWSTR>( pinnedText ),
			deviation, extrusion, &result, &adj, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	DataStream^ Mesh::LockAttributeBuffer( LockFlags flags )
	{
		DWORD *data;
		int faceCount = MeshPointer->GetNumFaces();
		
		HRESULT hr = MeshPointer->LockAttributeBuffer( static_cast<DWORD>( flags ), &data );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, faceCount * sizeof( DWORD ), true, !readOnly, false );
	}

	void Mesh::UnlockAttributeBuffer()
	{
		HRESULT hr = MeshPointer->UnlockAttributeBuffer();
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void Mesh::SetAttributeTable( array<AttributeRange>^ table )
	{
		pin_ptr<AttributeRange> pinnedTable = &table[0];

		HRESULT hr = MeshPointer->SetAttributeTable( reinterpret_cast<const D3DXATTRIBUTERANGE*>( pinnedTable ), table->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}		

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), adjacencyIn,
			adjacencyOut, reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			SetAdjacency( NULL );
		}
		else
		{
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
			if( adjacencyOut != NULL )
				SetAdjacency( adjacencyOut );
			else
				SetAdjacency( NULL );
		}

		delete[] adjacencyOut;
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags )
	{
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;
		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}		

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), adjacencyIn,
			adjacencyOut, NULL, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			SetAdjacency( NULL );
		else
		{
			if( adjacencyOut != NULL )
				SetAdjacency( adjacencyOut );
			else
				SetAdjacency( NULL );
		}

		delete[] adjacencyOut;
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}		

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), adjacencyIn,
			adjacencyOut, reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		Mesh^ mesh = gcnew Mesh( result );

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );

		if( adjacencyOut != NULL )
			mesh->SetAdjacency( adjacencyOut );

		delete[] adjacencyOut;

		return mesh;
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags )
	{
		ID3DXMesh *result;
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), adjacencyIn,
			adjacencyOut, NULL, NULL, &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		if( adjacencyOut != NULL )
			mesh->SetAdjacency( adjacencyOut );

		delete[] adjacencyOut;

		return mesh;
	}

	Mesh^ Mesh::Clean( CleanType type, [Out] String^% errorsAndWarnings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *errors;
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			adjacencyIn, &result, adjacencyOut, &errors );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			errorsAndWarnings = nullptr;
			return nullptr;
		}

		errorsAndWarnings = Utilities::BufferToString( errors );

		Mesh^ mesh = gcnew Mesh( result );

		if( adjacencyOut != NULL )
			mesh->SetAdjacency( adjacencyOut );

		delete[] adjacencyOut;

		return mesh;
	}

	Mesh^ Mesh::Clean( CleanType type )
	{
		ID3DXMesh *result;
		DWORD *adjacencyIn = NULL;
		DWORD *adjacencyOut = NULL;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut = new DWORD[FaceCount * 3];
		}

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			adjacencyIn, &result, adjacencyOut, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		if( adjacencyOut != NULL )
			mesh->SetAdjacency( adjacencyOut );

		delete[] adjacencyOut;

		return mesh;
	}

	void Mesh::ComputeNormals()
	{
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		array<int>^ adjacency = GetAdjacency();
		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeNormals( MeshPointer, adjacencyIn );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void Mesh::ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap )
	{
		array<int>^ adjacency = GetAdjacency();
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeTangent( MeshPointer, textureStage, tangentIndex, binormalIndex, wrap, adjacencyIn );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	Mesh^ Mesh::ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
		int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
		int normalOutIndex, TangentOptions options, float partialEdgeThreshold,
		float singularPointThreshold, float normalEdgeThreshold, [Out] array<int>^% vertexMapping )
	{
		ID3DXMesh *result;
		ID3DXBuffer *vertex;

		array<int>^ adjacency = GetAdjacency();
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeTangentFrameEx( MeshPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), adjacencyIn,
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, &vertex );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
		{
			vertexMapping = nullptr;
			return nullptr;
		}

		vertexMapping = ( gcnew DataStream( vertex ) )->ReadRange<int>( result->GetNumVertices() );

		if( (options & TangentOptions::GenerateInPlace) == TangentOptions::GenerateInPlace )
			return this;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
		int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
		int normalOutIndex, TangentOptions options, float partialEdgeThreshold,
		float singularPointThreshold, float normalEdgeThreshold )
	{
		ID3DXMesh *result;

		array<int>^ adjacency = GetAdjacency();
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeTangentFrameEx( MeshPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), adjacencyIn,
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		if( (options & TangentOptions::GenerateInPlace) == TangentOptions::GenerateInPlace )
			return this;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		D3DVERTEXELEMENT9 *decl = NULL;
		ID3DXMesh **input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;
		pin_ptr<VertexElement> pinnedDecl = nullptr;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		if( geometryTransforms != nullptr )
		{
			pinnedGeo = &geometryTransforms[0];
			geoXForms = reinterpret_cast<D3DXMATRIX*>( pinnedGeo );
		}

		if( textureTransforms != nullptr )
		{
			pinnedTexture = &textureTransforms[0];
			textureXForms = reinterpret_cast<D3DXMATRIX*>( pinnedTexture );
		}

		if( vertexDeclaration != nullptr )
		{
			pinnedDecl = &vertexDeclaration[0];
			decl = reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl );
		}

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, decl, device->InternalPointer, &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		ID3DXMesh **input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		if( geometryTransforms != nullptr )
		{
			pinnedGeo = &geometryTransforms[0];
			geoXForms = reinterpret_cast<D3DXMATRIX*>( pinnedGeo );
		}

		if( textureTransforms != nullptr )
		{
			pinnedTexture = &textureTransforms[0];
			textureXForms = reinterpret_cast<D3DXMATRIX*>( pinnedTexture );
		}

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, NULL, device->InternalPointer, &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options )
	{
		ID3DXMesh *result;
		ID3DXMesh **input;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), NULL,
			NULL, NULL, device->InternalPointer, &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	void Mesh::ToXFile( Mesh^ mesh, String^ fileName, XFileFormat format, CharSet charSet )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		
		array<int>^ adjacency = mesh->GetAdjacency();
		array<ExtendedMaterial>^ materials = mesh->GetMaterials();
		array<EffectInstance>^ effects = mesh->GetEffects();

		DWORD *adjacencyIn = NULL;
		D3DXMATERIAL *nativeMaterials = NULL;
		D3DXEFFECTINSTANCE *nativeEffects = NULL;
		pin_ptr<int> pinnedAdj;
		int length = 0;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		if( materials != nullptr )
		{
			length = materials->Length;
			nativeMaterials = new D3DXMATERIAL[length];
			for( int i = 0; i < length; i++ )
				nativeMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );
		}

		if( effects != nullptr )
		{
			nativeEffects = new D3DXEFFECTINSTANCE[effects->Length];
			for( int i = 0; i < effects->Length; i++ )
				nativeEffects[i] = EffectInstance::ToUnmanaged( effects[i] );
		}

		DWORD f = static_cast<DWORD>( format );
		if( charSet == CharSet::Unicode )
			f |= D3DXF_FILESAVE_TOWFILE;
		else
			f |= D3DXF_FILESAVE_TOFILE;

		HRESULT hr = D3DXSaveMeshToX( reinterpret_cast<LPCWSTR>( pinnedName ), mesh->MeshPointer, 
			adjacencyIn, nativeMaterials, nativeEffects, length, f );
		Direct3D9ErrorHandler::TestForFailure( hr );

		delete[] nativeMaterials;
		delete[] nativeEffects;
	}

	void Mesh::ToXFile( Mesh^ mesh, String^ fileName, XFileFormat format )
	{
		ToXFile( mesh, fileName, format, CharSet::Auto );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, array<AttributeWeights>^ attributeWeights,
		array<float>^ vertexWeights, int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<float> pinnedVW = &vertexWeights[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), reinterpret_cast<const FLOAT*>( pinnedVW ),
			minimumValue, static_cast<DWORD>( options ), &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, array<AttributeWeights>^ attributeWeights,
		int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		DWORD *adjacencyIn = NULL;
		array<int>^ adjacency = mesh->GetAdjacency();
		pin_ptr<int> pinnedAdj;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, adjacencyIn,
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}


}
}