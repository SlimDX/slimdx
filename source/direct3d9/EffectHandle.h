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

using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class EffectHandle
		{
		private:
			D3DXHANDLE m_Handle;

			//for when we were forced to allocate data for a string
			IntPtr m_StringData;
			bool m_HasString;

		internal:
			property D3DXHANDLE InternalHandle
			{
				D3DXHANDLE get() { return m_Handle; }
			}

		public:
			EffectHandle( D3DXHANDLE handle )
			{
				m_Handle = handle;
				m_StringData = IntPtr::Zero;
				m_HasString = false;
			}

			EffectHandle( String^ name )
			{
				m_StringData = Marshal::StringToHGlobalAnsi( name );
				m_HasString = true;

				m_Handle = (D3DXHANDLE) m_StringData.ToPointer();
			}

			~EffectHandle()
			{
				//MSDN says this is ok to do: http://msdn2.microsoft.com/en-us/library/ms235250(VS.80).aspx
				EffectHandle::!EffectHandle();
			}

			!EffectHandle()
			{
				if( m_HasString )
					Marshal::FreeHGlobal( m_StringData );
			}

			static bool operator == ( EffectHandle^ lhs, EffectHandle^ rhs )
			{
				Object^ lhsObj = lhs;
				Object^ rhsObj = rhs;
				if( lhsObj == nullptr )
					return rhsObj == nullptr;
				if( rhsObj == nullptr )
					return lhsObj == nullptr;

				return lhs->m_Handle == rhs->m_Handle;
			}

			static bool operator != ( EffectHandle^ lhs, EffectHandle^ rhs )
			{
				return !(lhs == rhs);
			}

			virtual bool Equals( Object^ obj ) override
			{
				if( obj == nullptr )
					return false;
				if( obj->GetType() != EffectHandle::typeid )
					return false;

				EffectHandle^ eh = (EffectHandle^) obj;
				return m_Handle == eh->m_Handle;
			}

			static operator EffectHandle^ ( String^ name )
			{
				return gcnew EffectHandle( name );
			}
		};    }
}
