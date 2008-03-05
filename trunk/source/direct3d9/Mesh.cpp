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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"
#include "../StackAlloc.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "SkinInfo.h"

using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	Mesh::Mesh( ID3DXMesh* mesh )
	{
		Construct( mesh );
	}

	Mesh::Mesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Mesh::Mesh( SlimDX::Direct3D9::Device^ device, int numFaces, int numVertices, MeshFlags options, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh* mesh;
		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];

		HRESULT hr = D3DXCreateMesh( numFaces, numVertices, static_cast<DWORD>( options ),
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), device->InternalPointer, &mesh );

		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(mesh);
	}

	Mesh::Mesh( SlimDX::Direct3D9::Device^ device, int numFaces, int numVertices, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = D3DXCreateMeshFVF( numFaces, numVertices, static_cast<DWORD>( options ), 
			static_cast<DWORD>( fvf ), device->InternalPointer, &mesh );

		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(mesh);
	}

	Mesh^ Mesh::FromPointer( ID3DXMesh* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Mesh^ tableEntry = safe_cast<Mesh^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Mesh( pointer );
	}

	Mesh^ Mesh::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Mesh^ tableEntry = safe_cast<Mesh^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Mesh( pointer );
	}

	Mesh^ Mesh::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ result = Mesh::FromPointer( mesh );

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

	Mesh^ Mesh::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, MeshFlags flags )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags );
	}

	Mesh^ Mesh::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ result = Mesh::FromPointer( mesh );

		result->SetAdjacency( ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 ) );
		result->SetMaterials( ExtendedMaterial::FromBuffer( materialBuffer, materialCount ) );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		result->SetEffects( EffectInstance::FromBuffer( instanceBuffer, instanceCount ) );

		materialBuffer->Release();
		instanceBuffer->Release();

		return result;
	}

	Mesh^ Mesh::FromXFile( SlimDX::Direct3D9::Device^ device, XFileData^ xfile, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &skin, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ result = Mesh::FromPointer( mesh );

		result->SetAdjacency( ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 ) );
		result->SetMaterials( ExtendedMaterial::FromBuffer( materialBuffer, materialCount ) );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		result->SetEffects( EffectInstance::FromBuffer( instanceBuffer, instanceCount ) );

		materialBuffer->Release();
		instanceBuffer->Release();

		result->SkinInfo = SlimDX::Direct3D9::SkinInfo::FromPointer( skin );

		return result;
	}

	Result Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( InternalPointer, static_cast<DWORD>( options ) );
		return RECORD_D3D9( hr );
	}

	Mesh^ Mesh::CreateBox( SlimDX::Direct3D9::Device^ device, float width, float height, float depth )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateBox( device->InternalPointer, width, height, depth, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateCylinder( SlimDX::Direct3D9::Device^ device, float radius1, float radius2, float length, int slices, int stacks )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateCylinder( device->InternalPointer, radius1, radius2, length, slices, stacks, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateSphere( SlimDX::Direct3D9::Device^ device, float radius, int slices, int stacks )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateSphere( device->InternalPointer, radius, slices, stacks, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateTeapot( SlimDX::Direct3D9::Device^ device )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTeapot( device->InternalPointer, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateTorus( SlimDX::Direct3D9::Device^ device, float innerRadius, float outerRadius, int sides, int rings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTorus( device->InternalPointer, innerRadius, outerRadius, sides, rings, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateText( SlimDX::Direct3D9::Device^ device, Font^ font, String^ text, float deviation, float extrusion, [Out] array<GlyphMetricsFloat>^% glyphMetrics )
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

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			glyphMetrics = nullptr;
			return nullptr;
		}

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateText( SlimDX::Direct3D9::Device^ device, Font^ font, String^ text, float deviation, float extrusion )
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

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	DataStream^ Mesh::LockAttributeBuffer( LockFlags flags )
	{
		DWORD *data;
		int faceCount = InternalPointer->GetNumFaces();
		
		HRESULT hr = InternalPointer->LockAttributeBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, faceCount * sizeof( DWORD ), true, !readOnly, false );
	}

	Result Mesh::UnlockAttributeBuffer()
	{
		HRESULT hr = InternalPointer->UnlockAttributeBuffer();
		return RECORD_D3D9( hr );
	}

	Result Mesh::SetAttributeTable( array<AttributeRange>^ table )
	{
		pin_ptr<AttributeRange> pinnedTable = &table[0];

		HRESULT hr = InternalPointer->SetAttributeTable( reinterpret_cast<const D3DXATTRIBUTERANGE*>( pinnedTable ), table->Length );
		return RECORD_D3D9( hr );
	}

	Result Mesh::OptimizeInPlace( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}		

		HRESULT hr = InternalPointer->OptimizeInplace( static_cast<DWORD>( flags ), adjacencyIn,
			&adjacencyOut[0], reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		RECORD_D3D9( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			SetAdjacency( NULL );
		}
		else
		{
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
			if( adjacencyOut.size() > 0 )
				SetAdjacency( &adjacencyOut[0] );
			else
				SetAdjacency( NULL );
		}

		return Result::Last;
	}

	Result Mesh::OptimizeInPlace( MeshOptimizeFlags flags )
	{
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;
		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}		

		HRESULT hr = InternalPointer->OptimizeInplace( static_cast<DWORD>( flags ), adjacencyIn,
			&adjacencyOut[0], NULL, NULL );
		RECORD_D3D9( hr );

		if( FAILED( hr ) )
			SetAdjacency( NULL );
		else
		{
			if( adjacencyOut.size() > 0 )
				SetAdjacency( &adjacencyOut[0] );
			else
				SetAdjacency( NULL );
		}

		return Result::Last;
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}		

		HRESULT hr = InternalPointer->Optimize( static_cast<DWORD>( flags ), adjacencyIn,
			&adjacencyOut[0], reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		Mesh^ mesh = Mesh::FromPointer( result );

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );

		if( adjacencyOut.size() > 0 )
			mesh->SetAdjacency( &adjacencyOut[0] );

		return mesh;
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags )
	{
		ID3DXMesh *result;
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}

		HRESULT hr = InternalPointer->Optimize( static_cast<DWORD>( flags ), adjacencyIn,
			&adjacencyOut[0], NULL, NULL, &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		if( adjacencyOut.size() > 0 )
			mesh->SetAdjacency( &adjacencyOut[0] );

		return mesh;
	}

	Mesh^ Mesh::Clean( CleanType type, [Out] String^% errorsAndWarnings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *errors;
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), InternalPointer, 
			adjacencyIn, &result, &adjacencyOut[0], &errors );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			errorsAndWarnings = nullptr;
			return nullptr;
		}

		errorsAndWarnings = Utilities::BufferToString( errors );

		Mesh^ mesh = Mesh::FromPointer( result );

		if( adjacencyOut.size() > 0 )
			mesh->SetAdjacency( &adjacencyOut[0] );

		return mesh;
	}

	Mesh^ Mesh::Clean( CleanType type )
	{
		ID3DXMesh *result;
		DWORD *adjacencyIn = NULL;
		stack_vector<DWORD> adjacencyOut;

		array<int>^ adjacency = GetAdjacency();
		pin_ptr<int> pinnedAdjIn;

		if( adjacency != nullptr )
		{
			pinnedAdjIn = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdjIn );
			adjacencyOut.resize( FaceCount * 3 );
		}

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), InternalPointer, 
			&adjacencyIn[0], &result, &adjacencyOut[0], NULL );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = Mesh::FromPointer( result );

		if( adjacencyOut.size() > 0 )
			mesh->SetAdjacency( &adjacencyOut[0] );

		return mesh;
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

	Result Mesh::ComputeNormals()
	{
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		array<int>^ adjacency = GetAdjacency();
		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeNormals( InternalPointer, adjacencyIn );
		return RECORD_D3D9( hr );
	}

	Result Mesh::ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap )
	{
		array<int>^ adjacency = GetAdjacency();
		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXComputeTangent( InternalPointer, textureStage, tangentIndex, binormalIndex, wrap, adjacencyIn );
		return RECORD_D3D9( hr );
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

		HRESULT hr = D3DXComputeTangentFrameEx( InternalPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), adjacencyIn,
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, &vertex );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			vertexMapping = nullptr;
			return nullptr;
		}

		vertexMapping = ( gcnew DataStream( vertex ) )->ReadRange<int>( result->GetNumVertices() );

		if( (options & TangentOptions::GenerateInPlace) == TangentOptions::GenerateInPlace )
			return this;

		return Mesh::FromPointer( result );
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

		HRESULT hr = D3DXComputeTangentFrameEx( InternalPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), adjacencyIn,
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, NULL );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		if( (options & TangentOptions::GenerateInPlace) == TangentOptions::GenerateInPlace )
			return this;

		return Mesh::FromPointer( result );
	}

	Mesh^ Mesh::Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		D3DVERTEXELEMENT9 *decl = NULL;
		stack_vector<ID3DXMesh*> input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;
		pin_ptr<VertexElement> pinnedDecl = nullptr;

		input.resize(meshes->Length);
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->InternalPointer;

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

		HRESULT hr = D3DXConcatenateMeshes( &input[0], meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, decl, device->InternalPointer, &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
	}

	Mesh^ Mesh::Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		stack_vector<ID3DXMesh*> input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;

		input.resize( meshes->Length );
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->InternalPointer;

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

		HRESULT hr = D3DXConcatenateMeshes( &input[0], meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, NULL, device->InternalPointer, &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
	}

	Mesh^ Mesh::Concatenate( SlimDX::Direct3D9::Device^ device, array<Mesh^>^ meshes, MeshFlags options )
	{
		ID3DXMesh *result;
		stack_vector<ID3DXMesh*> input;

		input.resize( meshes->Length );
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->InternalPointer;

		HRESULT hr = D3DXConcatenateMeshes( &input[0], meshes->Length, static_cast<DWORD>( options ), NULL,
			NULL, NULL, device->InternalPointer, &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
	}

	Result Mesh::ToXFile( Mesh^ mesh, String^ fileName, XFileFormat format, CharSet charSet )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		
		array<int>^ adjacency = mesh->GetAdjacency();
		array<ExtendedMaterial>^ materials = mesh->GetMaterials();
		array<EffectInstance>^ effects = mesh->GetEffects();

		DWORD *adjacencyIn = NULL;
		stack_vector<D3DXMATERIAL> nativeMaterials;
		stack_vector<D3DXEFFECTINSTANCE> nativeEffects;
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
			nativeMaterials.resize( length );
			for( int i = 0; i < length; i++ )
				nativeMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );
		}

		if( effects != nullptr )
		{
			nativeEffects.resize( effects->Length );
			for( int i = 0; i < effects->Length; i++ )
				nativeEffects[i] = EffectInstance::ToUnmanaged( effects[i] );
		}

		DWORD f = static_cast<DWORD>( format );
		if( charSet == CharSet::Unicode )
			f |= D3DXF_FILESAVE_TOWFILE;
		else
			f |= D3DXF_FILESAVE_TOFILE;

		HRESULT hr = D3DXSaveMeshToX( reinterpret_cast<LPCWSTR>( pinnedName ), mesh->InternalPointer, 
			adjacencyIn, &nativeMaterials[0], &nativeEffects[0], length, f );

		for( int i = 0; i < length; i++ )
			Utilities::FreeNativeString( nativeMaterials[i].pTextureFilename );

		for( int i = 0; i < effects->Length; i++ )
		{
			for( UINT j = 0; j < nativeEffects[i].NumDefaults; j++ )
				Utilities::FreeNativeString( nativeEffects[i].pDefaults[j].pParamName );

			delete[] nativeEffects[i].pDefaults;
		}

		return RECORD_D3D9( hr );
	}

	Result Mesh::ToXFile( Mesh^ mesh, String^ fileName, XFileFormat format )
	{
		return ToXFile( mesh, fileName, format, CharSet::Auto );
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

		HRESULT hr = D3DXSimplifyMesh( mesh->InternalPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), reinterpret_cast<const FLOAT*>( pinnedVW ),
			minimumValue, static_cast<DWORD>( options ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
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

		HRESULT hr = D3DXSimplifyMesh( mesh->InternalPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
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

		HRESULT hr = D3DXSimplifyMesh( mesh->InternalPointer, adjacencyIn,
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( result );
	}
}
}