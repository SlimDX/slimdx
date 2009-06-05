/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Enums11.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class Asynchronous;
		ref class Device;
		ref class CommandList;
		ref class Resource;
		ref class DepthStencilView;
		ref class RenderTargetView;
		ref class ShaderResourceView;
		ref class UnorderedAccessView;
		ref class Buffer;
		ref class Predicate;
		value class ResourceRegion;

		ref class GeometryShaderWrapper;
		ref class InputAssemblerWrapper;
		ref class OutputMergerWrapper;
		ref class RasterizerWrapper;
		ref class PixelShaderWrapper;
		ref class StreamOutputWrapper;
		ref class VertexShaderWrapper;

		public ref class DeviceContext : ComObject
		{
			COMOBJECT_CUSTOM(ID3D11DeviceContext, DeviceContext);

		private:
			InputAssemblerWrapper^ inputAssembler;
			OutputMergerWrapper^ outputMerger;
			StreamOutputWrapper^ streamOutput;
			RasterizerWrapper^ rasterizer;
			VertexShaderWrapper^ vertexShader;
			PixelShaderWrapper^ pixelShader;
			GeometryShaderWrapper^ geometryShader;

			void InitializeSubclasses();

		public:
			DeviceContext( Device^ device );

			void Begin( Asynchronous^ data );

			/// <summary>
			/// Clears the specified depth-stencil resource.
			/// </summary>
			/// <param name="view">The view of the resource to clear.</param>
			/// <param name="flags">Flags indicating which parts of the resource to clear.</param>
			/// <param name="depth">The depth value to clear to, if applicable.</param>
			/// <param name="stencil">The stencil value to clear to, if applicable.</param>
			void ClearDepthStencilView( DepthStencilView^ view, DepthStencilClearFlags flags, float depth, System::Byte stencil );
			
			/// <summary>
			/// Clears the specified render target resource.
			/// </summary>
			/// <param name="view">The view of the resource to clear.</param>
			/// <param name="color">The color to clear to.</param>
			void ClearRenderTargetView( RenderTargetView^ view, Color4 color );

			/// <summary>
			/// Restores all device state to defaults.
			/// </summary>
			void ClearState();

			void ClearUnorderedAccessView( UnorderedAccessView^ unorderedAccessView, array<int>^ values );
			void ClearUnorderedAccessView( UnorderedAccessView^ unorderedAccessView, array<float>^ values );
			
			/// <summary>
			/// Copies resource data using the GPU.
			/// </summary>
			/// <param name="source">The source resource.</param>
			/// <param name="destination">The destination resource.</param>
			void CopyResource( Resource^ source, Resource^ destination );

			/// <summary>
			/// Copies a portion of a resource's data using the GPU.
			/// </summary>
			/// <param name="source">The source resource.</param>
			/// <param name="sourceSubresource">The source subresource.</param>
			/// <param name="region">The source region.</param>
			/// <param name="destination">The destination resource.</param>
			/// <param name="destinationSubresource">The destination subresource.</param>
			/// <param name="x">The X offset between the source region origin and the destination location.</param>
			/// <param name="y">The Y offset between the source region origin and the destination location.</param>
			/// <param name="z">The Z offset between the source region origin and the destination location.</param>
			void CopySubresourceRegion( Resource^ source, int sourceSubresource, ResourceRegion region, Resource^ destination, int destinationSubresource, int x, int y, int z );
			
			/// <summary>
			/// Copies a multisampled resource into a non-multisampled resource.
			/// </summary>
			/// <param name="source">The source resource.</param>
			/// <param name="sourceSubresource">The source subresource.</param>
			/// <param name="destination">The destination resource.</param>
			/// <param name="destinationSubresource">The destination subresource.</param>
			/// <param name="format">The format that indicates how the multisampled resource will be resolved.</param>
			void ResolveSubresource( Resource^ source, int sourceSubresource, Resource^ destination, int destinationSubresource, DXGI::Format format );
			
			/// <summary>
			/// Copies data from the CPU to to a non-mappable subresource region.
			/// </summary>
			/// <param name="source">The source data.</param>
			/// <param name="resource">The destination resource.</param>
			/// <param name="subresource">The destination subresource.</param>
			void UpdateSubresource( DataBox^ source, Resource^ resource, int subresource );

			/// <summary>
			/// Copies data from the CPU to to a non-mappable subresource region.
			/// </summary>
			/// <param name="source">The source data.</param>
			/// <param name="resource">The destination resource.</param>
			/// <param name="subresource">The destination subresource.</param>
			/// <param name="region">The destination region within the resource.</param>
			void UpdateSubresource( DataBox^ source, Resource^ resource, int subresource, ResourceRegion region );

			void Dispatch( int threadGroupCountX, int threadGroupCountY, int threadGroupCountZ );
			void DispatchIndirect( Buffer^ arguments, int alignedOffset );

			/// <summary>
			/// Renders non-indexed, non-instanced primitive data.
			/// </summary>
			/// <param name="vertexCount">The number of vertices to use.</param>
			/// <param name="startVertexLocation">The index of the first vertex.</param>
			void Draw( int vertexCount, int startVertexLocation );

			/// <summary>
			/// Renders non-indexed, instanced primitive data.
			/// </summary>
			/// <param name="vertexCountPerInstance">The number of vertices to use per index.</param>
			/// <param name="instanceCount">The number of instances to render.</param>
			/// <param name="startVertexLocation">The index of the first vertex.</param>
			/// <param name="startInstanceLocation">The index of the first instance.</param>
			void DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation );

			void DrawInstancedIndirect( Buffer^ arguments, int alignedOffset );
			
			/// <summary>
			/// Renders indexed, non-instanced primitive data.
			/// </summary>
			/// <param name="indexCount">The number of indices to use.</param>
			/// <param name="startIndexLocation">The index of the first index.</param>
			/// <param name="baseVertexLocation">The index of the first vertex.</param>
			void DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation );

			/// <summary>
			/// Renders indexed, instanced primitive data.
			/// </summary>
			/// <param name="indexCountPerInstance">The number of indices to use per index.</param>
			/// <param name="instanceCount">The number of instances to render.</param>
			/// <param name="startIndexLocation">The index of the first index.</param>
			/// <param name="baseVertexLocation">The index of the first vertex.</param>
			/// <param name="startInstanceLocation">The index of the first instance.</param>
			void DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation );
			
			void DrawIndexedInstancedIndirect( Buffer^ arguments, int alignedOffset );

			/// <summary>
			/// Renders primitive data of an unknown size that was created by a geometry shader.
			/// </summary>
			void DrawAuto();

			void End( Asynchronous^ data );

			void ExecuteCommandList( CommandList^ commands, bool restoreState );
			CommandList^ FinishCommandList( bool restoreState );

			/// <summary>
			/// Sends queued commands in the command buffer to the GPU.
			/// </summary>
			void Flush();
			
			/// <summary>
			/// Generates mipmaps for the specified shader resource.
			/// </summary>
			/// <param name="view">A view of the resource to generate mipmaps for.</param>
			void GenerateMips( ShaderResourceView^ view );

			float GetMinimumLod( Resource^ resource );
			void SetMinimumLod( Resource^ resource, float minimumLod );

			DataStream^ GetData( Asynchronous^ data );
			DataStream^ GetData( Asynchronous^ data, AsynchronousFlags flags );

			void GetPredication( [Out] Predicate^ %predicate, [Out] bool %predicateValue );

			DataBox^ MapSubresource( Resource^ resource, int subresource, MapMode mode, MapFlags flags );
			void UnmapSubresource( Resource^ resource, int subresource );
			
			/// <summary>
			/// Sets a rendering predicate.
			/// </summary>
			/// <param name="predicate">The predicate to set.</param>
			/// <param name="predicateValue">If true, rendering will be affected when the predicate's conditions are met. Otherwise,
			/// rendering will be affected when the predicate's conditions are not met.</param>
			void SetPredication( Predicate^ predicate, bool predicateValue );

			property DeviceContextType Type
			{
				DeviceContextType get();
			}

			/// <summary>
			/// Gets the device's input assembler interface.
			/// </summary>
			property InputAssemblerWrapper^ InputAssembler
			{
				InputAssemblerWrapper^ get();
			}

			/// <summary>
			/// Gets the device's output merger interface.
			/// </summary>
			property OutputMergerWrapper^ OutputMerger
			{
				OutputMergerWrapper^ get();
			}

			/// <summary>
			/// Gets the device's stream output interface.
			/// </summary>
			property StreamOutputWrapper^ StreamOutput
			{
				StreamOutputWrapper^ get();
			}

			/// <summary>
			/// Gets the device's rasterizer interface.
			/// </summary>
			property RasterizerWrapper^ Rasterizer
			{
				RasterizerWrapper^ get();
			}

			/// <summary>
			/// Gets the device's vertex shader interface.
			/// </summary>
			property VertexShaderWrapper^ VertexShader
			{
				VertexShaderWrapper^ get();
			}

			/// <summary>
			/// Gets the device's pixel shader interface.
			/// </summary>
			property PixelShaderWrapper^ PixelShader
			{
				PixelShaderWrapper^ get();
			}

			/// <summary>
			/// Gets the device's geometry shader interface.
			/// </summary>
			property GeometryShaderWrapper^ GeometryShader
			{
				GeometryShaderWrapper^ get();
			}
		};
	}
}