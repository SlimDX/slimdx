#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "Exceptions.h"

namespace SlimDX
{
	namespace Direct3D
	{
		[StructLayout( LayoutKind::Sequential )]
		public value class DisplayMode
		{
		public:
			int Width;
			int Height;
			int RefreshRate;
			Format Format;
		};

		public ref class AdapterDetails
		{
		internal:
			AdapterDetails( unsigned int adapter );

		public:
			initonly String^ Description;
			initonly int DeviceId;
			initonly Guid DeviceIdentifier;
			initonly String^ DeviceName;
			initonly String^ DriverName;
			initonly Version^ DriverVersion;
			initonly int Revision;
			initonly int SubSystemId;
			initonly int VendorId;
			initonly int WhqlLevel;
		};

		public ref class AdapterInformation
		{
		internal:
			initonly int m_Adapter;

			AdapterInformation( unsigned int adapter );

		public:
			property int Adapter
			{
				int get() { return m_Adapter; }
			}

			property int Monitor { int get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
			//TODO: Enumerate display modes

			initonly AdapterDetails^ Details;
		};

		public value class Caps
		{
		internal:
			Caps( int adapter, DeviceType deviceType );

		public:
			initonly Version^ VertexShaderVersion;
			initonly Version^ PixelShaderVersion;
		};

		public ref class AdapterList sealed// : public IEnumerable<AdapterInformation^>
		{
		internal:
			AdapterList( unsigned int adapterCount ) { Count = (int) adapterCount; }

		public:
			initonly int Count;

			property AdapterInformation^ default[int]
			{
				AdapterInformation^ get( int index )
				{
					if( index < 0 || index >= Count )
						throw gcnew ArgumentOutOfRangeException( "index" );

					return gcnew AdapterInformation( index );
				}
			}
		};

		public ref class Manager
		{
		private:
			static IDirect3D9* m_Direct3D;

		internal:
			static property IDirect3D9* Direct3D
			{
				IDirect3D9* get() { return m_Direct3D; }
			}

		public:
			static property bool CheckWhql;
			static property AdapterList^ Adapters;

			static Manager()
			{
				m_Direct3D = Direct3DCreate9( D3D_SDK_VERSION );
				if( m_Direct3D == NULL )
					throw gcnew DirectXException( -1, "Could not create Direct3D instance." );

				CheckWhql = false;
				Adapters = gcnew AdapterList( m_Direct3D->GetAdapterCount() );
			}

			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed, [Out] int% result );
			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed );

			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, DepthFormat depthStencilFormat, [Out] int% result );
			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, DepthFormat depthStencilFormat );

			static Caps GetDeviceCaps( int adapter, DeviceType deviceType );
		};
	}
}
