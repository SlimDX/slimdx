#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace Direct3D
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
				//TODO: Check with Washu on this whole affair
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

		public ref class BaseEffect abstract
		{
		private:
			ID3DXBaseEffect* m_BaseEffect;

		protected:
			BaseEffect( ID3DXBaseEffect* pointer ) : m_BaseEffect( pointer )
			{ }

		internal:
			property ID3DXBaseEffect* BasePointer
			{
				ID3DXBaseEffect* get() { return m_BaseEffect; }
			}

		public:
			virtual ~BaseEffect()
			{
			}

			EffectHandle^ GetParameter( EffectHandle^ constant, String^ name )
			{
				array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
				pin_ptr<unsigned char> pinned_name = &nameBytes[0];

				D3DXHANDLE parentHandle = constant != nullptr ? constant->InternalHandle : NULL;
				D3DXHANDLE handle = m_BaseEffect->GetParameterByName( parentHandle, (const char*) pinned_name );
				
				if( handle != NULL )
					return gcnew EffectHandle( handle );
				else
					return nullptr;
			}

			void SetValue( EffectHandle^ param, bool value );
			//void SetValue( EffectHandle^ param, array<bool>^ value );
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
		};

		public ref class Effect sealed : public BaseEffect
		{
		private:
			ID3DXEffect* m_Effect;
			bool m_Disposed;

		internal:
			property ID3DXEffect* InternalPointer
			{
				ID3DXEffect* get() { return m_Effect; }
			}

		public:
			Effect( ID3DXEffect* effect );
			~Effect();
			!Effect();

			property EffectHandle^ Technique;

			static Effect^ FromStream( Device^ device, Stream^ stream, array<Macro^>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );

			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
			{
				return FromStream( device, stream, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
			}

			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, 
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool )
			{
				String^ compilationErrors;
				return FromStream( device, stream, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
			}

			EffectHandle^ FindNextValidTechnique( EffectHandle^ technique );

			int Begin( FX flags );
			void End();
			void BeginPass( int pass );
			void EndPass();
		};
	}
}
