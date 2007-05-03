#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		ref class Device;

		public ref class RenderStateManager sealed
		{
		private:
			Device^ m_Device;

		internal:
			RenderStateManager( Device^ device ) : m_Device( device )
			{ }

		public:
			property Cull CullMode { Cull get(); void set( Cull value ); }
			property bool ZBufferEnable { bool get(); void set( bool value ); }
		};
	}
}
