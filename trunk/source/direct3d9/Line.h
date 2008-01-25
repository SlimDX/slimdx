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

using namespace System::Drawing;

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class Line : ComObject
		{
			COMOBJECT(ID3DXLine);

		internal:
			/* Unused for now.
			Line( ID3DXLine* line );
			*/

		public:
			Line( IntPtr line );
			Line( Device^ device );
			~Line() { Destruct(); }

			void Begin();
			void End();

			void Draw( array<Vector2>^ vertexList, int color );
			void Draw( array<Vector2>^ vertexList, Color color );
			void DrawTransformed( array<Vector3>^ vertexList, Matrix matrix, int color );
			void DrawTransformed( array<Vector3>^ vertexList, Matrix matrix, Color color );
			
			void OnLostDevice();
			void OnResetDevice();

			Device^ GetDevice();

			property bool Antialias
			{
				bool get();
				void set( bool value );
			}

			property bool GLLines
			{
				bool get();
				void set( bool value );
			}

			property int Pattern
			{
				int get();
				void set( int value );
			}

			property float PatternScale
			{
				float get();
				void set( float value );
			}

			property float Width
			{
				float get();
				void set( float value );
			}
		};
	}
}