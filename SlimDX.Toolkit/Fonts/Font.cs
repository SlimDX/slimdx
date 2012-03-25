using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using SlimDX.Direct3D11;
using System.Drawing;
using SlimMath;

namespace SlimDX.Toolkit
{
    #region TextOptions

    /// <summary>Specifies various text drawing options.</summary>
    /// <remarks>These flags can be used for any methods that take a flags parameter. Not all flags have meaning for all methods however.
    /// Consult the documentation page for a particular method for information on which flags are valid.</remarks>
    [Flags]
    public enum TextOptions
    {
        /// <summary>Text is left-aligned. This is the default.</summary>
        Left = 0x0,

        /// <summary>Text is centered horizontally.</summary>
        Center = 0x1,

        /// <summary>Text is right-aligned.</summary>
        Right = 0x2,

        /// <summary>Text is aligned at the top of the layout-box. This is the default.</summary>
        Top = 0x0,

        /// <summary>Text is centered vertically.</summary>
        VerticalCenter = 0x4,

        /// <summary>Text is aligned at the bottom of the layout-box.</summary>
        Bottom = 0x8,

        /// <summary>No automatic wrapping when the text overflows the layout-box.</summary>
        NoWordWrap = 0x10,

        /// <summary>Text is drawn without anti-aliasing.</summary>
        Aliased = 0x20,

        /// <summary>If a clip-rect is specified together with this flag, all text is clipped to inside the specified rectangle.</summary>
        ClipRect = 0x40,

        /// <summary>The transform matrix and the clip-rect is not updated in the internal constant-buffer. Can be used as an optimization when a previous call has already set the correct data.</summary>
        ConstantsPrepared = 0x100,

        /// <summary>The internal vertex and index buffer (if used) are assumed to already be bound. Can be used as an optimization when a previous call has already set the buffers.</summary>
        BuffersPrepared = 0x200,

        /// <summary>The correct shaders/constant-buffer etc. are assumed to already be bound. Can be used as an optimization when a previous call has already set the states, or to override the default states.</summary>
        StatePrepared = 0x400,

        /// <summary>Can be used as an optimization on subsequent calls, when drawing several strings with the same settings.</summary>
        ImmediateCall = ConstantsPrepared | BuffersPrepared | StatePrepared,

        /// <summary>When a draw method returns, the device-context will have been restored to the same state as before the call.</summary>
        RestoreState = 0x800,

        /// <summary>Any new glyphs added during a call are not flushed to the device-resources.
        /// It is a good idea to use this flag for text-operations on deferred contexts, when drawing text on multiple threads simultaneously, in order to guarantee the proper order of operations.</summary>
        NoFlush = 0x1000,

        /// <summary>Any new glyphs will be cached in the atlas and glyph-maps, but no geometry is drawn.</summary>
        CacheOnly = 0x2000,

        /// <summary>No new glyphs will be added to the atlas or glyph-maps. Any glyphs not already present in the atlas will be replaced with a default fall-back glyph (empty box).</summary>
        NoNewGlyphs = 0x4000,

        /// <summary>A text-layout will be run through DirectWrite and new fonts will be prepared, but no actual drawing will take place, and no additional glyphs will be cached.</summary>
        AnalyzeOnly = 0x8000
    };

    #endregion

    /// <summary>
    /// Provides an interface for rendering text with a given font.
    /// </summary>
    public class Font : IDisposable
    {
        Factory factory;
        GlyphProvider glyphProvider;
        GlyphAtlas glyphAtlas;
        TextFormat defaultFormat;
        TextRenderer renderer;
        FeatureLevel featureLevel;
        RenderData renderStates;
        VertexDrawer glyphDrawer;

        /// <summary>
        /// Initializes a new instance of the <see cref="Font"/> class.
        /// </summary>
        /// <param name="factory">The DirectWrite factory.</param>
        /// <param name="device">The graphics device.</param>
        /// <param name="fontFamily">The font family.</param>
        public Font(Factory factory, Device device, string fontFamily)
            : this(factory, device, new CreateOptions(fontFamily))
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Font"/> class.
        /// </summary>
        /// <param name="factory">The DirectWrite factory.</param>
        /// <param name="device">The graphics device.</param>
        /// <param name="options">Various creation options.</param>
        public Font(Factory factory, Device device, CreateOptions options)
        {
            this.factory = factory;
            featureLevel = device.FeatureLevel;
            glyphAtlas = new GlyphAtlas(device, options.GlyphSheetWidth, options.GlyphSheetHeight, options.MaxGlyphCountPerSheet, 4096);
            glyphProvider = new GlyphProvider(factory, glyphAtlas, options.MaxGlyphWidth, options.MaxGlyphHeight);
            glyphDrawer = new VertexDrawer(device, options.VertexBufferSize);
            renderStates = new RenderData(device, options.AnisotropicFiltering);
            renderer = new TextRenderer(glyphProvider);

            if (!string.IsNullOrEmpty(options.DefaultFontParameters.FontFamily))
            {
                defaultFormat = factory.CreateTextFormat(
                    options.DefaultFontParameters.FontFamily,
                    options.DefaultFontParameters.FontWeight,
                    options.DefaultFontParameters.FontStyle,
                    options.DefaultFontParameters.FontStretch,
                    32.0f,
                    !string.IsNullOrEmpty(options.DefaultFontParameters.Locale) ? options.DefaultFontParameters.Locale : ""
                );
            }
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (glyphAtlas != null)
                glyphAtlas.Dispose();
            if (glyphProvider != null)
                glyphProvider.Dispose();
            if (renderStates != null)
                renderStates.Dispose();
            if (glyphDrawer != null)
                glyphDrawer.Dispose();
            if (defaultFormat != null)
                defaultFormat.Dispose();

            glyphAtlas = null;
            glyphProvider = null;
            renderStates = null;
            glyphDrawer = null;
            defaultFormat = null;
        }

        /// <summary>
        /// Draws a string of text.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="text">The text to draw.</param>
        /// <param name="size">The font size.</param>
        /// <param name="x">The X position.</param>
        /// <param name="y">The Y position.</param>
        /// <param name="color">The font color.</param>
        /// <param name="flags">Text rendering flags.</param>
        public void DrawText(DeviceContext context, string text, float size, float x, float y, int color, TextOptions flags)
        {
            DrawText(context, text, null, size, x, y, color, flags);
        }

        /// <summary>
        /// Draws a string of text.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="text">The text to draw.</param>
        /// <param name="fontFamily">The font family.</param>
        /// <param name="size">The font size.</param>
        /// <param name="x">The X position.</param>
        /// <param name="y">The Y position.</param>
        /// <param name="color">The font color.</param>
        /// <param name="flags">Text rendering flags.</param>
        public void DrawText(DeviceContext context, string text, string fontFamily, float size, float x, float y, int color, TextOptions flags)
        {
            flags |= TextOptions.NoWordWrap;

            var layout = CreateTextLayout(text, fontFamily, size, new RectangleF(x, y, 0, 0), flags);
            DrawTextLayout(context, layout, x, y, color, flags);

            layout.Dispose();
        }

        /// <summary>
        /// Draws a string of text.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="text">The text to draw.</param>
        /// <param name="fontFamily">The font family.</param>
        /// <param name="size">The font size.</param>
        /// <param name="layoutBounds">The layout bounds.</param>
        /// <param name="color">The font color.</param>
        /// <param name="clipBounds">The clipping bounds.</param>
        /// <param name="transformMatrix">The transform matrix.</param>
        /// <param name="flags">Text rendering flags.</param>
        public void DrawText(DeviceContext context, string text, string fontFamily, float size, RectangleF layoutBounds, int color, RectangleF clipBounds, Matrix transformMatrix, TextOptions flags)
        {
            using (var layout = CreateTextLayout(text, fontFamily, size, layoutBounds, flags))
                DrawTextLayout(context, layout, layoutBounds.X, layoutBounds.Y, color, clipBounds, transformMatrix, flags);
        }

        /// <summary>
        /// Draws a span of formatted text.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="textLayout">The formatted text span to draw.</param>
        /// <param name="originX">The X origin of the text.</param>
        /// <param name="originY">The Y origin of the text.</param>
        /// <param name="color">The text color.</param>
        /// <param name="flags">Text rendering flags.</param>
        public void DrawTextLayout(DeviceContext context, TextLayout textLayout, float originX, float originY, int color, TextOptions flags)
        {
            AnalyzeTextLayout(context, textLayout, originX, originY, color, flags);
            if ((flags & TextOptions.AnalyzeOnly) == 0 && (flags & TextOptions.CacheOnly) == 0)
                unsafe { DrawGeometry(context, null, null, flags); }
        }

        /// <summary>
        /// Draws a span of formatted text.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="textLayout">The formatted text span to draw.</param>
        /// <param name="originX">The X origin of the text.</param>
        /// <param name="originY">The Y origin of the text.</param>
        /// <param name="color">The text color.</param>
        /// <param name="clipBounds">The clipping bounds.</param>
        /// <param name="transformMatrix">The transform matrix.</param>
        /// <param name="flags">Text rendering flags.</param>
        public void DrawTextLayout(DeviceContext context, TextLayout textLayout, float originX, float originY, int color, RectangleF clipBounds, Matrix transformMatrix, TextOptions flags)
        {
            AnalyzeTextLayout(context, textLayout, originX, originY, color, flags);
            if ((flags & TextOptions.AnalyzeOnly) == 0 && (flags & TextOptions.CacheOnly) == 0)
                unsafe { DrawGeometry(context, &clipBounds, &transformMatrix, flags); }
        }

        /// <summary>
        /// Measures the text and returns the bounding metrics.
        /// </summary>
        /// <param name="text">The text to measure.</param>
        /// <param name="fontFamily">The font family.</param>
        /// <param name="size">The font size.</param>
        /// <param name="layoutBounds">The layout bounds.</param>
        /// <param name="flags">Text rendering flags.</param>
        /// <returns>A rectangle denoting the extents of the measured text.</returns>
        public RectangleF MeasureText(string text, string fontFamily, float size, RectangleF layoutBounds, TextOptions flags)
        {
            var result = new RectangleF(layoutBounds.Left, layoutBounds.Top, 0, 0);
            var layout = CreateTextLayout(text, fontFamily, size, layoutBounds, flags);
            var metrics = layout.OverhangMetrics;

            result.X = (float)Math.Floor(layoutBounds.Left - metrics.Left);
            result.Y = (float)Math.Floor(layoutBounds.Top - metrics.Top);
            result.Width = (float)Math.Ceiling(layoutBounds.Left + metrics.Right) - result.X;
            result.Height = (float)Math.Ceiling(layoutBounds.Top + metrics.Bottom) - result.Y;

            return result;
        }

        /// <summary>
        /// Flushes the glyph atlas.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        public void Flush(DeviceContext context)
        {
            glyphAtlas.Flush(context);
        }

        TextLayout CreateTextLayout(string text, string fontFamily, float size, RectangleF bounds, TextOptions flags)
        {
            if (defaultFormat == null)
                throw new InvalidOperationException("No default format set for font.");

            var layout = new TextLayout(factory, text, defaultFormat, bounds.Width, bounds.Height);
            var range = new TextRange(0, text.Length);

            layout.SetFontSize(size, range);
            if (fontFamily != null)
                layout.SetFontFamilyName(fontFamily, range);

            if ((flags & TextOptions.NoWordWrap) != 0)
                layout.WordWrapping = WordWrapping.NoWrap;

            if ((flags & TextOptions.Right) != 0)
                layout.TextAlignment = TextAlignment.Trailing;
            else if ((flags & TextOptions.Center) != 0)
                layout.TextAlignment = TextAlignment.Center;

            if ((flags & TextOptions.Bottom) != 0)
                layout.ParagraphAlignment = ParagraphAlignment.Far;
            else if ((flags & TextOptions.VerticalCenter) != 0)
                layout.ParagraphAlignment = ParagraphAlignment.Center;

            return layout;
        }

        void AnalyzeTextLayout(DeviceContext context, TextLayout layout, float originX, float originY, int color, TextOptions flags)
        {
            renderer.DrawTextLayout(layout, originX, originY, color, flags);

            // flush the glyph atlas in case any new glyphs were added
            if ((flags & TextOptions.NoFlush) == 0)
                glyphAtlas.Flush(context);
        }

        unsafe void DrawGeometry(DeviceContext context, RectangleF* clipBounds, Matrix* transformMatrix, TextOptions flags)
        {
            using (new StateSaver(context, (flags & TextOptions.RestoreState) != 0))
            {
                // set states and shaders
                if ((flags & TextOptions.StatePrepared) == 0)
                    renderStates.SetStates(context, flags);
                if ((flags & TextOptions.ConstantsPrepared) == 0)
                    renderStates.UpdateShaderConstants(context, clipBounds, transformMatrix);

                // draw glyphs
                glyphDrawer.DrawVertices(context, glyphAtlas, renderer.SortVertices(), flags);
            }
        }
    }
}
