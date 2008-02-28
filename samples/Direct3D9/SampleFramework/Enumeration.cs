using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;
using System.Drawing;

namespace SampleFramework
{
    #region AdapterInfo

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

        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        public AdapterDetails Details
        {
            get { return details; }
            set { details = value; }
        }

        public string Description
        {
            get { return description; }
            set { description = value; }
        }

        public List<DisplayMode> DisplayModes
        {
            get { return displayModes; }
        }

        public List<DeviceInfo> Devices
        {
            get { return devices; }
        }

        #endregion

        #region Constructor

        public AdapterInfo()
        {
        }

        #endregion
    }

    #endregion

    #region DeviceInfo

    public class DeviceInfo
    {
        #region Variables

        int adapterOrdinal;
        DeviceType deviceType;
        Capabilities capabilities;
        List<SettingsCombo> deviceSettings = new List<SettingsCombo>();

        #endregion

        #region Properties

        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        public Capabilities Capabilities
        {
            get { return capabilities; }
            set { capabilities = value; }
        }

        public List<SettingsCombo> DeviceSettings
        {
            get { return deviceSettings; }
        }

        #endregion

        #region Constructor

        public DeviceInfo()
        {
        }

        #endregion
    }

    #endregion

    #region SettingsCombo

    public class SettingsCombo
    {
        #region Variables

        int adapterOrdinal;
        DeviceType deviceType;
        Format adapterFormat;
        Format backBufferFormat;
        bool windowed;
        List<Format> depthStencilFormats = new List<Format>();
        List<DepthStencilConflict> depthStencilConflicts = new List<DepthStencilConflict>();
        List<MultisampleType> multisampleTypes = new List<MultisampleType>();
        List<int> multisampleQualities = new List<int>();
        List<PresentInterval> presentIntervals = new List<PresentInterval>();
        AdapterInfo adapterInfo;
        DeviceInfo deviceInfo;

        #endregion

        #region Properties

        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        public Format AdapterFormat
        {
            get { return adapterFormat; }
            set { adapterFormat = value; }
        }

        public Format BackBufferFormat
        {
            get { return backBufferFormat; }
            set { backBufferFormat = value; }
        }

        public bool Windowed
        {
            get { return windowed; }
            set { windowed = value; }
        }

        public List<Format> DepthStencilFormats
        {
            get { return depthStencilFormats; }
        }

        public List<MultisampleType> MultisampleTypes
        {
            get { return multisampleTypes; }
        }

        public List<int> MultisampleQualities
        {
            get { return multisampleQualities; }
        }

        public List<PresentInterval> PresentIntervals
        {
            get { return presentIntervals; }
        }

        public List<DepthStencilConflict> DepthStencilConflicts
        {
            get { return depthStencilConflicts; }
        }

        public AdapterInfo AdapterInfo
        {
            get { return adapterInfo; }
            set { adapterInfo = value; }
        }

        public DeviceInfo DeviceInfo
        {
            get { return deviceInfo; }
            set { deviceInfo = value; }
        }

        #endregion

        #region Constructor

        public SettingsCombo()
        {
        }

        #endregion
    }

    #endregion

    #region DepthStencilConflict

    public class DepthStencilConflict
    {
        #region Variables

        Format depthStencilFormat;
        MultisampleType multisampleType;

        #endregion

        #region Properties

        public Format DepthStencilFormat
        {
            get { return depthStencilFormat; }
            set { depthStencilFormat = value; }
        }

        public MultisampleType MultisampleType
        {
            get { return multisampleType; }
            set { multisampleType = value; }
        }

        #endregion

        #region Constructor

        public DepthStencilConflict()
        {
        }

        #endregion
    }

    #endregion

    #region DisplayModeComparer

    public class DisplayModeComparer : IComparer<DisplayMode>
    {
        #region Variables

        static DisplayModeComparer comparer = new DisplayModeComparer();

        #endregion

        #region Properties

        public static DisplayModeComparer Comparer
        {
            get { return comparer; }
        }

        #endregion

        #region Constructor

        public DisplayModeComparer()
        {
        }

        #endregion

        #region Methods

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

        public static List<AdapterInfo> Adapters
        {
            get { return adapters; }
        }

        public static List<Format> PossibleDepthStencilFormats
        {
            get { return possibleDepthStencilFormats; }
        }

        public static List<MultisampleType> PossibleMultisampleType
        {
            get { return possibleMultisampleTypes; }
        }

        public static List<PresentInterval> PossiblePresentIntervals
        {
            get { return possiblePresentIntervals; }
        }

        public static bool HasEnumerated
        {
            get { return hasEnumerated; }
        }

        public static bool RequireSoftwareVertexProcessing
        {
            get { return softwareVP; }
            set { softwareVP = value; }
        }

        public static bool RequireHardwareVertexProcessing
        {
            get { return hardwareVP; }
            set { hardwareVP = value; }
        }

        public static bool RequirePureHardwareVertexProcessing
        {
            get { return pureHardwareVP; }
            set { pureHardwareVP = value; }
        }

        public static bool RequireMixedVertexProcessing
        {
            get { return mixedVP; }
            set { mixedVP = value; }
        }

        public static bool RequirePostPixelShaderBlending
        {
            get { return requirePostPixelShaderBlending; }
            set { requirePostPixelShaderBlending = value; }
        }

        public static Size MinimumResolution
        {
            get { return minResolution; }
            set { minResolution = value; }
        }

        public static Size MaximumResolution
        {
            get { return maxResolution; }
            set { maxResolution = value; }
        }

        public static int MinimumRefreshRate
        {
            get { return minRefresh; }
            set { minRefresh = value; }
        }

        public static int MaximumRefreshRate
        {
            get { return maxRefresh; }
            set { maxRefresh = value; }
        }

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

        static Enumeration()
        {
            ResetPossibleDepthStencilFormats();
            ResetPossibleMultisampleTypes();
            ResetPossiblePresentIntervals();
        }

        #endregion

        #region Methods

        public static AdapterInfo GetAdapterInfo(int adapterOrdinal)
        {
            foreach (AdapterInfo info in adapters)
                if (info.AdapterOrdinal == adapterOrdinal)
                    return info;

            return null;
        }

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

                        if (displayMode.Width < MinimumResolution.Width ||
                            displayMode.Width > MaximumResolution.Width ||
                            displayMode.Height < MinimumResolution.Height ||
                            displayMode.Height > MaximumResolution.Height ||
                            displayMode.RefreshRate < MinimumRefreshRate ||
                            displayMode.RefreshRate > MaximumRefreshRate)
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
                    info.Description += " " + info.AdapterOrdinal.ToString();
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

                        if (!Direct3D.CheckDeviceType(adapterInfo.AdapterOrdinal, deviceInfo.DeviceType,
                            adapterFormat, backBufferFormat, (windowed == 1)))
                            continue;

                        if (RequirePostPixelShaderBlending && !Direct3D.CheckDeviceFormat(adapterInfo.AdapterOrdinal,
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
                    if (quality > MaximumMultisampleQuality + 1)
                        quality = MaximumMultisampleQuality + 1;
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
