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
    public partial class TextLayout
    {

        /// <summary>	
        ///  Takes a string, text format, and associated constraints, and produces an object that represents the fully analyzed and formatted result. 	
        /// </summary>	
        /// <param name="dwriteFactory">an instance of <see cref = "SlimDX2.DirectWrite.Factory" /></param>
        /// <param name="text">An array of characters that contains the string to create a new <see cref="SlimDX2.DirectWrite.TextLayout"/> object from. This array must be of length stringLength and can contain embedded NULL characters.</param>
        /// <param name="textFormat">A pointer to an object that indicates the format to apply to the string.</param>
        /// <param name="maxWidth">The width of the layout box.</param>
        /// <param name="maxHeight">The height of the layout box.</param>
        /// <unmanaged>HRESULT CreateTextLayout([In, Buffer] const wchar* string,[None] UINT32 stringLength,[None] IDWriteTextFormat* textFormat,[None] FLOAT maxWidth,[None] FLOAT maxHeight,[Out] IDWriteTextLayout** textLayout)</unmanaged>
        public TextLayout(Factory dwriteFactory, string text, SlimDX2.DirectWrite.TextFormat textFormat, float maxWidth, float maxHeight) : base(IntPtr.Zero)
        {
            TextLayout temp;
            dwriteFactory.CreateTextLayout(text, text.Length, textFormat, maxWidth, maxHeight, out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>	
        ///  Draws text using the specified client drawing context.	
        /// </summary>	
        /// <remarks>	
        /// To draw text with this method, a textLayout object needs to be created by the application using <see cref="SlimDX2.DirectWrite.Factory.CreateTextLayout"/>. After the textLayout object is obtained, the application calls the  IDWriteTextLayout::Draw method  to draw the text, decorations, and inline objects. The actual drawing is done through the callback interface passed in as the textRenderer argument; there, the corresponding DrawGlyphRun API is called. 	
        /// </remarks>	
        /// <param name="renderer">Pointer to the set of callback functions used to draw parts of a text string.</param>
        /// <param name="originX">The x-coordinate of the layout's left side.</param>
        /// <param name="originY">The y-coordinate of the layout's top side.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Draw([None] void* clientDrawingContext,[None] IDWriteTextRenderer* renderer,[None] FLOAT originX,[None] FLOAT originY)</unmanaged>
        public SlimDX2.Result Draw(TextRenderer renderer, float originX, float originY)
        {
            return Draw(IntPtr.Zero, renderer, originX, originY);
        }

        /// <summary>	
        ///  Draws text using the specified client drawing context.	
        /// </summary>	
        /// <remarks>	
        /// To draw text with this method, a textLayout object needs to be created by the application using <see cref="SlimDX2.DirectWrite.Factory.CreateTextLayout"/>. After the textLayout object is obtained, the application calls the  IDWriteTextLayout::Draw method  to draw the text, decorations, and inline objects. The actual drawing is done through the callback interface passed in as the textRenderer argument; there, the corresponding DrawGlyphRun API is called. 	
        /// </remarks>	
        /// <param name="clientDrawingContext">An application-defined drawing context. </param>
        /// <param name="renderer">Pointer to the set of callback functions used to draw parts of a text string.</param>
        /// <param name="originX">The x-coordinate of the layout's left side.</param>
        /// <param name="originY">The y-coordinate of the layout's top side.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Draw([None] void* clientDrawingContext,[None] IDWriteTextRenderer* renderer,[None] FLOAT originX,[None] FLOAT originY)</unmanaged>
        public SlimDX2.Result Draw(IntPtr clientDrawingContext, TextRenderer renderer, float originX, float originY) {
            var callback = new TextRendererCallback(renderer);
            return this.Draw_(clientDrawingContext, callback.NativePointer, originX, originY);
        }
    }
}
