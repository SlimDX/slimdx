using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using System.Drawing;
using System.Collections;

namespace SlimDX.Toolkit
{
    using ResourceKey = Tuple<Factory, int, int>;

    /// <summary>
    /// Handles rendering glyphs and caching them in an atlas.
    /// </summary>
    class GlyphProvider : IDisposable
    {
        #region FontKey

        // mutable tuple type that we can use as a key without allocating for every glyph
        class FontKey : IStructuralEquatable, IStructuralComparable, IComparable
        {
            public FontFace FontFace;
            public TextOptions Flags;
            public float FontSize;

            public FontKey()
            {
            }

            public void Set(FontFace fontFace, TextOptions flags, float fontSize)
            {
                FontFace = fontFace;
                Flags = flags;
                FontSize = fontSize;
            }

            public override bool Equals(object obj)
            {
                return ((IStructuralEquatable)this).Equals(obj, EqualityComparer<object>.Default);
            }

            public override int GetHashCode()
            {
                return ((IStructuralEquatable)this).GetHashCode(EqualityComparer<object>.Default);
            }

            int IStructuralComparable.CompareTo(object other, IComparer comparer)
            {
                if (other == null)
                    return 1;

                var key = other as FontKey;
                if (key == null)
                    throw new ArgumentException("gdiaf");

                int num = 0;
                num = comparer.Compare(FontFace, key.FontFace);
                if (num != 0)
                    return num;

                num = comparer.Compare(Flags, key.Flags);
                if (num != 0)
                    return num;

                return comparer.Compare(FontSize, key.FontSize);
            }

            bool IStructuralEquatable.Equals(object other, IEqualityComparer comparer)
            {
                if (other == null)
                    return false;

                var key = other as FontKey;
                if (key == null)
                    return false;

                return ((comparer.Equals(FontFace, key.FontFace) && comparer.Equals(Flags, key.Flags)) && comparer.Equals(FontSize, key.FontSize));
            }

            int IStructuralEquatable.GetHashCode(IEqualityComparer comparer)
            {
                return CombineHashCodes(CombineHashCodes(comparer.GetHashCode(FontFace), comparer.GetHashCode(Flags)), comparer.GetHashCode(FontSize));
            }

            int IComparable.CompareTo(object obj)
            {
                return ((IStructuralComparable)this).CompareTo(obj, Comparer<object>.Default);
            }

            public override string ToString()
            {
                var sb = new StringBuilder();
                sb.Append("(");
                sb.Append(FontFace);
                sb.Append(", ");
                sb.Append(Flags);
                sb.Append(", ");
                sb.Append(FontSize);
                sb.Append(")");
                return sb.ToString();
            }

            static int CombineHashCodes(int h1, int h2)
            {
                return ((h1 << 5) + h1) ^ h2;
            }
        }

        #endregion

        #region GlyphMap

        // keeps track of rendered glyphs for each font face
        class GlyphMap : IDisposable
        {
            public FontFace FontFace;
            public float FontSize;
            public TextOptions Flags;
            public Glyph[] Glyphs;

            public GlyphMap(FontFace fontFace, float fontSize, TextOptions flags)
            {
                FontFace = fontFace;
                FontSize = fontSize;
                Flags = flags;

                int count = fontFace.GlyphCount;
                Glyphs = new Glyph[count];
                for (int i = 0; i < count; i++)
                    Glyphs[i] = new Glyph(-1);
            }

            public void Dispose()
            {
                FontFace.Dispose();
            }
        }

        #endregion

        static SharedResourcePool<ResourceKey, GlyphImageRenderer> sharedRenderers = new SharedResourcePool<ResourceKey, GlyphImageRenderer>();
        static SharedResourcePool<FontKey, GlyphMap> sharedFontMaps = new SharedResourcePool<FontKey, GlyphMap>();

        Dictionary<FontKey, ISharedResource<GlyphMap>> localFontMaps = new Dictionary<FontKey, ISharedResource<GlyphMap>>();
        ISharedResource<GlyphImageRenderer> renderer;
        GlyphAtlas glyphAtlas;
        FontKey key= new FontKey();

        public GlyphProvider(Factory factory, GlyphAtlas glyphAtlas, int maxGlyphWidth, int maxGlyphHeight)
        {
            this.glyphAtlas = glyphAtlas;

            int renderTargetWidth = 384;
            if (maxGlyphWidth > 0 && maxGlyphWidth <= 8192)
                renderTargetWidth = maxGlyphWidth;
            int renderTargetHeight = 384;
            if (maxGlyphHeight > 0 && maxGlyphHeight <= 8192)
                renderTargetHeight = maxGlyphHeight;

            renderer = sharedRenderers.DemandCreate(new ResourceKey(factory, renderTargetWidth, renderTargetHeight), () => new GlyphImageRenderer(factory, renderTargetWidth, renderTargetHeight));
        }

        public void Dispose()
        {
            if (renderer != null)
            {
                renderer.Release();
                renderer = null;
            }

            foreach (var key in localFontMaps.Values)
                key.Release();
            localFontMaps.Clear();
        }

        GlyphMap GetGlyphMapFromFont(FontFace fontFace, float fontSize, TextOptions flags)
        {
            ISharedResource<GlyphMap> resource;
            key.Set(fontFace, flags & TextOptions.Aliased, fontSize);
            if (localFontMaps.TryGetValue(key, out resource))
                return resource.Resource;

            if ((flags & TextOptions.NoNewGlyphs) != 0)
                return null;

            // when creating a new map, insert the default glyph (glyph zero) to seed the map
            resource = sharedFontMaps.DemandCreate(key, () => 
            { 
                var map = new GlyphMap(fontFace, fontSize, flags);
                InsertNewGlyph(map, 0, fontFace);
                return map;
            });

            localFontMaps.Add(key, resource);
            return resource.Resource;
        }

        public void GetGlyph(int index, FontFace fontFace, float fontSize, TextOptions flags, out Glyph glyph)
        {
            var map = GetGlyphMapFromFont(fontFace, fontSize, flags);
            if (map == null || index >= map.Glyphs.Length)
                glyph = map.Glyphs[0];
            else
            {
                // try to look up the desired glyph in the map; if it's not there, create it
                glyph = map.Glyphs[index];
                if (glyph.SheetIndex == -1 && (flags & TextOptions.NoNewGlyphs) == 0)
                    InsertNewGlyph(map, index, fontFace);

                // fallback to the default glyph on failure
                glyph = map.Glyphs[index];
                if (glyph.SheetIndex == -1)
                    glyph = map.Glyphs[0];
            }
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

            var data = renderer.Resource.DrawGlyph(fontFace, index, glyphMap.FontSize, renderingMode, measuringMode);
            var glyph = new Glyph();
            glyph.SheetIndex = glyphAtlas.InsertGlyph(data, out glyph.PositionOffsets, out glyph.TextureCoordinates);

            glyphMap.Glyphs[index] = glyph;
        }
    }
}
