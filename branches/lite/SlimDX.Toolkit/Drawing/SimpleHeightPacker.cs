using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Performs rectangle packing by tracking heights and attempting to place each rectangle at the lowest Y-position possible.
    /// </summary>
    public class SimpleHeightPacker : IRectanglePacker
    {
        int totalWidth;
        int totalHeight;
        int[] heights;

        /// <summary>
        /// Initializes a new instance of the <see cref="SimpleHeightPacker"/> class.
        /// </summary>
        public SimpleHeightPacker()
        {
        }

        /// <summary>
        /// Defines the area of the packing region.
        /// </summary>
        /// <param name="width">The width of the packing region.</param>
        /// <param name="height">The height of the packing region.</param>
        public void DefineArea(int width, int height)
        {
            totalWidth = width;
            totalHeight = height;

            heights = new int[totalWidth];
        }

        /// <summary>
        /// Attempts to pack the given rectangle into the region.
        /// </summary>
        /// <param name="width">The width of the rectangle to pack.</param>
        /// <param name="height">The height of the rectangle to pack.</param>
        /// <param name="placement">Returns the (x,y) coordinates of the packed location, if the method succeeds.</param>
        /// <returns>
        ///   <c>true</c> if the rectangle was successfully packed; otherwise, <c>false</c>.
        /// </returns>
        public bool TryPack(int width, int height, out Point placement)
        {
            // a rectangle bigger than the whole area will obviously not fit
            placement = Point.Empty;
            if (width > totalWidth || height > totalHeight)
                return false;

            int currentMax = FindMax(0, width);
            int currentMin = currentMax;
            int minX = 0;

            // find the lowest Y value we can fit into nicely
            for (int i = 1; i < totalWidth - width; i++)
            {
                if (heights[i + width - 1] >= currentMax)
                    currentMax = heights[i + width - 1];
                else if (heights[i - 1] == currentMax)
                {
                    currentMax = FindMax(i, width);
                    if (currentMax < currentMin)
                    {
                        currentMin = currentMax;
                        minX = i;
                    }
                }
            }

            if (currentMin + height > totalHeight)
                return false;

            // update the heights for the new area we're adding to
            for (int i = 0; i < width; ++i)
                heights[minX + i] = height;

            placement = new Point(minX, currentMin);
            return false;
        }

        int FindMax(int startX, int width)
        {
            int currentMax = heights[startX];
            for (int i = 1; i < width; ++i)
                currentMax = Math.Max(currentMax, heights[startX + i]);

            return currentMax;
        }
    }
}
