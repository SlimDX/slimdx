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

#include "../math/Math.h"
#include "Device.h"

namespace SlimDX
{
	ref class GraphicsStream;

	namespace Direct3D9
	{
		//description structures for various things
		public value class EffectDescription
		{
		public:
			String^ Creator;
			int Parameters;
			int Techniques;
			int Functions;
		};

		public value class TechniqueDescription
		{
		public:
			String^ Name;
			int Passes;
			int Annotations;
		};

		public value class FunctionDescription
		{
		public:
			String^ Name;
			int Annotations;
		};

		public value class ParameterDescription
		{
		public:
			String^ Name;
			String^ Semantic;
			ParameterClass Class;
			ParameterType Type;
			int Rows;
			int Columns;
			int Elements;
			int Annotations;
			int StructMembers;
			ParameterFlags Flags;
			int Bytes;
		};

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
		};

		public ref class Include abstract
		{
		};

		public value class Macro
		{
		};

		public ref class EffectPool
		{
		};
		
		public ref class BaseEffect abstract : public DirectXObject<ID3DXBaseEffect>
		{
		protected:
			BaseEffect( ID3DXBaseEffect* pointer ) : DirectXObject( pointer )
			{ }

		public:
			EffectHandle^ GetAnnotation( EffectHandle^ handle, int index );
			EffectHandle^ GetAnnotation( EffectHandle^ handle, String^ name );

			EffectHandle^ GetParameter( EffectHandle^ parameter, int index );
			EffectHandle^ GetParameter( EffectHandle^ parameter, String^ name );
			EffectHandle^ GetParameterBySemantic( EffectHandle^ parameter, String^ name );
			EffectHandle^ GetParameterElement( EffectHandle^ parameter, int index );
			ParameterDescription GetParameterDescription( EffectHandle^ parameter );

			EffectHandle^ GetFunction( int index );
			EffectHandle^ GetFunction( String^ name );
			FunctionDescription GetFunctionDescription( EffectHandle^ handle );

			EffectHandle^ GetTechnique( int index );
			EffectHandle^ GetTechnique( String^ name );
			TechniqueDescription GetTechniqueDescription( EffectHandle^ handle );

			property EffectDescription Description
			{
				EffectDescription get();
			}

			void SetValue( EffectHandle^ param, bool value );
			void SetValue( EffectHandle^ param, array<bool>^ values );
			void SetValue( EffectHandle^ param, int value );
			void SetValue( EffectHandle^ param, array<int>^ values );
			void SetValue( EffectHandle^ param, float value );
			void SetValue( EffectHandle^ param, array<float>^ values );
			void SetValue( EffectHandle^ param, Vector4 value );
			void SetValue( EffectHandle^ param, array<Vector4>^ values );
			void SetValue( EffectHandle^ param, ColorValue value );
			void SetValue( EffectHandle^ param, array<ColorValue>^ values );
			void SetValue( EffectHandle^ param, Matrix value );
			void SetValue( EffectHandle^ param, array<Matrix>^ values );
			void SetValue( EffectHandle^ param, BaseTexture^ value );
			void SetValueTranspose( EffectHandle^ param, Matrix value );
			void SetValueTranspose( EffectHandle^ param, array<Matrix>^ values );

			bool GetBool( EffectHandle^ param );
			array<bool>^ GetBoolArray( EffectHandle^ param, int count );
			int GetInt( EffectHandle^ param );
			array<int>^ GetIntArray( EffectHandle^ param, int count );
			float GetFloat( EffectHandle^ param );
			array<float>^ GetFloatArray( EffectHandle^ param, int count );
			Vector4 GetVector( EffectHandle^ param );
			array<Vector4>^ GetVectorArray( EffectHandle^ param, int count );
			ColorValue GetColor( EffectHandle^ param );
			array<ColorValue>^ GetColorArray( EffectHandle^ param, int count );
			Matrix GetMatrix( EffectHandle^ param );
			array<Matrix>^ GetMatrixArray( EffectHandle^ param, int count );
			Matrix GetMatrixTranspose( EffectHandle^ param );
			array<Matrix>^ GetMatrixTransposeArray( EffectHandle^ param, int count );

			String^ GetValueString( EffectHandle^ param );
			GraphicsStream^ GetValue( EffectHandle^ param, int bytes );
		};

		public ref class Effect sealed : public BaseEffect
		{
		private:
		internal:
			property ID3DXEffect* EffectPointer
			{
				ID3DXEffect* get() { return (ID3DXEffect*) m_Pointer; }
			}

		public:
			Effect( ID3DXEffect* effect );

			//FromMemory
			static Effect^ FromMemory( Device^ device, array<Byte>^ memory, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );

			//FromStream
			static Effect^ FromStream( Device^ device, Stream^ stream, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, 
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool );

			//FromString
			static Effect^ FromString( Device^ device, String^ sourceData, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors);
			static Effect^ FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool);

			//FromFile
			static Effect^ FromFile( Device^ device, String^ fileName, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromFile( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors);
			static Effect^ FromFile( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool);

			int Begin( FX flags );
			void End();
			void BeginPass( int pass );
			void EndPass();

			void BeginParameterBlock();
			EffectHandle^ EndParameterBlock();
			void ApplyParameterBlock( EffectHandle^ parameterBlock );
			void DeleteParameterBlock( EffectHandle^ parameterBlock );

			void CommitChanges();

			EffectHandle^ FindNextValidTechnique( EffectHandle^ technique );
			bool ValidateTechnique( EffectHandle^ technique );

			property EffectHandle^ Technique
			{
				EffectHandle^ get();
				void set( EffectHandle^ value );
			}

			void OnLostDevice();
			void OnResetDevice();
		};
	}
}
