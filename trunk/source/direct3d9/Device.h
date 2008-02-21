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
#include "Vertex.h"

#include "../Direct3D/Viewport.h"
#include "../math/Math.h"

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class Material
		{
		public:
			property Color4 Diffuse;
			property Color4 Ambient;
			property Color4 Specular;
			property Color4 Emissive;
			property float Power;
		};

		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class TriPatchInfo
		{
		public:
			property int StartVertexOffset;
			property int VertexCount;
			property Basis Basis;
			property Degree Degree;
		};

		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class RectPatchInfo
		{
		public:
			property int StartVertexOffsetWidth;
			property int StartVertexOffsetHeight;
			property int Width;
			property int Height;
			property int Stride;
			property Basis Basis;
			property Degree Degree;
		};

		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class Light
		{
		public:
			property LightType Type;
			property Color4 Diffuse;
			property Color4 Specular;
			property Color4 Ambient;
			property Vector3 Position;
			property Vector3 Direction;
			property float Range;
			property float Falloff;
			property float Attenuation0;
			property float Attenuation1;
			property float Attenuation2;
			property float Theta;
			property float Phi;
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class PaletteEntry
		{
		public:
			property System::Byte Red;
			property System::Byte Green;
			property System::Byte Blue;
			property System::Byte Flags;
		};

		public ref class PresentParameters
		{
		public:
			PresentParameters();

			property int BackBufferWidth;
			property int BackBufferHeight;
			property Format BackBufferFormat;
			property int BackBufferCount;

			property MultisampleType Multisample;
			property int MultisampleQuality;

			property SwapEffect SwapEffect;
			property System::IntPtr DeviceWindowHandle;
			property bool Windowed;
			property bool EnableAutoDepthStencil;
			property Format AutoDepthStencilFormat;
			property PresentFlags PresentFlags;

			property int FullScreenRefreshRateInHertz;
			property PresentInterval PresentationInterval;
		};

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
			COMOBJECT(IDirect3DDevice9);

		internal:
			Device( IDirect3DDevice9* device );

		public:
			Device( System::IntPtr device );
			Device( int adapter, DeviceType deviceType, System::IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParameters );
			virtual ~Device() { Destruct(); }

			// --- Properties ---

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

			property SlimDX::Direct3D::Viewport Viewport
			{
				SlimDX::Direct3D::Viewport get();
				void set( SlimDX::Direct3D::Viewport value );
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

			// --- Methods ---

			bool IsQuerySupported( QueryType type );
			Result EvictManagedResources();

			int ValidateDevice();
			Result TestCooperativeLevel();
			CooperativeLevel CheckCooperativeLevel();
			Result Reset( PresentParameters^ presentParameters );

			Result Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil );
			Result BeginScene();
			Result EndScene();
			Result Present();
			Result Present( SlimDX::Direct3D9::Present flags );

			Surface^ GetBackBuffer( int swapChain, int backBuffer );
			Surface^ GetDepthStencilSurface();
			Surface^ GetRenderTarget( int index );
			SwapChain^ GetSwapChain( int swapChainIndex );
			IndexBuffer^ GetIndices();
			VertexShader^ GetVertexShader();
			PixelShader^ GetPixelShader();
			DisplayMode GetDisplayMode( int swapChain );
			Plane GetClipPlane( int index );

			generic<typename T> where T : value class
				T GetRenderState( RenderState state );
			int GetRenderState( RenderState state );

			Capabilities GetDeviceCaps();
			Result GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride );
			int GetStreamSourceFreq( int stream );

			Result GetFrontBufferData( int swapChain, Surface^ destinationSurface );
			Result GetRenderTargetData( Surface^ renderTarget, Surface^ destinationSurface );

			Result SetRenderState( RenderState state, int value );
			Result SetRenderState( RenderState state, bool value );
			Result SetRenderState( RenderState state, float value );
			generic<typename T> where T : System::Enum
				Result SetRenderState( RenderState state, T value );

			Result SetTextureStageState( int stage, TextureStage type, int value );
			Result SetTextureStageState( int stage, TextureStage type, TextureOperation textureOperation );
			Result SetTextureStageState( int stage, TextureStage type, TextureArgument textureArgument );
			Result SetTextureStageState( int stage, TextureStage type, TextureTransform textureTransform );
			Result SetTextureStageState( int stage, TextureStage type, float value );

			Result SetSamplerState( int sampler, SamplerState type, int value );
			Result SetSamplerState( int sampler, SamplerState type, float value );
			Result SetSamplerState( int sampler, SamplerState type, TextureAddress textureAddress );
			Result SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter );

			Result LightEnable( int lightIndex, bool enable );
			bool GetLightEnable( int lightIndex );
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
			Result SetStreamSourceFreq( int stream, int frequency );
			Result SetTexture( int sampler, BaseTexture^ texture );
			Result SetRenderTarget( int rtIndex, Surface^ target );
			Result SetPixelShader( PixelShader^ pixelShader );
			Result SetVertexShader( VertexShader^ vertexShader );			
			Result SetDepthStencilSurface( Surface^ target );
			Result SetDialogBoxMode( bool enableDialogs );
			Result SetIndices( IndexBuffer^ indices );
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

			Result ProcessVertices( int sourceStartIndex, int destinationIndex, int vertexCount, VertexBuffer^ destinationBuffer,
				SlimDX::Direct3D9::VertexDeclaration^ vertexDeclaration, LockFlags flags );

			Result DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			Result DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
				int vertexCount, int startIndex, int primCount );

			generic<typename T> where T : value class
			Result DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );

			generic<typename S, typename T> where S : value class where T : value class
			Result DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int vertexCount, int primitiveCount,
				array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride );

			Result DrawTriPatch( int handle, array<float>^ segmentCount, TriPatchInfo info );
			Result DrawTriPatch( int handle, array<float>^ segmentCount );
			Result DrawRectPatch( int handle, array<float>^ segmentCount, RectPatchInfo info );
			Result DrawRectPatch( int handle, array<float>^ segmentCount );
			Result DeletePatch( int handle );

			Result StretchRect( Surface^ source, System::Drawing::Rectangle sourceRect, Surface^ destination,
				System::Drawing::Rectangle destinationRectangle, TextureFilter filter );
			Result UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRect,
				Surface^ destination, System::Drawing::Point destinationPoint );
			Result UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destinationTexture );
			Result ColorFill( Surface^ destinationSurface, System::Drawing::Rectangle destinationRect, Color4 color );

			//ATI R2VB functionality, based on work by Oliver 'acid2' Charles
			Result SetR2VBMode( bool enableR2VB );
			Result BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVertexBuffer );
			Result RestoreVertexStream( int stream );
		};
	}
}
