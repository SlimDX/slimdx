namespace SlimDX.Direct3D10 {
    public interface IBuffer10 : IComObject {
        BufferDescription Description { get; }
        
        void Map();
        void Unmap();
    }
}
