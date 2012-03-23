using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;

namespace SlimDX.Toolkit
{
    /// <summary>Describes a single font.</summary>
    /// <remarks>If FontFamily is <c>null</c> when creating a font object, no default font will be set up.
    /// This is perfectly valid when drawing text using one of the DrawTextLayout methods.
    /// However, the DrawText methods will silently fail if no default font is set up.<br/>
    /// If FontFamily is not <c>null</c>, the FontWeight, FontStyle and FontStretch members must be set to valid values according to the DirectWrite documentation.
    /// Zero is not a valid value for these.</remarks>
    public class DWriteFontParameters
    {
        /// <summary>The name of the font-family. Valid values include <i>Arial</i>, <i>Courier New</i>, etc. as long as the specified font is installed.
        /// Unavailable fonts will automatically fall back to a different font.
        /// This member can be set to <c>null</c>, if no default font is desired when using the structure to create a font-wrapper.</summary>
        public string FontFamily { get; set; }

        /// <summary>The font weight. See DirectWrite documentation.</summary>
        public FontWeight FontWeight { get; set; }

        /// <summary>The font style. See DirectWrite documentation.</summary>
        public FontStyle FontStyle { get; set; }

        /// <summary>The font stretch. See DirectWrite documentation.</summary>
        public FontStretch FontStretch { get; set; }

        /// <summary>The locale. <c>null</c> for default.</summary>
        public string Locale { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DWriteFontParameters"/> class.
        /// </summary>
        /// <param name="fontFamily">The font family.</param>
        public DWriteFontParameters(string fontFamily)
        {
            FontFamily = fontFamily;
            FontWeight = FontWeight.Normal;
            FontStyle = FontStyle.Normal;
            FontStretch = FontStretch.Normal;
            Locale = "";
        }
    }

    /// <summary>Describes settings used for creating Font objects.</summary>
    public class CreateOptions
    {
        /// <summary>The width of the glyph sheet textures to store glyph images in. 0 defaults to 512.</summary>
        public int GlyphSheetWidth { get; set; }

        /// <summary>The height of the glyph sheet textures to store glyph images in. 0 defaults to 512.</summary>
        public int GlyphSheetHeight { get; set; }

        /// <summary>The maximum number of glyphs per texture. A buffer of <i>MaxGlyphCountPerSheet * 32</i> bytes is preallocated for each sheet. 0 defaults to 2048.</summary>
        public int MaxGlyphCountPerSheet { get; set; }

        /// <summary>The number of mip-levels for the glyph sheet textures. 0 defaults to 1.</summary>
        public int SheetMipLevels { get; set; }

        /// <summary>If set to <c>true</c>, the sampler-state is created with anisotropic filtering.</summary>
        public bool AnisotropicFiltering { get; set; }

        /// <summary>The maximum width of a single glyph.
        /// This value is used to decide how large the DirectWrite render target needs to be, which is used when drawing glyph images to put in the atlas.
        /// 0 defaults to 384.</summary>
        public int MaxGlyphWidth { get; set; }

        /// <summary>The maximum height of a single glyph.
        /// This value is used to decide how large the DirectWrite render target needs to be, which is used when drawing glyph images to put in the atlas.
        /// 0 defaults to 384.</summary>
        public int MaxGlyphHeight { get; set; }

        /// <summary>If set to <c>true</c>, no geometry shader is used.</summary>
        public bool DisableGeometryShader { get; set; }

        /// <summary>The size in bytes of the dynamic vertex buffer to upload glyph vertices to when drawing a string. 0 defaults to 4096 * 16.<br/>
        /// Each glyph vertex is either 16 or 20 bytes in size, and each glyph requires either 1 or 4 vertices depending on if the geometry shader is used.</summary>
        public int VertexBufferSize { get; set; }

        /// <summary>Description of the default font. See DWriteFontParameters.</summary>
        public DWriteFontParameters DefaultFontParameters { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="CreateOptions"/> class.
        /// </summary>
        /// <param name="fontFamily">The font family.</param>
        public CreateOptions(string fontFamily)
        {
            DefaultFontParameters = new DWriteFontParameters(fontFamily);
            GlyphSheetWidth = 512;
            GlyphSheetHeight = 512;
            MaxGlyphCountPerSheet = 2048;
            SheetMipLevels = 1;
            MaxGlyphWidth = 384;
            MaxGlyphHeight = 384;
        }
    }
}
