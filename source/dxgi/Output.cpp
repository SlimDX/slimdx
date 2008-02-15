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

#include <dxgi.h>

#include <vector>

#include "DXGIException.h"

#include "FrameStatistics.h"
#include "GammaControlCapabilities.h"
#include "ModeDescription.h"
#include "Output.h"
#include "OutputDescription.h"
#include "Surface.h"

namespace SlimDX
{
namespace DXGI
{ 	
	Output::Output( IDXGIOutput* pointer )
	{
		Construct( pointer );
	}
	
	Result Output::GetDescription( [Out] OutputDescription% description )
	{
		DXGI_OUTPUT_DESC nativeDescription;
		Result::Record( InternalPointer->GetDesc( &nativeDescription ) );
		if( Result::Last.IsSuccess )
			description = OutputDescription( nativeDescription );
		return Result::Last;
	}
	
	ReadOnlyCollection<ModeDescription>^ Output::GetDisplayModeList( Format format, DisplayModeEnumerationFlags flags )
	{
		UINT modeCount = 0;
		Result::Record( InternalPointer->GetDisplayModeList( static_cast<DXGI_FORMAT>( format ), static_cast<UINT>( flags ), &modeCount, 0 ) );
		if( Result::Last.IsFailure )
			return nullptr;
		
		std::vector<DXGI_MODE_DESC> nativeDescriptions(modeCount);
		Result::Record( InternalPointer->GetDisplayModeList( static_cast<DXGI_FORMAT>( format ), static_cast<UINT>( flags ), &modeCount, &nativeDescriptions[0] ) );
		if( Result::Last.IsFailure )
			return nullptr;
		
		System::Collections::Generic::List<ModeDescription>^ descriptions = gcnew System::Collections::Generic::List<ModeDescription>( modeCount );
		for( unsigned int descriptionIndex = 0; descriptionIndex < nativeDescriptions.size(); ++descriptionIndex )
			descriptions->Add( ModeDescription( nativeDescriptions[ descriptionIndex ] ) );
		
		return gcnew ReadOnlyCollection<ModeDescription>( descriptions );
	}
	
	Result Output::GetFrameStatistics( [Out] FrameStatistics% statistics )
	{
		DXGI_FRAME_STATISTICS stats;
		Result::Record( InternalPointer->GetFrameStatistics( &stats ) );
		if( Result::Last.IsSuccess )
			statistics = FrameStatistics( stats );
		return Result::Last;
	}

	Result Output::GetGammaControlCapabilities( [Out] GammaControlCapabilities% capabilities )
	{
		DXGI_GAMMA_CONTROL_CAPABILITIES caps;
		Result::Record( InternalPointer->GetGammaControlCapabilities( &caps ) );
		if( Result::Last.IsFailure )
			capabilities = GammaControlCapabilities( caps );
		return Result::Last;
	}
	
	Result Output::FindClosestMatchingMode( ComObject^ device, ModeDescription modeToMatch, [Out] ModeDescription% result )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
			
		DXGI_MODE_DESC nativeModeToMatch = modeToMatch.CreateNativeVersion();
		DXGI_MODE_DESC nativeResult;
		Result::Record( InternalPointer->FindClosestMatchingMode( &nativeModeToMatch, &nativeResult, device->UnknownPointer ) );
		if( Result::Last.IsSuccess )
			result = ModeDescription( nativeResult );
		return Result::Last;
	}
	
	Result Output::SetDisplaySurface( Surface^ surface )
	{
		if( surface == nullptr )
			throw gcnew ArgumentNullException( "surface" );
		return Result::Record( InternalPointer->SetDisplaySurface( surface->InternalPointer ) );
	}
	
	Result Output::TakeOwnership( ComObject^ device, bool exclusive )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		return Result::Record( InternalPointer->TakeOwnership( device->UnknownPointer, exclusive ) );
	}
	
	void Output::ReleaseOwnership()
	{
		InternalPointer->ReleaseOwnership();
	}
	
	Result Output::WaitForVerticalBlank()
	{
		return Result::Record( InternalPointer->WaitForVBlank() );
	}
}
}
