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
using System.Drawing;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Represents a single element of a user interface control that can be drawn.
    /// </summary>
    public class DrawingElement : ICloneable
    {
        /// <summary>
        /// Gets or sets the name of the element.
        /// </summary>
        /// <value>The name of the element.</value>
        public string Name
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the texture.
        /// </summary>
        /// <value>The color of the texture.</value>
        public BlendColor TextureColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the font.
        /// </summary>
        /// <value>The color of the font.</value>
        public BlendColor FontColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the text format.
        /// </summary>
        /// <value>The text format.</value>
        public DrawTextFormat TextFormat
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the texture rectangle.
        /// </summary>
        /// <value>The texture rectangle.</value>
        public Rectangle TextureRectangle
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the font.
        /// </summary>
        /// <value>The font.</value>
        public CachedFont CachedFont
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DrawingElement"/> class.
        /// </summary>
        public DrawingElement()
        {
            // set default values
            TextFormat = DrawTextFormat.Center | DrawTextFormat.VerticalCenter;
            FontColor = new BlendColor();
            TextureColor = new BlendColor();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DrawingElement"/> class.
        /// </summary>
        /// <param name="name">The name.</param>
        public DrawingElement(string name)
            : this()
        {
            // store the name
            Name = name;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public DrawingElement Clone()
        {
            // clone each member
            DrawingElement result = new DrawingElement();
            result.Name = Name;
            result.TextFormat = TextFormat;
            result.TextureRectangle = TextureRectangle;
            result.CachedFont = CachedFont;
            result.FontColor = FontColor != null ? FontColor.Clone() : null;
            result.TextureColor = TextureColor != null ? TextureColor.Clone() : null;

            // return the result
            return result;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        object ICloneable.Clone()
        {
            // call the overload
            return Clone();
        }
    }
}
