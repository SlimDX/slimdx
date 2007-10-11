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
using namespace System::Globalization;

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class EffectMatrixVariable;
		ref class EffectResourceVariable;
		ref class EffectShaderVariable;
		ref class EffectScalarVariable;
		ref class EffectVectorVariable;
		
		public ref class EffectVariable
		{
		private:
			ID3D10EffectVariable* m_Pointer;
			String^ m_Name;
			String^ m_Semantic;
			EffectVariableFlags m_Flags;
			int m_AnnotationCount;
			int m_BufferOffset;
			int m_ExplicitBindPoint;

		protected:
			property ID3D10EffectVariable* Pointer
			{
				ID3D10EffectVariable* get() { return m_Pointer; }
				void set( ID3D10EffectVariable* value ) { m_Pointer = value; }
			}
			
		internal:
			EffectVariable( ID3D10EffectVariable* variable );
			
		public:
			property String^ Name
			{
				String^ get() { return m_Name; }
			protected:
				void set( String^ value ) { m_Name = value; }
			}
			
			property String^ Semantic
			{
				String^ get() { return m_Semantic; }
			protected:
				void set( String^ value ) { m_Semantic = value; }
			}
			
			property EffectVariableFlags Flags
			{
				EffectVariableFlags get() { return m_Flags; }
			protected:
				void set( EffectVariableFlags value ) { m_Flags = value; }
			}
			
			property int AnnotationCount
			{
				int get() { return m_AnnotationCount; }
			protected:
				void set( int value ) { m_AnnotationCount = value; }
			}
			
			property int BufferOffset
			{
				int get() { return m_BufferOffset; }
			protected:
				void set( int value ) { m_BufferOffset = value; }
			}
			
			property int ExplicitBindPoint
			{
				int get() { return m_ExplicitBindPoint; }
			protected:
				void set( int value ) { m_ExplicitBindPoint = value; }
			}
			
			property bool IsValid
			{
				bool get() { return m_Pointer->IsValid() ? true : false; }
			}
			
			EffectVariable^ GetAnnotationByIndex( int index );
			EffectVariable^ GetAnnotationByName( String^ name );
			
			EffectVariable^ GetElement( int index );
			
			EffectVariable^ GetMemberByIndex( int index );
			EffectVariable^ GetMemberByName( String^ name );
			EffectVariable^ GetMemberBySemantic( String^ name );
			
			EffectMatrixVariable^ AsMatrix();
			EffectResourceVariable^ AsResource();
			EffectShaderVariable^ AsShader();
			EffectScalarVariable^ AsScalar();
			EffectVectorVariable^ AsVector();
		};
	}
};