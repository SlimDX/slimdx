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

#include "Enums.h"
#include "Direct3D.h"
#include "Vertex.h"
#include "../Direct3D/ColorValue.h"
#include "../Direct3D/Viewport.h"
#include "../math/Math.h"

using namespace SlimDX::Direct3D;

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
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
			property int NumVertices;
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

		public ref class PresentParameters
		{
		public:
			PresentParameters();

			property int BackBufferWidth;
			property int BackBufferHeight;
			property Format BackBufferFormat;
			property int BackBufferCount;

			property MultiSampleType MultiSample;
			property int MultiSampleQuality;

			property SwapEffect SwapEffect;
			property IntPtr DeviceWindowHandle;
			property bool Windowed;
			property bool EnableAutoDepthStencil;
			property Format AutoDepthStencilFormat;
			property PresentFlags PresentFlags;

			property int FullScreenRefreshRateInHz;
			property PresentInterval PresentationInterval;
		};

		ref class IndexBuffer;
		ref class VertexBuffer;
		ref class BaseTexture;
		ref class Surface;
		ref class PixelShader;
		ref class VertexShader;
		ref class SwapChain;
		ref class StateBlock;

		public ref class Device : public DirectXObject<IDirect3DDevice9>
		{
		private:
			IndexBuffer^ m_Indices;
			VertexFormat m_VertexFormat;
			VertexDeclaration^ m_VertexDecl;

		public:
			Device( IDirect3DDevice9* device );
			Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams );
			virtual ~Device() { Destruct(); }

			// --- Properties ---

			property IndexBuffer^ Indices
			{
				IndexBuffer^ get() { return m_Indices; }
				void set( IndexBuffer^ value );
			}

			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get() { return m_VertexFormat; }
				void set( SlimDX::Direct3D9::VertexFormat value );
			}

			property SlimDX::Direct3D9::VertexDeclaration^ VertexDeclaration
			{
				SlimDX::Direct3D9::VertexDeclaration^ get() { return m_VertexDecl; }
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

			property int AvailableTextureMem
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

			// --- Methods ---

			bool IsQuerySupported( QueryType type );
			void EvictManagedResources();
			DriverLevel GetDriverLevel();
			String^ GetVertexShaderProfile();
			String^ GetPixelShaderProfile();

			int ValidateDevice();
			void TestCooperativeLevel();
			CooperativeLevel CheckCooperativeLevel();
			void Reset( PresentParameters^ presentParams );

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

			generic<typename T> where T : value class
				T GetRenderState( RenderState state );
			int GetRenderState( RenderState state );

			Capabilities GetDeviceCaps();
			bool GetSoftwareVertexProcessing();
			void GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride );
			int GetStreamSourceFreq( int stream );

			void SetRenderState( RenderState state, int value );
			void SetRenderState( RenderState state, bool value );
			void SetRenderState( RenderState state, float value );
			generic<typename T> where T : Enum
				void SetRenderState( RenderState state, T value );

			void SetTextureStageState( int stage, TextureStage type, int value );
			void SetTextureStageState( int stage, TextureStage type, TextureOperation texOp );
			void SetTextureStageState( int stage, TextureStage type, TextureArgument texArg );
			void SetTextureStageState( int stage, TextureStage type, TextureTransform texTransform );
			void SetTextureStageState( int stage, TextureStage type, float value );

			void SetSamplerState( int sampler, SamplerState type, int value );
			void SetSamplerState( int sampler, SamplerState type, TextureAddress texAddr );
			void SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter );

			void LightEnable( int lightIndex, bool enable );
			bool GetLightEnable( int lightIndex );
			void SetLight( int lightIndex, Light lightData );
			Light GetLight( int lightIndex );

			void SetCursorPosition( int x, int y, bool immediateUpdate );
			void SetCursorPosition( System::Drawing::Point position, bool immediateUpdate ) { SetCursorPosition( position.X, position.Y, immediateUpdate ); }
			void SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap );
			void SetCursorProperties( System::Drawing::Point position, Surface^ cursorBitmap ) { SetCursorProperties( position.X, position.Y, cursorBitmap ); }

			void SetTransform( TransformState state, Matrix value );
			void MultiplyTransform( TransformState state, Matrix value );
			void SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			void SetStreamSourceFreq( int stream, int frequency );
			void SetTexture( int sampler, BaseTexture^ texture );
			void SetRenderTarget( int rtIndex, Surface^ target );
			void SetPixelShader( PixelShader^ pixelShader );
			void SetVertexShader( VertexShader^ vertexShader );			
			void SetDepthStencilSurface( Surface^ target );
			void SetDialogBoxMode( bool enableDialogs );

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

			void ProcessVertices( int sourceStartIndex, int destIndex, int vertexCount, VertexBuffer^ destBuffer,
				SlimDX::Direct3D9::VertexDeclaration^ vertexDecl, LockFlags flags );

			void DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			void DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
				int numVertices, int startIndex, int primCount );

			generic<typename T> where T : value class
			void DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );

			generic<typename S, typename T> where S : value class where T : value class
			void DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int numVertices, int primitiveCount,
				array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride );

			void DrawTriPatch( int handle, array<float>^ numSegments, TriPatchInfo info );
			void DrawTriPatch( int handle, array<float>^ numSegments );
			void DrawRectPatch( int handle, array<float>^ numSegments, RectPatchInfo info );
			void DrawRectPatch( int handle, array<float>^ numSegments );
			void DeletePatch( int handle );

			void StretchRect( Surface^ source, System::Drawing::Rectangle sourceRect, Surface^ dest,
				System::Drawing::Rectangle destRect, TextureFilter filter );
			void UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRect,
				Surface^ dest, System::Drawing::Point destPoint );
			void UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destTexture );
			void ColorFill( Surface^ destSurface, System::Drawing::Rectangle destRect, int color );
			void ColorFill( Surface^ destSurface, System::Drawing::Rectangle destRect, System::Drawing::Color color );
		};
	}
}
