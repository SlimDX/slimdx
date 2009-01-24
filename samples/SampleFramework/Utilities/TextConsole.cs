/*
* Copyright (c) 2007-2009 SlimDX Group
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
using System.Drawing;
using SlimDX;
using SlimDX.Direct3D9;
using System;

namespace SampleFramework
{
    /// <summary>
    /// Represents a specific on-screen region where text will be rendered.
    /// </summary>
    public sealed class TextConsole : IResource
    {
        GraphicsDeviceManager manager;
        Sprite sprite;
        SlimDX.Direct3D9.Font font;
        string fontName;
        int fontSize;
        FontWeight fontWeight;
        bool dirty;

        private Point m_Location;
        /// <summary>
        /// Gets or sets the location.
        /// </summary>
        /// <value>The location.</value>
        public Point Location
        {
            get { return m_Location; }
            set { m_Location = value;}
        }

        private Color4 m_ForegroundColor;
        /// <summary>
        /// Gets or sets the color of the foreground.
        /// </summary>
        /// <value>The color of the foreground.</value>
        public Color4 ForegroundColor
        {
            get { return m_ForegroundColor; }
            set { m_ForegroundColor = value; }
        }

		private int m_LineHeight;
        /// <summary>
        /// Gets or sets the height of a line.
        /// </summary>
        /// <value>The height of a line.</value>
        public int LineHeight
        {
			get { return m_LineHeight; }
			set { m_LineHeight = value; }
        }

        /// <summary>
        /// Gets or sets the name of the font.
        /// </summary>
        /// <value>The name of the font.</value>
        public string FontName
        {
            get { return fontName; }
            set
            {
                if (fontName == value)
                    return;

                fontName = value;
                dirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the size of the font.
        /// </summary>
        /// <value>The size of the font.</value>
        public int FontSize
        {
            get { return fontSize; }
            set
            {
                if (fontSize == value)
                    return;

                fontSize = value;
                dirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the font weight.
        /// </summary>
        /// <value>The font weight.</value>
        public FontWeight FontWeight
        {
            get { return fontWeight; }
            set
            {
                if (fontWeight == value)
                    return;

                fontWeight = value;
                dirty = true;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="TextConsole"/> class.
        /// </summary>
        public TextConsole()
        {
            FontSize = 15;
            LineHeight = 15;
            FontWeight = FontWeight.Bold;
            FontName = "Arial";
            ForegroundColor = Color.White;
        }

        /// <summary>
        /// Initializes the resource.
        /// </summary>
        /// <param name="graphicsDeviceManager">The graphics device manager.</param>
        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            manager = graphicsDeviceManager;

            CreateFont();

            sprite = new Sprite(manager.Direct3D9.Device);
        }

        /// <summary>
        /// Allows the resource to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            font.OnResetDevice();
            sprite.OnResetDevice();
        }

        /// <summary>
        /// Allows the resource to unload any short-term graphical content.
        /// </summary>
        public void UnloadContent()
        {
            font.OnLostDevice();
            sprite.OnLostDevice();
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            font.Dispose();
            sprite.Dispose();
            font = null;

            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Writes text to the console.
        /// </summary>
        public void Write(string text)
        {
            if (dirty)
                CreateFont();

            font.DrawString(sprite, text, Location.X, Location.Y, ForegroundColor);
        }

        /// <summary>
        /// Writes text to the console and then advances the position to the next line.
        /// </summary>
        public void WriteLine()
        {
            Location = new Point(Location.X, Location.Y + LineHeight);
        }

        /// <summary>
        /// Writes text to the console and then advances the position to the next line.
        /// </summary>
        public void WriteLine(string text)
        {
            Write(text);
            WriteLine();
        }

        /// <summary>
        /// Starts a frame of text.
        /// </summary>
        public void Begin()
        {
            sprite.Begin(SpriteFlags.AlphaBlend | SpriteFlags.SortTexture);
        }

        /// <summary>
        /// Ends a frame of text.
        /// </summary>
        public void End()
        {
            sprite.End();
        }

        void CreateFont()
        {
            if (font != null)
                font.Dispose();

            dirty = false;
            font = new SlimDX.Direct3D9.Font(manager.Direct3D9.Device, FontSize, 0, FontWeight, 0, false,
                CharacterSet.Default, Precision.TrueType, FontQuality.ClearTypeNatural,
                PitchAndFamily.Default | PitchAndFamily.DontCare, FontName);
        }
    }
}
