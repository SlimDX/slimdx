#pragma once

using namespace System;

namespace SlimDX
{
	namespace DirectInput
	{
		public value class MouseState
		{
		internal:
			array<Byte>^ buttons;

		public:
			int X, Y, Z;

			property array<Byte>^ Buttons
			{
				array<Byte>^ get() { return buttons; }
			}
		};

		public ref class Device : public DirectXObject
		{
		private:
			IDirectInputDevice8* m_Device;

		internal:
			property IDirectInputDevice8* InternalPointer
			{
				IDirectInputDevice8* get() { return m_Device; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Device; }
				virtual void set( IUnknown* value ) override { m_Device = (IDirectInputDevice8*) value; }
			}


		};
	}
}
