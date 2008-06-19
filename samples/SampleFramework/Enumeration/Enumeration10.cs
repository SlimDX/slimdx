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
using System.Collections.ObjectModel;
using System.Globalization;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

namespace SampleFramework
{
    /// <summary>
    /// Contains information about a Direct3D10 adapter.
    /// </summary>
    class AdapterInfo10
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
        /// Gets or sets the adapter description.
        /// </summary>
        /// <value>The adapter description.</value>
        public AdapterDescription AdapterDescription
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
        /// Gets or sets the adapter.
        /// </summary>
        /// <value>The adapter.</value>
        public Adapter Adapter
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the supported outputs.
        /// </summary>
        /// <value>The supported outputs.</value>
        public List<OutputInfo10> Outputs
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the supported devices.
        /// </summary>
        /// <value>The supported devices.</value>
        public List<DeviceInfo10> Devices
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the unique settings combinations.
        /// </summary>
        /// <value>The unique settings combinations.</value>
        public List<SettingsCombo10> SettingsCombos
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AdapterInfo10"/> class.
        /// </summary>
        public AdapterInfo10()
        {
            // create lists
            Outputs = new List<OutputInfo10>();
            Devices = new List<DeviceInfo10>();
            SettingsCombos = new List<SettingsCombo10>();
        }
    }

    /// <summary>
    /// Contains information about a Direct3D10 output.
    /// </summary>
    class OutputInfo10
    {
        /// <summary>
        /// Gets or sets the output ordinal.
        /// </summary>
        /// <value>The output ordinal.</value>
        public int OutputOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the output.
        /// </summary>
        /// <value>The output.</value>
        public Output Output
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the output description.
        /// </summary>
        /// <value>The output description.</value>
        public OutputDescription OutputDescription
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the supported display modes.
        /// </summary>
        /// <value>The supported display modes.</value>
        public List<ModeDescription> DisplayModes
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="OutputInfo10"/> class.
        /// </summary>
        public OutputInfo10()
        {
            // create the lists
            DisplayModes = new List<ModeDescription>();
        }
    }

    /// <summary>
    /// Contains information about a Direct3D10 device.
    /// </summary>
    class DeviceInfo10
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
        /// Gets or sets the type of the driver.
        /// </summary>
        /// <value>The type of the driver.</value>
        public DriverType DriverType
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceInfo10"/> class.
        /// </summary>
        public DeviceInfo10()
        {
        }
    }

    /// <summary>
    /// Contains a unique combination of Direct3D10 device settings.
    /// </summary>
    class SettingsCombo10
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
        /// Gets or sets the type of the driver.
        /// </summary>
        /// <value>The type of the driver.</value>
        public DriverType DriverType
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
        /// Gets or sets a value indicating whether the device is windowed.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the device is windowed; otherwise, <c>false</c>.
        /// </value>
        public bool IsWindowed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the output ordinal.
        /// </summary>
        /// <value>The output ordinal.</value>
        public int OutputOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the supported multisample counts.
        /// </summary>
        /// <value>The supported multisample counts.</value>
        public List<int> MultisampleCounts
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the supported multisample qualities.
        /// </summary>
        /// <value>The supported multisample qualities.</value>
        public List<int> MultisampleQualities
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the output info.
        /// </summary>
        /// <value>The output info.</value>
        public OutputInfo10 OutputInfo
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsCombo10"/> class.
        /// </summary>
        public SettingsCombo10()
        {
            // initialize the lists
            MultisampleCounts = new List<int>();
            MultisampleQualities = new List<int>();
        }
    }

    /// <summary>
    /// Handles device type enumeration for Direct3D10.
    /// </summary>
    static class Enumeration10
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
        public static List<AdapterInfo10> Adapters
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
        /// Gets the output info.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <param name="outputOrdinal">The output ordinal.</param>
        /// <returns>The output info with the desired settings.</returns>
        public static OutputInfo10 GetOutputInfo(int adapterOrdinal, int outputOrdinal)
        {
            // find the right output info descriptor
            AdapterInfo10 adapter = null;
            foreach( AdapterInfo10 a in Adapters )
            {
                // check for an ordinal match
                if( adapterOrdinal == a.AdapterOrdinal )
                {
                    // found it
                    adapter = a;
                    break;
                }
            }
            
            // return the found information
            if (adapter != null && adapter.Outputs.Count > outputOrdinal)
                return adapter.Outputs[outputOrdinal];
            return null;
        }

        /// <summary>
        /// Enumerates through all possible graphics devices.
        /// </summary>
        public static void Enumerate()
        {
            // initialize variables for the enumeration
            HasEnumerated = true;
            Adapters = new List<AdapterInfo10>();

            // loop through each adapter
            for (int i = 0; i < GraphicsDeviceManager.Factory.GetAdapterCount(); i++)
            {
                // grab the adapter
                Adapter adapter = GraphicsDeviceManager.Factory.GetAdapter(i);

                // create the adapter descriptor
                AdapterInfo10 adapterInfo = new AdapterInfo10();
                adapterInfo.AdapterOrdinal = i;
                adapterInfo.AdapterDescription = adapter.Description;
                adapterInfo.Adapter = adapter;

                // enumerate the devices on the adapter
                EnumerateDevices(adapterInfo);
                if (adapterInfo.Devices.Count == 0)
                    continue;

                // enumerate the outputs
                EnumerateOutputs(adapterInfo);
                if (adapterInfo.Outputs.Count == 0)
                    continue;

                // enumerate the unique settings combinations
                EnumerateSettingsCombos(adapterInfo);
                if (adapterInfo.SettingsCombos.Count == 0)
                    continue;

                // add the item to the list
                Adapters.Add(adapterInfo);
            }

            // check if all of the adapter names are unique
            bool unique = true;
            foreach (AdapterInfo10 adapter1 in Adapters)
            {
                // check each adapter against every other adapter
                foreach (AdapterInfo10 adapter2 in Adapters)
                {
                    // check for a duplicate name
                    if (adapter1 == adapter2)
                        continue;
                    if (adapter1.AdapterDescription.Description == adapter2.AdapterDescription.Description)
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
            foreach (AdapterInfo10 info in Adapters)
            {
                // build up the description string
                info.Description = info.AdapterDescription.Description;
                if (!unique)
                    info.Description += " " + info.AdapterOrdinal.ToString(CultureInfo.CurrentCulture);
            }
        }

        /// <summary>
        /// Enumerates the outputs on an adapter.
        /// </summary>
        /// <param name="adapterInfo">The adapter info.</param>
        static void EnumerateOutputs(AdapterInfo10 adapterInfo)
        {
            // loop through each output
            for (int i = 0; i < adapterInfo.Adapter.GetOutputCount(); i++)
            {
                // grab the output
                Output output = adapterInfo.Adapter.GetOutput(i);

                // create the output descriptor
                OutputInfo10 outputInfo = new OutputInfo10();
                outputInfo.OutputDescription = output.Description;
                outputInfo.OutputOrdinal = i;
                outputInfo.Output = output;

                // enumerate the display modes on the output
                EnumerateDisplayModes(outputInfo);
                if (outputInfo.DisplayModes.Count == 0)
                    continue;

                // add the item to the list
                adapterInfo.Outputs.Add(outputInfo);
            }
        }

        /// <summary>
        /// Enumerates the display modes on an output.
        /// </summary>
        /// <param name="outputInfo">The output info.</param>
        static void EnumerateDisplayModes(OutputInfo10 outputInfo)
        {
            // set up the allowed formats
            Format[] allowedFormats = { Format.R8G8B8A8_UNorm_SRGB, Format.R8G8B8A8_UNorm,
                Format.R16G16B16A16_Float, Format.R10G10B10A2_UNorm };

            // loop over each allowed format
            foreach (Format format in allowedFormats)
            {
                // get the list of display modes
                ReadOnlyCollection<ModeDescription> modes = outputInfo.Output.GetDisplayModeList(format, DisplayModeEnumerationFlags.Scaling);

                // add each item to the list
                foreach (ModeDescription mode in modes)
                {
                    // make sure the mode passes our minimum settings
                    if (MinimumSettings != null)
                    {
                        // check the settings
                        if (mode.Width < MinimumSettings.BackBufferWidth ||
                            mode.Height < MinimumSettings.BackBufferHeight ||
                            (int)ConversionMethods.ToFloat(mode.RefreshRate) < MinimumSettings.RefreshRate)
                            continue;
                    }

                    // add the item
                    outputInfo.DisplayModes.Add(mode);
                }
            }
        }

        /// <summary>
        /// Enumerates the possible devices.
        /// </summary>
        /// <param name="adapterInfo">The adapter info.</param>
        static void EnumerateDevices(AdapterInfo10 adapterInfo)
        {
            // set up allowed types
            DriverType[] allowedTypes = { DriverType.Hardware, DriverType.Reference };

            // loop over each allowed type
            foreach (DriverType type in allowedTypes)
            {
                // make sure the type matches that of the minimum settings
                if (MinimumSettings != null && type != ConversionMethods.ToDirect3D10(MinimumSettings.DeviceType))
                    continue;

                // set up the device type descriptor
                DeviceInfo10 deviceInfo = new DeviceInfo10();
                deviceInfo.AdapterOrdinal = adapterInfo.AdapterOrdinal;
                deviceInfo.DriverType = type;
                SlimDX.Direct3D10.Device device;

                // create the device to ensure that this is a valid device
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
                    // TODO: Uncomment the following lines, as soon as jpetrie makes the changes
                    // so that it will compile
                    //SlimDX.DXGI.Device dxgiDevice = new SlimDX.DXGI.Device(device);
                    //adapterInfo.Adapter = dxgiDevice.Adapter;
                    //dxgiDevice.Dispose();
                }

                // release the device
                device.Dispose();

                // add the item to the list
                adapterInfo.Devices.Add(deviceInfo);
            }
        }

        /// <summary>
        /// Enumerates the unique settings combinations.
        /// </summary>
        /// <param name="adapterInfo">The adapter info.</param>
        static void EnumerateSettingsCombos(AdapterInfo10 adapterInfo)
        {
            // set up the backbuffer format list
            Format[] backBufferFormats = { Format.R8G8B8A8_UNorm_SRGB, Format.R8G8B8A8_UNorm,
                                           Format.R16G16B16A16_Float, Format.R10G10B10A2_UNorm };

            // loop over each output
            foreach (OutputInfo10 outputInfo in adapterInfo.Outputs)
            {
                // loop over each device
                foreach (DeviceInfo10 deviceInfo in adapterInfo.Devices)
                {
                    // loop over each allowed back buffer format
                    foreach (Format backBufferFormat in backBufferFormats)
                    {
                        // make sure we don't violate our minimum settings
                        if (MinimumSettings != null && MinimumSettings.BackBufferFormat != SlimDX.Direct3D9.Format.Unknown &&
                            ConversionMethods.ToDirect3D10(MinimumSettings.BackBufferFormat) != backBufferFormat)
                            continue;

                        // loop through each windowed mode
                        for (int windowed = 0; windowed < 2; windowed++)
                        {
                            // make sure we have display modes if we are in fullscreen
                            if (windowed == 0 && outputInfo.DisplayModes.Count == 0)
                                continue;

                            // make sure we have valid display modes
                            bool found = false;
                            foreach (ModeDescription mode in outputInfo.DisplayModes)
                            {
                                // check for a match
                                if (mode.Format == backBufferFormat)
                                {
                                    // found it
                                    found = true;
                                    break;
                                }
                            }
                            if (!found)
                                continue;

                            // build up the settings combo
                            SettingsCombo10 combo = new SettingsCombo10();
                            combo.AdapterOrdinal = deviceInfo.AdapterOrdinal;
                            combo.DriverType = deviceInfo.DriverType;
                            combo.BackBufferFormat = backBufferFormat;
                            combo.IsWindowed = (windowed != 0);
                            combo.OutputOrdinal = outputInfo.OutputOrdinal;
                            combo.OutputInfo = outputInfo;

                            // build the multisample list
                            BuildMultisampleList(backBufferFormat, combo);

                            // make sure we don't violate our minimum settings
                            if (MinimumSettings != null && !combo.MultisampleCounts.Contains(ConversionMethods.ToDirect3D10(MinimumSettings.MultisampleType, 0)))
                                continue;

                            // add the item to the list
                            adapterInfo.SettingsCombos.Add(combo);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Builds the multisample list.
        /// </summary>
        /// <param name="backBufferFormat">The back buffer format.</param>
        /// <param name="combo">The combo.</param>
        static void BuildMultisampleList(Format backBufferFormat, SettingsCombo10 combo)
        {
            // create the device to check quality levels
            Adapter adapter = null;
            if (combo.DriverType == DriverType.Hardware)
                adapter = GraphicsDeviceManager.Factory.GetAdapter(combo.AdapterOrdinal);
            SlimDX.Direct3D10.Device device = new SlimDX.Direct3D10.Device(adapter, combo.DriverType, DeviceCreationFlags.None);

            // loop through each multisample amount
            // TODO: replace 32 with a constant: D3D10_MAX_MULTISAMPLE_SAMPLE_COUNT
            for (int i = 1; i < 32; i++)
            {
                try
                {
                    // set up the levels
                    int quality = device.CheckMultisampleQualityLevels(backBufferFormat, i);
                    combo.MultisampleCounts.Add(i);
                    combo.MultisampleQualities.Add(quality);
                }
                catch (Direct3D10Exception)
                {
                    // eat the exception
                }
            }

            // release the device
            device.Dispose();
        }
    }
}
