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

#include "../ComObject.h"

//#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "Device.h"
#include "Query.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
		bool BandwidthTimings::operator == ( BandwidthTimings left, BandwidthTimings right )
	{
		return BandwidthTimings::Equals( left, right );
	}

	bool BandwidthTimings::operator != ( BandwidthTimings left, BandwidthTimings right )
	{
		return !BandwidthTimings::Equals( left, right );
	}

	int BandwidthTimings::GetHashCode()
	{
		return MaximumBandwidthUtilized.GetHashCode() + FrontEndUploadMemoryUtilizedPercent.GetHashCode() + VertexRateUtilizedPercent.GetHashCode()
			 + TriangleSetupRateUtilizedPercent.GetHashCode() + FillRateUtilizedPercent.GetHashCode();
	}

	bool BandwidthTimings::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<BandwidthTimings>( value ) );
	}

	bool BandwidthTimings::Equals( BandwidthTimings value )
	{
		return ( MaximumBandwidthUtilized == value.MaximumBandwidthUtilized && FrontEndUploadMemoryUtilizedPercent == value.FrontEndUploadMemoryUtilizedPercent && VertexRateUtilizedPercent == value.VertexRateUtilizedPercent
			 && TriangleSetupRateUtilizedPercent == value.TriangleSetupRateUtilizedPercent && FillRateUtilizedPercent == value.FillRateUtilizedPercent );
	}

	bool BandwidthTimings::Equals( BandwidthTimings% value1, BandwidthTimings% value2 )
	{
		return ( value1.MaximumBandwidthUtilized == value2.MaximumBandwidthUtilized && value1.FrontEndUploadMemoryUtilizedPercent == value2.FrontEndUploadMemoryUtilizedPercent && value1.VertexRateUtilizedPercent == value2.VertexRateUtilizedPercent
			 && value1.TriangleSetupRateUtilizedPercent == value2.TriangleSetupRateUtilizedPercent && value1.FillRateUtilizedPercent == value2.FillRateUtilizedPercent );
	}

	bool CacheUtilization::operator == ( CacheUtilization left, CacheUtilization right )
	{
		return CacheUtilization::Equals( left, right );
	}

	bool CacheUtilization::operator != ( CacheUtilization left, CacheUtilization right )
	{
		return !CacheUtilization::Equals( left, right );
	}

	int CacheUtilization::GetHashCode()
	{
		return TextureCacheHitRate.GetHashCode() + PostTransformVertexCacheHitRate.GetHashCode();
	}

	bool CacheUtilization::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<CacheUtilization>( value ) );
	}

	bool CacheUtilization::Equals( CacheUtilization value )
	{
		return ( TextureCacheHitRate == value.TextureCacheHitRate && PostTransformVertexCacheHitRate == value.PostTransformVertexCacheHitRate );
	}

	bool CacheUtilization::Equals( CacheUtilization% value1, CacheUtilization% value2 )
	{
		return ( value1.TextureCacheHitRate == value2.TextureCacheHitRate && value1.PostTransformVertexCacheHitRate == value2.PostTransformVertexCacheHitRate );
	}

	bool InterfaceTimings::operator == ( InterfaceTimings left, InterfaceTimings right )
	{
		return InterfaceTimings::Equals( left, right );
	}

	bool InterfaceTimings::operator != ( InterfaceTimings left, InterfaceTimings right )
	{
		return !InterfaceTimings::Equals( left, right );
	}

	int InterfaceTimings::GetHashCode()
	{
		return WaitingForGPUToUseApplicationResourceTimePercent.GetHashCode() + WaitingForGPUToAcceptMoreCommandsTimePercent.GetHashCode() + WaitingForGPUToStayWithinLatencyTimePercent.GetHashCode()
			 + WaitingForGPUExclusiveResourceTimePercent.GetHashCode() + WaitingForGPUOtherTimePercent.GetHashCode();
	}

	bool InterfaceTimings::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<InterfaceTimings>( value ) );
	}

	bool InterfaceTimings::Equals( InterfaceTimings value )
	{
		return ( WaitingForGPUToUseApplicationResourceTimePercent == value.WaitingForGPUToUseApplicationResourceTimePercent && WaitingForGPUToAcceptMoreCommandsTimePercent == value.WaitingForGPUToAcceptMoreCommandsTimePercent && WaitingForGPUToStayWithinLatencyTimePercent == value.WaitingForGPUToStayWithinLatencyTimePercent
			 && WaitingForGPUExclusiveResourceTimePercent == value.WaitingForGPUExclusiveResourceTimePercent && WaitingForGPUOtherTimePercent == value.WaitingForGPUOtherTimePercent );
	}

	bool InterfaceTimings::Equals( InterfaceTimings% value1, InterfaceTimings% value2 )
	{
		return ( value1.WaitingForGPUToUseApplicationResourceTimePercent == value2.WaitingForGPUToUseApplicationResourceTimePercent && value1.WaitingForGPUToAcceptMoreCommandsTimePercent == value2.WaitingForGPUToAcceptMoreCommandsTimePercent && value1.WaitingForGPUToStayWithinLatencyTimePercent == value2.WaitingForGPUToStayWithinLatencyTimePercent
			 && value1.WaitingForGPUExclusiveResourceTimePercent == value2.WaitingForGPUExclusiveResourceTimePercent && value1.WaitingForGPUOtherTimePercent == value2.WaitingForGPUOtherTimePercent );
	}

	bool PipelineTimings::operator == ( PipelineTimings left, PipelineTimings right )
	{
		return PipelineTimings::Equals( left, right );
	}

	bool PipelineTimings::operator != ( PipelineTimings left, PipelineTimings right )
	{
		return !PipelineTimings::Equals( left, right );
	}

	int PipelineTimings::GetHashCode()
	{
		return VertexProcessingTimePercent.GetHashCode() + PixelProcessingTimePercent.GetHashCode() + OtherGPUProcessingTimePercent.GetHashCode()
			 + GPUIdleTimePercent.GetHashCode();
	}

	bool PipelineTimings::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<PipelineTimings>( value ) );
	}

	bool PipelineTimings::Equals( PipelineTimings value )
	{
		return ( VertexProcessingTimePercent == value.VertexProcessingTimePercent && PixelProcessingTimePercent == value.PixelProcessingTimePercent && OtherGPUProcessingTimePercent == value.OtherGPUProcessingTimePercent
			 && GPUIdleTimePercent == value.GPUIdleTimePercent );
	}

	bool PipelineTimings::Equals( PipelineTimings% value1, PipelineTimings% value2 )
	{
		return ( value1.VertexProcessingTimePercent == value2.VertexProcessingTimePercent && value1.PixelProcessingTimePercent == value2.PixelProcessingTimePercent && value1.OtherGPUProcessingTimePercent == value2.OtherGPUProcessingTimePercent
			 && value1.GPUIdleTimePercent == value2.GPUIdleTimePercent );
	}

	bool ResourceStats::operator == ( ResourceStats left, ResourceStats right )
	{
		return ResourceStats::Equals( left, right );
	}

	bool ResourceStats::operator != ( ResourceStats left, ResourceStats right )
	{
		return !ResourceStats::Equals( left, right );
	}

	int ResourceStats::GetHashCode()
	{
		return Thrashing.GetHashCode() + ApproximateBytesDownloaded.GetHashCode() + NumberEvicted.GetHashCode()
			 + NumberVideoCreated.GetHashCode() + LastPriority.GetHashCode() + NumberUsed.GetHashCode()
			 + NumberUsedInVideoMemory.GetHashCode() + WorkingSet.GetHashCode() + WorkingSetBytes.GetHashCode()
			 + TotalManaged.GetHashCode() + TotalBytes.GetHashCode();
	}

	bool ResourceStats::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ResourceStats>( value ) );
	}

	bool ResourceStats::Equals( ResourceStats value )
	{
		return ( Thrashing == value.Thrashing && ApproximateBytesDownloaded == value.ApproximateBytesDownloaded && NumberEvicted == value.NumberEvicted
			 && NumberVideoCreated == value.NumberVideoCreated && LastPriority == value.LastPriority && NumberUsed == value.NumberUsed
			 && NumberUsedInVideoMemory == value.NumberUsedInVideoMemory && WorkingSet == value.WorkingSet && WorkingSetBytes == value.WorkingSetBytes
			 && TotalManaged == value.TotalManaged && TotalBytes == value.TotalBytes );
	}

	bool ResourceStats::Equals( ResourceStats% value1, ResourceStats% value2 )
	{
		return ( value1.Thrashing == value2.Thrashing && value1.ApproximateBytesDownloaded == value2.ApproximateBytesDownloaded && value1.NumberEvicted == value2.NumberEvicted
			 && value1.NumberVideoCreated == value2.NumberVideoCreated && value1.LastPriority == value2.LastPriority && value1.NumberUsed == value2.NumberUsed
			 && value1.NumberUsedInVideoMemory == value2.NumberUsedInVideoMemory && value1.WorkingSet == value2.WorkingSet && value1.WorkingSetBytes == value2.WorkingSetBytes
			 && value1.TotalManaged == value2.TotalManaged && value1.TotalBytes == value2.TotalBytes );
	}

	bool ResourceManager::operator == ( ResourceManager left, ResourceManager right )
	{
		return ResourceManager::Equals( left, right );
	}

	bool ResourceManager::operator != ( ResourceManager left, ResourceManager right )
	{
		return !ResourceManager::Equals( left, right );
	}

	int ResourceManager::GetHashCode()
	{
		return Stats.GetHashCode() + SurfaceStats.GetHashCode() + VolumeStats.GetHashCode()
			 + TextureStats.GetHashCode() + VolumeTextureStats.GetHashCode() + CubeTextureStats.GetHashCode()
			 + VertexBufferStats.GetHashCode() + IndexBufferStats.GetHashCode();
	}

	bool ResourceManager::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ResourceManager>( value ) );
	}

	bool ResourceManager::Equals( ResourceManager value )
	{
		return ( Stats == value.Stats && SurfaceStats == value.SurfaceStats && VolumeStats == value.VolumeStats
			 && TextureStats == value.TextureStats && VolumeTextureStats == value.VolumeTextureStats && CubeTextureStats == value.CubeTextureStats
			 && VertexBufferStats == value.VertexBufferStats && IndexBufferStats == value.IndexBufferStats );
	}

	bool ResourceManager::Equals( ResourceManager% value1, ResourceManager% value2 )
	{
		return ( value1.Stats == value2.Stats && value1.SurfaceStats == value2.SurfaceStats && value1.VolumeStats == value2.VolumeStats
			 && value1.TextureStats == value2.TextureStats && value1.VolumeTextureStats == value2.VolumeTextureStats && value1.CubeTextureStats == value2.CubeTextureStats
			 && value1.VertexBufferStats == value2.VertexBufferStats && value1.IndexBufferStats == value2.IndexBufferStats );
	}

	bool VCache::operator == ( VCache left, VCache right )
	{
		return VCache::Equals( left, right );
	}

	bool VCache::operator != ( VCache left, VCache right )
	{
		return !VCache::Equals( left, right );
	}

	int VCache::GetHashCode()
	{
		return Pattern.GetHashCode() + OptMethod.GetHashCode() + CacheSize.GetHashCode()
			 + MagicNumber.GetHashCode();
	}

	bool VCache::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<VCache>( value ) );
	}

	bool VCache::Equals( VCache value )
	{
		return ( Pattern == value.Pattern && OptMethod == value.OptMethod && CacheSize == value.CacheSize
			 && MagicNumber == value.MagicNumber );
	}

	bool VCache::Equals( VCache% value1, VCache% value2 )
	{
		return ( value1.Pattern == value2.Pattern && value1.OptMethod == value2.OptMethod && value1.CacheSize == value2.CacheSize
			 && value1.MagicNumber == value2.MagicNumber );
	}

	bool VertexStats::operator == ( VertexStats left, VertexStats right )
	{
		return VertexStats::Equals( left, right );
	}

	bool VertexStats::operator != ( VertexStats left, VertexStats right )
	{
		return !VertexStats::Equals( left, right );
	}

	int VertexStats::GetHashCode()
	{
		return RenderedTriangleCount.GetHashCode() + ExtraClippingTriangleCount.GetHashCode();
	}

	bool VertexStats::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<VertexStats>( value ) );
	}

	bool VertexStats::Equals( VertexStats value )
	{
		return ( RenderedTriangleCount == value.RenderedTriangleCount && ExtraClippingTriangleCount == value.ExtraClippingTriangleCount );
	}

	bool VertexStats::Equals( VertexStats% value1, VertexStats% value2 )
	{
		return ( value1.RenderedTriangleCount == value2.RenderedTriangleCount && value1.ExtraClippingTriangleCount == value2.ExtraClippingTriangleCount );
	}

	bool StageTimings::operator == ( StageTimings left, StageTimings right )
	{
		return StageTimings::Equals( left, right );
	}

	bool StageTimings::operator != ( StageTimings left, StageTimings right )
	{
		return !StageTimings::Equals( left, right );
	}

	int StageTimings::GetHashCode()
	{
		return MemoryProcessingPercent.GetHashCode() + ComputationProcessingPercent.GetHashCode();
	}

	bool StageTimings::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<StageTimings>( value ) );
	}

	bool StageTimings::Equals( StageTimings value )
	{
		return ( MemoryProcessingPercent == value.MemoryProcessingPercent && ComputationProcessingPercent == value.ComputationProcessingPercent );
	}

	bool StageTimings::Equals( StageTimings% value1, StageTimings% value2 )
	{
		return ( value1.MemoryProcessingPercent == value2.MemoryProcessingPercent && value1.ComputationProcessingPercent == value2.ComputationProcessingPercent );
	}

	Query::Query( IDirect3DQuery9* pointer )
	{
		Construct( pointer );
	}

	Query::Query( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Query::Query( Device^ device, QueryType type )
	{
		IDirect3DQuery9* query;
		HRESULT hr = device->InternalPointer->CreateQuery( static_cast<D3DQUERYTYPE>( type ), &query );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( "Failed to create Query." );

		Construct(query);
	}

	Query^ Query::FromPointer( IDirect3DQuery9* pointer )
	{
		Query^ tableEntry = safe_cast<Query^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Query( pointer );
	}

	Query^ Query::FromPointer( IntPtr pointer )
	{
		Query^ tableEntry = safe_cast<Query^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Query( pointer );
	}


	int Query::DataSize::get()
	{
		return InternalPointer->GetDataSize();
	}

	QueryType Query::Type::get()
	{
		return static_cast<QueryType>( InternalPointer->GetType() );
	}

	Device^ Query::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Device::FromPointer( device );
	}

	Result Query::Issue( SlimDX::Direct3D9::Issue flags )
	{
		HRESULT hr = InternalPointer->Issue( static_cast<DWORD>( flags ) );
		return RECORD_D3D9( hr );
	}

	bool Query::CheckStatus( bool flush )
	{
		HRESULT hr = InternalPointer->GetData( NULL, 0, flush ? D3DGETDATA_FLUSH : 0 );
		
		switch( hr )
		{
		case S_OK:
			return true;
		case S_FALSE:
			return false;
			
		default:
			RECORD_D3D9( hr );
			return false;
		}
	}

	generic<typename T>
	T Query::GetData( bool flush )
	{
		HRESULT hr = S_OK;
		QueryType type = Type;

		switch( type )
		{
		case QueryType::BandwidthTimings:
			if( T::typeid != BandwidthTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::CacheUtilization:
			if( T::typeid != CacheUtilization::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Event:
			if( T::typeid != bool::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::InterfaceTimings:
			if( T::typeid != InterfaceTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Occlusion:
			if( T::typeid != Int32::typeid && T::typeid != UInt32::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::PipelineTimings:
			if( T::typeid != PipelineTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::ResourceManager:
			if( T::typeid != ResourceManager::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Timestamp:
			if( T::typeid != Int64::typeid && T::typeid != UInt64::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::TimestampDisjoint:
			if( T::typeid != bool::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::TimestampFreq:
			if( T::typeid != Int64::typeid && T::typeid != UInt64::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VCache:
			if( T::typeid != VCache::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VertexStats:
			if( T::typeid != VertexStats::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VertexTimings:
			if( T::typeid != StageTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		}

		RECORD_D3D9( hr );

		DWORD flags = flush ? D3DGETDATA_FLUSH : 0;

		//get the actual data now
		if( type == QueryType::Event || type == QueryType::TimestampDisjoint )
		{
			//need to marshal BOOL (int) to bool
			BOOL value = FALSE;
			hr = InternalPointer->GetData( &value, sizeof(BOOL), flags );
			RECORD_D3D9( hr );
			//we know that T is a bool, but the runtime does not
			return (T) (value > 0);
		}
		else
		{
			T data;
			hr = InternalPointer->GetData( &data, Marshal::SizeOf( T::typeid ), flags );
			RECORD_D3D9( hr );
			return data;
		}
	}
}
}
