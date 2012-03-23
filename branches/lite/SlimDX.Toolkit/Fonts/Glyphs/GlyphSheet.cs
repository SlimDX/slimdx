using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using SlimDX.Direct3D11;
using Device = SlimDX.Direct3D11.Device;
using Buffer = SlimDX.Direct3D11.Buffer;
using Resource = SlimDX.Direct3D11.Resource;
using SlimDX.DXGI;

namespace SlimDX.Toolkit.Fonts
{
    /// <summary>
    /// Represents a texture containing a sheet of glyph images.
    /// </summary>
    class GlyphSheet : IDisposable
    {
        bool closed;
        bool isStatic;
        int count;
        int maxCount = 2048;
        int updatedCount;
        int alignWidth;
        int sheetWidth;
        int sheetHeight;
        int mipCount;
        bool allowOversizedGlyph;
        bool hardwareCoordBuffer;
        GlyphCoords[] glyphCoords;
        DataStream textureData;
        Rectangle dirtyRect;
        HeightRange heightRange;
        Buffer coordBuffer;
        Texture2D texture;
        ShaderResourceView textureView;
        ShaderResourceView bufferView;

        public GlyphSheet(Device device, int sheetWidth, int sheetHeight, bool useCoordBuffer, bool allowOversizedGlyph, int maxGlyphCount, int mipLevelCount)
        {
            this.sheetWidth = sheetWidth > 0 ? sheetWidth : 512;
            this.sheetHeight = sheetHeight > 0 ? sheetHeight : 512;
            this.allowOversizedGlyph = allowOversizedGlyph;

            if (useCoordBuffer && device.FeatureLevel >= FeatureLevel.Level_10_0)
                hardwareCoordBuffer = true;

            if (maxGlyphCount > 0 && maxGlyphCount < 65535)
                this.maxCount = maxGlyphCount;

            if (mipLevelCount > 1)
            {
                // reasonable mip limit considering borders
                mipCount = Math.Min(mipLevelCount, 5);
                alignWidth = (1 << (mipCount - 1));
            }
            else
            {
                mipCount = 1;
                alignWidth = 1;
            }

            // Storage
            int textureSize = sheetWidth * sheetHeight;
            int mipSize = textureSize;
            for (int i = 1; i < mipCount; i++)
            {
                mipSize >>= 2;
                textureSize += mipSize;
            }

            textureData = new DataStream(textureSize, true, true);
            for (int i = 0; i < textureSize; i++)
                textureData.WriteByte(0);

            glyphCoords = new GlyphCoords[maxCount];
            heightRange = new HeightRange(sheetWidth / alignWidth);

            CreateDeviceResources(device);
        }

        public void Dispose()
        {
            if (bufferView != null)
                bufferView.Dispose();

            if (coordBuffer != null)
                coordBuffer.Dispose();

            if (textureView != null)
                textureView.Dispose();

            if (texture != null)
                texture.Dispose();

            if (textureData != null)
                textureData.Dispose();

            bufferView = null;
            coordBuffer = null;
            textureView = null;
            texture = null;
            textureData = null;
        }

        public int InsertGlyph(GlyphImageData glyph)
        {
            if (closed || count >= maxCount)
                return int.MaxValue;

            // position the glyph
            int width = glyph.Metrics.Width;
            int height = glyph.Metrics.Height;
            int blockWidth = width / alignWidth + 1;
            int blockHeight = height / alignWidth + 1;

            if (width % alignWidth != 0)
                blockWidth++;
            if (height % alignWidth != 0)
                blockHeight++;

            int blockX, blockY;
            int positionX, positionY;
            if (count > 0 || !allowOversizedGlyph)
            {
                if (alignWidth + width + alignWidth > sheetWidth)
                    return int.MaxValue;

                // position the glyph at the lowest Y possible (fills reasonably well with different sized glyphs)
                blockX = heightRange.FindMin(blockWidth, out blockY);

                positionX = alignWidth + blockX * alignWidth;
                positionY = alignWidth + blockY * alignWidth;

                if (positionY + height + alignWidth > sheetHeight)
                    return int.MaxValue;
            }
            else
            {
                blockX = blockY = 0;
                positionX = positionY = alignWidth;
            }

            heightRange.Update(blockX, blockWidth, blockY + blockHeight);

            // store glyph coordinates
            float coordOffset = alignWidth * 0.5f;
            int alignedWidth = (blockWidth - 1) * alignWidth;
            int alignedHeight = (blockHeight - 1) * alignWidth;
            var coords = new GlyphCoords()
            {
                TexCoordLeft = (positionX - coordOffset) / (float)sheetWidth,
                TexCoordTop = (positionY - coordOffset) / (float)sheetHeight,
                TexCoordRight = (positionX + alignedWidth + coordOffset) / (float)sheetWidth,
                TexCoordBottom = (positionY + alignedHeight + coordOffset) / (float)sheetHeight,
                PositionLeft = glyph.Metrics.OffsetX - coordOffset,
                PositionTop = glyph.Metrics.OffsetY - coordOffset,
                PositionRight = glyph.Metrics.OffsetX + alignedWidth + coordOffset,
                PositionBottom = glyph.Metrics.OffsetY + alignedHeight + coordOffset
            };

            int index = count;
            glyphCoords[index] = coords;

            // blit the pixels
            unsafe
            {
                for (int i = 0; i < height && i < sheetHeight - positionY; i++)
                {
                    byte* src = (byte*)glyph.GlyphPixels + (i * glyph.RowPitch);
                    byte* dest = (byte*)textureData.DataPointer + (positionY + i) * sheetWidth + positionX;
                    for (int j = 0; j < width && j < sheetWidth - positionX; j++)
                        dest[j] = src[j * glyph.PixelStride];
                }
            }

            // update the dirty rect to be flushed to device texture
            if (updatedCount == 0)
            {
                dirtyRect.X = positionX - alignWidth;
                dirtyRect.Y = positionY - alignWidth;
                dirtyRect.Width = Math.Min(positionX + width + alignWidth, sheetWidth) - dirtyRect.X;
                dirtyRect.Height = Math.Min(positionY + height + alignWidth, sheetHeight) - dirtyRect.Y;
            }
            else
            {
                dirtyRect.X = Math.Min(dirtyRect.Left, positionX - alignWidth);
                dirtyRect.Y = Math.Min(dirtyRect.Y, positionY - alignWidth);
                dirtyRect.Width = Math.Min(Math.Max(dirtyRect.Right, positionX + width + alignWidth), sheetWidth) - dirtyRect.X;
                dirtyRect.Height = Math.Min(Math.Max(dirtyRect.Bottom, positionY + height + alignWidth), sheetHeight) - dirtyRect.Y;
            }

            count++;
            updatedCount++;

            return index;
        }

        public void BindSheet(DeviceContext context, TextOptions flags)
        {
            context.PixelShader.SetShaderResource(textureView, 0);
            if ((flags & TextOptions.NoGeometryShader) == 0 && hardwareCoordBuffer)
                context.GeometryShader.SetShaderResource(bufferView, 0);
        }

        public GlyphCoords[] GetGlyphCoords()
        {
            return glyphCoords;
        }

        public void CloseSheet()
        {
            closed = true;
        }

        public void Flush(DeviceContext context)
        {
            if (isStatic)
                return;

            if (updatedCount > 0)
            {
                // update the coordinate buffer
                if (hardwareCoordBuffer)
                {
                    int startIndex = count - updatedCount;
                    int endIndex = count;

                    var data = new DataStream(glyphCoords, true, false);
                    data.Position += startIndex;
                    context.UpdateSubresource(new DataBox(0, 0, data), coordBuffer, 0, new ResourceRegion(startIndex * GlyphCoords.SizeInBytes, 0, 0, endIndex * GlyphCoords.SizeInBytes, 1, 1));
                    data.Close();
                }

                // update the texture
                if (dirtyRect.Right > dirtyRect.Left && dirtyRect.Bottom > dirtyRect.Top)
                {
                    textureData.Position = 0;
                    var region = new ResourceRegion(dirtyRect.Left, dirtyRect.Top, 0, dirtyRect.Right, dirtyRect.Bottom, 1);

                    // update each mip level
                    for (int i = 0; i < mipCount; i++)
                    {
                        long oldPosition = textureData.Position;
                        textureData.Position += region.Top * (sheetWidth >> i) + region.Left;

                        context.UpdateSubresource(new DataBox(sheetWidth >> i, 0, textureData), texture, Resource.CalculateSubresourceIndex(i, 0, mipCount), region);
                        if (i + 1 < mipCount)
                        {
                            region.Left >>= 1;
                            region.Right >>= 1;
                            region.Top >>= 1;
                            region.Bottom >>= 1;

                            long nextMip = oldPosition + (sheetWidth >> i) * (sheetHeight >> i);
                            for (int j = region.Top; j < region.Bottom; j++) unsafe
                                {
                                    byte* src0 = (byte*)textureData.Position + oldPosition + j * 2 * (sheetWidth >> i);
                                    byte* src1 = src0 + (sheetWidth >> i);
                                    byte* dst = (byte*)textureData.Position + nextMip + j * (sheetWidth >> (i + 1));

                                    for (int k = region.Left; k < region.Right; k++)
                                    {
                                        int src = src0[k * 2] + src0[k * 2 + 1] + src1[k * 2] + src1[k * 2 + 1];
                                        dst[k] = (byte)(src >> 2);
                                    }
                                }

                            textureData.Position = nextMip;
                        }
                    }
                }
            }

            updatedCount = 0;
            if (closed)
            {
                // the sheet is now static; save memory
                isStatic = true;
                textureData.Dispose();
                textureData = null;
            }
        }

        void CreateDeviceResources(Device device)
        {
            texture = new Texture2D(device, new Texture2DDescription
            {
                Width = sheetWidth,
                Height = sheetHeight,
                ArraySize = 1,
                Format = Format.R8_UNorm,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default,
                MipLevels = mipCount,
                BindFlags = BindFlags.ShaderResource
            });

            textureView = new ShaderResourceView(device, texture);

            if (hardwareCoordBuffer)
            {
                coordBuffer = new Buffer(device, new BufferDescription
                {
                    SizeInBytes = maxCount * GlyphCoords.SizeInBytes,
                    Usage = ResourceUsage.Default,
                    BindFlags = BindFlags.ShaderResource
                });

                bufferView = new ShaderResourceView(device, coordBuffer, new ShaderResourceViewDescription
                {
                    Format = Format.R32G32B32A32_Float,
                    Dimension = ShaderResourceViewDimension.Buffer,
                    ElementOffset = 0,
                    ElementWidth = maxCount * 2 // two float4 per glyphcoords
                });
            }
        }
    }
}
