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

#include "Enums.h"
#include "Direct3D.h"
#include "VertexDeclaration.h"

#include "../Viewport.h"

#include "../math/Plane.h"

#include "PaletteEntry.h"
#include "Light.h"
#include "PatchInfo.h"
#include "Material.h"
#include "PresentParameters.h"
#include "GammaRamp.h"
#include "ClipStatus.h"
#include "CreationParameters.h"

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
		ref class IndexBuffer;
		ref class VertexBuffer;
		ref class BaseTexture;
		ref class Texture;
		ref class Surface;
		ref class PixelShader;
		ref class VertexShader;
		ref class SwapChain;
		ref class StateBlock;

		public ref class Device : public ComObject
		{
			COMOBJECT(IDirect3DDevice9, Device);

		public:
			Device( int adapter, DeviceType deviceType, System::IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParameters );
			static Device^ FromPointer( System::IntPtr pointer );

			bool IsQuerySupported( QueryType type );
			Result EvictManagedResources();

			int ValidateDevice();
			Result TestCooperativeLevel();
			Result Reset( PresentParameters^ presentParameters );

			Result Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil, array<System::Drawing::Rectangle>^ rectangles );
			Result Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil );
			Result BeginScene();
			Result EndScene();
			Result Present();
			Result Present( SlimDX::Direct3D9::Present flags );

			Surface^ GetBackBuffer( int swapChain, int backBuffer );
			Surface^ GetRenderTarget( int index );
			SwapChain^ GetSwapChain( int swapChainIndex );
			DisplayMode GetDisplayMode( int swapChain );
			Plane GetClipPlane( int index );

			generic<typename T> where T : value class
				T GetRenderState( RenderState state );
			int GetRenderState( RenderState state );

			generic<typename T> where T : value class
				T GetSamplerState( int sampler, SamplerState type );
			int GetSamplerState( int sampler, SamplerState type );

			generic<typename T> where T : value class
				T GetTextureStageState( int stage, TextureStage type );
			int GetTextureStageState( int stage, TextureStage type );

			Result GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride );
			int GetStreamSourceFrequency( int stream );

			Result GetFrontBufferData( int swapChain, Surface^ destinationSurface );
			Result GetRenderTargetData( Surface^ renderTarget, Surface^ destinationSurface );

			Result SetRenderState( RenderState state, int value );
			Result SetRenderState( RenderState state, bool value );
			Result SetRenderState( RenderState state, float value );
			generic<typename T> where T : System::Enum
				Result SetRenderState( RenderState state, T value );

			array<PaletteEntry>^ GetPaletteEntries( int paletteNumber );
			Result SetPaletteEntries( int paletteNumber, array<PaletteEntry>^ entries );

			GammaRamp^ GetGammaRamp( int swapChain );
			void SetGammaRamp( int swapChain, GammaRamp^ ramp, bool calibrate );

			Result SetTextureStageState( int stage, TextureStage type, int value );
			Result SetTextureStageState( int stage, TextureStage type, TextureOperation textureOperation );
			Result SetTextureStageState( int stage, TextureStage type, TextureArgument textureArgument );
			Result SetTextureStageState( int stage, TextureStage type, TextureTransform textureTransform );
			Result SetTextureStageState( int stage, TextureStage type, float value );

			Result SetSamplerState( int sampler, SamplerState type, int value );
			Result SetSamplerState( int sampler, SamplerState type, float value );
			Result SetSamplerState( int sampler, SamplerState type, TextureAddress textureAddress );
			Result SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter );

			Result EnableLight( int lightIndex, bool enable );
			bool IsLightEnabled( int lightIndex );
			Result SetLight( int lightIndex, Light lightData );
			Light GetLight( int lightIndex );

			Result SetCursor( System::Windows::Forms::Cursor^ cursor, bool addWatermark );
			void SetCursorPosition( int x, int y, bool immediateUpdate );
			void SetCursorPosition( System::Drawing::Point position, bool immediateUpdate ) { SetCursorPosition( position.X, position.Y, immediateUpdate ); }
			Result SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap );
			Result SetCursorProperties( System::Drawing::Point position, Surface^ cursorBitmap ) { return SetCursorProperties( position.X, position.Y, cursorBitmap ); }

			Result SetTransform( TransformState state, Matrix value );
			Matrix GetTransform( TransformState state );

			Result SetTransform( int index, Matrix value );
			Matrix GetTransform( int index );
			
			Result MultiplyTransform( TransformState state, Matrix value );
			Result SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			Result SetStreamSourceFrequency( int stream, int frequency );
			Result SetTexture( int sampler, BaseTexture^ texture );
			Result SetRenderTarget( int targetIndex, Surface^ target );
			Result SetDialogBoxMode( bool enableDialogs );
			Result SetClipPlane( int index, Plane clipPlane );

			Result SetVertexShaderConstant( int startRegister, array<bool>^ data, int offset, int count );
			Result SetVertexShaderConstant( int startRegister, array<float>^ data, int offset, int count );
			Result SetVertexShaderConstant( int startRegister, array<int>^ data, int offset, int count );
			Result SetVertexShaderConstant( int startRegister, array<bool>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			Result SetVertexShaderConstant( int startRegister, array<float>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			Result SetVertexShaderConstant( int startRegister, array<int>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }

			Result SetPixelShaderConstant( int startRegister, array<bool>^ data, int offset, int count );
			Result SetPixelShaderConstant( int startRegister, array<float>^ data, int offset, int count );
			Result SetPixelShaderConstant( int startRegister, array<int>^ data, int offset, int count );
			Result SetPixelShaderConstant( int startRegister, array<bool>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			Result SetPixelShaderConstant( int startRegister, array<float>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			Result SetPixelShaderConstant( int startRegister, array<int>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }

			Result BeginStateBlock();
			StateBlock^ EndStateBlock();

			Result ProcessVertices( int sourceStartIndex, int destinationIndex, int vertexCount, VertexBuffer^ destinationBuffer, SlimDX::Direct3D9::VertexDeclaration^ vertexDeclaration, LockFlags flags );

			Result DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			Result DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, int vertexCount, int startIndex, int primCount );

			generic<typename T> where T : value class
			Result DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );

			generic<typename S, typename T> where S : value class where T : value class
			Result DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minimumVertexIndex, int vertexCount, int primitiveCount, array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride );

			Result DrawTrianglePatch( int handle, array<float>^ segmentCount, TrianglePatchInfo info );
			Result DrawTrianglePatch( int handle, array<float>^ segmentCount );
			Result DrawRectanglePatch( int handle, array<float>^ segmentCount, RectanglePatchInfo info );
			Result DrawRectanglePatch( int handle, array<float>^ segmentCount );
			Result DeletePatch( int handle );

			Result StretchRectangle( Surface^ source, System::Drawing::Rectangle sourceRectangle, Surface^ destination, System::Drawing::Rectangle destinationRectangle, TextureFilter filter );
			Result StretchRectangle( Surface^ source, Surface^ destination, TextureFilter filter );

			Result UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRectangle, Surface^ destination, System::Drawing::Point destinationPoint );
			Result UpdateSurface( Surface^ source, Surface^ destination );

			Result UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destinationTexture );
			
			Result ColorFill( Surface^ destinationSurface, System::Drawing::Rectangle destinationRectangle, Color4 color );
			Result ColorFill( Surface^ destinationSurface, Color4 color );

			Result SetR2VBMode( bool enableR2VB );
			Result BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVertexBuffer );
			Result RestoreVertexStream( int stream );

			property Capabilities^ Capabilities
			{
				SlimDX::Direct3D9::Capabilities^ get();
			}

			property CreationParameters CreationParameters
			{
				SlimDX::Direct3D9::CreationParameters get();
			}

			property ClipStatus ClipStatus
			{
				SlimDX::Direct3D9::ClipStatus get();
				void set( SlimDX::Direct3D9::ClipStatus value );
			}

			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get();
				void set( SlimDX::Direct3D9::VertexFormat value );
			}

			property SlimDX::Direct3D9::VertexDeclaration^ VertexDeclaration
			{
				SlimDX::Direct3D9::VertexDeclaration^ get();
				void set( SlimDX::Direct3D9::VertexDeclaration^ value );
			}

			property bool SoftwareVertexProcessing
			{
				bool get();
				void set( bool value );
			}

			property Material Material
			{
				SlimDX::Direct3D9::Material get();
				void set( SlimDX::Direct3D9::Material value );
			}

			property SlimDX::Viewport Viewport
			{
				SlimDX::Viewport get();
				void set( SlimDX::Viewport value );
			}

			property System::Drawing::Rectangle ScissorRect
			{
				System::Drawing::Rectangle get();
				void set( System::Drawing::Rectangle value );
			}

			property int AvailableTextureMemory
			{
				int get();
			}

			property bool ShowCursor
			{
				bool get();
				void set( bool show );
			}

			property int SwapChainCount
			{
				int get();
			}

			property float NPatchMode
			{
				float get();
				void set( float value );
			}

			property int CurrentTexturePalette
			{
				int get();
				void set( int value );
			}

			property DriverLevel DriverLevel
			{
				SlimDX::Direct3D9::DriverLevel get();
			}

			property System::String^ VertexShaderProfile
			{
				System::String^ get();
			}

			property System::String^ PixelShaderProfile
			{
				System::String^ get();
			}

			property Surface^ DepthStencilSurface
			{
				Surface^ get();
				void set( Surface^ value );
			}

			property IndexBuffer^ Indices
			{
				IndexBuffer^ get();
				void set( IndexBuffer^ value );
			}

			property VertexShader^ VertexShader
			{
				SlimDX::Direct3D9::VertexShader^ get();
				void set( SlimDX::Direct3D9::VertexShader^ value );
			}

			property PixelShader^ PixelShader
			{
				SlimDX::Direct3D9::PixelShader^ get();
				void set( SlimDX::Direct3D9::PixelShader^ value );
			}
		};
	}
}
