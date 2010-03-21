namespace SlimDX.Direct3D10 {
    public struct BufferDescription {
        public int SizeInBytes { get; set; }
        public int Usage { get; set; }
        public BindFlags BindFlags { get; set; }
        public CpuAccessFlags CpuAccessFlags { get; set; }
        public int OptionFlags { get; set; }
    }
}
