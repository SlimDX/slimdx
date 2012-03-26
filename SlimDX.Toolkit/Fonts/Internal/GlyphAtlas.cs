using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using System.Drawing;

namespace SlimDX.Toolkit
{
    struct GlyphBounds
    {
        public float X;
        public float Y;
        public int Width;
        public int Height;
    }

    class GlyphImageData
    {
        public GlyphBounds Metrics;
        public IntPtr GlyphPixels;
        public int RowPitch;
        public int PixelStride;
    }

    /// <summary>
    /// Maintains a collection of texture atlases for the font glyphs.
    /// </summary>
    class GlyphAtlas : IDisposable
    {
        TextureAtlas[] glyphSheets;
        int currentSheetIndex;
        int sheetCount;
        int maxSheetCount = 4096;
        Device device;
        int sheetWidth;
        int sheetHeight;
        int maxGlyphCount;
        int flushedSheetIndex;

        public GlyphAtlas(Device device, int sheetWidth, int sheetHeight, int maxGlyphCount, int maxSheetCount)
        {
            this.device = device;
            this.sheetWidth = sheetWidth;
            this.sheetHeight = sheetHeight;
            this.maxGlyphCount = maxGlyphCount;

            if (maxSheetCount > 0 && maxSheetCount < 655536)
                this.maxSheetCount = maxSheetCount;
            glyphSheets = new TextureAtlas[this.maxSheetCount];
        }

        public void Dispose()
        {
            if (glyphSheets != null)
            {
                foreach (var sheet in glyphSheets)
                {
                    if (sheet != null)
                        sheet.Dispose();
                }
            }

            glyphSheets = null;
        }

        public void Flush(DeviceContext context)
        {
            int first = flushedSheetIndex;
            flushedSheetIndex = currentSheetIndex;

            for (int i = first; i < sheetCount; i++)
                glyphSheets[i].Flush(context);
        }

        public void BindSheet(DeviceContext context, int sheetIndex)
        {
            if (sheetIndex < sheetCount)
                glyphSheets[sheetIndex].Bind(context);
        }

        public int InsertGlyph(GlyphImageData data, out RectangleF positionOffsets, out RectangleF textureCoordinates)
        {
            int sheetIndex = 0;
            int glyphIndex = -1;

            // attempt to insert the glyph into each sheet that we have
            for (int i = currentSheetIndex; i < sheetCount; i++)
            {
                glyphIndex = glyphSheets[i].AddTexture(data.Metrics.Width, data.Metrics.Height, data.GlyphPixels, data.RowPitch, data.PixelStride);
                if (glyphIndex != -1)
                {
                    sheetIndex = i;
                    break;
                }
            }

            // if the glyph didn't fit into any of the sheets we have, create a new one
            if (glyphIndex == -1 && sheetCount < maxSheetCount)
            {
                var sheet = new TextureAtlas(device, sheetWidth, sheetHeight, maxGlyphCount, format: DXGI.Format.R8_UNorm);
                glyphIndex = sheet.AddTexture(data.Metrics.Width, data.Metrics.Height, data.GlyphPixels, data.RowPitch, data.PixelStride);

                int newSheetIndex = InsertSheet(sheet);
                if (newSheetIndex != -1)
                    sheetIndex = newSheetIndex;
                else
                    glyphIndex = -1;
            }

            if (glyphIndex == -1)
            {
                positionOffsets = RectangleF.Empty;
                textureCoordinates = RectangleF.Empty;
                return -1;
            }

            textureCoordinates = glyphSheets[sheetIndex].GetCoordinates(glyphIndex);
            positionOffsets = new RectangleF(data.Metrics.X, data.Metrics.Y, data.Metrics.Width, data.Metrics.Height);

            return sheetIndex;
        }

        int InsertSheet(TextureAtlas sheet)
        {
            int sheetIndex = -1;
            if (sheetCount < maxSheetCount)
            {
                sheetIndex = sheetCount;
                glyphSheets[sheetIndex] = sheet;
                sheetCount++;

                int activeCount = 4;
                if (sheetCount > currentSheetIndex + activeCount)
                {
                    glyphSheets[currentSheetIndex].Freeze();
                    currentSheetIndex++;
                }
            }

            return sheetIndex;
        }
    }
}
