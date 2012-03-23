using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;

namespace SlimDX.Toolkit.Fonts
{
    class GlyphAtlas : IDisposable
    {
        GlyphSheet[] glyphSheets;
        int currentSheetIndex;
        int sheetCount;
        int maxSheetCount = 4096;
        Device device;
        int sheetWidth;
        int sheetHeight;
        bool hardwareCoordBuffer;
        bool allowOversizedGlyph;
        int mipLevelCount;
        int maxGlyphCount;
        int flushedSheetIndex;

        public GlyphAtlas(Device device, int sheetWidth, int sheetHeight, bool useCoordBuffer, bool allowOversizedGlyph, int maxGlyphCount, int mipLevelCount, int maxSheetCount)
        {
            this.device = device;
            this.sheetWidth = sheetWidth;
            this.sheetHeight = sheetHeight;
            this.hardwareCoordBuffer = useCoordBuffer;
            this.allowOversizedGlyph = allowOversizedGlyph;
            this.mipLevelCount = mipLevelCount;
            this.maxGlyphCount = maxGlyphCount;

            if (maxSheetCount > 0 && maxSheetCount < 655536)
                this.maxSheetCount = maxSheetCount;
            glyphSheets = new GlyphSheet[this.maxSheetCount];

            // create a default glyph
            unsafe
            {
                byte* glyph0 = stackalloc byte[256];
                for (int i = 0; i < 256; i++)
                    glyph0[i] = 0xff;

                var metrics =
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

        public GlyphCoords[] GetGlyphCoords(int sheetIndex)
        {
            if (sheetIndex < sheetCount)
                return glyphSheets[sheetIndex].GetGlyphCoords();

            return null;
        }

        public void BindSheet(DeviceContext context, int sheetIndex, TextOptions flags)
        {
            if (sheetIndex < sheetCount)
                glyphSheets[sheetIndex].BindSheet(context, flags);
        }

        public int InsertGlyph(GlyphImageData data)
        {
            int sheetIndex = 0;
            int index = int.MaxValue;
            int start = currentSheetIndex;
            int end = sheetCount;

            // attempt to insert the glyph
            for (int i = start; i < end; i++)
            {
                index = glyphSheets[i].InsertGlyph(data);
                if (index != int.MaxValue)
                {
                    sheetIndex = i;
                    break;
                }
            }

            // try to create a new glyph sheet on failure
            if (index == int.MaxValue && sheetCount < maxSheetCount)
            {
                var sheet = new GlyphSheet(device, sheetWidth, sheetHeight, hardwareCoordBuffer, allowOversizedGlyph, maxGlyphCount, mipLevelCount);
                index = sheet.InsertGlyph(data);

                int newSheetIndex = InsertSheet(sheet);
                if (newSheetIndex != int.MaxValue)
                    sheetIndex = newSheetIndex;
                else
                    index = int.MaxValue;
            }

            if (index == int.MaxValue)
                return int.MaxValue;

            return (sheetIndex << 16) | index;
        }

        int InsertSheet(GlyphSheet sheet)
        {
            int sheetIndex = int.MaxValue;
            if (sheetCount < maxSheetCount)
            {
                sheetIndex = sheetCount;
                glyphSheets[sheetIndex] = sheet;
                sheetCount++;

                int activeCount = 4;
                if (sheetCount > currentSheetIndex + activeCount)
                {
                    glyphSheets[currentSheetIndex].CloseSheet();
                    currentSheetIndex++;
                }
            }

            return sheetIndex;
        }
    }
}
