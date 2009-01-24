/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Enums.h"
#include "BezierSegment.h"

namespace SlimDX
{
	namespace Direct2D
	{
		public ref class SimplifiedGeometrySink : ComObject
		{
			COMOBJECT(ID2D1SimplifiedGeometrySink, SimplifiedGeometrySink);
			
		public:
			static SimplifiedGeometrySink^ FromPointer( System::IntPtr pointer );

			void BeginFigure( System::Drawing::Point startPoint, FigureBegin style );
			void BeginFigure( System::Drawing::PointF startPoint, FigureBegin style );
			void EndFigure( FigureEnd style );

			Result Close();

			void SetFillMode( FillMode fillMode );
			void SetSegmentFlags( PathSegment vertexFlags );

			void AddLine( int x1, int y1, int x2, int y2 );
			void AddLine( float x1, float y1, float x2, float y2 );
			void AddLine( System::Drawing::Point point1, System::Drawing::Point point2 );
			void AddLine( System::Drawing::PointF point1, System::Drawing::PointF point2 );
			void AddLines( array<System::Drawing::PointF>^ points );

			void AddBezier( BezierSegment bezier );
			void AddBeziers( array<BezierSegment>^ beziers );
		};
	}
}