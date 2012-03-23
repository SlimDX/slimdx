using System;
using System.Drawing;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using Device = SlimDX.Direct3D11.Device;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Manages a collection of textures packed into one sheet for efficiency.
    /// </summary>
    public class TextureAtlas : IDisposable
    {
        int count;
        int sheetWidth;
        int sheetHeight;
        int dirtyCount;
        int gutterWidth;
        int formatSize;
        bool shouldFreeze;
        bool frozen;
        Rectangle dirtyArea;
        AlignedArray<RectangleF> coordinates;
        DataStream textureData;
        Texture2D texture;
        ShaderResourceView textureView;
        IRectanglePacker packer;

        /// <summary>
        /// Initializes a new instance of the <see cref="TextureAtlas"/> class.
        /// </summary>
        /// <param name="device">The device used to create hardware resources.</param>
        /// <param name="sheetWidth">Width of the sheet, in pixels.</param>
        /// <param name="sheetHeight">Height of the sheet, in pixels.</param>
        /// <param name="maxTextureCount">The maximum number of textures that can be stored in the atlas. Must be less than 65535.</param>
        /// <param name="gutterWidth">Width of the gutter region surrounding each texture.</param>
        /// <param name="format">The pixel format of the atlas texture.</param>
        /// <param name="packer">The packing algorithm to use to optimally store textures. If <c>null</c>, a default packer will be used.</param>
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="device"/> is <c>null</c>.</exception>
        /// <exception cref="ArgumentOutOfRangeException">Thrown if <paramref name="sheetWidth"/>, <paramref name="sheetHeight"/>, or <paramref name="maxTextureCount"/> is not in a valid range of values.</exception>
        public TextureAtlas(Device device, int sheetWidth = 512, int sheetHeight = 512, int maxTextureCount = 2048, int gutterWidth = 1, Format format = Format.R8G8B8A8_UNorm_SRGB, IRectanglePacker packer = null)
        {
            if (device == null)
                throw new ArgumentNullException("device");
            if (sheetWidth <= 0)
                throw new ArgumentOutOfRangeException("sheetWidth", sheetWidth, "Size of the texture atlas must be positive.");
            if (sheetHeight <= 0)
                throw new ArgumentOutOfRangeException("sheetHeight", sheetHeight, "Size of the texture atlas must be positive.");
            if (maxTextureCount <= 0 || maxTextureCount >= 65535)
                throw new ArgumentOutOfRangeException("maxTextureCount", maxTextureCount, "Maximum texture count must be between 0 and 65535.");

            this.sheetWidth = sheetWidth;
            this.sheetHeight = sheetHeight;
            this.gutterWidth = gutterWidth;
            this.packer = packer ?? new SimpleHeightPacker();
            coordinates = new AlignedArray<RectangleF>(maxTextureCount);

            // create space for all the texture data; use native memory to avoid the GC
            formatSize = format.SizeInBytes();
            int textureSize = sheetWidth * sheetHeight * formatSize;
            textureData = new DataStream(textureSize, true, true);
            for (int i = 0; i < textureSize; i++)
                textureData.WriteByte(0);

            texture = new Texture2D(device, new Texture2DDescription
            {
                Width = sheetWidth,
                Height = sheetHeight,
                ArraySize = 1,
                MipLevels = 1,
                Format = format,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.ShaderResource
            });

            textureView = new ShaderResourceView(device, texture);
        }

        /// <summary>
        /// Adds a texture to the atlas.
        /// </summary>
        /// <param name="width">The width of the texture.</param>
        /// <param name="height">The height of the texture.</param>
        /// <param name="pixelData">The pixel data.</param>
        /// <param name="rowPitch">The number of bytes in a row, including padding.</param>
        /// <param name="bytesPerPixel">The number of bytes per pixel in the texture.</param>
        /// <returns>A handle that can be used to retrieve texture coordinates for the stored texture, or -1 if the texture cannot fit into the atlas.</returns>
        /// <exception cref="InvalidOperationException">Thrown if the atlas has been frozen.</exception>
        public int AddTexture(int width, int height, DataStream pixelData, int rowPitch, int bytesPerPixel)
        {
            if (shouldFreeze || frozen)
                throw new InvalidOperationException("Cannot add a texture to an atlas that has been frozen.");
            if (count >= coordinates.Length)
                return -1;

            // pad the width and height with a gutter region to prevent blending artifacts
            Point position;
            if (!packer.TryPack(width + (gutterWidth * 2), height + (gutterWidth * 2), out position))
                return -1;

            unsafe
            {
                var coords = (RectangleF*)coordinates[count];
                coords->X = (position.X + gutterWidth) / (float)sheetWidth;
                coords->Y = (position.Y + gutterWidth) / (float)sheetHeight;
                coords->Width = width / (float)sheetWidth;
                coords->Height = height / (float)sheetHeight;

                // blit the pixel data into the texture, making sure we don't overrun the bounds of the atlas texture
                int bytesToCopy = Math.Min(bytesPerPixel, formatSize);
                position.X += gutterWidth;
                position.Y += gutterWidth;
                for (int i = 0; i < height && i < sheetHeight - position.Y; i++)
                {
                    byte* src = (byte*)pixelData.DataPointer + (i * rowPitch);
                    byte* dest = (byte*)textureData.DataPointer + ((position.Y + i) * sheetWidth + position.X) * formatSize;

                    // copy each pixel into the texture, only copying the number of bytes that we have support for
                    for (int j = 0; j < width && j < sheetWidth - position.X; j++)
                    {
                        for (int k = 0; k < bytesToCopy; k++)
                            dest[j * formatSize + k] = src[j * bytesPerPixel + k];
                    }
                }
            }

            // update the dirty rect to be flushed to device texture
            if (dirtyCount == 0)
            {
                dirtyArea.X = position.X;
                dirtyArea.Y = position.Y;
                dirtyArea.Width = Math.Min(position.X + width, sheetWidth) - dirtyArea.X;
                dirtyArea.Height = Math.Min(position.Y + height, sheetHeight) - dirtyArea.Y;
            }
            else
            {
                dirtyArea.X = Math.Min(dirtyArea.X, position.X);
                dirtyArea.Y = Math.Min(dirtyArea.Y, position.Y);
                dirtyArea.Width = Math.Min(Math.Max(dirtyArea.Right, position.X + width), sheetWidth) - dirtyArea.X;
                dirtyArea.Height = Math.Min(Math.Max(dirtyArea.Bottom, position.Y + height), sheetHeight) - dirtyArea.Y;
            }

            dirtyCount++;
            return count++;
        }

        /// <summary>
        /// Gets the texture coordinates for the given texture stored in the atlas.
        /// </summary>
        /// <param name="texture">The ID of the texture whose coordinates are to be retrieved.</param>
        /// <returns>The normalized texture coordinates.</returns>
        public RectangleF GetCoordinates(int texture)
        {
            unsafe { return *(RectangleF*)coordinates[texture]; }
        }

        /// <summary>
        /// Freezes the texture atlas, preventing further additions and allowing the local copy
        /// of the texture memory to be released.
        /// </summary>
        public void Freeze()
        {
            // freeze the next time we flush
            shouldFreeze = true;
        }

        /// <summary>
        /// Binds the texture atlas as a pixel shader resource.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="slot">The resource slot to bind.</param>
        public void Bind(DeviceContext context, int slot = 0)
        {
            context.PixelShader.SetShaderResource(textureView, slot);
        }

        /// <summary>
        /// Flushes the texture memory to the graphics device. This must be called before the texture atlas can be used for rendering operations.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        public void Flush(DeviceContext context)
        {
            if (frozen)
                return;

            if (dirtyCount > 0 && dirtyArea.Right > dirtyArea.Left && dirtyArea.Bottom > dirtyArea.Top)
            {
                // upload the texture changes to the GPU
                var region = new ResourceRegion(dirtyArea.Left, dirtyArea.Top, 0, dirtyArea.Right, dirtyArea.Bottom, 1);
                textureData.Position = (region.Top * sheetWidth + region.Left) * formatSize;
                context.UpdateSubresource(new DataBox(sheetWidth * formatSize, 0, textureData), texture, 0, region);
            }

            dirtyCount = 0;
            if (shouldFreeze)
            {
                // the sheet is now static; save memory
                frozen = true;
                textureData.Dispose();
                textureData = null;
            }
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (textureView != null)
                textureView.Dispose();
            if (texture != null)
                texture.Dispose();
            if (textureData != null)
                textureData.Dispose();
            if (coordinates != null)
                coordinates.Dispose();

            textureView = null;
            texture = null;
            textureData = null;
            coordinates = null;
        }
    }
}
