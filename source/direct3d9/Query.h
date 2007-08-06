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
	namespace Direct3D9
	{
		[Flags]
		public enum class Issue
		{
			Begin = D3DISSUE_BEGIN,
			End = D3DISSUE_END
		};

		public value class BandwidthTimings
		{
		public:
			float MaxBandwidthUtilized;
			float FrontEndUploadMemoryUtilizedPercent;
			float VertexRateUtilizedPercent;
			float TriangleSetupRateUtilizedPercent;
			float FillRateUtilizedPercent;
		};

		public value class CacheUtilization
		{
		public:
			float TextureCacheHitRate;
			float PostTransformVertexCacheHitRate;
		};

		public value class InterfaceTimings
		{
		public:
			float WaitingForGPUToUseApplicationResourceTimePercent;
			float WaitingForGPUToAcceptMoreCommandsTimePercent;
			float WaitingForGPUToStayWithinLatencyTimePercent;
			float WaitingForGPUExclusiveResourceTimePercent;
			float WaitingForGPUOtherTimePercent;
		};

		public value class PipelineTimings
		{
		public:
			float VertexProcessingTimePercent;
			float PixelProcessingTimePercent;
			float OtherGPUProcessingTimePercent;
			float GPUIdleTimePercent;
		};

		public value class ResourceStats
		{
		public:
			bool Thrashing;
			int ApproxBytesDownloaded;
			int NumberEvicted;
			int NumberVidCreated;
			int LastPriority;
			int NumberUsed;
			int NumberUsedInVidMem;
			int WorkingSet;
			int WorkingSetBytes;
			int TotalManaged;
			int TotalBytes;
		};

		public value class ResourceManager
		{
		public:
			ResourceStats Stats;
			ResourceStats SurfaceStats;
			ResourceStats VolumeStats;
			ResourceStats TextureStats;
			ResourceStats VolumeTextureStats;
			ResourceStats CubeTextureStats;
			ResourceStats VertexBufferStats;
			ResourceStats IndexBufferStats;
		};

		public value class VCache
		{
		public:
			int Pattern;
			int OptMethod;
			int CacheSize;
			int MagicNumber;
		};

		public value class VertexStats
		{
		public:
			int NumRenderedTriangles;
			int NumExtraClippingTriangles;
		};

		public value class StageTimings
		{
		public:
			float MemoryProcessingPercent;
			float ComputationProcessingPercent;
		};

		public ref class Query sealed : public DirectXObject<IDirect3DQuery9>
		{
		public:
			Query( IDirect3DQuery9* query );
			Query( Device^ device, QueryType type );
			~Query() { Destruct(); }

			property QueryType Type
			{
				QueryType get();
			};

			property int DataSize
			{
				int get();
			}

			Device^ GetDevice();
			void Issue( SlimDX::Direct3D9::Issue flags );
			bool CheckStatus( bool flush );

			generic<typename T> where T : value class
			T GetData( bool flush );
		};
	}
}
