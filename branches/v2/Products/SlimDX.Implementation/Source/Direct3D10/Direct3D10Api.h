
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
				virtual IEffect10^ CreateEffect(IDevice10^ device, System::String^ filename, System::String^ shaderProfile, ShaderFlags10 shaderFlags, EffectFlags10 effectFlags);

				virtual SlimDX::Result CreateDeviceAndSwapChain( SlimDX::DXGI::IAdapterDXGI^ adapter, DriverType10 driverType, DeviceCreationFlags10 creationFlags, SlimDX::DXGI::SwapChainDescription^ swapChainDescription, [Out] IDevice10^% device, [Out] SlimDX::DXGI::ISwapChainDXGI^% swapChain );
		};
	}
}