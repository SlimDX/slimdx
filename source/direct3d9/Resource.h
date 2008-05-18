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

#include "../ComObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Device;
		
		/// <summary>Applications use the methods of the Resource class to query and prepare resources.</summary>
		/// <unmanaged>IDirect3DResource9</unmanaged>
		public ref class Resource abstract : public ComObject
		{
			COMOBJECT_BASE(IDirect3DResource9);

		protected:
			Resource() { }

		public:
			void Preload();

			literal int PriorityMinimum = D3D9_RESOURCE_PRIORITY_MINIMUM;
			literal int PriorityLow = D3D9_RESOURCE_PRIORITY_LOW;
			literal int PriorityNormal = D3D9_RESOURCE_PRIORITY_NORMAL;
			literal int PriorityHigh = D3D9_RESOURCE_PRIORITY_HIGH;
			literal int PriorityMaximum = D3D9_RESOURCE_PRIORITY_MAXIMUM;

			property SlimDX::Direct3D9::Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}

			property int Priority
			{
				int get() { return InternalPointer->GetPriority(); }
				void set(int value) { InternalPointer->SetPriority( value ); }
			};
		
			property SlimDX::Direct3D9::ResourceType ResourceType
			{
				SlimDX::Direct3D9::ResourceType get() { return ( SlimDX::Direct3D9::ResourceType ) InternalPointer->GetType(); }
			}
		};
	}
}
