/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System.Collections.Generic;
using System.Globalization;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains information about a Direct3D9 adapter.
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
    /// Contains information about a Direct3D9 device.
    /// </summary>
    class DeviceInfo9
    {
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
    /// Contains a unique combination of Direct3D9 device settings.
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
            MultisampleQualities = new List<int>();
            MultisampleTypes = new List<MultisampleType>();
            PresentIntervals = new List<PresentInterval>();
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
    /// Handles device type enumeration for Direct3D9.
    /// </summary>
    static class Enumeration9
    {
        /// <summary>
        /// Gets or sets the minimum required settings.
        /// </summary>
        /// <value>The minimum required settings.</value>
        public static DeviceSettings MinimumSettings
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the adapters that were enumerated.
        /// </summary>
        /// <value>The adapters that were enumerated.</value>
        public static List<AdapterInfo9> Adapters
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
            foreach (AdapterInformation adapter in Direct3D.Adapters)
            {
                // set up the adapter info structure
                AdapterInfo9 info = new AdapterInfo9();
                info.AdapterOrdinal = adapter.Adapter;
                info.Details = adapter.Details;

                // loop through each possible format
                adapterFormats.Clear();
                foreach (Format adapterFormat in allowedAdapterFormats)
                {
                    // loop through each possible mode
                    foreach (DisplayMode displayMode in adapter.GetDisplayModes(adapterFormat))
                    {
                        // if we have minimum settings, make sure this display mode passes them
                        if (MinimumSettings != null)
                        {
                            // make sure the settings are sufficient
                            if (displayMode.Width < MinimumSettings.BackBufferWidth ||
                                displayMode.Height < MinimumSettings.BackBufferHeight ||
                                displayMode.RefreshRate < MinimumSettings.RefreshRate)
                                continue;
                        }

                        // add the mode to the list
                        info.DisplayModes.Add(displayMode);

                        // add the format to the adapter
                        if (!adapterFormats.Contains(displayMode.Format))
                            adapterFormats.Add(displayMode.Format);
                    }
                }

                // make sure the current display mode is in the list
                if (!adapterFormats.Contains(adapter.CurrentDisplayMode.Format))
                    adapterFormats.Add(adapter.CurrentDisplayMode.Format);

                // sort the list
                info.DisplayModes.Sort(DisplayModeComparer9.Comparer);

                // enumerate all the devices on this adapter
                EnumerateDevices(info, adapterFormats);

                // only keep this adapter if it has valid devices
                if (info.Devices.Count > 0)
                    Adapters.Add(info);
            }

            // check if all of the adapter names are unique
            bool unique = true;
            foreach (AdapterInfo9 adapter1 in Adapters)
            {
                // check each adapter against every other adapter
                foreach (AdapterInfo9 adapter2 in Adapters)
                {
                    // check for a duplicate name
                    if (adapter1 == adapter2)
                        continue;
                    if (adapter1.Details.Description == adapter2.Details.Description)
                    {
                        // not unique
                        unique = false;
                        break;
                    }
                }

                // check for a cut off right now
                if (!unique)
                    break;
            }

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
            foreach (DeviceType deviceType in deviceTypes)
            {
                // check the device type
                if (MinimumSettings != null && MinimumSettings.DeviceType != deviceType)
                    continue;

                // build up the device
                DeviceInfo9 deviceInfo = new DeviceInfo9();
                deviceInfo.DeviceType = deviceType;
                deviceInfo.Capabilities = Direct3D.GetDeviceCaps(info.AdapterOrdinal, deviceInfo.DeviceType);

                // enumerate the settings on this device
                EnumerateSettingsCombos(info, deviceInfo, adapterFormats);

                // only keep the device if it has valid settings combos
                if (deviceInfo.DeviceSettings.Count > 0)
                    info.Devices.Add(deviceInfo);
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
                        if (!Direct3D.CheckDeviceFormat(adapterInfo.AdapterOrdinal,
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
                        BuildPresentIntervalList(combo);

                        // make sure the combo supports the minimum settings
                        if (MinimumSettings != null)
                        {
                            // check the back buffer format
                            if (MinimumSettings.BackBufferFormat != Format.Unknown &&
                                MinimumSettings.BackBufferFormat != backBufferFormat)
                                continue;

                            // check the depth stencil format
                            if (MinimumSettings.DepthStencilFormat != Format.Unknown &&
                                !combo.DepthStencilFormats.Contains(MinimumSettings.DepthStencilFormat))
                                continue;

                            // check the multisample type
                            if (!combo.MultisampleTypes.Contains(MinimumSettings.MultisampleType))
                                continue;
                        }

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
            List<Format> possibleDepthStencilFormats = new List<Format> {
                Format.D16,     Format.D15S1,   Format.D24X8,
                Format.D24S8,   Format.D24X4S4, Format.D32 };

            // return the valid depth stencil formats
            foreach (Format format in possibleDepthStencilFormats)
            {
                // check for a valid format
                if (Direct3D.CheckDeviceFormat(combo.AdapterOrdinal, combo.DeviceType, combo.AdapterFormat,
                    Usage.DepthStencil, ResourceType.Surface, format) &&
                    Direct3D.CheckDepthStencilMatch(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.BackBufferFormat, format))
                    combo.DepthStencilFormats.Add(format);
            }
        }

        /// <summary>
        /// Builds the multisample type list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildMultisampleTypeList(SettingsCombo9 combo)
        {
            // build the list
            List<MultisampleType> possibleMultisampleTypes = new List<MultisampleType>() {
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

            // loop through each multisample type
            int quality;
            foreach (MultisampleType type in possibleMultisampleTypes)
            {
                // check if the multisample type is valid
                if (Direct3D.CheckDeviceMultisampleType(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.Windowed, type, out quality))
                {
                    // add the items to the list
                    combo.MultisampleTypes.Add(type);
                    combo.MultisampleQualities.Add(quality);
                }
            }
        }

        /// <summary>
        /// Builds the present interval list for a given combo.
        /// </summary>
        /// <param name="combo">The combo.</param>
        static void BuildPresentIntervalList(SettingsCombo9 combo)
        {
            // build the list
            List<PresentInterval> possiblePresentIntervals = new List<PresentInterval>() {
                PresentInterval.Immediate,  PresentInterval.Default,
                PresentInterval.One,        PresentInterval.Two,
                PresentInterval.Three,      PresentInterval.Four
            };

            // loop through each possible present interval
            foreach (PresentInterval interval in possiblePresentIntervals)
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
