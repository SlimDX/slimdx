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
using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;
using System.Drawing;
using System.Globalization;

namespace SampleFramework
{
    #region AdapterInfo

    /// <summary>
    /// Contains information about a single graphics adapter.
    /// </summary>
    public class AdapterInfo
    {
        #region Variables

        int adapterOrdinal;
        AdapterDetails details;
        string description;
        List<DisplayMode> displayModes = new List<DisplayMode>();
        List<DeviceInfo> devices = new List<DeviceInfo>();

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        /// <summary>
        /// Gets or sets the adapter details.
        /// </summary>
        /// <value>The adapter details.</value>
        public AdapterDetails Details
        {
            get { return details; }
            set { details = value; }
        }

        /// <summary>
        /// Gets or sets the description.
        /// </summary>
        /// <value>The description.</value>
        public string Description
        {
            get { return description; }
            set { description = value; }
        }

        /// <summary>
        /// Gets the display modes.
        /// </summary>
        /// <value>The display modes.</value>
        public List<DisplayMode> DisplayModes
        {
            get { return displayModes; }
        }

        /// <summary>
        /// Gets the devices.
        /// </summary>
        /// <value>The devices.</value>
        public List<DeviceInfo> Devices
        {
            get { return devices; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="AdapterInfo"/> class.
        /// </summary>
        public AdapterInfo()
        {
        }

        #endregion
    }

    #endregion

    #region DeviceInfo

    /// <summary>
    /// Contains information about a single graphics device.
    /// </summary>
    public class DeviceInfo
    {
        #region Variables

        int adapterOrdinal;
        DeviceType deviceType;
        Capabilities capabilities;
        List<SettingsCombo> deviceSettings = new List<SettingsCombo>();

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        /// <summary>
        /// Gets or sets the type of the device.
        /// </summary>
        /// <value>The type of the device.</value>
        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        /// <summary>
        /// Gets or sets the capabilities.
        /// </summary>
        /// <value>The capabilities.</value>
        public Capabilities Capabilities
        {
            get { return capabilities; }
            set { capabilities = value; }
        }

        /// <summary>
        /// Gets the device settings.
        /// </summary>
        /// <value>The device settings.</value>
        public List<SettingsCombo> DeviceSettings
        {
            get { return deviceSettings; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceInfo"/> class.
        /// </summary>
        public DeviceInfo()
        {
        }

        #endregion
    }

    #endregion

    #region SettingsCombo

    /// <summary>
    /// Contains information about a combination of device settings.
    /// </summary>
    public class SettingsCombo
    {
        #region Variables

        int adapterOrdinal;
        DeviceType deviceType;
        Format adapterFormat;
        Format backBufferFormat;
        bool windowed;
        List<Format> depthStencilFormats = new List<Format>();
        List<MultisampleType> multisampleTypes = new List<MultisampleType>();
        List<int> multisampleQualities = new List<int>();
        List<PresentInterval> presentIntervals = new List<PresentInterval>();
        List<DepthStencilConflict> depthStencilConflicts = new List<DepthStencilConflict>();
        AdapterInfo adapterInfo;
        DeviceInfo deviceInfo;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        /// <summary>
        /// Gets or sets the type of the device.
        /// </summary>
        /// <value>The type of the device.</value>
        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        /// <summary>
        /// Gets or sets the adapter format.
        /// </summary>
        /// <value>The adapter format.</value>
        public Format AdapterFormat
        {
            get { return adapterFormat; }
            set { adapterFormat = value; }
        }

        /// <summary>
        /// Gets or sets the back buffer format.
        /// </summary>
        /// <value>The back buffer format.</value>
        public Format BackBufferFormat
        {
            get { return backBufferFormat; }
            set { backBufferFormat = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="SettingsCombo"/> is windowed.
        /// </summary>
        /// <value><c>true</c> if windowed; otherwise, <c>false</c>.</value>
        public bool Windowed
        {
            get { return windowed; }
            set { windowed = value; }
        }

        /// <summary>
        /// Gets the depth stencil formats.
        /// </summary>
        /// <value>The depth stencil formats.</value>
        public List<Format> DepthStencilFormats
        {
            get { return depthStencilFormats; }
        }

        /// <summary>
        /// Gets the multisample types.
        /// </summary>
        /// <value>The multisample types.</value>
        public List<MultisampleType> MultisampleTypes
        {
            get { return multisampleTypes; }
        }

        /// <summary>
        /// Gets the multisample qualities.
        /// </summary>
        /// <value>The multisample qualities.</value>
        public List<int> MultisampleQualities
        {
            get { return multisampleQualities; }
        }

        /// <summary>
        /// Gets the present intervals.
        /// </summary>
        /// <value>The present intervals.</value>
        public List<PresentInterval> PresentIntervals
        {
            get { return presentIntervals; }
        }

        /// <summary>
        /// Gets the depth stencil conflicts.
        /// </summary>
        /// <value>The depth stencil conflicts.</value>
        public List<DepthStencilConflict> DepthStencilConflicts
        {
            get { return depthStencilConflicts; }
        }

        /// <summary>
        /// Gets or sets the adapter info.
        /// </summary>
        /// <value>The adapter info.</value>
        public AdapterInfo AdapterInfo
        {
            get { return adapterInfo; }
            set { adapterInfo = value; }
        }

        /// <summary>
        /// Gets or sets the device info.
        /// </summary>
        /// <value>The device info.</value>
        public DeviceInfo DeviceInfo
        {
            get { return deviceInfo; }
            set { deviceInfo = value; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsCombo"/> class.
        /// </summary>
        public SettingsCombo()
        {
        }

        #endregion
    }

    #endregion

    #region DepthStencilConflict

    /// <summary>
    /// Contains information about a depth stencil conflict.
    /// </summary>
    public class DepthStencilConflict
    {
        #region Variables

        Format depthStencilFormat;
        MultisampleType multisampleType;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the depth stencil format.
        /// </summary>
        /// <value>The depth stencil format.</value>
        public Format DepthStencilFormat
        {
            get { return depthStencilFormat; }
            set { depthStencilFormat = value; }
        }

        /// <summary>
        /// Gets or sets the multisample type.
        /// </summary>
        /// <value>The multisample type.</value>
        public MultisampleType MultisampleType
        {
            get { return multisampleType; }
            set { multisampleType = value; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="DepthStencilConflict"/> class.
        /// </summary>
        public DepthStencilConflict()
        {
        }

        #endregion
    }

    #endregion

    #region DisplayModeComparer

    /// <summary>
    /// Handles the comparison between two display modes.
    /// </summary>
    public class DisplayModeComparer : IComparer<DisplayMode>
    {
        #region Variables

        static DisplayModeComparer comparer = new DisplayModeComparer();

        #endregion

        #region Properties

        /// <summary>
        /// Gets the global comparer.
        /// </summary>
        /// <value>The global comparer.</value>
        public static DisplayModeComparer Comparer
        {
            get { return comparer; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="DisplayModeComparer"/> class.
        /// </summary>
        public DisplayModeComparer()
        {
        }

        #endregion

        #region Methods

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

            return 0;
        }

        #endregion
    }

    #endregion

    #region Enumeration

    /// <summary>
    /// Handles device type enumeration.
    /// </summary>
    public static class Enumeration
    {
        #region Variables

        static bool requirePostPixelShaderBlending = true;
        static Size minResolution = new Size(640, 480);
        static Size maxResolution = new Size(int.MaxValue, int.MaxValue);
        static int minRefresh;
        static int maxRefresh = int.MaxValue;
        static int maxMultisampleQuality = 65535;
        static bool softwareVP = true;
        static bool hardwareVP = true;
        static bool pureHardwareVP = true;
        static bool mixedVP;
        static bool hasEnumerated;
        static List<Format> possibleDepthStencilFormats;
        static List<MultisampleType> possibleMultisampleTypes;
        static List<PresentInterval> possiblePresentIntervals;
        static List<AdapterInfo> adapters;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the adapters that were enumerated.
        /// </summary>
        /// <value>The adapters that were enumerated.</value>
        public static List<AdapterInfo> Adapters
        {
            get { return adapters; }
        }

        /// <summary>
        /// Gets the possible depth stencil formats.
        /// </summary>
        /// <value>The possible depth stencil formats.</value>
        public static List<Format> PossibleDepthStencilFormats
        {
            get { return possibleDepthStencilFormats; }
        }

        /// <summary>
        /// Gets the possible multisample types.
        /// </summary>
        /// <value>The possible multisample types.</value>
        public static List<MultisampleType> PossibleMultisampleType
        {
            get { return possibleMultisampleTypes; }
        }

        /// <summary>
        /// Gets the possible present intervals.
        /// </summary>
        /// <value>The possible present intervals.</value>
        public static List<PresentInterval> PossiblePresentIntervals
        {
            get { return possiblePresentIntervals; }
        }

        /// <summary>
        /// Gets a value indicating whether the devices have been enumerated.
        /// </summary>
        /// <value>
        /// <c>true</c> if the devices have been enumerated; otherwise, <c>false</c>.
        /// </value>
        public static bool HasEnumerated
        {
            get { return hasEnumerated; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether software vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if software vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireSoftwareVertexProcessing
        {
            get { return softwareVP; }
            set { softwareVP = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether hardware vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if hardware vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireHardwareVertexProcessing
        {
            get { return hardwareVP; }
            set { hardwareVP = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether pure hardware vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if pure hardware vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequirePureHardwareVertexProcessing
        {
            get { return pureHardwareVP; }
            set { pureHardwareVP = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether mixed vertex processing is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if mixed vertex processing is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequireMixedVertexProcessing
        {
            get { return mixedVP; }
            set { mixedVP = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether post pixel shader blending is required.
        /// </summary>
        /// <value>
        /// <c>true</c> if post pixel shader blending is required; otherwise, <c>false</c>.
        /// </value>
        public static bool RequirePostPixelShaderBlending
        {
            get { return requirePostPixelShaderBlending; }
            set { requirePostPixelShaderBlending = value; }
        }

        /// <summary>
        /// Gets or sets the minimum resolution.
        /// </summary>
        /// <value>The minimum resolution.</value>
        public static Size MinimumResolution
        {
            get { return minResolution; }
            set { minResolution = value; }
        }

        /// <summary>
        /// Gets or sets the maximum resolution.
        /// </summary>
        /// <value>The maximum resolution.</value>
        public static Size MaximumResolution
        {
            get { return maxResolution; }
            set { maxResolution = value; }
        }

        /// <summary>
        /// Gets or sets the minimum refresh rate.
        /// </summary>
        /// <value>The minimum refresh rate.</value>
        public static int MinimumRefreshRate
        {
            get { return minRefresh; }
            set { minRefresh = value; }
        }

        /// <summary>
        /// Gets or sets the maximum refresh rate.
        /// </summary>
        /// <value>The maximum refresh rate.</value>
        public static int MaximumRefreshRate
        {
            get { return maxRefresh; }
            set { maxRefresh = value; }
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

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes the <see cref="Enumeration"/> class.
        /// </summary>
        static Enumeration()
        {
            ResetPossibleDepthStencilFormats();
            ResetPossibleMultisampleTypes();
            ResetPossiblePresentIntervals();
        }

        #endregion

        #region Methods

        /// <summary>
        /// Gets the adapter information descriptor for the given adapter.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <returns>
        /// The adapter information descriptor for the given adapter, or <c>null</c>
        /// if a valid combination cannot be found.
        /// </returns>
        public static AdapterInfo GetAdapterInfo(int adapterOrdinal)
        {
            foreach (AdapterInfo info in adapters)
                if (info.AdapterOrdinal == adapterOrdinal)
                    return info;

            return null;
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
        public static DeviceInfo GetDeviceInfo(int adapterOrdinal, DeviceType deviceType)
        {
            AdapterInfo info = GetAdapterInfo(adapterOrdinal);
            if (info != null)
            {
                foreach (DeviceInfo deviceInfo in info.Devices)
                    if (deviceInfo.DeviceType == deviceType)
                        return deviceInfo;
            }

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
        public static SettingsCombo GetSettingsCombo(int adapterOrdinal, DeviceType deviceType,
            Format adapterFormat, Format backBufferFormat, bool windowed)
        {
            DeviceInfo info = GetDeviceInfo(adapterOrdinal, deviceType);
            if (info != null)
            {
                foreach (SettingsCombo combo in info.DeviceSettings)
                    if (combo.AdapterFormat == adapterFormat && combo.BackBufferFormat == backBufferFormat &&
                        combo.Windowed == windowed)
                        return combo;
            }

            return null;
        }

        /// <summary>
        /// Resets the possible depth stencil formats.
        /// </summary>
        public static void ResetPossibleDepthStencilFormats()
        {
            possibleDepthStencilFormats = new List<Format>();
            possibleDepthStencilFormats.Add(Format.D16);
            possibleDepthStencilFormats.Add(Format.D15S1);
            possibleDepthStencilFormats.Add(Format.D24X8);
            possibleDepthStencilFormats.Add(Format.D24S8);
            possibleDepthStencilFormats.Add(Format.D24X4S4);
            possibleDepthStencilFormats.Add(Format.D32);
        }

        /// <summary>
        /// Resets the possible multisample types.
        /// </summary>
        public static void ResetPossibleMultisampleTypes()
        {
            possibleMultisampleTypes = new List<MultisampleType>();
            possibleMultisampleTypes.Add(MultisampleType.None);
            possibleMultisampleTypes.Add(MultisampleType.NonMaskable);
            possibleMultisampleTypes.Add(MultisampleType.TwoSamples);
            possibleMultisampleTypes.Add(MultisampleType.ThreeSamples);
            possibleMultisampleTypes.Add(MultisampleType.FourSamples);
            possibleMultisampleTypes.Add(MultisampleType.FiveSamples);
            possibleMultisampleTypes.Add(MultisampleType.SixSamples);
            possibleMultisampleTypes.Add(MultisampleType.SevenSamples);
            possibleMultisampleTypes.Add(MultisampleType.EightSamples);
            possibleMultisampleTypes.Add(MultisampleType.NineSamples);
            possibleMultisampleTypes.Add(MultisampleType.TenSamples);
            possibleMultisampleTypes.Add(MultisampleType.ElevenSamples);
            possibleMultisampleTypes.Add(MultisampleType.TwelveSamples);
            possibleMultisampleTypes.Add(MultisampleType.ThirteenSamples);
            possibleMultisampleTypes.Add(MultisampleType.FourteenSamples);
            possibleMultisampleTypes.Add(MultisampleType.FifteenSamples);
            possibleMultisampleTypes.Add(MultisampleType.SixteenSamples);
        }

        /// <summary>
        /// Resets the possible present intervals.
        /// </summary>
        public static void ResetPossiblePresentIntervals()
        {
            possiblePresentIntervals = new List<PresentInterval>();
            possiblePresentIntervals.Add(PresentInterval.Immediate);
            possiblePresentIntervals.Add(PresentInterval.Default);
            possiblePresentIntervals.Add(PresentInterval.One);
            possiblePresentIntervals.Add(PresentInterval.Two);
            possiblePresentIntervals.Add(PresentInterval.Three);
            possiblePresentIntervals.Add(PresentInterval.Four);
        }

        /// <summary>
        /// Enumerates through all possible Direct3D devices.
        /// </summary>
        public static void Enumerate()
        {
            hasEnumerated = true;
            adapters = new List<AdapterInfo>();
            List<Format> adapterFormats = new List<Format>();
            Format[] allowedAdapterFormats = { Format.X8R8G8B8, Format.X1R5G5B5, Format.R5G6B5, 
                Format.A2R10G10B10 };

            int adapterCount = Direct3D.AdapterCount;
            for (int adapterOrdinal = 0; adapterOrdinal < adapterCount; adapterOrdinal++)
            {
                AdapterInfo adapterInfo = new AdapterInfo();
                DisplayMode displayMode;
                adapterInfo.AdapterOrdinal = adapterOrdinal;
                adapterInfo.Details = Direct3D.GetAdapterIdentifier(adapterOrdinal);

                adapterFormats.Clear();
                for (int formatList = 0; formatList < allowedAdapterFormats.Length; formatList++)
                {
                    Format allowedAdapterFormat = allowedAdapterFormats[formatList];
                    int adapterModeCount = Direct3D.GetAdapterModeCount(adapterOrdinal, allowedAdapterFormat);
                    for (int mode = 0; mode < adapterModeCount; mode++)
                    {
                        displayMode = Direct3D.EnumerateAdapterModes(adapterOrdinal, allowedAdapterFormat, mode);

                        if (displayMode.Width < minResolution.Width ||
                            displayMode.Width > maxResolution.Width ||
                            displayMode.Height < minResolution.Height ||
                            displayMode.Height > maxResolution.Height ||
                            displayMode.RefreshRate < minRefresh ||
                            displayMode.RefreshRate > maxRefresh)
                            continue;

                        adapterInfo.DisplayModes.Add(displayMode);

                        if (!adapterFormats.Contains(displayMode.Format))
                            adapterFormats.Add(displayMode.Format);
                    }
                }

                displayMode = Direct3D.GetAdapterDisplayMode(adapterOrdinal);
                if (!adapterFormats.Contains(displayMode.Format))
                    adapterFormats.Add(displayMode.Format);

                adapterInfo.DisplayModes.Sort(DisplayModeComparer.Comparer);

                EnumerateDevices(adapterInfo, adapterFormats);

                if (adapterInfo.Devices.Count > 0)
                    adapters.Add(adapterInfo);
            }

            bool unique = true;
            for (int i = 0; i < adapters.Count; i++)
            {
                for (int j = i + 1; j < adapters.Count; j++)
                {
                    if (adapters[i].Details.Description == adapters[j].Details.Description)
                    {
                        unique = false;
                        break;
                    }
                }

                if (!unique)
                    break;
            }

            foreach (AdapterInfo info in adapters)
            {
                info.Description = info.Details.Description;
                if (!unique)
                    info.Description += " " + info.AdapterOrdinal.ToString(CultureInfo.CurrentCulture);
            }
        }

        #endregion

        #region Helpers

        static void EnumerateDevices(AdapterInfo info, List<Format> adapterFormats)
        {
            DeviceType[] deviceTypes = { DeviceType.Hardware, DeviceType.Reference };

            for (int deviceType = 0; deviceType < deviceTypes.Length; deviceType++)
            {
                DeviceInfo deviceInfo = new DeviceInfo();
                deviceInfo.AdapterOrdinal = info.AdapterOrdinal;
                deviceInfo.DeviceType = deviceTypes[deviceType];
                deviceInfo.Capabilities = Direct3D.GetDeviceCaps(info.AdapterOrdinal, deviceInfo.DeviceType);

                EnumerateSettingsCombos(info, deviceInfo, adapterFormats);

                if (deviceInfo.DeviceSettings.Count > 0)
                    info.Devices.Add(deviceInfo);
            }
        }

        static void EnumerateSettingsCombos(AdapterInfo adapterInfo, DeviceInfo deviceInfo, List<Format> adapterFormats)
        {
            Format[] backBufferFormats = { Format.A8R8G8B8, Format.X8R8G8B8, Format.A2R10G10B10,
                Format.R5G6B5, Format.A1R5G5B5, Format.X1R5G5B5 };

            foreach (Format adapterFormat in adapterFormats)
            {
                foreach (Format backBufferFormat in backBufferFormats)
                {
                    for (int windowed = 0; windowed < 2; windowed++)
                    {
                        if (windowed == 0 && adapterInfo.DisplayModes.Count == 0)
                            continue;

                        // make sure we have a valid device type
                        if (!Direct3D.CheckDeviceType(adapterInfo.AdapterOrdinal, deviceInfo.DeviceType,
                            adapterFormat, backBufferFormat, (windowed == 1)))
                            continue;

                        // check if post pixel shader blending is required
                        if (requirePostPixelShaderBlending && !Direct3D.CheckDeviceFormat(adapterInfo.AdapterOrdinal,
                            deviceInfo.DeviceType, adapterFormat, Usage.QueryPostPixelShaderBlending,
                            ResourceType.Texture, backBufferFormat))
                            continue;

                        SettingsCombo combo = new SettingsCombo();
                        combo.AdapterOrdinal = adapterInfo.AdapterOrdinal;
                        combo.DeviceType = deviceInfo.DeviceType;
                        combo.AdapterFormat = adapterFormat;
                        combo.BackBufferFormat = backBufferFormat;
                        combo.Windowed = (windowed == 1);
                        combo.AdapterInfo = adapterInfo;
                        combo.DeviceInfo = deviceInfo;

                        BuildDepthStencilFormatList(combo);
                        BuildMultisampleTypeList(combo);

                        if (combo.MultisampleTypes.Count == 0)
                            continue;

                        BuildDepthStencilConflictList(combo);
                        BuildPresentIntervalList(combo);

                        deviceInfo.DeviceSettings.Add(combo);
                    }
                }
            }
        }

        static void BuildDepthStencilFormatList(SettingsCombo combo)
        {
            foreach (Format format in possibleDepthStencilFormats)
            {
                if (Direct3D.CheckDeviceFormat(combo.AdapterOrdinal, combo.DeviceType, combo.AdapterFormat,
                    Usage.DepthStencil, ResourceType.Surface, format) &&
                    Direct3D.CheckDepthStencilMatch(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.BackBufferFormat, format))
                    combo.DepthStencilFormats.Add(format);
            }
        }

        static void BuildMultisampleTypeList(SettingsCombo combo)
        {
            int quality;
            foreach (MultisampleType type in possibleMultisampleTypes)
            {
                if (Direct3D.CheckDeviceMultisampleType(combo.AdapterOrdinal, combo.DeviceType,
                    combo.AdapterFormat, combo.Windowed, type, out quality))
                {
                    combo.MultisampleTypes.Add(type);
                    if (quality > maxMultisampleQuality + 1)
                        quality = maxMultisampleQuality + 1;
                    combo.MultisampleQualities.Add(quality);
                }
            }
        }

        static void BuildDepthStencilConflictList(SettingsCombo combo)
        {
            foreach (Format format in combo.DepthStencilFormats)
            {
                foreach (MultisampleType type in combo.MultisampleTypes)
                {
                    if (!Direct3D.CheckDeviceMultisampleType(combo.AdapterOrdinal, combo.DeviceType,
                        format, combo.Windowed, type))
                    {
                        DepthStencilConflict conflict = new DepthStencilConflict();
                        conflict.DepthStencilFormat = format;
                        conflict.MultisampleType = type;
                        combo.DepthStencilConflicts.Add(conflict);
                    }
                }
            }
        }

        static void BuildPresentIntervalList(SettingsCombo combo)
        {
            foreach (PresentInterval interval in possiblePresentIntervals)
            {
                if (combo.Windowed && (interval == PresentInterval.Two ||
                    interval == PresentInterval.Three || interval == PresentInterval.Four))
                    continue;

                if (interval == PresentInterval.Default ||
                    (combo.DeviceInfo.Capabilities.PresentationIntervals & interval) != 0)
                    combo.PresentIntervals.Add(interval);
            }
        }

        #endregion
    }

    #endregion
}
