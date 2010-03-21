namespace SlimDX.DXGI {
    public interface ISwapChainDXGI : IComObject {
        T GetBuffer<T>( int index );
    }
}
