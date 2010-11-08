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

namespace SlimDX2.DirectWrite
{
    public partial class TextFormat
    {

        /// <summary>	
        ///  Creates a text format object used for text layout with normal weight, style and stretch.
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="fontFamilyName">An array of characters that contains the name of the font family</param>
        /// <param name="fontSize">The logical size of the font in DIP ("device-independent pixel") units. A DIP equals 1/96 inch.</param>
        /// <unmanaged>HRESULT CreateTextFormat([In] const wchar* fontFamilyName,[None] IDWriteFontCollection* fontCollection,[None] DWRITE_FONT_WEIGHT fontWeight,[None] DWRITE_FONT_STYLE fontStyle,[None] DWRITE_FONT_STRETCH fontStretch,[None] FLOAT fontSize,[In] const wchar* localeName,[Out] IDWriteTextFormat** textFormat)</unmanaged>
        public TextFormat(Factory dwriteFactory, string fontFamilyName, float fontSize)
            : this(dwriteFactory, fontFamilyName, null, DirectWrite.FontWeight.Normal, DirectWrite.FontStyle.Normal, DirectWrite.FontStretch.Normal, fontSize, "")
        {
        }

        /// <summary>	
        ///  Creates a text format object used for text layout with normal stretch.
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="fontFamilyName">An array of characters that contains the name of the font family</param>
        /// <param name="fontWeight">A value that indicates the font weight for the text object created by this method.</param>
        /// <param name="fontStyle">A value that indicates the font style for the text object created by this method.</param>
        /// <param name="fontSize">The logical size of the font in DIP ("device-independent pixel") units. A DIP equals 1/96 inch.</param>
        /// <unmanaged>HRESULT CreateTextFormat([In] const wchar* fontFamilyName,[None] IDWriteFontCollection* fontCollection,[None] DWRITE_FONT_WEIGHT fontWeight,[None] DWRITE_FONT_STYLE fontStyle,[None] DWRITE_FONT_STRETCH fontStretch,[None] FLOAT fontSize,[In] const wchar* localeName,[Out] IDWriteTextFormat** textFormat)</unmanaged>
        public TextFormat(Factory dwriteFactory, string fontFamilyName, SlimDX2.DirectWrite.FontWeight fontWeight, SlimDX2.DirectWrite.FontStyle fontStyle, float fontSize)
            : this(dwriteFactory, fontFamilyName, null, fontWeight, fontStyle, DirectWrite.FontStretch.Normal, fontSize, "")
        {
        }

        /// <summary>	
        ///  Creates a text format object used for text layout. 	
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="fontFamilyName">An array of characters that contains the name of the font family</param>
        /// <param name="fontWeight">A value that indicates the font weight for the text object created by this method.</param>
        /// <param name="fontStyle">A value that indicates the font style for the text object created by this method.</param>
        /// <param name="fontStretch">A value that indicates the font stretch for the text object created by this method.</param>
        /// <param name="fontSize">The logical size of the font in DIP ("device-independent pixel") units. A DIP equals 1/96 inch.</param>
        /// <unmanaged>HRESULT CreateTextFormat([In] const wchar* fontFamilyName,[None] IDWriteFontCollection* fontCollection,[None] DWRITE_FONT_WEIGHT fontWeight,[None] DWRITE_FONT_STYLE fontStyle,[None] DWRITE_FONT_STRETCH fontStretch,[None] FLOAT fontSize,[In] const wchar* localeName,[Out] IDWriteTextFormat** textFormat)</unmanaged>
        public TextFormat(Factory dwriteFactory, string fontFamilyName, SlimDX2.DirectWrite.FontWeight fontWeight, SlimDX2.DirectWrite.FontStyle fontStyle, SlimDX2.DirectWrite.FontStretch fontStretch, float fontSize)
            : this(dwriteFactory, fontFamilyName, null, fontWeight, fontStyle, fontStretch, fontSize, "")
        {
        }

        /// <summary>	
        ///  Creates a text format object used for text layout. 	
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="fontFamilyName">An array of characters that contains the name of the font family</param>
        /// <param name="fontCollection">A pointer to a font collection object. When this is NULL, indicates the system font collection.</param>
        /// <param name="fontWeight">A value that indicates the font weight for the text object created by this method.</param>
        /// <param name="fontStyle">A value that indicates the font style for the text object created by this method.</param>
        /// <param name="fontStretch">A value that indicates the font stretch for the text object created by this method.</param>
        /// <param name="fontSize">The logical size of the font in DIP ("device-independent pixel") units. A DIP equals 1/96 inch.</param>
        /// <unmanaged>HRESULT CreateTextFormat([In] const wchar* fontFamilyName,[None] IDWriteFontCollection* fontCollection,[None] DWRITE_FONT_WEIGHT fontWeight,[None] DWRITE_FONT_STYLE fontStyle,[None] DWRITE_FONT_STRETCH fontStretch,[None] FLOAT fontSize,[In] const wchar* localeName,[Out] IDWriteTextFormat** textFormat)</unmanaged>
        public TextFormat(Factory dwriteFactory, string fontFamilyName, SlimDX2.DirectWrite.FontCollection fontCollection, SlimDX2.DirectWrite.FontWeight fontWeight, SlimDX2.DirectWrite.FontStyle fontStyle, SlimDX2.DirectWrite.FontStretch fontStretch, float fontSize)
            : this(dwriteFactory, fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize,"")
        {
        }

        /// <summary>	
        ///  Creates a text format object used for text layout. 	
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="fontFamilyName">An array of characters that contains the name of the font family</param>
        /// <param name="fontCollection">A pointer to a font collection object. When this is NULL, indicates the system font collection.</param>
        /// <param name="fontWeight">A value that indicates the font weight for the text object created by this method.</param>
        /// <param name="fontStyle">A value that indicates the font style for the text object created by this method.</param>
        /// <param name="fontStretch">A value that indicates the font stretch for the text object created by this method.</param>
        /// <param name="fontSize">The logical size of the font in DIP ("device-independent pixel") units. A DIP equals 1/96 inch.</param>
        /// <param name="localeName">An array of characters that contains the locale name.</param>
        /// <unmanaged>HRESULT CreateTextFormat([In] const wchar* fontFamilyName,[None] IDWriteFontCollection* fontCollection,[None] DWRITE_FONT_WEIGHT fontWeight,[None] DWRITE_FONT_STYLE fontStyle,[None] DWRITE_FONT_STRETCH fontStretch,[None] FLOAT fontSize,[In] const wchar* localeName,[Out] IDWriteTextFormat** textFormat)</unmanaged>
        public TextFormat(Factory dwriteFactory, string fontFamilyName, SlimDX2.DirectWrite.FontCollection fontCollection, SlimDX2.DirectWrite.FontWeight fontWeight, SlimDX2.DirectWrite.FontStyle fontStyle, SlimDX2.DirectWrite.FontStretch fontStretch, float fontSize, string localeName) : base(IntPtr.Zero)
        {
            TextFormat temp;
            dwriteFactory.CreateTextFormat(fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, out temp);
            NativePointer = temp.NativePointer;
        }
    }
}
