namespace SlimDX.DXGI {
    public interface IFactoryDXGI : IObjectDXGI {
        ISwapChainDXGI CreateSwapChain( IComObject device, SwapChainDescription description );
    }
}
