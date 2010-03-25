#include "stdafx.h"

#include "Device10.h"
#include "Direct3D10Recorder.h"

#include "../Common/Utilities.h"
#include "RenderTargetView10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Device10::Device10( ID3D10Device* native )
		: ComObject( native )
		{
		}
		
		Device10::Device10( IntPtr native )
		: ComObject( native )
		{
		}
		
		IRenderTargetView10^ Device10::CreateRenderTargetView( IResource10^ resource ) {
			if( resource == nullptr )
				throw gcnew ArgumentNullException( "resource" );
			
			//TODO: Hack.
			ID3D10Resource* nativeResource = (ID3D10Resource*)Utilities::ToUnknown( resource );
			ID3D10RenderTargetView* nativeView = 0;
			if( RecordResult( NativePointer->CreateRenderTargetView( nativeResource, NULL, &nativeView ) ).IsSuccess )
				return gcnew RenderTargetView10( nativeView );
			return nullptr;
		}
	}
}