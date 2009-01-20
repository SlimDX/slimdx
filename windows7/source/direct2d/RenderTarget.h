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

#include "Resource.h"
#include "Matrix3x2.h"
#include "StrokeStyle.h"
#include "Brush.h"

namespace SlimDX
{
	namespace Direct2D
	{
		public ref class RenderTarget abstract : Resource
		{
			COMOBJECT_BASE(ID2D1RenderTarget);

		public:
			void BeginDraw();
			Result EndDraw();

			void Clear();
			void Clear( Color4 color );

			void DrawLine( Brush^ brush, System::Drawing::PointF point1, System::Drawing::PointF point2 );
			void DrawLine( Brush^ brush, System::Drawing::PointF point1, System::Drawing::PointF point2, float strokeWidth );
			void DrawLine( Brush^ brush, System::Drawing::PointF point1, System::Drawing::PointF point2, float strokeWidth, StrokeStyle^ strokeStyle );

			void DrawLine( Brush^ brush, float x1, float y1, float x2, float y2 );
			void DrawLine( Brush^ brush, float x1, float y1, float x2, float y2, float strokeWidth );
			void DrawLine( Brush^ brush, float x1, float y1, float x2, float y2, float strokeWidth, StrokeStyle^ style );

			void FillRectangle( Brush^ brush, System::Drawing::Rectangle rectangle );
			void FillRectangle( Brush^ brush, System::Drawing::RectangleF rectangle );

			void DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle );
			void DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle, float strokeWidth );
			void DrawRectangle( Brush^ brush, System::Drawing::Rectangle rectangle, float strokeWidth, StrokeStyle^ strokeStyle );

			void DrawRectangle( Brush^ brush, System::Drawing::RectangleF rectangle );
			void DrawRectangle( Brush^ brush, System::Drawing::RectangleF rectangle, float strokeWidth );
			void DrawRectangle( Brush^ brush, System::Drawing::RectangleF rectangle, float strokeWidth, StrokeStyle^ strokeStyle );

			property Matrix3x2 Transform
			{
				Matrix3x2 get();
				void set( Matrix3x2 value );
			}

			property System::Drawing::SizeF Size
			{
				System::Drawing::SizeF get();
			}
		};
	}
}