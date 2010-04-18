/* Copyright (c) 2007-2010 SlimDX Group
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

namespace SlimDX.DXGI {
    /// <summary>
    /// 
    /// </summary>
    public enum Format : int {
        /// <summary>
        /// 
        /// </summary>
        Unknown = 0,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32A32_Typeless = 1,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32A32_Float = 2,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32A32_Unsigned = 3,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32A32_Signed = 4,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32_TYPELESS = 5,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32_FLOAT = 6,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32_UINT = 7,

        /// <summary>
        /// 
        /// </summary>
        R32G32B32_SINT = 8,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_TYPELESS = 9,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_FLOAT = 10,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_UNORM = 11,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_UINT = 12,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_SNORM = 13,

        /// <summary>
        /// 
        /// </summary>
        R16G16B16A16_SINT = 14,

        /// <summary>
        /// 
        /// </summary>
        R32G32_TYPELESS = 15,

        /// <summary>
        /// 
        /// </summary>
        R32G32_FLOAT = 16,

        /// <summary>
        /// 
        /// </summary>
        R32G32_UINT = 17,

        /// <summary>
        /// 
        /// </summary>
        R32G32_SINT = 18,

        /// <summary>
        /// 
        /// </summary>
        R32G8X24_TYPELESS = 19,

        /// <summary>
        /// 
        /// </summary>
        D32_FLOAT_S8X24_UINT = 20,

        /// <summary>
        /// 
        /// </summary>
        R32_FLOAT_X8X24_TYPELESS = 21,

        /// <summary>
        /// 
        /// </summary>
        X32_TYPELESS_G8X24_UINT = 22,

        /// <summary>
        /// 
        /// </summary>
        R10G10BA2_TYPELESS = 23,

        /// <summary>
        /// 
        /// </summary>
        R10G10BA2_UNORM = 24,

        /// <summary>
        /// 
        /// </summary>
        R10G10BA2_UINT = 25,

        /// <summary>
        /// 
        /// </summary>
        R11G11B_FLOAT = 26,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_TYPELESS = 27,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_UNORM = 28,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_UNORM_SRGB = 29,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_UINT = 30,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_SNORM = 31,

        /// <summary>
        /// 
        /// </summary>
        R8G8B8A8_SINT = 32,

        /// <summary>
        /// 
        /// </summary>
        R16G16_TYPELESS = 33,

        /// <summary>
        /// 
        /// </summary>
        R16G16_FLOAT = 34,

        /// <summary>
        /// 
        /// </summary>
        R16G16_UNORM = 35,

        /// <summary>
        /// 
        /// </summary>
        R16G16_UINT = 36,

        /// <summary>
        /// 
        /// </summary>
        R16G16_SNORM = 37,

        /// <summary>
        /// 
        /// </summary>
        R16G16_SINT = 38,

        /// <summary>
        /// 
        /// </summary>
        R32_TYPELESS = 39,

        /// <summary>
        /// 
        /// </summary>
        D32_FLOAT = 40,

        /// <summary>
        /// 
        /// </summary>
        R32_FLOAT = 41,

        /// <summary>
        /// 
        /// </summary>
        R32_UINT = 42,

        /// <summary>
        /// 
        /// </summary>
        R32_SINT = 43,

        /// <summary>
        /// 
        /// </summary>
        R24G8_TYPELESS = 44,

        /// <summary>
        /// 
        /// </summary>
        D24_UNORM_S8_UINT = 45,

        /// <summary>
        /// 
        /// </summary>
        R24_UNORM_X8_TYPELESS = 46,

        /// <summary>
        /// 
        /// </summary>
        X24_TYPELESS_G8_UINT = 47,

        /// <summary>
        /// 
        /// </summary>
        R8G8_TYPELESS = 48,

        /// <summary>
        /// 
        /// </summary>
        R8G8_UNORM = 49,

        /// <summary>
        /// 
        /// </summary>
        R8G8_UINT = 50,

        /// <summary>
        /// 
        /// </summary>
        R8G8_SNORM = 51,

        /// <summary>
        /// 
        /// </summary>
        R8G8_SINT = 52,

        /// <summary>
        /// 
        /// </summary>
        R16_TYPELESS = 53,

        /// <summary>
        /// 
        /// </summary>
        R16_FLOAT = 54,

        /// <summary>
        /// 
        /// </summary>
        D16_UNORM = 55,

        /// <summary>
        /// 
        /// </summary>
        R16_UNORM = 56,

        /// <summary>
        /// 
        /// </summary>
        R16_UINT = 57,

        /// <summary>
        /// 
        /// </summary>
        R16_SNORM = 58,

        /// <summary>
        /// 
        /// </summary>
        R16_SINT = 59,

        /// <summary>
        /// 
        /// </summary>
        R8_TYPELESS = 60,

        /// <summary>
        /// 
        /// </summary>
        R8_UNORM = 61,

        /// <summary>
        /// 
        /// </summary>
        R8_UINT = 62,

        /// <summary>
        /// 
        /// </summary>
        R8_SNORM = 63,

        /// <summary>
        /// 
        /// </summary>
        R8_SINT = 64,

        /// <summary>
        /// 
        /// </summary>
        A8_UNORM = 65,

        /// <summary>
        /// 
        /// </summary>
        R1_UNORM = 66,

        /// <summary>
        /// 
        /// </summary>
        R9G9B9E5_SHAREDEXP = 67,

        /// <summary>
        /// 
        /// </summary>
        R8G8_B8G8_UNORM = 68,

        /// <summary>
        /// 
        /// </summary>
        G8R8_G8B8_UNORM = 69,

        /// <summary>
        /// 
        /// </summary>
        BC1_TYPELESS = 70,

        /// <summary>
        /// 
        /// </summary>
        BC1_UNORM = 71,

        /// <summary>
        /// 
        /// </summary>
        BC1_UNORM_SRGB = 72,

        /// <summary>
        /// 
        /// </summary>
        BC2_TYPELESS = 73,

        /// <summary>
        /// 
        /// </summary>
        BC2_UNORM = 74,

        /// <summary>
        /// 
        /// </summary>
        BC2_UNORM_SRGB = 75,

        /// <summary>
        /// 
        /// </summary>
        BC3_TYPELESS = 76,

        /// <summary>
        /// 
        /// </summary>
        BC3_UNORM = 77,

        /// <summary>
        /// 
        /// </summary>
        BC3_UNORM_SRGB = 78,

        /// <summary>
        /// 
        /// </summary>
        BC4_TYPELESS = 79,

        /// <summary>
        /// 
        /// </summary>
        BC4_UNORM = 80,

        /// <summary>
        /// 
        /// </summary>
        BC4_SNORM = 81,

        /// <summary>
        /// 
        /// </summary>
        BC5_TYPELESS = 82,

        /// <summary>
        /// 
        /// </summary>
        BC5_UNORM = 83,

        /// <summary>
        /// 
        /// </summary>
        BC5_SNORM = 84,

        /// <summary>
        /// 
        /// </summary>
        B5G6R5_UNORM = 85,

        /// <summary>
        /// 
        /// </summary>
        B5G5R5A1_UNORM = 86,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8A8_UNORM = 87,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8X8_UNORM = 88,

        /// <summary>
        /// 
        /// </summary>
        R10G10B_XR_BIAS_A2_UNORM = 89,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8A8_TYPELESS = 90,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8A8_UNORM_SRGB = 91,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8X8_TYPELESS = 92,

        /// <summary>
        /// 
        /// </summary>
        B8G8R8X8_UNORM_SRGB = 93,

        /// <summary>
        /// 
        /// </summary>
        BC6H_TYPELESS = 94,

        /// <summary>
        /// 
        /// </summary>
        BC6H_UF16 = 95,

        /// <summary>
        /// 
        /// </summary>
        BC6H_SF16 = 96,

        /// <summary>
        /// 
        /// </summary>
        BC7_TYPELESS = 97,

        /// <summary>
        /// 
        /// </summary>
        BC7_UNORM = 98,

        /// <summary>
        /// 
        /// </summary>
        BC7_UNORM_SRGB = 99,
    }
}
