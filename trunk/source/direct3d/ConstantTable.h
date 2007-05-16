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

using namespace System;

#include "../math/Math.h"

namespace SlimDX
{
	namespace Direct3D
	{
		ref class EffectHandle;
	
		public ref class ConstantTable : public DirectXObject
		{
		private:
			IDirect3DDevice9* m_Device;
			ID3DXConstantTable* m_ConstantTable;

		internal:
			property ID3DXConstantTable* InternalPointer
			{
				ID3DXConstantTable* get() { return m_ConstantTable; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_ConstantTable; }
				virtual void set( IUnknown* value ) override { m_ConstantTable = (ID3DXConstantTable*) value; }
			}

		public:
			ConstantTable( IDirect3DDevice9* device, ID3DXConstantTable* constantTable );
			~ConstantTable();
			
			EffectHandle^ GetConstant( EffectHandle^ handle,int index );
			EffectHandle^ GetConstant( EffectHandle^ handle,String^ name );
			
			void SetValue( EffectHandle^ constant, Vector4 value );
			void SetValue( EffectHandle^ constant, Matrix value );
		};
	}
}
