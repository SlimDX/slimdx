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
	namespace Direct3D9
	{
		[System::Flags]
		public enum class Issue
		{
			Begin = D3DISSUE_BEGIN,
			End = D3DISSUE_END
		};

		public value class BandwidthTimings : System::IEquatable<BandwidthTimings>
		{
		public:
			property float MaximumBandwidthUtilized;
			property float FrontEndUploadMemoryUtilizedPercent;
			property float VertexRateUtilizedPercent;
			property float TriangleSetupRateUtilizedPercent;
			property float FillRateUtilizedPercent;

			static bool operator == ( BandwidthTimings left, BandwidthTimings right );
			static bool operator != ( BandwidthTimings left, BandwidthTimings right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( BandwidthTimings other );
			static bool Equals( BandwidthTimings% value1, BandwidthTimings% value2 );
		};

		public value class CacheUtilization : System::IEquatable<CacheUtilization>
		{
		public:
			property float TextureCacheHitRate;
			property float PostTransformVertexCacheHitRate;

			static bool operator == ( CacheUtilization left, CacheUtilization right );
			static bool operator != ( CacheUtilization left, CacheUtilization right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( CacheUtilization other );
			static bool Equals( CacheUtilization% value1, CacheUtilization% value2 );
		};

		public value class InterfaceTimings : System::IEquatable<InterfaceTimings>
		{
		public:
			property float WaitingForGPUToUseApplicationResourceTimePercent;
			property float WaitingForGPUToAcceptMoreCommandsTimePercent;
			property float WaitingForGPUToStayWithinLatencyTimePercent;
			property float WaitingForGPUExclusiveResourceTimePercent;
			property float WaitingForGPUOtherTimePercent;

			static bool operator == ( InterfaceTimings left, InterfaceTimings right );
			static bool operator != ( InterfaceTimings left, InterfaceTimings right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( InterfaceTimings other );
			static bool Equals( InterfaceTimings% value1, InterfaceTimings% value2 );
		};

		public value class PipelineTimings : System::IEquatable<PipelineTimings>
		{
		public:
			property float VertexProcessingTimePercent;
			property float PixelProcessingTimePercent;
			property float OtherGPUProcessingTimePercent;
			property float GPUIdleTimePercent;

			static bool operator == ( PipelineTimings left, PipelineTimings right );
			static bool operator != ( PipelineTimings left, PipelineTimings right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( PipelineTimings other );
			static bool Equals( PipelineTimings% value1, PipelineTimings% value2 );
		};

		public value class ResourceStats : System::IEquatable<ResourceStats>
		{
		public:
			property bool Thrashing;
			property int ApproximateBytesDownloaded;
			property int NumberEvicted;
			property int NumberVideoCreated;
			property int LastPriority;
			property int NumberUsed;
			property int NumberUsedInVideoMemory;
			property int WorkingSet;
			property int WorkingSetBytes;
			property int TotalManaged;
			property int TotalBytes;

			static bool operator == ( ResourceStats left, ResourceStats right );
			static bool operator != ( ResourceStats left, ResourceStats right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ResourceStats other );
			static bool Equals( ResourceStats% value1, ResourceStats% value2 );
		};

		public value class ResourceManager : System::IEquatable<ResourceManager>
		{
		public:
			property ResourceStats Stats;
			property ResourceStats SurfaceStats;
			property ResourceStats VolumeStats;
			property ResourceStats TextureStats;
			property ResourceStats VolumeTextureStats;
			property ResourceStats CubeTextureStats;
			property ResourceStats VertexBufferStats;
			property ResourceStats IndexBufferStats;

			static bool operator == ( ResourceManager left, ResourceManager right );
			static bool operator != ( ResourceManager left, ResourceManager right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ResourceManager other );
			static bool Equals( ResourceManager% value1, ResourceManager% value2 );
		};

		public value class VCache : System::IEquatable<VCache>
		{
		public:
			property int Pattern;
			property int OptMethod;
			property int CacheSize;
			property int MagicNumber;

			static bool operator == ( VCache left, VCache right );
			static bool operator != ( VCache left, VCache right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VCache other );
			static bool Equals( VCache% value1, VCache% value2 );
		};

		public value class VertexStats : System::IEquatable<VertexStats>
		{
		public:
			property int RenderedTriangleCount;
			property int ExtraClippingTriangleCount;

			static bool operator == ( VertexStats left, VertexStats right );
			static bool operator != ( VertexStats left, VertexStats right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VertexStats other );
			static bool Equals( VertexStats% value1, VertexStats% value2 );
		};

		public value class StageTimings : System::IEquatable<StageTimings>
		{
		public:
			property float MemoryProcessingPercent;
			property float ComputationProcessingPercent;

			static bool operator == ( StageTimings left, StageTimings right );
			static bool operator != ( StageTimings left, StageTimings right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( StageTimings other );
			static bool Equals( StageTimings% value1, StageTimings% value2 );
		};

		public ref class Query : public ComObject
		{
			COMOBJECT(IDirect3DQuery9);

		internal:
			/* Unused for now.
			Query( IDirect3DQuery9* query );
			*/

		public:
			Query( System::IntPtr query );
			Query( Device^ device, QueryType type );
			~Query() { Destruct(); }

			Device^ GetDevice();
			Result Issue( SlimDX::Direct3D9::Issue flags );
			bool CheckStatus( bool flush );

			generic<typename T> where T : value class
			T GetData( bool flush );

			property QueryType Type
			{
				QueryType get();
			};

			property int DataSize
			{
				int get();
			}
		};
	}
}
