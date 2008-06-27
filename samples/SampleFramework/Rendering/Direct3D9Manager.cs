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
using SlimDX.Direct3D9;
using SlimDX;
using System;

namespace SampleFramework
{
    /// <summary>
    /// Manages aspects of the graphics device unique to Direct3D9.
    /// </summary>
    public class Direct3D9Manager
    {
        // variables
        GraphicsDeviceManager manager;

        /// <summary>
        /// Gets the graphics device.
        /// </summary>
        /// <value>The graphics device.</value>
        public Device Device
        {
            get;
            internal set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Direct3D9Manager"/> class.
        /// </summary>
        /// <param name="manager">The parent manager.</param>
        internal Direct3D9Manager(GraphicsDeviceManager manager)
        {
            // store variables
            this.manager = manager;
        }

        /// <summary>
        /// Creates a render target surface that is compatible with the current device settings.
        /// </summary>
        /// <param name="width">The width of the surface.</param>
        /// <param name="height">The height of the surface.</param>
        /// <returns>The newly created render target surface.</returns>
        public Surface CreateRenderTarget(int width, int height)
        {
            // create the surface, using the current device settings
            return Surface.CreateRenderTarget(Device, width, height, manager.CurrentSettings.BackBufferFormat,
                manager.CurrentSettings.MultisampleType, manager.CurrentSettings.MultisampleQuality, false);
        }

        /// <summary>
        /// Resolves the current back buffer into a texture.
        /// </summary>
        /// <returns>A texture containing the resolved back buffer.</returns>
        /// <exception cref="InvalidOperationException">Thrown when the resolve process fails.</exception>
        public Texture ResolveBackBuffer()
        {
            // call the overload
            return ResolveBackBuffer(0);
        }

        /// <summary>
        /// Resolves the current back buffer into a texture.
        /// </summary>
        /// <param name="backBufferIndex">The index of the back buffer.</param>
        /// <returns>A texture containing the resolved back buffer.</returns>
        /// <exception cref="InvalidOperationException">Thrown when the resolve process fails.</exception>
        public Texture ResolveBackBuffer(int backBufferIndex)
        {
            // disable exceptions for this method
            bool storedThrow = Configuration.ThrowOnError;
            Configuration.ThrowOnError = false;

            // create the destination texture
            Texture target = new Texture(Device, manager.CurrentSettings.BackBufferWidth, manager.CurrentSettings.BackBufferHeight,
                1, Usage.RenderTarget, manager.CurrentSettings.BackBufferFormat, Pool.Default);
            if (target == null || Result.Last.IsFailure)
            {
                // error occured in target creation
                Configuration.ThrowOnError = storedThrow;
                throw new InvalidOperationException("Could not create resolve target texture.");
            }

            try
            {
                // grab the current back buffer
                Surface backBuffer = Device.GetBackBuffer(0, backBufferIndex);
                if (backBuffer == null || Result.Last.IsFailure)
                    throw new InvalidOperationException("Could not obtain back buffer surface.");

                // grab the destination surface
                Surface destination = target.GetSurfaceLevel(0);
                if (destination == null || Result.Last.IsFailure)
                    throw new InvalidOperationException("Could not obtain resolve target surface.");

                // first try to copy using linear filtering
                if (Device.StretchRectangle(backBuffer, destination, TextureFilter.Linear).IsFailure)
                {
                    // that failed, so try with no filtering
                    if (Device.StretchRectangle(backBuffer, destination, TextureFilter.None).IsFailure)
                    {
                        // that failed as well, so the last thing we can try is a load surface call
                        if (Surface.FromSurface(destination, backBuffer, Filter.Default, 0).IsFailure)
                            throw new InvalidOperationException("Could not copy surfaces.");
                    }
                }
            }
            catch
            {
                // clean up the target
                target.Dispose();
                throw;
            }
            finally
            {
                // restore the throw state
                Configuration.ThrowOnError = storedThrow;
            }

            // return the target
            return target;
        }
    }
}
