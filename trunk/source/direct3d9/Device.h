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

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

#include "Enums.h"
#include "Direct3D.h"
#include "Vertex.h"
#include "ErrorCode.h"
#include "../Direct3D/Viewport.h"
#include "../math/Math.h"

using namespace SlimDX::Direct3D;

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
		[StructLayout( LayoutKind::Sequential )]
		public value class Material
		{
		public:
			property ColorValue Diffuse;
			property ColorValue Ambient;
			property ColorValue Specular;
			property ColorValue Emissive;
			property float Power;
		};

		[StructLayout( LayoutKind::Sequential )]
		public value class TriPatchInfo
		{
		public:
			property int StartVertexOffset;
			property int VertexCount;
			property Basis Basis;
			property Degree Degree;
		};

		[StructLayout( LayoutKind::Sequential )]
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

		[StructLayout( LayoutKind::Sequential )]
		public value class Light
		{
		public:
			property LightType Type;
			property ColorValue Diffuse;
			property ColorValue Specular;
			property ColorValue Ambient;
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

		[StructLayout(LayoutKind::Sequential)]
		public value class PaletteEntry
		{
		public:
			property Byte Red;
			property Byte Green;
			property Byte Blue;
			property Byte Flags;
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
			property IntPtr DeviceWindowHandle;
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
			Device( IntPtr device );
			Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParameters );
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

			property Viewport Viewport
			{
				SlimDX::Direct3D::Viewport get();
				void set( SlimDX::Direct3D::Viewport value );
			}

			property Drawing::Rectangle ScissorRect
			{
				Drawing::Rectangle get();
				void set( Drawing::Rectangle value );
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

			property String^ VertexShaderProfile
			{
				String^ get();
			}

			property String^ PixelShaderProfile
			{
				String^ get();
			}

			// --- Methods ---

			bool IsQuerySupported( QueryType type );
			void EvictManagedResources();

			int ValidateDevice();
			void TestCooperativeLevel();
			CooperativeLevel CheckCooperativeLevel();
			void Reset( PresentParameters^ presentParameters );

			void Clear( ClearFlags clearFlags, int color, float zdepth, int stencil );
			void Clear( ClearFlags clearFlags, Color color, float zdepth, int stencil );
			void BeginScene();
			void EndScene();
			void Present();
			void Present( SlimDX::Direct3D9::Present flags );

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
			void GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride );
			int GetStreamSourceFreq( int stream );

			void GetFrontBufferData( int swapChain, Surface^ destinationSurface );
			void GetRenderTargetData( Surface^ renderTarget, Surface^ destinationSurface );

			void SetRenderState( RenderState state, int value );
			void SetRenderState( RenderState state, bool value );
			void SetRenderState( RenderState state, float value );
			generic<typename T> where T : Enum
				void SetRenderState( RenderState state, T value );

			void SetTextureStageState( int stage, TextureStage type, int value );
			void SetTextureStageState( int stage, TextureStage type, TextureOperation textureOperation );
			void SetTextureStageState( int stage, TextureStage type, TextureArgument textureArgument );
			void SetTextureStageState( int stage, TextureStage type, TextureTransform textureTransform );
			void SetTextureStageState( int stage, TextureStage type, float value );

			void SetSamplerState( int sampler, SamplerState type, int value );
			void SetSamplerState( int sampler, SamplerState type, float value );
			void SetSamplerState( int sampler, SamplerState type, TextureAddress textureAddress );
			void SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter );

			void LightEnable( int lightIndex, bool enable );
			bool GetLightEnable( int lightIndex );
			void SetLight( int lightIndex, Light lightData );
			Light GetLight( int lightIndex );

			void SetCursor( Cursor^ cursor, bool addWatermark );
			void SetCursorPosition( int x, int y, bool immediateUpdate );
			void SetCursorPosition( System::Drawing::Point position, bool immediateUpdate ) { SetCursorPosition( position.X, position.Y, immediateUpdate ); }
			void SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap );
			void SetCursorProperties( System::Drawing::Point position, Surface^ cursorBitmap ) { SetCursorProperties( position.X, position.Y, cursorBitmap ); }

			void SetTransform( TransformState state, Matrix value );
			Matrix GetTransform( TransformState state );

			void SetTransform( int index, Matrix value );
			Matrix GetTransform( int index );
			
			void MultiplyTransform( TransformState state, Matrix value );
			void SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			void SetStreamSourceFreq( int stream, int frequency );
			void SetTexture( int sampler, BaseTexture^ texture );
			void SetRenderTarget( int rtIndex, Surface^ target );
			void SetPixelShader( PixelShader^ pixelShader );
			void SetVertexShader( VertexShader^ vertexShader );			
			void SetDepthStencilSurface( Surface^ target );
			void SetDialogBoxMode( bool enableDialogs );
			void SetIndices( IndexBuffer^ indices );
			void SetClipPlane( int index, Plane clipPlane );

			void SetVertexShaderConstant( int startRegister, array<bool>^ data, int offset, int count );
			void SetVertexShaderConstant( int startRegister, array<float>^ data, int offset, int count );
			void SetVertexShaderConstant( int startRegister, array<int>^ data, int offset, int count );
			void SetVertexShaderConstant( int startRegister, array<bool>^ data ) { SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			void SetVertexShaderConstant( int startRegister, array<float>^ data ) { SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			void SetVertexShaderConstant( int startRegister, array<int>^ data ) { SetVertexShaderConstant( startRegister, data, 0, 0 ); }

			void SetPixelShaderConstant( int startRegister, array<bool>^ data, int offset, int count );
			void SetPixelShaderConstant( int startRegister, array<float>^ data, int offset, int count );
			void SetPixelShaderConstant( int startRegister, array<int>^ data, int offset, int count );
			void SetPixelShaderConstant( int startRegister, array<bool>^ data ) { SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			void SetPixelShaderConstant( int startRegister, array<float>^ data ) { SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			void SetPixelShaderConstant( int startRegister, array<int>^ data ) { SetPixelShaderConstant( startRegister, data, 0, 0 ); }

			void BeginStateBlock();
			StateBlock^ EndStateBlock();

			void ProcessVertices( int sourceStartIndex, int destinationIndex, int vertexCount, VertexBuffer^ destinationBuffer,
				SlimDX::Direct3D9::VertexDeclaration^ vertexDeclaration, LockFlags flags );

			void DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			void DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
				int vertexCount, int startIndex, int primCount );

			generic<typename T> where T : value class
			void DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );

			generic<typename S, typename T> where S : value class where T : value class
			void DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int vertexCount, int primitiveCount,
				array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride );

			void DrawTriPatch( int handle, array<float>^ segmentCount, TriPatchInfo info );
			void DrawTriPatch( int handle, array<float>^ segmentCount );
			void DrawRectPatch( int handle, array<float>^ segmentCount, RectPatchInfo info );
			void DrawRectPatch( int handle, array<float>^ segmentCount );
			void DeletePatch( int handle );

			void StretchRect( Surface^ source, System::Drawing::Rectangle sourceRect, Surface^ destination,
				System::Drawing::Rectangle destinationRectangle, TextureFilter filter );
			void UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRect,
				Surface^ destination, System::Drawing::Point destinationPoint );
			void UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destinationTexture );
			void ColorFill( Surface^ destinationSurface, System::Drawing::Rectangle destinationRect, int color );
			void ColorFill( Surface^ destinationSurface, System::Drawing::Rectangle destinationRect, System::Drawing::Color color );

			//ATI R2VB functionality, based on work by Oliver 'acid2' Charles
			void SetR2VBMode( bool enableR2VB );
			void BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVertexBuffer );
			void RestoreVertexStream( int stream );
		};
	}
}
