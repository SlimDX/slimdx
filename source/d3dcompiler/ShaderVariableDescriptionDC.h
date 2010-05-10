/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include "EnumsDC.h"

namespace SlimDX
{
	namespace D3DCompiler
	{	
		public value class ShaderVariableDescription : System::IEquatable<ShaderVariableDescription>
		{
		private:
			System::String^ m_Name;
			int m_StartOffset;
			int m_Size;
			ShaderVariableFlags m_Flags;
			System::IntPtr defaultValue;
		
		internal:
			ShaderVariableDescription( const D3D11_SHADER_VARIABLE_DESC& description );
		
		public:
			property System::String^ Name
			{
				System::String^ get();
			}
			
			property int StartOffset
			{
				int get();
			}
			
			property int Size
			{
				int get();
			}

			property ShaderVariableFlags Flags
			{
				ShaderVariableFlags get();
			}

			property System::IntPtr DefaultValue
			{
				System::IntPtr get();
			}

			static bool operator == ( ShaderVariableDescription left, ShaderVariableDescription right );
			static bool operator != ( ShaderVariableDescription left, ShaderVariableDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ShaderVariableDescription other );
			static bool Equals( ShaderVariableDescription% value1, ShaderVariableDescription% value2 );
		};
	}
};