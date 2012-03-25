using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;

namespace SlimDX.Toolkit
{
    using FontKey = Tuple<FontFace, TextOptions, float>;
    using ResourceKey = Tuple<Factory, int, int>;

    /// <summary>
    /// Handles rendering glyphs and caching them in an atlas.
    /// </summary>
    class GlyphProvider : IDisposable
    {
        class GlyphMap : IDisposable
        {
            public FontFace FontFace;
            public float FontSize;
            public TextOptions Flags;
            public GlyphIndex[] Glyphs;

            public GlyphMap(FontFace fontFace, float fontSize, TextOptions flags)
            {
                FontFace = fontFace;
                FontSize = fontSize;
                Flags = flags;

                int count = fontFace.GlyphCount;
                Glyphs = new GlyphIndex[count];
                for (int i = 0; i < count; i++)
                    Glyphs[i] = new GlyphIndex(-1);
            }

            public void Dispose()
            {
                FontFace.Dispose();
            }
        }

        static SharedResourcePool<ResourceKey, GlyphImageRenderer> sharedRenderTargets = new SharedResourcePool<ResourceKey, GlyphImageRenderer>();
        static SharedResourcePool<FontKey, GlyphMap> sharedFontMaps = new SharedResourcePool<FontKey, GlyphMap>();

        Dictionary<FontKey, ISharedResource<GlyphMap>> localFontMaps = new Dictionary<FontKey, ISharedResource<GlyphMap>>();
        ISharedResource<GlyphImageRenderer> renderTargetResource;
        GlyphImageRenderer renderTarget;
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

            renderTargetResource = sharedRenderTargets.DemandCreate(new ResourceKey(factory, renderTargetWidth, renderTargetHeight), () => new GlyphImageRenderer(factory, renderTargetWidth, renderTargetHeight));
            renderTarget = renderTargetResource.Resource;
        }

        public void Dispose()
        {
            if (renderTargetResource != null)
            {
                renderTargetResource.Release();
                renderTargetResource = null;
            }

            foreach (var key in localFontMaps.Values)
                key.Release();
            localFontMaps.Clear();
        }

        GlyphMap GetGlyphMapFromFont(FontFace fontFace, float fontSize, TextOptions flags)
        {
            ISharedResource<GlyphMap> resource;
            var key = new FontKey(fontFace, flags & TextOptions.Aliased, fontSize);
            if (localFontMaps.TryGetValue(key, out resource))
                return resource.Resource;

            if ((flags & TextOptions.NoNewGlyphs) != 0)
                return null;

            // when creating a new map, insert the default glyph (glyph zero) to seed the map
            resource = sharedFontMaps.DemandCreate(key, () => { var map = new GlyphMap(fontFace, fontSize, flags); InsertNewGlyph(map, 0, fontFace); return map; });
            localFontMaps.Add(key, resource);

            return resource.Resource;
        }

        public GlyphIndex RenderToAtlas(int index, FontFace fontFace, float fontSize, TextOptions flags)
        {
            var map = GetGlyphMapFromFont(fontFace, fontSize, flags);
            if (map == null || index >= map.Glyphs.Length)
                return new GlyphIndex(0);

            // try to look up the desired glyph in the map; if it's not there, create it
            var atlasId = map.Glyphs[index];
            if (!atlasId.IsValid && (flags & TextOptions.NoNewGlyphs) == 0)
                InsertNewGlyph(map, index, fontFace);

            // fallback to the default glyph on failure
            atlasId = map.Glyphs[index];
            if (!atlasId.IsValid)
                atlasId = map.Glyphs[0];

            return atlasId;
        }

        void InsertNewGlyph(GlyphMap glyphMap, int index, FontFace fontFace)
        {
            var renderingMode = RenderingMode.Default;
            var measuringMode = MeasuringMode.Natural;
            if ((glyphMap.Flags & TextOptions.Aliased) != 0)
            {
                renderingMode = RenderingMode.Aliased;
                measuringMode = MeasuringMode.GdiClassic;
            }

            var data = renderTarget.DrawGlyph(fontFace, index, glyphMap.FontSize, renderingMode, measuringMode);
            glyphMap.Glyphs[index] = glyphAtlas.InsertGlyph(data);
        }
    }
}
