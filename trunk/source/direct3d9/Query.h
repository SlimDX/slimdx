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
		private:
			float maxBandwidthUtilized;
            float frontEndUploadMemoryUtilizedPercent;
            float vertexRateUtilizedPercent;
            float triangleSetupRateUtilizedPercent;
            float fillRateUtilizedPercent;

		public:
			property float MaxBandwidthUtilized
            {
                float get() { return maxBandwidthUtilized; }
                void set( float value ) { maxBandwidthUtilized = value; }
            }

            property float FrontEndUploadMemoryUtilizedPercent
            {
                float get() { return frontEndUploadMemoryUtilizedPercent; }
                void set( float value ) { frontEndUploadMemoryUtilizedPercent = value; }
            }

            property float VertexRateUtilizedPercent
            {
                float get() { return vertexRateUtilizedPercent; }
                void set( float value ) { vertexRateUtilizedPercent = value; }
            }

            property float TriangleSetupRateUtilizedPercent
            {
                float get() { return triangleSetupRateUtilizedPercent; }
                void set( float value ) { triangleSetupRateUtilizedPercent = value; }
            }

            property float FillRateUtilizedPercent
            {
                float get() { return fillRateUtilizedPercent; }
                void set( float value ) { fillRateUtilizedPercent = value; }
            }
		};

		public value class CacheUtilization
		{
		private:
			float textureCacheHitRate;
            float postTransformVertexCacheHitRate;

		public:
			property float TextureCacheHitRate
            {
                float get() { return textureCacheHitRate; }
                void set( float value ) { textureCacheHitRate = value; }
            }

            property float PostTransformVertexCacheHitRate
            {
                float get() { return postTransformVertexCacheHitRate; }
                void set( float value ) { postTransformVertexCacheHitRate = value; }
            }
		};

		public value class InterfaceTimings
		{
		private:
			float waitingForGPUToUseApplicationResourceTimePercent;
			float waitingForGPUToAcceptMoreCommandsTimePercent;
            float waitingForGPUToStayWithinLatencyTimePercent;
            float waitingForGPUExclusiveResourceTimePercent;
            float waitingForGPUOtherTimePercent;

		public:
			property float WaitingForGpuToUseApplicationResourceTimePercent
            {
                float get() { return waitingForGPUToUseApplicationResourceTimePercent; }
                void set( float value ) { waitingForGPUToUseApplicationResourceTimePercent = value; }
            }

            property float WaitingForGpuToAcceptMoreCommandsTimePercent
            {
                float get() { return waitingForGPUToAcceptMoreCommandsTimePercent; }
                void set( float value ) { waitingForGPUToAcceptMoreCommandsTimePercent = value; }
            }

            property float WaitingForGpuToStayWithinLatencyTimePercent
            {
                float get() { return waitingForGPUToStayWithinLatencyTimePercent; }
                void set( float value ) { waitingForGPUToStayWithinLatencyTimePercent = value; }
            }

            property float WaitingForGpuExclusiveResourceTimePercent
            {
                float get() { return waitingForGPUExclusiveResourceTimePercent; }
                void set( float value ) { waitingForGPUExclusiveResourceTimePercent = value; }
            }

            property float WaitingForGpuOtherTimePercent
            {
                float get() { return waitingForGPUOtherTimePercent; }
                void set( float value ) { waitingForGPUOtherTimePercent = value; }
            }
		};

		public value class PipelineTimings
		{
		private:
			float vertexProcessingTimePercent;
            float pixelProcessingTimePercent;
            float otherGPUProcessingTimePercent;
            float gPUIdleTimePercent;

		public:
			property float VertexProcessingTimePercent
            {
                float get() { return vertexProcessingTimePercent; }
                void set( float value ) { vertexProcessingTimePercent = value; }
            }

            property float PixelProcessingTimePercent
            {
                float get() { return pixelProcessingTimePercent; }
                void set( float value ) { pixelProcessingTimePercent = value; }
            }

            property float OtherGpuProcessingTimePercent
            {
                float get() { return otherGPUProcessingTimePercent; }
                void set( float value ) { otherGPUProcessingTimePercent = value; }
            }

            property float GpuIdleTimePercent
            {
                float get() { return gPUIdleTimePercent; }
                void set( float value ) { gPUIdleTimePercent = value; }
            }
		};

		public value class ResourceStats
		{
		private:
            bool thrashing;
            int approxBytesDownloaded;
            int numberEvicted;
            int numberVidCreated;
            int lastPriority;
            int numberUsed;
            int numberUsedInVidMem;
            int workingSet;
            int workingSetBytes;
            int totalManaged;
            int totalBytes;

		public:
			property bool Thrashing
            {
                bool get() { return thrashing; }
                void set( bool value ) { thrashing = value; }
            }

            property int ApproxBytesDownloaded
            {
                int get() { return approxBytesDownloaded; }
                void set( int value ) { approxBytesDownloaded = value; }
            }

            property int NumberEvicted
            {
                int get() { return numberEvicted; }
                void set( int value ) { numberEvicted = value; }
            }

            property int NumberVidCreated
            {
                int get() { return numberVidCreated; }
                void set( int value ) { numberVidCreated = value; }
            }

            property int LastPriority
            {
                int get() { return lastPriority; }
                void set( int value ) { lastPriority = value; }
            }

            property int NumberUsed
            {
                int get() { return numberUsed; }
                void set( int value ) { numberUsed = value; }
            }

            property int NumberUsedInVidMem
            {
                int get() { return numberUsedInVidMem; }
                void set( int value ) { numberUsedInVidMem = value; }
            }

            property int WorkingSet
            {
                int get() { return workingSet; }
                void set( int value ) { workingSet = value; }
            }

            property int WorkingSetBytes
            {
                int get() { return workingSetBytes; }
                void set( int value ) { workingSetBytes = value; }
            }

            property int TotalManaged
            {
                int get() { return totalManaged; }
                void set( int value ) { totalManaged = value; }
            }

            property int TotalBytes
            {
                int get() { return totalBytes; }
                void set( int value ) { totalBytes = value; }
            }
		};

		public value class ResourceManager
		{
		private:
			ResourceStats stats;
            ResourceStats surfaceStats;
            ResourceStats volumeStats;
            ResourceStats textureStats;
            ResourceStats volumeTextureStats;
            ResourceStats cubeTextureStats;
            ResourceStats vertexBufferStats;
            ResourceStats indexBufferStats;

		public:
			property ResourceStats Stats
            {
                ResourceStats get() { return stats; }
                void set( ResourceStats value ) { stats = value; }
            }

            property ResourceStats SurfaceStats
            {
                ResourceStats get() { return surfaceStats; }
                void set( ResourceStats value ) { surfaceStats = value; }
            }

            property ResourceStats VolumeStats
            {
                ResourceStats get() { return volumeStats; }
                void set( ResourceStats value ) { volumeStats = value; }
            }

            property ResourceStats TextureStats
            {
                ResourceStats get() { return textureStats; }
                void set( ResourceStats value ) { textureStats = value; }
            }

            property ResourceStats VolumeTextureStats
            {
                ResourceStats get() { return volumeTextureStats; }
                void set( ResourceStats value ) { volumeTextureStats = value; }
            }

            property ResourceStats CubeTextureStats
            {
                ResourceStats get() { return cubeTextureStats; }
                void set( ResourceStats value ) { cubeTextureStats = value; }
            }

            property ResourceStats VertexBufferStats
            {
                ResourceStats get() { return vertexBufferStats; }
                void set( ResourceStats value ) { vertexBufferStats = value; }
            }

            property ResourceStats IndexBufferStats
            {
                ResourceStats get() { return indexBufferStats; }
                void set( ResourceStats value ) { indexBufferStats = value; }
            }
		};

		public value class VCache
		{
		private:
			int pattern;
            int optMethod;
            int cacheSize;
            int magicNumber;

		public:
			property int Pattern
            {
                int get() { return pattern; }
                void set( int value ) { pattern = value; }
            }

            property int OptMethod
            {
                int get() { return optMethod; }
                void set( int value ) { optMethod = value; }
            }

            property int CacheSize
            {
                int get() { return cacheSize; }
                void set( int value ) { cacheSize = value; }
            }

            property int MagicNumber
            {
                int get() { return magicNumber; }
                void set( int value ) { magicNumber = value; }
            }
		};

		public value class VertexStats
		{
		private:
			int numRenderedTriangles;
            int numExtraClippingTriangles;

		public:
			property int RenderedTriangleCount
            {
                int get() { return numRenderedTriangles; }
                void set( int value ) { numRenderedTriangles = value; }
            }

            property int ExtraClippingTriangleCount
            {
                int get() { return numExtraClippingTriangles; }
                void set( int value ) { numExtraClippingTriangles = value; }
            }
		};

		public value class StageTimings
		{
		private:
			float memoryProcessingPercent;
            float computationProcessingPercent;

		public:
			property float MemoryProcessingPercent
            {
                float get() { return memoryProcessingPercent; }
                void set( float value ) { memoryProcessingPercent = value; }
            }

            property float ComputationProcessingPercent
            {
                float get() { return computationProcessingPercent; }
                void set( float value ) { computationProcessingPercent = value; }
            }
		};

		public ref class Query : public DirectXObject<IDirect3DQuery9>
		{
		internal:
			/* Unused for now.
			Query( IDirect3DQuery9* query );
			*/

		public:
			Query( IntPtr query );
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
