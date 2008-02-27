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
	//Utility function to convert from D3D color to SlimDX color. Can't put it in Color4 because
	//that thing is shared between D3D 9 and D3D 10.
	Color4 ConvertColor( const D3DCOLORVALUE& color )
	{
		Color4 cv;
		cv.Red = color.r;
		cv.Green = color.g;
		cv.Blue = color.b;
		cv.Alpha = color.a;

		return cv;
	}

	D3DCOLORVALUE ConvertColor( Color4 color )
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
		result.pTextureFilename = Utilities::AllocateNativeString( material.TextureFileName );
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

	bool ExtendedMaterial::operator == ( ExtendedMaterial left, ExtendedMaterial right )
	{
		return ExtendedMaterial::Equals( left, right );
	}

	bool ExtendedMaterial::operator != ( ExtendedMaterial left, ExtendedMaterial right )
	{
		return !ExtendedMaterial::Equals( left, right );
	}

	int ExtendedMaterial::GetHashCode()
	{
		return MaterialD3D.GetHashCode() + TextureFileName->GetHashCode();
	}

	bool ExtendedMaterial::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ExtendedMaterial>( value ) );
	}

	bool ExtendedMaterial::Equals( ExtendedMaterial value )
	{
		return ( MaterialD3D == value.MaterialD3D && TextureFileName == value.TextureFileName );
	}

	bool ExtendedMaterial::Equals( ExtendedMaterial% value1, ExtendedMaterial% value2 )
	{
		return ( value1.MaterialD3D == value2.MaterialD3D && value1.TextureFileName == value2.TextureFileName );
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
		result.pEffectFilename = Utilities::AllocateNativeString( effect.EffectFileName );

		for( int i = 0; i < effect.Defaults->Length; i++ )
		{
			result.pDefaults[i].pParamName = Utilities::AllocateNativeString( effect.Defaults[i].ParameterName );
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

	bool EffectInstance::operator == ( EffectInstance left, EffectInstance right )
	{
		return EffectInstance::Equals( left, right );
	}

	bool EffectInstance::operator != ( EffectInstance left, EffectInstance right )
	{
		return !EffectInstance::Equals( left, right );
	}

	int EffectInstance::GetHashCode()
	{
		return EffectFileName->GetHashCode() + Defaults->GetHashCode();
	}

	bool EffectInstance::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<EffectInstance>( value ) );
	}

	bool EffectInstance::Equals( EffectInstance value )
	{
		return ( EffectFileName == value.EffectFileName && Defaults == value.Defaults );
	}

	bool EffectInstance::Equals( EffectInstance% value1, EffectInstance% value2 )
	{
		return ( value1.EffectFileName == value2.EffectFileName && value1.Defaults == value2.Defaults );
	}
	
	bool EffectDefault::operator == ( EffectDefault left, EffectDefault right )
	{
		return EffectDefault::Equals( left, right );
	}

	bool EffectDefault::operator != ( EffectDefault left, EffectDefault right )
	{
		return !EffectDefault::Equals( left, right );
	}

	int EffectDefault::GetHashCode()
	{
		return ParameterName->GetHashCode() + Type.GetHashCode() + Value->GetHashCode();
	}

	bool EffectDefault::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<EffectDefault>( value ) );
	}

	bool EffectDefault::Equals( EffectDefault value )
	{
		return ( ParameterName == value.ParameterName && Type == value.Type && Value == value.Value );
	}

	bool EffectDefault::Equals( EffectDefault% value1, EffectDefault% value2 )
	{
		return ( value1.ParameterName == value2.ParameterName && value1.Type == value2.Type && value1.Value == value2.Value );
	}

	bool AttributeRange::operator == ( AttributeRange left, AttributeRange right )
	{
		return AttributeRange::Equals( left, right );
	}

	bool AttributeRange::operator != ( AttributeRange left, AttributeRange right )
	{
		return !AttributeRange::Equals( left, right );
	}

	int AttributeRange::GetHashCode()
	{
		return AttribId.GetHashCode() + FaceStart.GetHashCode() + FaceCount.GetHashCode()
			 + VertexStart.GetHashCode() + VertexCount.GetHashCode();
	}

	bool AttributeRange::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<AttributeRange>( value ) );
	}

	bool AttributeRange::Equals( AttributeRange value )
	{
		return ( AttribId == value.AttribId && FaceStart == value.FaceStart && FaceCount == value.FaceCount
			 && VertexStart == value.VertexStart && VertexCount == value.VertexCount );
	}

	bool AttributeRange::Equals( AttributeRange% value1, AttributeRange% value2 )
	{
		return ( value1.AttribId == value2.AttribId && value1.FaceStart == value2.FaceStart && value1.FaceCount == value2.FaceCount
			 && value1.VertexStart == value2.VertexStart && value1.VertexCount == value2.VertexCount );
	}

	bool GlyphMetricsFloat::operator == ( GlyphMetricsFloat left, GlyphMetricsFloat right )
	{
		return GlyphMetricsFloat::Equals( left, right );
	}

	bool GlyphMetricsFloat::operator != ( GlyphMetricsFloat left, GlyphMetricsFloat right )
	{
		return !GlyphMetricsFloat::Equals( left, right );
	}

	int GlyphMetricsFloat::GetHashCode()
	{
		return BlackBoxX.GetHashCode() + BlackBoxY.GetHashCode() + GlyphOrigin.GetHashCode()
			 + CellIncX.GetHashCode() + CellIncY.GetHashCode();
	}

	bool GlyphMetricsFloat::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<GlyphMetricsFloat>( value ) );
	}

	bool GlyphMetricsFloat::Equals( GlyphMetricsFloat value )
	{
		return ( BlackBoxX == value.BlackBoxX && BlackBoxY == value.BlackBoxY && GlyphOrigin == value.GlyphOrigin
			 && CellIncX == value.CellIncX && CellIncY == value.CellIncY );
	}

	bool GlyphMetricsFloat::Equals( GlyphMetricsFloat% value1, GlyphMetricsFloat% value2 )
	{
		return ( value1.BlackBoxX == value2.BlackBoxX && value1.BlackBoxY == value2.BlackBoxY && value1.GlyphOrigin == value2.GlyphOrigin
			 && value1.CellIncX == value2.CellIncX && value1.CellIncY == value2.CellIncY );
	}

	bool AttributeWeights::operator == ( AttributeWeights left, AttributeWeights right )
	{
		return AttributeWeights::Equals( left, right );
	}

	bool AttributeWeights::operator != ( AttributeWeights left, AttributeWeights right )
	{
		return !AttributeWeights::Equals( left, right );
	}

	int AttributeWeights::GetHashCode()
	{
		return Position.GetHashCode() + Boundary.GetHashCode() + Normal.GetHashCode()
			 + Diffuse.GetHashCode() + Specular.GetHashCode() + TextureCoordinate1.GetHashCode()
			 + TextureCoordinate2.GetHashCode() + TextureCoordinate3.GetHashCode() + TextureCoordinate4.GetHashCode()
			 + TextureCoordinate5.GetHashCode() + TextureCoordinate6.GetHashCode() + TextureCoordinate7.GetHashCode()
			 + TextureCoordinate8.GetHashCode() + Tangent.GetHashCode() + Binormal.GetHashCode();
	}

	bool AttributeWeights::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<AttributeWeights>( value ) );
	}

	bool AttributeWeights::Equals( AttributeWeights value )
	{
		return ( Position == value.Position && Boundary == value.Boundary && Normal == value.Normal
			 && Diffuse == value.Diffuse && Specular == value.Specular && TextureCoordinate1 == value.TextureCoordinate1
			 && TextureCoordinate2 == value.TextureCoordinate2 && TextureCoordinate3 == value.TextureCoordinate3 && TextureCoordinate4 == value.TextureCoordinate4
			 && TextureCoordinate5 == value.TextureCoordinate5 && TextureCoordinate6 == value.TextureCoordinate6 && TextureCoordinate7 == value.TextureCoordinate7
			 && TextureCoordinate8 == value.TextureCoordinate8 && Tangent == value.Tangent && Binormal == value.Binormal );
	}

	bool AttributeWeights::Equals( AttributeWeights% value1, AttributeWeights% value2 )
	{
		return ( value1.Position == value2.Position && value1.Boundary == value2.Boundary && value1.Normal == value2.Normal
			 && value1.Diffuse == value2.Diffuse && value1.Specular == value2.Specular && value1.TextureCoordinate1 == value2.TextureCoordinate1
			 && value1.TextureCoordinate2 == value2.TextureCoordinate2 && value1.TextureCoordinate3 == value2.TextureCoordinate3 && value1.TextureCoordinate4 == value2.TextureCoordinate4
			 && value1.TextureCoordinate5 == value2.TextureCoordinate5 && value1.TextureCoordinate6 == value2.TextureCoordinate6 && value1.TextureCoordinate7 == value2.TextureCoordinate7
			 && value1.TextureCoordinate8 == value2.TextureCoordinate8 && value1.Tangent == value2.Tangent && value1.Binormal == value2.Binormal );
	}

	bool IntersectInformation::operator == ( IntersectInformation left, IntersectInformation right )
	{
		return IntersectInformation::Equals( left, right );
	}

	bool IntersectInformation::operator != ( IntersectInformation left, IntersectInformation right )
	{
		return !IntersectInformation::Equals( left, right );
	}

	int IntersectInformation::GetHashCode()
	{
		return FaceIndex.GetHashCode() + U.GetHashCode() + V.GetHashCode()
			 + Distance.GetHashCode();
	}

	bool IntersectInformation::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<IntersectInformation>( value ) );
	}

	bool IntersectInformation::Equals( IntersectInformation value )
	{
		return ( FaceIndex == value.FaceIndex && U == value.U && V == value.V
			 && Distance == value.Distance );
	}

	bool IntersectInformation::Equals( IntersectInformation% value1, IntersectInformation% value2 )
	{
		return ( value1.FaceIndex == value2.FaceIndex && value1.U == value2.U && value1.V == value2.V
			 && value1.Distance == value2.Distance );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<VertexElement> pinned_elements = &elements[0];

		HRESULT hr = InternalPointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( mesh );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = InternalPointer->CloneMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( fvf ), 
			device->InternalPointer, &mesh );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Mesh::FromPointer( mesh );
	}

	Result BaseMesh::DrawSubset( int subset )
	{
		HRESULT hr = InternalPointer->DrawSubset( subset );
		return RECORD_D3D9( hr );
	}

	Device^ BaseMesh::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Device::FromPointer( device );
	}

	IndexBuffer^ BaseMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;
		HRESULT hr = InternalPointer->GetIndexBuffer( &ib );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return IndexBuffer::FromPointer( ib );
	}

	VertexBuffer^ BaseMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = InternalPointer->GetVertexBuffer( &vb );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return VertexBuffer::FromPointer( vb );
	}

	array<VertexElement>^ BaseMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];
		HRESULT hr = InternalPointer->GetDeclaration( elementBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
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

		if( RECORD_D3D9( hr ).IsFailure || count == 0 )
			return nullptr;

		array<AttributeRange>^ attribTable = gcnew array<AttributeRange>( count );
		pin_ptr<AttributeRange> pinnedTable = &attribTable[0];
		hr = InternalPointer->GetAttributeTable( reinterpret_cast<D3DXATTRIBUTERANGE*>( pinnedTable ), &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return attribTable;
	}

	DataStream^ BaseMesh::LockIndexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = InternalPointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		// determine the size of the buffer
		int size = 6 * FaceCount;
		if( (CreationOptions & MeshFlags::Use32Bit) == MeshFlags::Use32Bit )
			size *= 2;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	Result BaseMesh::UnlockIndexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockIndexBuffer();
		return RECORD_D3D9( hr );
	}

	DataStream^ BaseMesh::LockVertexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = InternalPointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		// determine the size of the buffer
		int size = BytesPerVertex * VertexCount;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	Result BaseMesh::UnlockVertexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockVertexBuffer();
		return RECORD_D3D9( hr );
	}

	array<int>^ BaseMesh::GenerateAdjacency( float epsilon )
	{
		// allocate the array to write the adjacency into
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = InternalPointer->GenerateAdjacency( epsilon, reinterpret_cast<DWORD*>( pinnedAdj ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return adjacency;
	}

	Result BaseMesh::UpdateSemantics( array<VertexElement>^ elements )
	{
		pin_ptr<VertexElement> pinnedElements = &elements[0];

		HRESULT hr = InternalPointer->UpdateSemantics( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ) );
		return RECORD_D3D9( hr );
	}

	IndexBuffer^ BaseMesh::ConvertSubsetToSingleStrip( int attributeId, MeshFlags options, [Out] int% indexCount )
	{
		IDirect3DIndexBuffer9 *result;
		DWORD count;

		HRESULT hr = D3DXConvertMeshSubsetToSingleStrip( InternalPointer, attributeId, static_cast<DWORD>( options ),
			&result, &count );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			indexCount = 0;
			return nullptr;
		}

		indexCount = count;
		return IndexBuffer::FromPointer( result );
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

		if( RECORD_D3D9( hr ).IsFailure )
		{
			indexCount = 0;
			stripLengths = nullptr;
			return nullptr;
		}

		indexCount = numIndices;
		stripLengths = ( gcnew DataStream( buffer ) )->ReadRange<int>( numStrips );
		return IndexBuffer::FromPointer( result );
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

		if( RECORD_D3D9( hr ).IsFailure )
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

		if( RECORD_D3D9( hr ).IsFailure )
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

		if( RECORD_D3D9( hr ).IsFailure || !result )
			return false;

		return true;
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

		if( RECORD_D3D9( hr ).IsFailure )
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

		if( RECORD_D3D9( hr ).IsFailure )
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

		if( RECORD_D3D9( hr ).IsFailure || !result )
			return false;

		return true;
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

	Mesh::Mesh( ID3DXMesh* mesh )
	{
		Construct( mesh );
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

		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(mesh);
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
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
		Mesh^ tableEntry = safe_cast<Mesh^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Mesh( pointer );
	}

	Mesh^ Mesh::FromPointer( IntPtr pointer )
	{
		Mesh^ tableEntry = safe_cast<Mesh^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Mesh( pointer );
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
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ result = gcnew Mesh( mesh );

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

	Mesh^ Mesh::CreateBox( Device^ device, float width, float height, float depth )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateBox( device->InternalPointer, width, height, depth, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

		mesh->SetAdjacency( ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 ) );
		return mesh;
	}

	Mesh^ Mesh::CreateTeapot( Device^ device )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTeapot( device->InternalPointer, &result, &adj );
		
		if( RECORD_D3D9( hr ).IsFailure )
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
		
		if( RECORD_D3D9( hr ).IsFailure )
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

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( RECORD_D3D9( hr ).IsFailure )
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

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );

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

		Mesh^ mesh = gcnew Mesh( result );

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

		Mesh^ mesh = gcnew Mesh( result );

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

		Mesh^ mesh = gcnew Mesh( result );

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

		Mesh^ mesh = gcnew Mesh( result );

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

		HRESULT hr = D3DXComputeTangentFrameEx( InternalPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), adjacencyIn,
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, NULL );

		if( RECORD_D3D9( hr ).IsFailure )
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

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
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

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options )
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

		return gcnew Mesh( result );
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

		HRESULT hr = D3DXSimplifyMesh( mesh->InternalPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
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

		HRESULT hr = D3DXSimplifyMesh( mesh->InternalPointer, adjacencyIn,
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew Mesh( result );
	}
}
}