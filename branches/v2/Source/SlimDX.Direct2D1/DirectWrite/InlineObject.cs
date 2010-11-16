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

namespace SlimDX.DirectWrite
{
    public partial class InlineObject
    {
        /// <summary>	
        ///  The application implemented rendering callback (<see cref="SlimDX.DirectWrite.TextRenderer.DrawInlineObject"/>) can use this to draw the inline object without needing to cast or query the object type. The text layout does not call this method directly. 	
        /// </summary>	
        /// <param name="clientDrawingContext">The drawing context passed to <see cref="SlimDX.DirectWrite.TextLayout.Draw_"/>.  This parameter may be NULL.</param>
        /// <param name="renderer">The same renderer passed to <see cref="SlimDX.DirectWrite.TextLayout.Draw_"/> as the object's containing parent.  This is useful if the inline object is recursive such as a nested layout.</param>
        /// <param name="originX">The x-coordinate at the upper-left corner of the inline object.</param>
        /// <param name="originY">The y-coordinate at the upper-left corner of the inline object.</param>
        /// <param name="isSideways">A Boolean flag that indicates whether the object's baseline runs alongside the baseline axis of the line.</param>
        /// <param name="isRightToLeft">A Boolean flag that indicates whether the object is in a right-to-left context and should be drawn flipped.</param>
        /// <param name="clientDrawingEffect">The drawing effect set in <see cref="SlimDX.DirectWrite.TextLayout.SetDrawingEffect"/>.  Usually this effect is a foreground brush that  is used in glyph drawing.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Draw([None] void* clientDrawingContext,[None] IDWriteTextRenderer* renderer,[None] FLOAT originX,[None] FLOAT originY,[None] BOOL isSideways,[None] BOOL isRightToLeft,[None] IUnknown* clientDrawingEffect)</unmanaged>
        public SlimDX.Result Draw(IntPtr clientDrawingContext, TextRenderer renderer, float originX, float originY, bool isSideways, bool isRightToLeft, SlimDX.ComObject clientDrawingEffect)
        {
            var callback = new TextRendererCallback(renderer);
            return this.Draw_(clientDrawingContext, callback.NativePointer, originX, originY, isSideways, isRightToLeft, clientDrawingEffect);
        }
    }
}
