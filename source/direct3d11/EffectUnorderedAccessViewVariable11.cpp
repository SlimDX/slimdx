#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include <d3d11.h>
#include <d3dx11effect.h>

#include "Direct3D11Exception.h"

#include "EffectUnorderedAccessViewVariable11.h"
#include "UnorderedAccessView11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	EffectUnorderedAccessViewVariable::EffectUnorderedAccessViewVariable( ID3DX11EffectUnorderedAccessViewVariable* pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = pointer;
	}
	
	EffectUnorderedAccessViewVariable::EffectUnorderedAccessViewVariable( IntPtr pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = reinterpret_cast<ID3DX11EffectUnorderedAccessViewVariable*>( pointer.ToPointer() );
	}
	
	Result EffectUnorderedAccessViewVariable::SetView( UnorderedAccessView^ view )
	{
		if( view == nullptr )
			return RECORD_D3D11( m_Pointer->SetUnorderedAccessView( 0 ) );
		else
			return RECORD_D3D11( m_Pointer->SetUnorderedAccessView( static_cast<ID3D11UnorderedAccessView*>( view->InternalPointer ) ) );
	}

	UnorderedAccessView^ EffectUnorderedAccessViewVariable::GetView()
	{
		ID3D11UnorderedAccessView* view = 0;
		if( RECORD_D3D11( m_Pointer->GetUnorderedAccessView( &view ) ).IsFailure )
			return nullptr;
			
		return UnorderedAccessView::FromPointer( view );
	}

	Result EffectUnorderedAccessViewVariable::SetViewArray(...array<UnorderedAccessView^>^ views )
	{
		if( views == nullptr || views->Length == 0)
			return RECORD_D3D11( m_Pointer->SetUnorderedAccessViewArray(NULL, 0, 0) );
		
		array<ID3D11UnorderedAccessView*>^ internalViews = gcnew array<ID3D11UnorderedAccessView*>(views->Length);
		for (int i = 0; i < views->Length; ++i)
			internalViews[i] = views[i]->InternalPointer;

		pin_ptr<ID3D11UnorderedAccessView*> pinned_views = &internalViews[0];
		return RECORD_D3D11( m_Pointer->SetUnorderedAccessViewArray( pinned_views, 0, (UINT)internalViews->Length ) );
	}

	array<UnorderedAccessView^>^ EffectUnorderedAccessViewVariable::GetViewArray(int count)
	{
		array<ID3D11UnorderedAccessView*>^ internalViews = gcnew array<ID3D11UnorderedAccessView*>(count);
		pin_ptr<ID3D11UnorderedAccessView*> pinned_views = &internalViews[0];

		if (RECORD_D3D11( m_Pointer->SetUnorderedAccessViewArray( pinned_views, 0, (UINT)internalViews->Length )).IsFailure)
			return nullptr;

		array<UnorderedAccessView^>^ views = gcnew array<UnorderedAccessView^>(count);
		for (int i = 0; i < count; ++i)
			views[i] = UnorderedAccessView::FromPointer(internalViews[i]);
		
		return views;
	}
}
}
