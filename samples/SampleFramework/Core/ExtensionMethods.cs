/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using SlimDX;
using SlimDX.Direct3D9;
using D3D10 = SlimDX.Direct3D10;
using DXGI = SlimDX.DXGI;

namespace SampleFramework
{
    /// <summary>
    /// Contains various extension methods for use with the sample framework.
    /// </summary>
    static class ExtensionMethods
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

        /// <summary>
        /// Gets the color bits in a format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The number of bits in the format dedicated to color information.</returns>
        public static int GetColorBits(this DXGI.Format format)
        {
            // check the format
            switch (format)
            {
                // 32 bits
                case SlimDX.DXGI.Format.R32G32B32A32_Float:
                case SlimDX.DXGI.Format.R32G32B32A32_SInt:
                case SlimDX.DXGI.Format.R32G32B32A32_Typeless:
                case SlimDX.DXGI.Format.R32G32B32A32_UInt:
                case SlimDX.DXGI.Format.R32G32B32_Float:
                case SlimDX.DXGI.Format.R32G32B32_SInt:
                case SlimDX.DXGI.Format.R32G32B32_Typeless:
                case SlimDX.DXGI.Format.R32G32B32_UInt:
                    return 32;

                // 16 bits
                case SlimDX.DXGI.Format.R16G16B16A16_Float:
                case SlimDX.DXGI.Format.R16G16B16A16_SInt:
                case SlimDX.DXGI.Format.R16G16B16A16_SNorm:
                case SlimDX.DXGI.Format.R16G16B16A16_Typeless:
                case SlimDX.DXGI.Format.R16G16B16A16_UInt:
                case SlimDX.DXGI.Format.R16G16B16A16_UNorm:
                    return 16;

                // 10 bits
                case SlimDX.DXGI.Format.R10G10B10A2_Typeless:
                case SlimDX.DXGI.Format.R10G10B10A2_UInt:
                case SlimDX.DXGI.Format.R10G10B10A2_UNorm:
                    return 10;

                // 8 bits
                case SlimDX.DXGI.Format.R8G8B8A8_SInt:
                case SlimDX.DXGI.Format.R8G8B8A8_SNorm:
                case SlimDX.DXGI.Format.R8G8B8A8_Typeless:
                case SlimDX.DXGI.Format.R8G8B8A8_UInt:
                case SlimDX.DXGI.Format.R8G8B8A8_UNorm:
                case SlimDX.DXGI.Format.R8G8B8A8_UNorm_SRGB:
                    return 8;

                // 5 bits
                case SlimDX.DXGI.Format.B5G5R5A1_UNorm:
                case SlimDX.DXGI.Format.B5G6R5_UNorm:
                    return 5;

                // unknown / 0 bits
                default:
                    return 0;
            }
        }

        /// <summary>
        /// Converts a Direct3D9 device type to a Direct3D10 driver type.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>The equivalent driver type.</returns>
        public static D3D10.DriverType ToDirect3D10(this DeviceType type)
        {
            // return the correct value
            if (type == DeviceType.Hardware)
                return SlimDX.Direct3D10.DriverType.Hardware;
            else if (type == DeviceType.Reference)
                return SlimDX.Direct3D10.DriverType.Reference;
            else if (type == DeviceType.Software)
                return SlimDX.Direct3D10.DriverType.Software;
            else
                return SlimDX.Direct3D10.DriverType.Null;
        }

        /// <summary>
        /// Converts a Direct3D10 driver type to a Direct3D9 device type.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>The equivalent device type.</returns>
        public static DeviceType ToDirect3D9(this D3D10.DriverType type)
        {
            // return the correct value
            if (type == SlimDX.Direct3D10.DriverType.Hardware)
                return DeviceType.Hardware;
            else if (type == SlimDX.Direct3D10.DriverType.Reference)
                return DeviceType.Reference;
            else if (type == SlimDX.Direct3D10.DriverType.Software)
                return DeviceType.Software;
            else
                return DeviceType.NullReference;
        }

        /// <summary>
        /// Converts a Direct3D9 multisample type to a Direct3D10 multisample count.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <param name="quality">The quality.</param>
        /// <returns>The equivalent multisample count.</returns>
        public static int ToDirect3D10(this MultisampleType type, int quality)
        {
            // convert the value
            if (type == MultisampleType.NonMaskable)
                return quality;
            else
                return (int)type;
        }

        /// <summary>
        /// Converts a Direct3D10 multisample count to a Direct3D9 multisample type.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>The equivalent multisample type.</returns>
        public static MultisampleType ToDirect3D9(this int type)
        {
            // return the correct value
            return (MultisampleType)type;
        }

        /// <summary>
        /// Converts a Direct3D9 surface format to a Direct3D10 surface format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The equivalent format.</returns>
        public static DXGI.Format ToDirect3D10(this Format format)
        {
            // return the appropriate format
            switch (format)
            {
                case Format.R8G8B8:
                case Format.A8R8G8B8:
                case Format.X8R8G8B8:
                case Format.A4R4G4B4:
                case Format.R3G3B2:
                case Format.A8R3G3B2:
                case Format.X4R4G4B4:
                    return SlimDX.DXGI.Format.R8G8B8A8_UNorm;
                case Format.R5G6B5:
                    return SlimDX.DXGI.Format.B5G6R5_UNorm;
                case Format.X1R5G5B5:
                case Format.A1R5G5B5:
                    return SlimDX.DXGI.Format.B5G5R5A1_UNorm;
                case Format.A8:
                    return SlimDX.DXGI.Format.A8_UNorm;
                case Format.A2B10G10R10:
                case Format.A2R10G10B10:
                    return SlimDX.DXGI.Format.R10G10B10A2_UNorm;
                case Format.A8B8G8R8:
                case Format.X8B8G8R8:
                    return SlimDX.DXGI.Format.B8G8R8A8_UNorm;
                case Format.G16R16:
                    return SlimDX.DXGI.Format.R16G16_UNorm;
                case Format.A16B16G16R16:
                    return SlimDX.DXGI.Format.R16G16B16A16_UNorm;
                case Format.R16F:
                    return SlimDX.DXGI.Format.R16_Float;
                case Format.G16R16F:
                    return SlimDX.DXGI.Format.R16G16_Float;
                case Format.A16B16G16R16F:
                    return SlimDX.DXGI.Format.R16G16B16A16_Float;
                case Format.R32F:
                    return SlimDX.DXGI.Format.R32_Float;
                case Format.G32R32F:
                    return SlimDX.DXGI.Format.R32G32_Float;
                case Format.A32B32G32R32F:
                    return SlimDX.DXGI.Format.R32G32B32A32_Float;
            }

            // otherwise, we don't know the right format
            return SlimDX.DXGI.Format.Unknown;
        }

        /// <summary>
        /// Converts a Direct3D10 surface format to a Direct3D9 surface format.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>The equivalent format.</returns>
        public static Format ToDirect3D9(this DXGI.Format format)
        {
            // return the appropriate format
            switch (format)
            {
                case SlimDX.DXGI.Format.R8G8B8A8_UNorm:
                    return Format.A8R8G8B8;
                case SlimDX.DXGI.Format.B5G6R5_UNorm:
                    return Format.R5G6B5;
                case SlimDX.DXGI.Format.B5G5R5A1_UNorm:
                    return Format.A1R5G5B5;
                case SlimDX.DXGI.Format.A8_UNorm:
                    return Format.A8;
                case SlimDX.DXGI.Format.R10G10B10A2_UNorm:
                    return Format.A2B10G10R10;
                case SlimDX.DXGI.Format.B8G8R8A8_UNorm:
                    return Format.A8B8G8R8;
                case SlimDX.DXGI.Format.R16G16_UNorm:
                    return Format.G16R16;
                case SlimDX.DXGI.Format.R16G16B16A16_UNorm:
                    return Format.A16B16G16R16;
                case SlimDX.DXGI.Format.R16_Float:
                    return Format.R16F;
                case SlimDX.DXGI.Format.R16G16_Float:
                    return Format.G16R16F;
                case SlimDX.DXGI.Format.R16G16B16A16_Float:
                    return Format.A16B16G16R16F;
                case SlimDX.DXGI.Format.R32_Float:
                    return Format.R32F;
                case SlimDX.DXGI.Format.R32G32_Float:
                    return Format.G32R32F;
                case SlimDX.DXGI.Format.R32G32B32A32_Float:
                    return Format.A32B32G32R32F;
            }

            // otherwise, we don't know the right format
            return Format.Unknown;
        }

        /// <summary>
        /// Converts a rational to a floating point value.
        /// </summary>
        /// <param name="rational">The rational.</param>
        /// <returns>The floating point value.</returns>
        public static float ToFloat(this Rational rational)
        {
            // make sure there are no divide-by-zero errors when we convert
            float denom = 1;
            if (rational.Denominator != 0)
                denom = rational.Denominator;
            return rational.Numerator / rational.Denominator;
        }
    }
}
