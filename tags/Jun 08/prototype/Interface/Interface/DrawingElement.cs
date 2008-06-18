using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D9;
using System.Drawing;

namespace Interface
{
    /// <summary>
    /// Represents a single element of a user interface control that can be drawn.
    /// </summary>
    public class DrawingElement : ICloneable
    {
        #region Properties

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

        #endregion

        #region Constructor

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

        #endregion

        #region Methods

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

        #endregion
    }
}
