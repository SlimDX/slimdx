using System.Runtime.InteropServices;

namespace SlimDX2
{
    /// <summary>
    /// Define a Rectangle. This structure is slightly different from System.Drawing.Rectangle as It is 
    /// internally storing Left,Top,Right,Bottom instead of Left,Top,Width,Height.
    /// Although automatic casting from a to System.Drawing.Rectangle is provided by this class.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Rectangle
    {
        private int _left;
        private int _top;
        private int _right;
        private int _bottom;

        public Rectangle(int left, int top, int right, int bottom)
        {
            _left = left;
            _top = top;
            _right = right;
            _bottom = bottom;
        }

        public int Left
        {
            get { return _left; }
            set { _left = value; }
        }

        public int Top
        {
            get { return _top; }
            set { _top = value; }
        }

        public int Right
        {
            get { return _right; }
            set { _right = value; }
        }

        public int Bottom
        {
            get { return _bottom; }
            set { _bottom = value; }
        }

        public int Width
        {
            get { return Right - Left; }
            set { Right = Left + value; }
        }

        public int Height
        {
            get { return Bottom - Top; }
            set { Top = Bottom + value; }
        }

        public static implicit operator Rectangle(System.Drawing.Rectangle input)
        {
            return new Rectangle(input.Left, input.Top, input.Right, input.Bottom);
        }

        public static implicit operator System.Drawing.Rectangle(Rectangle input)
        {
            return new System.Drawing.Rectangle(input.Left, input.Top, input.Right-input.Left, input.Bottom-input.Top);
        }
    }
}
