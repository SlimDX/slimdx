using SlimDX.Direct3D9;

namespace Interface
{
    /// <summary>
    /// Stores details that can be used to recreate a cached font.
    /// </summary>
    public class CachedFont
    {
        #region Variables

        // variables
        Font font;
        string faceName;
        int height;
        FontWeight weight;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the device.
        /// </summary>
        /// <value>The device.</value>
        public Device Device
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the font.
        /// </summary>
        /// <value>The font.</value>
        public Font Font
        {
            get
            {
                // if we don't have a font yet, create one from the stored variables
                Create();
                return font;
            }
        }

        /// <summary>
        /// Gets or sets the face name.
        /// </summary>
        /// <value>The face name.</value>
        public string FaceName
        {
            get { return faceName; }
            set
            {
                // avoid unecessary changes
                if (faceName == value)
                    return;

                // update the value
                faceName = value;
                Release();
            }
        }

        /// <summary>
        /// Gets or sets the height.
        /// </summary>
        /// <value>The height.</value>
        public int Height
        {
            get { return height; }
            set
            {
                // avoid unecessary changes
                if (height == value)
                    return;

                // update the value
                height = value;
                Release();
            }
        }

        /// <summary>
        /// Gets or sets the weight.
        /// </summary>
        /// <value>The weight.</value>
        public FontWeight Weight
        {
            get { return weight; }
            set
            {
                // avoid unecessary changes
                if (weight == value)
                    return;

                // update the value
                weight = value;
                Release();
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="CachedFont"/> class.
        /// </summary>
        /// <param name="device">The device.</param>
        /// <param name="faceName">Name of the type face.</param>
        /// <param name="height">The height.</param>
        /// <param name="weight">The weight.</param>
        internal CachedFont(Device device, string faceName, int height, FontWeight weight)
        {
            // store variables
            Device = device;
            FaceName = faceName;
            Height = height;
            Weight = weight;
        }

        #endregion

        #region Methods

        /// <summary>
        /// Ensures that the internally managed font handle has been created.
        /// </summary>
        public void Create()
        {
            // ensure that the font has been created
            if (font == null && Device != null)
                font = new Font(Device, Height, 0, Weight, 1, false, CharacterSet.Default, Precision.Default,
                    FontQuality.Default, PitchAndFamily.Default | PitchAndFamily.DontCare, FaceName);
        }

        /// <summary>
        /// Releases the internally managed font handle.
        /// </summary>
        public void Release()
        {
            // release the font
            if (font != null)
                font.Dispose();
            font = null;
        }

        #endregion
    }
}
