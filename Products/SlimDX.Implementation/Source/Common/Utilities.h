#pragma once

namespace SlimDX
{	
	ref class Utilities sealed
	{
		public:
			static Utilities();
		
			generic< typename T >
			static System::Guid GetInterfaceID();
		
			generic< typename T >
			static System::Type^ GetInterfaceImplementation();
				
			static IUnknown* ToUnknown( IComObject^ source );
			
			static DXGI_MODE_DESC ToNative( SlimDX::DXGI::DisplayModeDescription^ source );
			static DXGI_RATIONAL ToNative( SlimDX::DXGI::Rational source );
			static DXGI_SAMPLE_DESC ToNative( SlimDX::DXGI::SampleDescription^ source );
			static DXGI_SWAP_CHAIN_DESC ToNative( SlimDX::DXGI::SwapChainDescription^ source );
			
			static System::Guid ToManaged( const GUID& guid );
			static GUID ToNative( System::Guid guid );

		private:
			static System::Collections::Generic::Dictionary<System::Type^, System::Type^>^ m_Implementations;
			static System::Collections::Generic::Dictionary<System::Type^, System::Guid>^ m_IIDs;
	};
}