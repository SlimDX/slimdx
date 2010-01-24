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

namespace SlimDX
{
	namespace Direct3D11
	{	
		public value class ClassInstanceDescription : System::IEquatable<ClassInstanceDescription>
		{				
		internal:
			ClassInstanceDescription( const D3D11_CLASS_INSTANCE_DESC& native );
			
			D3D11_CLASS_INSTANCE_DESC CreateNativeVersion();
		
		public:
			property int InstanceId;
			property int InstanceIndex;
			property int TypeId;
			property int ConstantBuffer;
			property int BaseConstantBufferOffset;
			property int BaseTexture;
			property int BaseSampler;
			property bool IsCreated;

			static bool operator == ( ClassInstanceDescription left, ClassInstanceDescription right );
			static bool operator != ( ClassInstanceDescription left, ClassInstanceDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ClassInstanceDescription other );
			static bool Equals( ClassInstanceDescription% value1, ClassInstanceDescription% value2 );
		};
	}
};