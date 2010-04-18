
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
					
				virtual IDevice^ CreateDevice();
				virtual IEffect^ CreateEffect(IDevice^ device, System::String^ filename, System::String^ shaderProfile, ShaderFlags shaderFlags, EffectFlags effectFlags);

				virtual SlimDX::Result CreateDeviceAndSwapChain( SlimDX::DXGI::IAdapter^ adapter, DriverType driverType, DeviceCreationFlags creationFlags, SlimDX::DXGI::SwapChainDescription^ swapChainDescription, [Out] IDevice^% device, [Out] SlimDX::DXGI::ISwapChain^% swapChain );
		};
	}
}