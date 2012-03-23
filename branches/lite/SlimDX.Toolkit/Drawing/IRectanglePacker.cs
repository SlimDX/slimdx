using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Defines an interface for rectangle packing algorithms.
    /// </summary>
    public interface IRectanglePacker
    {
        /// <summary>
        /// Defines the area of the packing region.
        /// </summary>
        /// <param name="width">The width of the packing region.</param>
        /// <param name="height">The height of the packing region.</param>
        void DefineArea(int width, int height);

        /// <summary>
        /// Attempts to pack the given rectangle into the region.
        /// </summary>
        /// <param name="width">The width of the rectangle to pack.</param>
        /// <param name="height">The height of the rectangle to pack.</param>
        /// <param name="placement">Returns the (x,y) coordinates of the packed location, if the method succeeds.</param>
        /// <returns><c>true</c> if the rectangle was successfully packed; otherwise, <c>false</c>.</returns>
        bool TryPack(int width, int height, out Point placement);
    }
}
