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

		public value class BandwidthTimings
		{
		public:
			property float MaximumBandwidthUtilized;
			property float FrontEndUploadMemoryUtilizedPercent;
			property float VertexRateUtilizedPercent;
			property float TriangleSetupRateUtilizedPercent;
			property float FillRateUtilizedPercent;
		};

		public value class CacheUtilization
		{
		public:
			property float TextureCacheHitRate;
			property float PostTransformVertexCacheHitRate;
		};

		public value class InterfaceTimings
		{
		public:
			property float WaitingForGPUToUseApplicationResourceTimePercent;
			property float WaitingForGPUToAcceptMoreCommandsTimePercent;
			property float WaitingForGPUToStayWithinLatencyTimePercent;
			property float WaitingForGPUExclusiveResourceTimePercent;
			property float WaitingForGPUOtherTimePercent;
		};

		public value class PipelineTimings
		{
		public:
			property float VertexProcessingTimePercent;
			property float PixelProcessingTimePercent;
			property float OtherGPUProcessingTimePercent;
			property float GPUIdleTimePercent;
		};

		public value class ResourceStats
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
		};

		public value class ResourceManager
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
		};

		public value class VCache
		{
		public:
			property int Pattern;
			property int OptMethod;
			property int CacheSize;
			property int MagicNumber;
		};

		public value class VertexStats
		{
		public:
			property int RenderedTriangleCount;
			property int ExtraClippingTriangleCount;
		};

		public value class StageTimings
		{
		public:
			property float MemoryProcessingPercent;
			property float ComputationProcessingPercent;
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
