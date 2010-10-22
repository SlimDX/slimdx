// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;

namespace SlimDX2.Tools.XIDLToCSharp
{
    [Flags]
    public enum FilterFlags : uint
    {
        None = 1,
        Point = 2,
        Linear = 3,
        Triangle = 4,
        Box = 5,
        MirrorU = 65536,
        MirrorV = 131072,
        MirrorW = 262144,
        Mirror = 458752,
        Dither = 524288,
        DitherDiffusion = 1048576,
        SRgbIn = 2097152,
        SRgbOut = 4194304,
        SRgb = 6291456,
    }

    [Flags]
    public enum NormalMapFlags : uint
    {
        MirrorU = 65536,
        MirrorV = 131072,
        Mirror = 196608,
        Invertsign = 524288,
        ComputeOcclusion = 1048576,
        None = 0,
    }

    [Flags]
    public enum ChannelFlags : uint
    {
        Red = 1,
        Blue = 2,
        Green = 4,
        Alpha = 8,
        Luminance = 16,
        None = 0,
    }

    public enum ImageFileFormat : uint
    {
        Bmp = 0,
        Jpg = 1,
        Png = 3,
        Dds = 4,
        Tiff = 10,
        Gif = 11,
        Wmp = 12,
    }

    [Flags]
    public enum SaveTextureFlags : uint
    {
        TfUseinputblob = 1,
        None = 0,
    }
}