
using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Direct3D10Api : IDirect3D10Api
		{
			public:
				Direct3D10Api();
				
				generic< typename T >
				virtual T CreateWrapper( System::IntPtr pointer );
					
				virtual IDevice10^ CreateDevice();
				
				virtual SlimDX::Result CreateDeviceAndSwapChain( SlimDX::DXGI::IAdapterDXGI^ adapter, DriverType driverType, DeviceCreationFlags creationFlags, SlimDX::DXGI::SwapChainDescription^ swapChainDescription, [Out] IDevice10^% device, [Out] SlimDX::DXGI::ISwapChainDXGI^% swapChain );
		};
	}
}