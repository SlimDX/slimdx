/*
* Copyright (c) 2007-2009 SlimDX Group
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
using System.Collections.ObjectModel;
using System.Globalization;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

namespace SampleFramework
{
    class AdapterInfo10
    {
        public int AdapterOrdinal
        {
            get;
            set;
        }

        public AdapterDescription AdapterDescription
        {
            get;
            set;
        }

        public string Description
        {
            get;
            set;
        }

        public Adapter Adapter
        {
            get;
            set;
        }

        public List<OutputInfo10> Outputs
        {
            get;
            private set;
        }

        public List<DeviceInfo10> Devices
        {
            get;
            private set;
        }

        public List<SettingsCombo10> SettingsCombos
        {
            get;
            private set;
        }

        public AdapterInfo10()
        {
            Outputs = new List<OutputInfo10>();
            Devices = new List<DeviceInfo10>();
            SettingsCombos = new List<SettingsCombo10>();
        }
    }

    class OutputInfo10
    {
        public int OutputOrdinal
        {
            get;
            set;
        }

        public Output Output
        {
            get;
            set;
        }

        public OutputDescription OutputDescription
        {
            get;
            set;
        }

        public List<ModeDescription> DisplayModes
        {
            get;
            private set;
        }

        public OutputInfo10()
        {
            DisplayModes = new List<ModeDescription>();
        }
    }

    class DeviceInfo10
    {
        public int AdapterOrdinal
        {
            get;
            set;
        }

        public DriverType DriverType
        {
            get;
            set;
        }

        public DeviceInfo10()
        {
        }
    }

    class SettingsCombo10
    {
        public int AdapterOrdinal
        {
            get;
            set;
        }

        public DriverType DriverType
        {
            get;
            set;
        }

        public Format BackBufferFormat
        {
            get;
            set;
        }

        public bool IsWindowed
        {
            get;
            set;
        }

        public int OutputOrdinal
        {
            get;
            set;
        }

        public List<int> MultisampleCounts
        {
            get;
            private set;
        }

        public List<int> MultisampleQualities
        {
            get;
            private set;
        }

        public OutputInfo10 OutputInfo
        {
            get;
            set;
        }

        public SettingsCombo10()
        {
            MultisampleCounts = new List<int>();
            MultisampleQualities = new List<int>();
        }
    }

    static class Enumeration10
    {
        public static DeviceSettings MinimumSettings
        {
            get;
            set;
        }

        public static List<AdapterInfo10> Adapters
        {
            get;
            private set;
        }

        public static bool HasEnumerated
        {
            get;
            private set;
        }

        public static OutputInfo10 GetOutputInfo(int adapterOrdinal, int outputOrdinal)
        {
            AdapterInfo10 adapter = null;
            foreach (AdapterInfo10 a in Adapters)
            {
                if (adapterOrdinal == a.AdapterOrdinal)
                {
                    adapter = a;
                    break;
                }
            }

            if (adapter != null && adapter.Outputs.Count > outputOrdinal)
                return adapter.Outputs[outputOrdinal];
            return null;
        }

        public static void Enumerate()
        {
            HasEnumerated = true;
            Adapters = new List<AdapterInfo10>();

            for (int i = 0; i < GraphicsDeviceManager.Factory.GetAdapterCount(); i++)
            {
                Adapter adapter = (Adapter)GraphicsDeviceManager.Factory.GetAdapter(i);

                AdapterInfo10 adapterInfo = new AdapterInfo10();
                adapterInfo.AdapterOrdinal = i;
                adapterInfo.AdapterDescription = adapter.Description;
                adapterInfo.Adapter = adapter;

                EnumerateDevices(adapterInfo);
                if (adapterInfo.Devices.Count == 0)
                    continue;

                EnumerateOutputs(adapterInfo);
                if (adapterInfo.Outputs.Count == 0)
                    continue;

                EnumerateSettingsCombos(adapterInfo);
                if (adapterInfo.SettingsCombos.Count == 0)
                    continue;

                Adapters.Add(adapterInfo);
            }

            bool unique = true;
            foreach (AdapterInfo10 adapter1 in Adapters)
            {
                foreach (AdapterInfo10 adapter2 in Adapters)
                {
                    if (adapter1 == adapter2)
                        continue;
                    if (adapter1.AdapterDescription.Description == adapter2.AdapterDescription.Description)
                    {
                        unique = false;
                        break;
                    }
                }

                if (!unique)
                    break;
            }

            foreach (AdapterInfo10 info in Adapters)
            {
                info.Description = info.AdapterDescription.Description;
                if (!unique)
                    info.Description += " " + info.AdapterOrdinal.ToString(CultureInfo.CurrentCulture);
            }
        }

        static void EnumerateOutputs(AdapterInfo10 adapterInfo)
        {
            for (int i = 0; i < adapterInfo.Adapter.GetOutputCount(); i++)
            {
                Output output = (Output)adapterInfo.Adapter.GetOutput(i);

                OutputInfo10 outputInfo = new OutputInfo10();
                outputInfo.OutputDescription = output.Description;
                outputInfo.OutputOrdinal = i;
                outputInfo.Output = output;

                EnumerateDisplayModes(outputInfo);
                if (outputInfo.DisplayModes.Count == 0)
                    continue;

                adapterInfo.Outputs.Add(outputInfo);
            }
        }

        static void EnumerateDisplayModes(OutputInfo10 outputInfo)
        {
            Format[] allowedFormats = { Format.R8G8B8A8_UNorm, Format.R8G8B8A8_UNorm_SRGB,
                Format.R16G16B16A16_Float, Format.R10G10B10A2_UNorm };

            foreach (Format format in allowedFormats)
            {
                ReadOnlyCollection<ModeDescription> modes = outputInfo.Output.GetDisplayModeList(format, DisplayModeEnumerationFlags.Scaling);
                foreach (ModeDescription mode in modes)
                {
                    if (MinimumSettings != null)
                    {
                        if (mode.Width < MinimumSettings.BackBufferWidth ||
                            mode.Height < MinimumSettings.BackBufferHeight ||
                            (int)ConversionMethods.ToFloat(mode.RefreshRate) < MinimumSettings.RefreshRate)
                            continue;
                    }

                    outputInfo.DisplayModes.Add(mode);
                }
            }
        }

        static void EnumerateDevices(AdapterInfo10 adapterInfo)
        {
            DriverType[] allowedTypes = { DriverType.Hardware, DriverType.Reference };

            foreach (DriverType type in allowedTypes)
            {
                if (MinimumSettings != null && type != ConversionMethods.ToDirect3D10(MinimumSettings.DeviceType))
                    continue;

                DeviceInfo10 deviceInfo = new DeviceInfo10();
                deviceInfo.AdapterOrdinal = adapterInfo.AdapterOrdinal;
                deviceInfo.DriverType = type;
                SlimDX.Direct3D10.Device device;

                try
                {
                    Adapter adapter = null;
                    if (type == DriverType.Hardware)
                        adapter = adapterInfo.Adapter;
                    device = new SlimDX.Direct3D10.Device(adapter, type, DeviceCreationFlags.None);
                }
                catch (Direct3D10Exception)
                {
                    // swallow the exception
                    continue;
                }

                // if the driver type is not hardware, create a DXGI device and GetAdapter
                // from it to replace adapterInfo.Adapter
                if (type != DriverType.Hardware)
                {
                    SlimDX.DXGI.Device dxgiDevice = new SlimDX.DXGI.Device(device);
                    if (adapterInfo.Adapter != null)
                        adapterInfo.Adapter.Dispose();
                    adapterInfo.Adapter = (Adapter)dxgiDevice.Adapter;
                    dxgiDevice.Dispose();
                }

                device.Dispose();
                adapterInfo.Devices.Add(deviceInfo);
            }
        }

        static void EnumerateSettingsCombos(AdapterInfo10 adapterInfo)
        {
            Format[] backBufferFormats = { Format.R8G8B8A8_UNorm, Format.R8G8B8A8_UNorm_SRGB,
                                           Format.R16G16B16A16_Float, Format.R10G10B10A2_UNorm };

            foreach (OutputInfo10 outputInfo in adapterInfo.Outputs)
            {
                foreach (DeviceInfo10 deviceInfo in adapterInfo.Devices)
                {
                    foreach (Format backBufferFormat in backBufferFormats)
                    {
                        if (MinimumSettings != null && MinimumSettings.BackBufferFormat != SlimDX.Direct3D9.Format.Unknown &&
                            ConversionMethods.ToDirect3D10(MinimumSettings.BackBufferFormat) != backBufferFormat)
                            continue;

                        for (int windowed = 0; windowed < 2; windowed++)
                        {
                            if (windowed == 0 && outputInfo.DisplayModes.Count == 0)
                                continue;

                            bool found = false;
                            foreach (ModeDescription mode in outputInfo.DisplayModes)
                            {
                                if (mode.Format == backBufferFormat)
                                {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found)
                                continue;

                            SettingsCombo10 combo = new SettingsCombo10();
                            combo.AdapterOrdinal = deviceInfo.AdapterOrdinal;
                            combo.DriverType = deviceInfo.DriverType;
                            combo.BackBufferFormat = backBufferFormat;
                            combo.IsWindowed = (windowed != 0);
                            combo.OutputOrdinal = outputInfo.OutputOrdinal;
                            combo.OutputInfo = outputInfo;

                            BuildMultisampleList(backBufferFormat, combo);

                            if (MinimumSettings != null && !combo.MultisampleCounts.Contains(ConversionMethods.ToDirect3D10(MinimumSettings.MultisampleType, 0)))
                                continue;

                            adapterInfo.SettingsCombos.Add(combo);
                        }
                    }
                }
            }
        }

        static void BuildMultisampleList(Format backBufferFormat, SettingsCombo10 combo)
        {
            Adapter adapter = null;
            if (combo.DriverType == DriverType.Hardware)
                adapter = (Adapter)GraphicsDeviceManager.Factory.GetAdapter(combo.AdapterOrdinal);
            SlimDX.Direct3D10.Device device;

            try
            {
                device = new SlimDX.Direct3D10.Device(adapter, combo.DriverType, DeviceCreationFlags.None);
            }
            catch (Direct3D10Exception)
            {
                // no good
                if (adapter != null)
                    adapter.Dispose();
                return;
            }

            for (int i = 1; i <= SlimDX.Direct3D10.Device.MultisampleCountMaximum; i++)
            {
                try
                {
                    int quality = device.CheckMultisampleQualityLevels(backBufferFormat, i);
                    combo.MultisampleCounts.Add(i);
                    combo.MultisampleQualities.Add(quality);
                }
                catch (Direct3D10Exception)
                {
                    // eat the exception
                }
            }

            device.Dispose();

            if (adapter != null)
                adapter.Dispose();
        }
    }
}
