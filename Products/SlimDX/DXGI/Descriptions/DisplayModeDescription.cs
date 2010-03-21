namespace SlimDX.DXGI {
    public class DisplayModeDescription {
        public int Width { get; set; }
        public int Height { get; set; }
        public Rational RefreshRate { get; set; }
        public Format Format { get; set; }
        public DisplayModeScanlineOrder ScanlineOrdering { get; set; }
        public DisplayModeScale Scaling { get; set; }
    }
}