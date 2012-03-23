using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Toolkit.Fonts
{
    class HeightRange
    {
        int totalWidth;
        int[] heights;

        public HeightRange(int totalWidth)
        {
            this.totalWidth = totalWidth;
            heights = new int[totalWidth];
        }

        public int FindMin(int width, out int minY)
        {
            if (width > totalWidth)
                width = totalWidth;

            int currentMax = FindMax(0, width);
            int currentMin = currentMax;
            int minX = 0;

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

            minY = currentMin;
            return minX;
        }

        public int FindMax(int startX, int width)
        {
            int currentMax = heights[startX];
            for (int i = 1; i < width; ++i)
                currentMax = Math.Max(currentMax, heights[startX + i]);

            return currentMax;
        }

        public void Update(int startX, int width, int height)
        {
            if (width > totalWidth)
                width = totalWidth;

            for (int i = 0; i < width; ++i)
                heights[startX + i] = height;
        }
    }
}
