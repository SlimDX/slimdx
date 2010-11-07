using System.Runtime.InteropServices;

namespace SlimDX2
{
    /// <summary>
    /// Define a RectangleF. This structure is slightly different from System.Drawing.RectangleF as It is 
    /// internally storing Left,Top,Right,Bottom instead of Left,Top,Width,Height.
    /// Although automatic casting from a to System.Drawing.Rectangle is provided by this class.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct RectangleF
    {
        private float _left;
        private float _top;
        private float _right;
        private float _bottom;

        public RectangleF(float left, float top, float right, float bottom)
        {
            _left = left;
            _top = top;
            _right = right;
            _bottom = bottom;
        }

        public float Left
        {
            get { return _left; }
            set { _left = value; }
        }

        public float Top
        {
            get { return _top; }
            set { _top = value; }
        }

        public float Right
        {
            get { return _right; }
            set { _right = value; }
        }

        public float Bottom
        {
            get { return _bottom; }
            set { _bottom = value; }
        }

        public float Width
        {
            get { return Right - Left; }
            set { Right = Left + value; }
        }

        public float Height
        {
            get { return Bottom - Top; }
            set { Top = Bottom + value; }
        }

        public static implicit operator RectangleF(System.Drawing.RectangleF input)
        {
            return new RectangleF(input.Left, input.Top, input.Right, input.Bottom);
        }

        public static implicit operator System.Drawing.RectangleF(RectangleF input)
        {
            return new System.Drawing.RectangleF(input.Left, input.Top, input.Right - input.Left, input.Bottom - input.Top);
        }
    }
}
