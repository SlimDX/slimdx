using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;

namespace SlimDX.Toolkit.Fonts
{
    using FontKey = Tuple<FontFace, TextOptions, float>;
    using SlimDX.DirectWrite;

    class GlyphMap
    {
        public float FontSize;
        public TextOptions Flags;
        public int[] Glyphs;
    }

    /// <summary>
    /// Handles matching glyphs to images in an atlas.
    /// </summary>
    class GlyphProvider : IDisposable
    {
        Dictionary<FontKey, GlyphMap> fontMap = new Dictionary<FontKey, GlyphMap>();
        RenderTargetWrapper renderTarget;
        GlyphAtlas glyphAtlas;

        public GlyphProvider(Factory factory, GlyphAtlas glyphAtlas, int maxGlyphWidth, int maxGlyphHeight)
        {
            this.glyphAtlas = glyphAtlas;

            int renderTargetWidth = 384;
            if (maxGlyphWidth > 0 && maxGlyphWidth <= 8192)
                renderTargetWidth = maxGlyphWidth;
            int renderTargetHeight = 384;
            if (maxGlyphHeight > 0 && maxGlyphHeight <= 8192)
                renderTargetHeight = maxGlyphHeight;

            renderTarget = new RenderTargetWrapper(factory, renderTargetWidth, renderTargetHeight);
        }

        public void Dispose()
        {
            if (renderTarget != null)
                renderTarget.Dispose();
            renderTarget = null;

            foreach (var key in fontMap.Keys)
                key.Item1.Dispose();
            fontMap.Clear();
        }

        public GlyphMap GetGlyphMapFromFont(FontFace fontFace, float fontSize, TextOptions flags)
        {
            GlyphMap glyphMap;
            var key = new FontKey(fontFace, flags & TextOptions.Aliased, fontSize);
            if (fontMap.TryGetValue(key, out glyphMap))
                return glyphMap;

            if ((flags & TextOptions.NoNewGlyphs) != 0)
                return null;

            glyphMap = new GlyphMap()
            {
                Flags = flags,
                FontSize = fontSize,
                Glyphs = Enumerable.Repeat(int.MaxValue, fontFace.GlyphCount).ToArray()
            };

            fontMap.Add(key, glyphMap);
            InsertNewGlyph(glyphMap, 0, fontFace);

            return glyphMap;
        }

        public int GetAtlasIdFromGlyphIndex(GlyphMap glyphMap, int index, FontFace fontFace, TextOptions flags)
        {
            if (glyphMap == null || index >= glyphMap.Glyphs.Length)
                return 0;

            int atlasId = glyphMap.Glyphs[index];
            if (atlasId == int.MaxValue && (flags & TextOptions.NoNewGlyphs) == 0)
                atlasId = InsertNewGlyph(glyphMap, index, fontFace);

            // fallback to the default glyph on failure
            if (atlasId == int.MaxValue)
            {
                atlasId = glyphMap.Glyphs[0];
                if ((flags & TextOptions.NoNewGlyphs) == 0)
                {
                    if (atlasId == int.MaxValue)
                        atlasId = index == 0 ? 0 : GetAtlasIdFromGlyphIndex(glyphMap, 0, fontFace, flags);
                    glyphMap.Glyphs[index] = atlasId;
                }

                if (atlasId == int.MaxValue)
                    atlasId = 0;
            }

            return atlasId;
        }

        int InsertNewGlyph(GlyphMap glyphMap, int index, FontFace fontFace)
        {
            var renderingMode = RenderingMode.Default;
            var measuringMode = MeasuringMode.Natural;
            if ((glyphMap.Flags & TextOptions.Aliased) != 0)
            {
                renderingMode = RenderingMode.Aliased;
                measuringMode = MeasuringMode.GdiClassic;
            }

            var data = renderTarget.DrawGlyph(fontFace, index, glyphMap.FontSize, renderingMode, measuringMode);
            int atlasId = glyphMap.Glyphs[index];
            if (atlasId == int.MaxValue)
            {
                atlasId = glyphAtlas.InsertGlyph(data);
                glyphMap.Glyphs[index] = atlasId;
            }

            return atlasId;
        }
    }
}
