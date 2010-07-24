#pragma once

namespace SlimDX
{	
	template< typename T > 
	public ref class ComObject abstract : IComObject
	{
		public:
			ComObject( T* pointer )
			: m_Pointer( pointer )
			{
			}
			
			ComObject( System::IntPtr pointer )
			: m_Pointer( reinterpret_cast<T*>( pointer.ToPointer() ) )
			{
			}
			
			property System::IntPtr UnknownPointer
			{
				virtual System::IntPtr get()
				{
					return System::IntPtr( m_Pointer );
				}
			}
		
			virtual void AddReference()
			{
				m_Pointer->AddRef();
			}
			
			virtual void Release()
			{
				m_Pointer->Release();
			}

			virtual bool Equals( System::Object^ other ) override
			{
				if( other != nullptr )
				{
					ComObject<T>^ concrete = safe_cast<ComObject<T>^>( other );
					return NativePointer == concrete->NativePointer;
				}

				return false;
			}
			
		protected:
			property T* NativePointer
			{
				T* get()
				{
					return m_Pointer;
				}
			}
			
		private:
			T* m_Pointer;
	};
}