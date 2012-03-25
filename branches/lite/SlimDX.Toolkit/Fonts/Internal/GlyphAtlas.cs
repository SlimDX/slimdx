using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;

namespace SlimDX.Toolkit
{
    struct GlyphBounds
    {
        public float OffsetX;
        public float OffsetY;
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

    struct GlyphCoords
    {
        public float TexCoordLeft;
        public float TexCoordTop;
        public float TexCoordRight;
        public float TexCoordBottom;
        public float PositionLeft;
        public float PositionTop;
        public float PositionRight;
        public float PositionBottom;
    }

    // an index into a glyph atlas, including the sheet index and the texture index within that sheet
    struct GlyphIndex
    {
        public short SheetIndex;
        public short LocalIndex;

        public bool IsValid
        {
            get { return SheetIndex != -1 && LocalIndex != -1; }
        }

        public GlyphIndex(int value)
        {
            SheetIndex = (short)value;
            LocalIndex = (short)value;
        }

        public GlyphIndex(int localIndex, int sheetIndex)
        {
            SheetIndex = (short)sheetIndex;
            LocalIndex = (short)localIndex;
        }
    }

    /// <summary>
    /// Maintains a collection of texture atlases for the font glyphs.
    /// </summary>
    class GlyphAtlas : IDisposable
    {
        Dictionary<GlyphIndex, GlyphCoords> coordinates = new Dictionary<GlyphIndex, GlyphCoords>(); 
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

            // create a default glyph
            unsafe
            {
                byte* glyph0 = stackalloc byte[256];
                for (int i = 0; i < 256; i++)
                    glyph0[i] = 0xff;

                InsertGlyph(new GlyphImageData
                {
                    GlyphPixels = new IntPtr(glyph0),
                    RowPitch = 16,
                    PixelStride = 1,
                    Metrics = new GlyphBounds
                    {
                        Width = 16,
                        Height = 16
                    }
                });
            }
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

        public GlyphCoords GetGlyphCoords(GlyphIndex index)
        {
            return coordinates[index];
        }

        public void BindSheet(DeviceContext context, int sheetIndex)
        {
            if (sheetIndex < sheetCount)
                glyphSheets[sheetIndex].Bind(context);
        }

        public GlyphIndex InsertGlyph(GlyphImageData data)
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
                return new GlyphIndex(-1);

            var result = new GlyphIndex(glyphIndex, sheetIndex);
            var coords = glyphSheets[sheetIndex].GetCoordinates(glyphIndex);
            coordinates[result] = new GlyphCoords()
            {
                PositionLeft = data.Metrics.OffsetX,
                PositionTop = data.Metrics.OffsetY,
                PositionRight = data.Metrics.OffsetX + data.Metrics.Width,
                PositionBottom = data.Metrics.OffsetY + data.Metrics.Height,
                TexCoordLeft = coords.Left,
                TexCoordTop = coords.Top,
                TexCoordRight = coords.Right,
                TexCoordBottom = coords.Bottom
            };

            return result;
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
