#include "stdafx.h"

#include "Device10.h"
#include "Direct3D10Recorder.h"

#include "../Common/Utilities.h"
#include "RenderTargetView10.h"
#include "Buffer10.h"
#include "Inputlayout10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Device::Device( ID3D10Device* native )
		: ComObject( native )
		{
		}
		
		Device::Device( IntPtr native )
		: ComObject( native )
		{
		}
		
		IRenderTargetView^ Device::CreateRenderTargetView( IResource^ resource ) {
			if( resource == nullptr )
				throw gcnew ArgumentNullException( "resource" );
			
			//TODO: Hack.
			ID3D10Resource* nativeResource = reinterpret_cast<ID3D10Resource*>(Utilities::ToUnknown( resource ));
			ID3D10RenderTargetView* nativeView = 0;
			if( RecordResult( NativePointer->CreateRenderTargetView( nativeResource, NULL, &nativeView ) ).IsSuccess )
				return gcnew RenderTargetView( nativeView );
			return nullptr;
		}

		IBuffer^ Device::CreateEmptyBuffer(BufferDescription bufferDescription) {//TODO: Huh?
			return CreateBuffer<char>(bufferDescription, nullptr);
		}

		generic<typename T> where T : value class
		IBuffer^ Device::CreateBuffer(BufferDescription bufferDescription, array<T>^ bufferData) {
			D3D10_BUFFER_DESC desc = {
				bufferDescription.SizeInBytes,
				(D3D10_USAGE)bufferDescription.Usage,
				(UINT)bufferDescription.BindFlags,
				(UINT)bufferDescription.CpuAccessFlags,
				(UINT)bufferDescription.OptionFlags
			};

			ID3D10Buffer* buffer;

			if(bufferData != nullptr) {
				pin_ptr<T> bufferPtr = &bufferData[0];
				D3D10_SUBRESOURCE_DATA bufferDataRs = {  bufferPtr };

				if(RecordResult(NativePointer->CreateBuffer(&desc, &bufferDataRs, &buffer)).IsSuccess)
					return gcnew Buffer(buffer);
			} else {
				if(RecordResult(NativePointer->CreateBuffer(&desc, nullptr, &buffer)).IsSuccess)
					return gcnew Buffer(buffer);
			}
			return nullptr;
		}

		IInputLayout^ Device::CreateInputLayout(array<InputElement>^ elements, ShaderSignature signature) {
			using namespace System::Runtime::InteropServices;

			D3D10_INPUT_ELEMENT_DESC descriptions[16];
			for(int i = 0; i < elements->Length && i < 16; ++i) {
				descriptions[i].SemanticName = reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(elements[i].Name).ToPointer());
				descriptions[i].SemanticIndex = elements[i].Index;
				descriptions[i].Format = (DXGI_FORMAT)elements[i].Format;
				descriptions[i].InputSlot = elements[i].Slot;
				descriptions[i].AlignedByteOffset = elements[i].AlignedByteOffset;
				descriptions[i].InputSlotClass = (D3D10_INPUT_CLASSIFICATION)elements[i].InputClassification;
				descriptions[i].InstanceDataStepRate = elements[i].InstanceDataStep;
			}

			ID3D10InputLayout* layout;
			NativePointer->CreateInputLayout(descriptions, elements->Length, signature.Signature.ToPointer(), signature.SignatureLength, &layout);

			for(int i = 0; i < elements->Length && i < 16; ++i) {
				Marshal::FreeHGlobal(IntPtr(const_cast<LPSTR>(descriptions[i].SemanticName)));
			}

			return gcnew InputLayout(layout);
		}

		void Device::ClearRenderTargetView(IRenderTargetView^ renderTargetView, System::Drawing::Color clearColor) {
			float clearColorFloats[4] = {(float)clearColor.R / 255, (float)clearColor.G / 255, (float)clearColor.B / 255, (float)clearColor.A / 255 };
			ID3D10RenderTargetView* nativeView = reinterpret_cast<ID3D10RenderTargetView*>(Utilities::ToUnknown(renderTargetView));
			NativePointer->ClearRenderTargetView(nativeView, clearColorFloats);
		}

		void Device::IASetPrimitiveTopology(PrimitiveTopology primitiveTopology) {
			NativePointer->IASetPrimitiveTopology(static_cast<D3D10_PRIMITIVE_TOPOLOGY>(primitiveTopology));
		}

		void Device::IASetVertexBuffer(int startSlot, VertexBufferBinding vertexBufferBinding) {
			ID3D10Buffer* buffer = reinterpret_cast<ID3D10Buffer*>(Utilities::ToUnknown(vertexBufferBinding.VertexBuffer));
			NativePointer->IASetVertexBuffers(startSlot, 1, &buffer, reinterpret_cast<UINT*>(&vertexBufferBinding.Stride), reinterpret_cast<UINT*>(&vertexBufferBinding.Offset));
		}

		void Device::IASetVertexBuffers(int startSlot, array<VertexBufferBinding>^ vertexBufferBindings) {
			ID3D10Buffer* buffers[16];
			UINT strides[16];
			UINT offsets[16];
			
			for(int i = 0; i < vertexBufferBindings->Length; ++i) {
				buffers[i] = reinterpret_cast<ID3D10Buffer*>(Utilities::ToUnknown(vertexBufferBindings[i].VertexBuffer));
				strides[i] = vertexBufferBindings[i].Stride;
				offsets[i] = vertexBufferBindings[i].Offset;
			}

			NativePointer->IASetVertexBuffers(startSlot, vertexBufferBindings->Length, buffers, strides, offsets);
		}

		void Device::IASetInputLayout(IInputLayout^ inputLayout) {
			NativePointer->IASetInputLayout(static_cast<ID3D10InputLayout*>(Utilities::ToUnknown(inputLayout)));
		}

		void Device::RSSetViewport(Viewport viewport) {
			NativePointer->RSSetViewports(1, reinterpret_cast<D3D10_VIEWPORT*>(&viewport));
		}

		void Device::RSSetViewports(array<Viewport>^ viewports) {
			pin_ptr<Viewport> vps = &viewports[0];
			NativePointer->RSSetViewports(viewports->Length, reinterpret_cast<D3D10_VIEWPORT*>(vps));
		}

		void Device::OMSetRenderTargets(array<IRenderTargetView^>^ renderTargetViews, IDepthStencilView^ depthStencilView) {
			ID3D10RenderTargetView* renderTargetViewsArray[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
			for(int i = 0; i < renderTargetViews->Length; ++i) {
				renderTargetViewsArray[i] = reinterpret_cast<ID3D10RenderTargetView*>(Utilities::ToUnknown( renderTargetViews[i] ));
			}

			ID3D10DepthStencilView* depthStencilViewPtr = NULL;
			if(depthStencilView != nullptr)
				depthStencilViewPtr = (ID3D10DepthStencilView*)Utilities::ToUnknown( depthStencilView );

			NativePointer->OMSetRenderTargets(renderTargetViews->Length, renderTargetViewsArray, depthStencilViewPtr);
		}

		void Device::OMSetRenderTarget(IRenderTargetView^ renderTargetView, IDepthStencilView^ depthStencilView) {
			ID3D10RenderTargetView* renderTargetViewsArray[1] = { (ID3D10RenderTargetView*)Utilities::ToUnknown( renderTargetView ) };

			ID3D10DepthStencilView* depthStencilViewPtr = NULL;
			if(depthStencilView != nullptr)
				depthStencilViewPtr = reinterpret_cast<ID3D10DepthStencilView*>(Utilities::ToUnknown( depthStencilView ));

			NativePointer->OMSetRenderTargets(1, renderTargetViewsArray, depthStencilViewPtr);
		}

		void Device::Draw(int vertexCount, int startLocation) {
			NativePointer->Draw(vertexCount, startLocation);
		}
	}
}