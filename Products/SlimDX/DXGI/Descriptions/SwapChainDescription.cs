using System;

namespace SlimDX.DXGI {
    public class SwapChainDescription {
        public DisplayModeDescription BufferDescription { get; set; }
        public SampleDescription SampleDescription { get; set; }
        public Usage BufferUsage { get; set; }
        public int BufferCount { get; set; }
        public IntPtr OutputWindow { get; set; }
        public bool IsWindowed { get; set; }
        public SwapEffect SwapEffect { get; set; }
        public SwapChainFlags Flags { get; set; }
    }
}
