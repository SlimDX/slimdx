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

#include "../DirectXObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Device;
		
		public ref class Resource abstract : public DirectXObject<IDirect3DResource9>
		{
		protected:
			Resource() { }

		public:
			virtual ~Resource() { Destruct(); }
			DXOBJECT_FUNCTIONS;

			property int Priority
			{
				int get() { return m_Pointer->GetPriority(); }
				void set(int value) { m_Pointer->SetPriority( value ); }
			};
		
			property SlimDX::Direct3D9::ResourceType ResourceType
			{
				SlimDX::Direct3D9::ResourceType get() { return ( SlimDX::Direct3D9::ResourceType ) m_Pointer->GetType(); }
			}
			
			Device^ GetDevice();
			
			void Preload();
		};
	}
}