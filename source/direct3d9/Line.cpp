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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "../math/Math.h"

#include "Device.h"
#include "Line.h"

namespace SlimDX
{
namespace Direct3D9
{
	/* Unused for now.
	Line::Line( ID3DXLine* line ) : DirectXObject( line )
	{
		if( line == NULL )
			throw gcnew ArgumentNullException( "line" );
	}
	*/

	Line::Line( IntPtr line )
	{
		if( line == IntPtr::Zero )
			throw gcnew ArgumentNullException( "line" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( line.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXLine, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXLine*>( pointer );
	}

	Line::Line( Device^ device )
	{
		ID3DXLine* line;

		HRESULT hr = D3DXCreateLine( device->InternalPointer, &line );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = line;
	}

	void Line::Begin()
	{
		HRESULT hr = m_Pointer->Begin();
		GraphicsException::CheckHResult( hr );
	}

	void Line::End()
	{
		HRESULT hr = m_Pointer->End();
		GraphicsException::CheckHResult( hr );
	}

	void Line::Draw( array<Vector2>^ vertexList, int color )
	{
		pin_ptr<Vector2> pinnedVerts = &vertexList[0];

		HRESULT hr = m_Pointer->Draw( reinterpret_cast<D3DXVECTOR2*>( pinnedVerts ), vertexList->Length, color );
		GraphicsException::CheckHResult( hr );
	}

	void Line::Draw( array<Vector2>^ vertexList, Color color )
	{
		Draw( vertexList, color.ToArgb() );
	}
	
	void Line::DrawTransformed( array<Vector3>^ vertexList, Matrix transform, int color )
	{
		pin_ptr<Vector3> pinnedVerts = &vertexList[0];

		HRESULT hr = m_Pointer->DrawTransform( reinterpret_cast<D3DXVECTOR3*>( pinnedVerts ), vertexList->Length, reinterpret_cast<const D3DXMATRIX*>( &transform ), color );
		GraphicsException::CheckHResult( hr );
	}
	
	void Line::DrawTransformed( array<Vector3>^ vertexList, Matrix transform, Color color )
	{
		DrawTransformed( vertexList, transform, color.ToArgb() );
	}
	
	void Line::OnLostDevice()
	{
		HRESULT hr = m_Pointer->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Line::OnResetDevice()
	{
		HRESULT hr = m_Pointer->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	Device^ Line::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	bool Line::Antialias::get()
	{
		return m_Pointer->GetAntialias() > 0;
	}

	void Line::Antialias::set( bool value )
	{
		HRESULT hr = m_Pointer->SetAntialias( value );
		GraphicsException::CheckHResult( hr );
	}

	bool Line::GLLines::get()
	{
		return m_Pointer->GetGLLines() > 0;
	}

	void Line::GLLines::set( bool value )
	{
		HRESULT hr = m_Pointer->SetGLLines( value );
		GraphicsException::CheckHResult( hr );
	}

	int Line::Pattern::get()
	{
		return m_Pointer->GetPattern();
	}

	void Line::Pattern::set( int value )
	{
		HRESULT hr = m_Pointer->SetPattern( value );
		GraphicsException::CheckHResult( hr );
	}

	float Line::PatternScale::get()
	{
		return m_Pointer->GetPatternScale();
	}

	void Line::PatternScale::set( float value )
	{
		HRESULT hr = m_Pointer->SetPatternScale( value );
		GraphicsException::CheckHResult( hr );
	}

	float Line::Width::get()
	{
		return m_Pointer->GetWidth();
	}

	void Line::Width::set( float value )
	{
		HRESULT hr = m_Pointer->SetWidth( value );
		GraphicsException::CheckHResult( hr );
	}

}
}