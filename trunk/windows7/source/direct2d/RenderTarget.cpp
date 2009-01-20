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

#define DEFINE_ENUM_FLAG_OPERATORS(x)

#include <d2d1.h>
#include <d2d1helper.h>

#include "Direct2DException.h"

#include "RenderTarget.h"

const IID IID_ID2D1RenderTarget = __uuidof(ID2D1RenderTarget);

using namespace System;
using namespace System::Drawing;

namespace SlimDX
{
namespace Direct2D
{
	void RenderTarget::BeginDraw()
	{
		InternalPointer->BeginDraw();
	}

	Result RenderTarget::EndDraw()
	{
		return RECORD_D2D( InternalPointer->EndDraw() );
	}

	void RenderTarget::Clear()
	{
		InternalPointer->Clear( NULL );
	}

	void RenderTarget::Clear( Color4 color )
	{
		InternalPointer->Clear( reinterpret_cast<D2D1_COLOR_F*>( &color ) );
	}

	void RenderTarget::DrawLine( Brush^ brush, PointF point1, PointF point2 )
	{
		D2D1_POINT_2F point1_n = D2D1::Point2F( point1.X, point1.Y );
		D2D1_POINT_2F point2_n = D2D1::Point2F( point2.X, point2.Y );

		InternalPointer->DrawLine( point1_n, point2_n, brush->InternalPointer );
	}

	void RenderTarget::DrawLine( Brush^ brush, PointF point1, PointF point2, float strokeWidth )
	{
		D2D1_POINT_2F point1_n = D2D1::Point2F( point1.X, point1.Y );
		D2D1_POINT_2F point2_n = D2D1::Point2F( point2.X, point2.Y );

		InternalPointer->DrawLine( point1_n, point2_n, brush->InternalPointer, strokeWidth );
	}

	void RenderTarget::DrawLine( Brush^ brush, PointF point1, PointF point2, float strokeWidth, StrokeStyle^ strokeStyle )
	{
		ID2D1StrokeStyle *style = strokeStyle == nullptr ? NULL : strokeStyle->InternalPointer;
		D2D1_POINT_2F point1_n = D2D1::Point2F( point1.X, point1.Y );
		D2D1_POINT_2F point2_n = D2D1::Point2F( point2.X, point2.Y );

		InternalPointer->DrawLine( point1_n, point2_n, brush->InternalPointer, strokeWidth, style );
	}

	void RenderTarget::DrawLine( Brush^ brush, float x1, float y1, float x2, float y2 )
	{
		DrawLine( brush, PointF( x1, y1 ), PointF( x2, y2 ) );
	}

	void RenderTarget::DrawLine( Brush^ brush, float x1, float y1, float x2, float y2, float strokeWidth )
	{
		DrawLine( brush, PointF( x1, y1 ), PointF( x2, y2 ), strokeWidth );
	}

	void RenderTarget::DrawLine( Brush^ brush, float x1, float y1, float x2, float y2, float strokeWidth, StrokeStyle^ strokeStyle )
	{
		DrawLine( brush, PointF( x1, y1 ), PointF( x2, y2 ), strokeWidth, strokeStyle );
	}

	void RenderTarget::FillRectangle( Brush^ brush, System::Drawing::Rectangle rectangle )
	{
		FillRectangle( brush, RectangleF( static_cast<FLOAT>( rectangle.X ), static_cast<FLOAT>( rectangle.Y ), 
			static_cast<FLOAT>( rectangle.Width ), static_cast<FLOAT>( rectangle.Height ) ) );
	}

	void RenderTarget::FillRectangle( Brush^ brush, RectangleF rectangle )
	{
		D2D1_RECT_F rect = D2D1::RectF( rectangle.Left, rectangle.Top, rectangle.Right, rectangle.Bottom );
		InternalPointer->FillRectangle( rect, brush->InternalPointer );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle )
	{
		DrawRectangle( brush, RectangleF( static_cast<FLOAT>( rectangle.X ), static_cast<FLOAT>( rectangle.Y ), 
			static_cast<FLOAT>( rectangle.Width ), static_cast<FLOAT>( rectangle.Height ) ) );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle, float strokeWidth )
	{
		DrawRectangle( brush, RectangleF( static_cast<FLOAT>( rectangle.X ), static_cast<FLOAT>( rectangle.Y ), 
			static_cast<FLOAT>( rectangle.Width ), static_cast<FLOAT>( rectangle.Height ) ), strokeWidth );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle, float strokeWidth, StrokeStyle^ strokeStyle )
	{
		DrawRectangle( brush, RectangleF( static_cast<FLOAT>( rectangle.X ), static_cast<FLOAT>( rectangle.Y ), 
			static_cast<FLOAT>( rectangle.Width ), static_cast<FLOAT>( rectangle.Height ) ), strokeWidth, strokeStyle );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, RectangleF rectangle )
	{
		D2D1_RECT_F rect = D2D1::RectF( rectangle.Left, rectangle.Top, rectangle.Right, rectangle.Bottom );
		InternalPointer->DrawRectangle( rect, brush->InternalPointer );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, RectangleF rectangle, float strokeWidth )
	{
		D2D1_RECT_F rect = D2D1::RectF( rectangle.Left, rectangle.Top, rectangle.Right, rectangle.Bottom );
		InternalPointer->DrawRectangle( rect, brush->InternalPointer, strokeWidth );
	}

	void RenderTarget::DrawRectangle( Brush^ brush, RectangleF rectangle, float strokeWidth, StrokeStyle^ strokeStyle )
	{
		ID2D1StrokeStyle *style = strokeStyle == nullptr ? NULL : strokeStyle->InternalPointer;
		D2D1_RECT_F rect = D2D1::RectF( rectangle.Left, rectangle.Top, rectangle.Right, rectangle.Bottom );

		InternalPointer->DrawRectangle( rect, brush->InternalPointer, strokeWidth, style );
	}

	Matrix3x2 RenderTarget::Transform::get()
	{
		Matrix3x2 result;
		InternalPointer->GetTransform( reinterpret_cast<D2D1_MATRIX_3X2_F*>( &result ) );

		return result;
	}

	void RenderTarget::Transform::set( Matrix3x2 value )
	{
		InternalPointer->SetTransform( reinterpret_cast<D2D1_MATRIX_3X2_F*>( &value ) );
	}

	System::Drawing::SizeF RenderTarget::Size::get()
	{
		D2D1_SIZE_F size = InternalPointer->GetSize();
		return System::Drawing::SizeF( size.width, size.height );
	}
}
}