using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimDX.Direct3D10 {
    [StructLayout(LayoutKind.Sequential)]
    public struct Viewport {
        public Viewport(int x, int y, int width, int height, float minDepth, float maxDepth) {
            topLeftX = x;
            topLeftY = y;
            this.width = width;
            this.height = height;
            this.minDepth = minDepth;
            this.maxDepth = maxDepth;
        }

        private int topLeftX;
        public int TopLeftX {
            get { return topLeftX; }
            set { topLeftX = value; }
        }

        private int topLeftY;
        public int TopLeftY {
            get { return topLeftY; }
            set { topLeftY = value; }
        }

        private int width;
        public int Width {
            get { return width; }
            set { width = value; }
        }

        private int height;
        public int Height {
            get { return height; }
            set { height = value; }
        }

        private float minDepth;
        public float MinDepth {
            get { return minDepth; }
            set { minDepth = value; }
        }

        private float maxDepth;
        public float MaxDepth {
            get { return maxDepth; }
            set { maxDepth = value; }
        }
    }
}
