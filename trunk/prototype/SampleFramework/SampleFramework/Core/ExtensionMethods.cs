using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains various extension methods for use with the sample framework.
    /// </summary>
    public static class ExtensionMethods
    {
        /// <summary>
        /// Finds the best match in the collection.
        /// </summary>
        /// <typeparam name="TSource">The type of the source.</typeparam>
        /// <typeparam name="TRank">The type of the rank.</typeparam>
        /// <param name="source">The source collection.</param>
        /// <param name="func">The ranking function.</param>
        /// <returns>The highest ranked match.</returns>
        public static TSource BestMatch<TSource, TRank>(this IEnumerable<TSource> source, Func<TSource, TRank> func)
        {
            // call the overload
            return BestMatch(source, func, Comparer<TRank>.Default);
        }

        /// <summary>
        /// Finds the best match in the collection.
        /// </summary>
        /// <typeparam name="TSource">The type of the source.</typeparam>
        /// <typeparam name="TRank">The type of the rank.</typeparam>
        /// <param name="source">The source collection.</param>
        /// <param name="func">The ranking function.</param>
        /// <param name="comparer">The comparer.</param>
        /// <returns>The highest ranked match.</returns>
        public static TSource BestMatch<TSource, TRank>(this IEnumerable<TSource> source, Func<TSource, TRank> func, IComparer<TRank> comparer)
        {
            // find the best match
            TRank currentRank = default(TRank);
            TSource result = default(TSource);

            // apply the function to each element
            foreach (TSource item in source)
            {
                // apply the function
                TRank rank = func.Invoke(item);
                if (comparer.Compare(rank, currentRank) > 0)
                {
                    // we found a new best match
                    currentRank = rank;
                    result = item;
                }
            }

            // return the best match
            return result;
        }

        /// <summary>
        /// Gets the depth bits in a format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The number of bits in the format dedicated to depth information.</returns>
        public static int GetDepthBits(this Format format)
        {
            // check the format
            switch (format)
            {
                // 32 bit
                case Format.D32SingleLockable:
                case Format.D32:
                    return 32;

                // 24 bit
                case Format.D24X8:
                case Format.D24S8:
                case Format.D24X4S4:
                case Format.D24SingleS8:
                    return 24;

                // 16 bit
                case Format.D16Lockable:
                case Format.D16:
                    return 16;

                // 15 bit
                case Format.D15S1:
                    return 15;

                // unknown / no bits
                default:
                    return 0;
            }
        }

        /// <summary>
        /// Gets the stencil bits in a format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The number of bits in the format dedicated to stencil information.</returns>
        public static int GetStencilBits(this Format format)
        {
            // check the format
            switch (format)
            {
                // 1 bit
                case Format.D15S1:
                    return 1;

                // 4 bits
                case Format.D24X4S4:
                    return 4;

                // 8 bits
                case Format.D24S8:
                case Format.D24SingleS8:
                    return 8;

                // unknown / 0 bits
                default:
                    return 0;
            }
        }

        /// <summary>
        /// Gets the color bits in a format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The number of bits in the format dedicated to color information.</returns>
        public static int GetColorBits(this Format format)
        {
            // check the format
            switch (format)
            {
                // 8 bits
                case Format.R8G8B8:
                case Format.A8R8G8B8:
                case Format.A8B8G8R8:
                case Format.X8R8G8B8:
                    return 8;

                // 5 bits
                case Format.R5G6B5:
                case Format.X1R5G5B5:
                case Format.A1R5G5B5:
                    return 5;

                // 4 bits
                case Format.A4R4G4B4:
                case Format.X4R4G4B4:
                    return 4;

                // 2 bits
                case Format.R3G3B2:
                case Format.A8R3G3B2:
                    return 2;

                // 10 bits
                case Format.A2R10G10B10:
                case Format.A2B10G10R10:
                    return 10;

                // 16 bits
                case Format.A16B16G16R16:
                    return 16;

                // unknown / 0 bits
                default:
                    return 0;
            }
        }
    }
}
