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

#include "../BaseObject.h"
#include "../math/Math.h"

#include "Device.h"
#include "Line.h"

namespace SlimDX
{
namespace Direct3D9
{
	/* Unused for now.
	Line::Line( ID3DXLine* line ) : BaseObject( line )
	{
		if( line == NULL )
			throw gcnew ArgumentNullException( "line" );
	}
	*/

	Line::Line( IntPtr line )
	{
		Construct( line, NativeInterface );
	}

	Line::Line( Device^ device )
	{
		ID3DXLine* line;

		HRESULT hr = D3DXCreateLine( device->InternalPointer, &line );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		Construct(line);
	}

	void Line::Begin()
	{
		HRESULT hr = InternalPointer->Begin();
		GraphicsException::CheckHResult( hr );
	}

	void Line::End()
	{
		HRESULT hr = InternalPointer->End();
		GraphicsException::CheckHResult( hr );
	}

	void Line::Draw( array<Vector2>^ vertexList, int color )
	{
		pin_ptr<Vector2> pinnedVerts = &vertexList[0];

		HRESULT hr = InternalPointer->Draw( reinterpret_cast<D3DXVECTOR2*>( pinnedVerts ), vertexList->Length, color );
		GraphicsException::CheckHResult( hr );
	}

	void Line::Draw( array<Vector2>^ vertexList, Color color )
	{
		Draw( vertexList, color.ToArgb() );
	}
	
	void Line::DrawTransformed( array<Vector3>^ vertexList, Matrix transform, int color )
	{
		pin_ptr<Vector3> pinnedVerts = &vertexList[0];

		HRESULT hr = InternalPointer->DrawTransform( reinterpret_cast<D3DXVECTOR3*>( pinnedVerts ), vertexList->Length, reinterpret_cast<const D3DXMATRIX*>( &transform ), color );
		GraphicsException::CheckHResult( hr );
	}
	
	void Line::DrawTransformed( array<Vector3>^ vertexList, Matrix transform, Color color )
	{
		DrawTransformed( vertexList, transform, color.ToArgb() );
	}
	
	void Line::OnLostDevice()
	{
		HRESULT hr = InternalPointer->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Line::OnResetDevice()
	{
		HRESULT hr = InternalPointer->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	Device^ Line::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	bool Line::Antialias::get()
	{
		return InternalPointer->GetAntialias() > 0;
	}

	void Line::Antialias::set( bool value )
	{
		HRESULT hr = InternalPointer->SetAntialias( value );
		GraphicsException::CheckHResult( hr );
	}

	bool Line::GLLines::get()
	{
		return InternalPointer->GetGLLines() > 0;
	}

	void Line::GLLines::set( bool value )
	{
		HRESULT hr = InternalPointer->SetGLLines( value );
		GraphicsException::CheckHResult( hr );
	}

	int Line::Pattern::get()
	{
		return InternalPointer->GetPattern();
	}

	void Line::Pattern::set( int value )
	{
		HRESULT hr = InternalPointer->SetPattern( value );
		GraphicsException::CheckHResult( hr );
	}

	float Line::PatternScale::get()
	{
		return InternalPointer->GetPatternScale();
	}

	void Line::PatternScale::set( float value )
	{
		HRESULT hr = InternalPointer->SetPatternScale( value );
		GraphicsException::CheckHResult( hr );
	}

	float Line::Width::get()
	{
		return InternalPointer->GetWidth();
	}

	void Line::Width::set( float value )
	{
		HRESULT hr = InternalPointer->SetWidth( value );
		GraphicsException::CheckHResult( hr );
	}

}
}