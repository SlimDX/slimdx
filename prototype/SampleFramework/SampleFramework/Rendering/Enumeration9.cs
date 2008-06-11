using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Linq;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains information about a single graphics adapter.
    /// </summary>
    class AdapterInfo9
    {
        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the adapter details.
        /// </summary>
        /// <value>The adapter details.</value>
        public AdapterDetails Details
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the description.
        /// </summary>
        /// <value>The description.</value>
        public string Description
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the display modes.
        /// </summary>
        /// <value>The display modes.</value>
        public List<DisplayMode> DisplayModes
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the devices.
        /// </summary>
        /// <value>The devices.</value>
        public List<DeviceInfo9> Devices
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AdapterInfo9"/> class.
        /// </summary>
        public AdapterInfo9()
        {
            // create lists
            DisplayModes = new List<DisplayMode>();
            Devices = new List<DeviceInfo9>();
        }
    }

    /// <summary>
    /// Contains information about a single graphics device.
    /// </summary>
    class DeviceInfo9
    {
        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the type of the device.
        /// </summary>
        /// <value>The type of the device.</value>
        public DeviceType DeviceType
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the capabilities.
        /// </summary>
        /// <value>The capabilities.</value>
        public Capabilities Capabilities
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the device settings.
        /// </summary>
        /// <value>The device settings.</value>
        public List<SettingsCombo9> DeviceSettings
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceInfo9"/> class.
        /// </summary>
        public DeviceInfo9()
        {
            // create the list
            DeviceSettings = new List<SettingsCombo9>();
        }
    }

    /// <summary>
    /// Contains information about a combination of device settings.
    /// </summary>
    class SettingsCombo9
    {
        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the type of the device.
        /// </summary>
        /// <value>The type of the device.</value>
        public DeviceType DeviceType
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the adapter format.
        /// </summary>
        /// <value>The adapter format.</value>
        public Format AdapterFormat
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the back buffer format.
        /// </summary>
        /// <value>The back buffer format.</value>
        public Format BackBufferFormat
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="SettingsCombo9"/> is windowed.
        /// </summary>
        /// <value><c>true</c> if windowed; otherwise, <c>false</c>.</value>
        public bool Windowed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the depth stencil formats.
        /// </summary>
        /// <value>The depth stencil formats.</value>
        public List<Format> DepthStencilFormats
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the multisample types.
        /// </summary>
        /// <value>The multisample types.</value>
        public List<MultisampleType> MultisampleTypes
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the multisample qualities.
        /// </summary>
        /// <value>The multisample qualities.</value>
        public List<int> MultisampleQualities
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the present intervals.
        /// </summary>
        /// <value>The present intervals.</value>
        public List<PresentInterval> PresentIntervals
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the depth stencil conflicts.
        /// </summary>
        /// <value>The depth stencil conflicts.</value>
        public List<DepthStencilConflict9> DepthStencilConflicts
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the adapter info.
        /// </summary>
        /// <value>The adapter info.</value>
        public AdapterInfo9 AdapterInfo
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the device info.
        /// </summary>
        /// <value>The device info.</value>
        public DeviceInfo9 DeviceInfo
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsCombo9"/> class.
        /// </summary>
        public SettingsCombo9()
        {
            // create the lists
            DepthStencilFormats = new List<Format>();
            DepthStencilConflicts = new List<DepthStencilConflict9>();
            MultisampleQualities = new List<int>();
            MultisampleTypes = new List<MultisampleType>();
            PresentIntervals = new List<PresentInterval>();
        }
    }

    /// <summary>
    /// Contains information about a depth stencil conflict.
    /// </summary>
    class DepthStencilConflict9
    {
        /// <summary>
        /// Gets or sets the depth stencil format.
        /// </summary>
        /// <value>The depth stencil format.</value>
        public Format DepthStencilFormat
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the multisample type.
        /// </summary>
        /// <value>The multisample type.</value>
        public MultisampleType MultisampleType
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DepthStencilConflict9"/> class.
        /// </summary>
        public DepthStencilConflict9()
        {
        }
    }

    /// <summary>
    /// Handles the comparison between two display modes.
    /// </summary>
    class DisplayModeComparer9 : IComparer<DisplayMode>
    {
        // variables
        static DisplayModeComparer9 comparer = new DisplayModeComparer9();

        /// <summary>
        /// Gets the global comparer.
        /// </summary>
        /// <value>The global comparer.</value>
        public static DisplayModeComparer9 Comparer
        {
            get { return comparer; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DisplayModeComparer9"/> class.
        /// </summary>
        public DisplayModeComparer9()
        {
        }

        /// <summary>
        /// Compares two objects and returns a value indicating whether one is less than, equal to, or greater than the other.
        /// </summary>
        /// <param name="x">The first object to compare.</param>
        /// <param name="y">The second object to compare.</param>
        /// <returns>
        /// Value Condition Less than zerox is less than y.Zerox equals y.Greater than zerox is greater than y.
        /// </returns>
        public int Compare(DisplayMode x, DisplayMode y)
        {
            // compare each field
            if (x.Width > y.Width)
                return 1;
            if (x.Width < y.Width)
                return -1;
            if (x.Height > y.Height)
                return 1;
            if (x.Height < y.Height)
                return -1;
            if (x.Format > y.Format)
                return 1;
            if (x.Format < y.Format)
                return -1;
            if (x.RefreshRate > y.RefreshRate)
                return 1;
            if (x.RefreshRate < y.RefreshRate)
                return -1;

            // the two instances are equal
            return 0;
        }
    }

    /// <summary>
    /// Handles device type enumeration.
    /// </summary>
    static class Enumeration9
    {
        // variables
        static int maxMultisampleQuality = 65535;

        /// <summary>
        /// Gets the Adapters that were enumerated.
        /// </summary>
        /// <value>The Adapters that were enumerated.</value>
        public static List<AdapterInfo9> Adapters
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the possible depth stencil formats.
        /// </summary>
        /// <value>The possible depth stencil formats.</value>
        public static List<Format> PossibleDepthStencilFormats
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the possible multisample types.
        /// </summary>
        /// <value>The possible multisample types.</value>
        public static List<MultisampleType> PossibleMultisampleTypes
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the possible present intervals.
        /// </summary>
        /// <value>The possible present intervals.</value>
        public static List<PresentInterval> PossiblePresentIntervals
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a value indicating whether the devices have been enumerated.
        /// </summary>
        /// <value>
        /// <c>true</c> if the devices have been enumerated; otherwise, <c>false</c>.
        /// </value>
        public static bool HasEnumerated
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether software vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if software vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireSoftwareVertexProcessing
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether hardware vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if hardware vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireHardwareVertexProcessing
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether pure hardware vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if pure hardware vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequirePureHardwareVertexProcessing
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether mixed vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if mixed vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireMixedVertexProcessing
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether post pixel shader blending is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if post pixel shader blending is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequirePostPixelShaderBlending
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum resolution.
        /// </summary>
        /// <value>The minimum resolution.</value>
        public static Size MinimumResolution
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum resolution.
        /// </summary>
        /// <value>The maximum resolution.</value>
        public static Size MaximumResolution
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum refresh rate.
        /// </summary>
        /// <value>The minimum refresh rate.</value>
        public static int MinimumRefreshRate
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum refresh rate.
        /// </summary>
        /// <value>The maximum refresh rate.</value>
        public static int MaximumRefreshRate
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum multisample quality.
        /// </summary>
        /// <value>The maximum multisample quality.</value>
        public static int MaximumMultisampleQuality
        {
            get { return maxMultisampleQuality; }
            set
            {
                maxMultisampleQuality = value;
                if (maxMultisampleQuality > 65535)
                    maxMultisampleQuality = 65535;
            }
        }

        /// <summary>
        /// Initializes the <see cref="Enumeration9"/> class.
        /// </summary>
        static Enumeration9()
        {
            // set default values
            RequirePostPixelShaderBlending = true;
            MinimumResolution = new Size(640, 480);
            MaximumResolution = new Size(int.MaxValue, int.MaxValue);
            MaximumRefreshRate = int.MaxValue;
            RequireSoftwareVertexProcessing = true;
            RequireHardwareVertexProcessing = true;
            RequirePureHardwareVertexProcessing = true;
            Adapters = new List<AdapterInfo9>();

            // reset the lists
            ResetPossibleDepthStencilFormats();
            ResetPossibleMultisampleTypes();
            ResetPossiblePresentIntervals();
        }

        /// <summary>
        /// Gets the adapter information descriptor for the given adapter.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <returns>
        /// The adapter information descriptor for the given adapter, or <c>null</c>
        /// if a valid combination cannot be found.
        /// </returns>
        public static AdapterInfo9 GetAdapterInfo(int adapterOrdinal)
        {
            // return the correct adapter
            return Adapters.FirstOrDefault(adapter => adapter.AdapterOrdinal == adapterOrdinal);
        }

        /// <summary>
        /// Gets the device information descriptor for the given settings.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <param name="deviceType">Type of the device.</param>
        /// <returns>
        /// The device information descriptor for the given settings, or <c>null</c>
        /// if a valid combination cannot be found.
        /// </returns>
        public static DeviceInfo9 GetDeviceInfo(int adapterOrdinal, DeviceType deviceType)
        {
            // grab the adapter
            AdapterInfo9 info = GetAdapterInfo(adapterOrdinal);
            if (info != null)
                return info.Devices.FirstOrDefault(device => device.DeviceType == deviceType);

            // otherwise, we don't have it
            return null;
        }

        /// <summary>
        /// Gets the settings combination for the given settings.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <param name="deviceType">Type of the device.</param>
        /// <param name="adapterFormat">The adapter format.</param>
        /// <param name="backBufferFormat">The back buffer format.</param>
        /// <param name="windowed">if set to <c>true</c>, searches for windowed settings.</param>
        /// <returns>
        /// The settings combination for the given settings, or <c>null</c> if a valid combination
        /// cannot be found.
        /// </returns>
        public static SettingsCombo9 GetSettingsCombo(int adapterOrdinal, DeviceType deviceType,
            Format adapterFormat, Format backBufferFormat, bool windowed)
        {
            // grab the device
            DeviceInfo9 info = GetDeviceInfo(adapterOrdinal, deviceType);
            if (info != null)
                return info.DeviceSettings.FirstOrDefault(setting =>
                    (setting.AdapterFormat == adapterFormat) &&
                    (setting.BackBufferFormat == backBufferFormat) &&
                    (setting.Windowed == windowed));

            // otherwise, we don't have it
            return null;
        }

        /// <summary>
        /// Resets the possible depth stencil formats.
        /// </summary>
        public static void ResetPossibleDepthStencilFormats()
        {
            // reset the list
            PossibleDepthStencilFormats = new List<Format> {
                Format.D16,     Format.D15S1,   Format.D24X8,
                Format.D24S8,   Format.D24X4S4, Format.D32 };
        }

        /// <summary>
        /// Resets the possible multisample types.
        /// </summary>
        public static void ResetPossibleMultisampleTypes()
        {
            // reset the list
            PossibleMultisampleTypes = new List<MultisampleType>() {
                MultisampleType.None,               MultisampleType.NonMaskable,
                MultisampleType.TwoSamples,         MultisampleType.ThreeSamples,
                MultisampleType.FourSamples,        MultisampleType.FiveSamples,
                MultisampleType.SixSamples,         MultisampleType.SevenSamples,
                MultisampleType.EightSamples,       MultisampleType.NineSamples,
                MultisampleType.TenSamples,         MultisampleType.ElevenSamples,
                MultisampleType.TwelveSamples,      MultisampleType.ThirteenSamples,
                MultisampleType.FourteenSamples,    MultisampleType.FifteenSamples,
                MultisampleType.SixteenSamples
            };
        }

        /// <summary>
        /// Resets the possible present intervals.
        /// </summary>
        public static void ResetPossiblePresentIntervals()
        {
            // reset the list
            PossiblePresentIntervals = new List<PresentInterval>() {
                PresentInterval.Immediate,  PresentInterval.Default,
                PresentInterval.One,        PresentInterval.Two,
                PresentInterval.Three,      PresentInterval.Four
            };
        }

        /// <summary>
        /// Enumerates through all possible graphics devices.
        /// </summary>
        public static void Enumerate()
        {
            // intialize variables for the enumeration
            HasEnumerated = true;
            Adapters = new List<AdapterInfo9>();
            List<Format> adapterFormats = new List<Format>();
            Format[] allowedAdapterFormats = { Format.X8R8G8B8, Format.X1R5G5B5, Format.R5G6B5, 
                Format.A2R10G10B10 };

            // loop through each adapter
            int adapterCount = Direct3D.AdapterCount;
            for (int adapterOrdinal = 0; adapterOrdinal < adapterCount; adapterOrdinal++)
            {
                // setup the adapter info structure
                AdapterInfo9 AdapterInfo9 = new AdapterInfo9();
                DisplayMode displayMode;
                AdapterInfo9.AdapterOrdinal = adapterOrdinal;
                AdapterInfo9.Details = Direct3D.GetAdapterIdentifier(adapterOrdinal);

                // loop through each possible format
                adapterFormats.Clear();
                for (int formatList = 0; formatList < allowedAdapterFormats.Length; formatList++)
                {
                    // grab the format
                    Format allowedAdapterFormat = allowedAdapterFormats[formatList];

                    // loop through each possible mode
                    int adapterModeCount = Direct3D.GetAdapterModeCount(adapterOrdinal, allowedAdapterFormat);
                    for (int mode = 0; mode < adapterModeCount; mode++)
                    {
                        // grab the display mode
                        displayMode = Direct3D.EnumerateAdapterModes(adapterOrdinal, allowedAdapterFormat, mode);

                        // make sure we can use this display mode
                        if (displayMode.Width < MinimumResolution.Width ||
                            displayMode.Width > MaximumResolution.Width ||
                            displayMode.Height < MinimumResolution.Height ||
                            displayMode.Height > MaximumResolution.Height ||
                            displayMode.RefreshRate < MinimumRefreshRate ||
                            displayMode.RefreshRate > MaximumRefreshRate)
                            continue;

                        // add the mode to the list
                        AdapterInfo9.DisplayModes.Add(displayMode);

                        // add the format to the adapter
                        if (!adapterFormats.Contains(displayMode.Format))
                            adapterFormats.Add(displayMode.Format);
                    }
                }

                // grab the display mode and make sure it's in the list
                displayMode = Direct3D.GetAdapterDisplayMode(adapterOrdinal);
                if (!adapterFormats.Contains(displayMode.Format))
                    adapterFormats.Add(displayMode.Format);

                // sort the list
                AdapterInfo9.DisplayModes.Sort(DisplayModeComparer9.Comparer);

                // enumerate all the devices on this adapter
                EnumerateDevices(AdapterInfo9, adapterFormats);

                // only keep this adapter if it has valid devices
                if (AdapterInfo9.Devices.Count > 0)
                    Adapters.Add(AdapterInfo9);
            }

            // check if all of the adapter names are unique
            bool unique = !Adapters.Any(adapter1 => Adapters.Any(adapter2 =>
                adapter1.Details.Description == adapter2.Details.Description));

            // loop through each adapter to build up the descriptions
            foreach (AdapterInfo9 info in Adapters)
            {
                // build up the description string
                info.Description = info.Details.Description;
                if (!unique)
                    info.Description += " " + info.AdapterOrdinal.ToString(CultureInfo.CurrentCulture);
            }
        }

        /// <summary>
        /// Enumerates the devices on a given adapter.
        /// </summary>
        /// <param name="info">The adapter info.</param>
        /// <param name="adapterFormats">The adapter formats.</param>
        static void EnumerateDevices(AdapterInfo9 info, List<Format> adapterFormats)
        {
            // setup possible device types
            DeviceType[] deviceTypes = { DeviceType.Hardware, DeviceType.Reference };

            // loop through each possible device type
            for (int deviceType = 0; deviceType < deviceTypes.Length; deviceType++)
            {
                // build up the device
                DeviceInfo9 DeviceInfo9 = new DeviceInfo9();
                DeviceInfo9.AdapterOrdinal = info.AdapterOrdinal;
                DeviceInfo9.DeviceType = deviceTypes[deviceType];
                DeviceInfo9.Capabilities = Direct3D.GetDeviceCaps(info.AdapterOrdinal, DeviceInfo9.DeviceType);

                // enumerate the settings on this device
                EnumerateSettingsCombos(info, DeviceInfo9, adapterFormats);

                // only keep the device if it has valid settings combos
                if (DeviceInfo9.DeviceSettings.Count > 0)
                    info.Devices.Add(DeviceInfo9);
            }
        }

        /// <summary>
        /// Enumerates the settings combos on a device.
        /// </summary>
        /// <param name="adapterInfo">The adapter info.</param>
        /// <param name="deviceInfo">The device info.</param>
        /// <param name="adapterFormats">The adapter formats.</param>
        static void EnumerateSettingsCombos(AdapterInfo9 adapterInfo, DeviceInfo9 deviceInfo, List<Format> adapterFormats)
        {
            // setup possible back buffer formats
            Format[] backBufferFormats = { Format.A8R8G8B8, Format.X8R8G8B8, Format.A2R10G10B10,
                Format.R5G6B5, Format.A1R5G5B5, Format.X1R5G5B5 };

            // loop through each adapter format
            foreach (Format adapterFormat in adapterFormats)
            {
                // loop through each back buffer format
                foreach (Format backBufferFormat in backBufferFormats)
                {
                    // loop through each windowed mode
                    for (int windowed = 0; windowed < 2; windowed++)
                    {
                        // check if we don't have any display modes
                        if (windowed == 0 && adapterInfo.DisplayModes.Count == 0)
                            continue;

                        // make sure we have a valid device type
                        if (!Direct3D.CheckDeviceType(adapterInfo.AdapterOrdinal, deviceInfo.DeviceType,
                            adapterFormat, backBufferFormat, (windowed == 1)))
                            continue;

                        // check if post pixel shader blending is required
                        if (RequirePostPixelShaderBlending && !Direct3D.CheckDeviceFormat(adapterInfo.AdapterOrdinal,
                            deviceInfo.DeviceType, adapterFormat, Usage.QueryPostPixelShaderBlending,
                            ResourceType.Texture, backBufferFormat))
                            continue;

                        // build up the settings combo
                        SettingsCombo9 combo = new SettingsCombo9();
                        combo.AdapterOrdinal = adapterInfo.AdapterOrdinal;
                        combo.DeviceType = deviceInfo.DeviceType;
                        combo.AdapterFormat = adapterFormat;
                        combo.BackBufferFormat = backBufferFormat;
                        combo.Windowed = (windowed == 1);
                        combo.AdapterInfo = adapterInfo;
                        combo.DeviceInfo = deviceInfo;

                        // build up info lists
                        BuildDepthStencilFormatList(combo);
                        BuildMultisampleTypeList(combo);

                        // make sure we have at least one multisample type
                        if (combo.MultisampleTypes.Count == 0)
                            continue;

                        // build up more info lists
                        BuildDepthStencilConflictList(combo);
                        BuildPresentIntervalList(combo);

                        // add the item to the list
                        deviceInfo.DeviceSettings.Add(combo);
                    }
                }
            }
        }

        /// <summary>
        /// Builds the depth stencil format list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildDepthStencilFormatList(SettingsCombo9 combo)
        {
            // build up the list
            combo.DepthStencilFormats = PossibleDepthStencilFormats.Where(format =>
                Direct3D.CheckDeviceFormat(combo.AdapterOrdinal, combo.DeviceType, combo.AdapterFormat,
                    Usage.DepthStencil, ResourceType.Surface, format) &&
                    Direct3D.CheckDepthStencilMatch(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.BackBufferFormat, format)).ToList();
        }

        /// <summary>
        /// Builds the multisample type list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildMultisampleTypeList(SettingsCombo9 combo)
        {
            // loop through each multisample type
            int quality;
            foreach (MultisampleType type in PossibleMultisampleTypes)
            {
                // check if the multisample type is valid
                if (Direct3D.CheckDeviceMultisampleType(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.Windowed, type, out quality))
                {
                    // add the items to the list
                    combo.MultisampleTypes.Add(type);
                    if (quality > maxMultisampleQuality + 1)
                        quality = maxMultisampleQuality + 1;
                    combo.MultisampleQualities.Add(quality);
                }
            }
        }

        /// <summary>
        /// Builds the depth stencil conflict list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildDepthStencilConflictList(SettingsCombo9 combo)
        {
            // check each format
            foreach (Format format in combo.DepthStencilFormats)
            {
                // check each multisample type
                foreach (MultisampleType type in combo.MultisampleTypes)
                {
                    // check for errors
                    if (!Direct3D.CheckDeviceMultisampleType(combo.AdapterOrdinal, combo.DeviceType,
                        format, combo.Windowed, type))
                    {
                        // build up the conflict
                        DepthStencilConflict9 conflict = new DepthStencilConflict9();
                        conflict.DepthStencilFormat = format;
                        conflict.MultisampleType = type;

                        // add the item to the list
                        combo.DepthStencilConflicts.Add(conflict);
                    }
                }
            }
        }

        /// <summary>
        /// Builds the present interval list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildPresentIntervalList(SettingsCombo9 combo)
        {
            // loop through each possible present interval
            foreach (PresentInterval interval in PossiblePresentIntervals)
            {
                // if we are windowed we can't use higher intervals
                if (combo.Windowed && (interval == PresentInterval.Two ||
                    interval == PresentInterval.Three || interval == PresentInterval.Four))
                    continue;

                // check if we can add the item to the list
                if (interval == PresentInterval.Default ||
                    (combo.DeviceInfo.Capabilities.PresentationIntervals & interval) != 0)
                    combo.PresentIntervals.Add(interval);
            }
        }
    }
}
