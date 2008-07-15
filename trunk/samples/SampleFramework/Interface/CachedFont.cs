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
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Stores details that can be used to recreate a cached font.
    /// </summary>
    public class CachedFont : IDisposable
    {
        // variables
        Font font;
        string faceName;
        int height;
        FontWeight weight;

        /// <summary>
        /// Gets the device.
        /// </summary>
        /// <value>The device.</value>
        public Device Device
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the font.
        /// </summary>
        /// <value>The font.</value>
        public Font Font
        {
            get
            {
                // if we don't have a font yet, create one from the stored variables
                Create();
                return font;
            }
        }

        /// <summary>
        /// Gets or sets the face name.
        /// </summary>
        /// <value>The face name.</value>
        public string FaceName
        {
            get { return faceName; }
            set
            {
                // avoid unecessary changes
                if (faceName == value)
                    return;

                // update the value
                faceName = value;
                Release();
            }
        }

        /// <summary>
        /// Gets or sets the height.
        /// </summary>
        /// <value>The height.</value>
        public int Height
        {
            get { return height; }
            set
            {
                // avoid unecessary changes
                if (height == value)
                    return;

                // update the value
                height = value;
                Release();
            }
        }

        /// <summary>
        /// Gets or sets the weight.
        /// </summary>
        /// <value>The weight.</value>
        public FontWeight Weight
        {
            get { return weight; }
            set
            {
                // avoid unecessary changes
                if (weight == value)
                    return;

                // update the value
                weight = value;
                Release();
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CachedFont"/> class.
        /// </summary>
        /// <param name="device">The device.</param>
        /// <param name="faceName">Name of the type face.</param>
        /// <param name="height">The height.</param>
        /// <param name="weight">The weight.</param>
        internal CachedFont(Device device, string faceName, int height, FontWeight weight)
        {
            // store variables
            Device = device;
            FaceName = faceName;
            Height = height;
            Weight = weight;
        }

        /// <summary>
        /// Ensures that the internally managed font handle has been created.
        /// </summary>
        public void Create()
        {
            // ensure that the font has been created
            if (font == null && Device != null)
                font = new Font(Device, Height, 0, Weight, 1, false, CharacterSet.Default, Precision.Default,
                    FontQuality.Default, PitchAndFamily.Default | PitchAndFamily.DontCare, FaceName);
        }

        /// <summary>
        /// Releases the internally managed font handle.
        /// </summary>
        public void Release()
        {
            // release the font
            if (font != null)
                font.Dispose();
            font = null;
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            // call the overload
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            // check if we should release managed resources
            if (disposing)
                Release();
        }
    }
}
