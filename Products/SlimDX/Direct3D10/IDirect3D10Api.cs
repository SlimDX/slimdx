using System;

using SlimDX.Direct3D10;
using SlimDX.DXGI;

namespace SlimDX.Direct3D10 {
    public interface IDirect3D10Api {
        IDevice10 CreateDevice();

        Result CreateDeviceAndSwapChain( IAdapterDXGI adapter, DriverType driverType, DeviceCreationFlags creationFlags, SwapChainDescription swapChainDescription, out IDevice10 device, out ISwapChainDXGI swapChain );
        
        T CreateWrapper<T>( IntPtr pointer ) where T : IComObject;
    }
}
