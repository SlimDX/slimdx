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
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains settings for creating a 3D device.
    /// </summary>
    public class DeviceSettings : ICloneable
    {
        /// <summary>
        /// Gets or sets the device version.
        /// </summary>
        /// <value>The device version.</value>
        public DeviceVersion DeviceVersion
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
        /// Gets or sets the refresh rate.
        /// </summary>
        /// <value>The refresh rate.</value>
        public int RefreshRate
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the width of the back buffer.
        /// </summary>
        /// <value>The width of the back buffer.</value>
        public int BackBufferWidth
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the height of the back buffer.
        /// </summary>
        /// <value>The height of the back buffer.</value>
        public int BackBufferHeight
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
        /// Gets or sets the back buffer count.
        /// </summary>
        /// <value>The back buffer count.</value>
        public int BackBufferCount
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether the device is windowed.
        /// </summary>
        /// <value><c>true</c> if windowed; otherwise, <c>false</c>.</value>
        public bool Windowed
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
        /// Gets or sets the multisample quality.
        /// </summary>
        /// <value>The multisample quality.</value>
        public int MultisampleQuality
        {
            get;
            set;
        }

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
        /// Gets or sets the Direct3D9 specific settings.
        /// </summary>
        /// <value>The Direct3D9 specific settings.</value>
        internal Direct3D9Settings Direct3D9
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the Direct3D10 specific settings.
        /// </summary>
        /// <value>The Direct3D10 specific settings.</value>
        internal Direct3D10Settings Direct3D10
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceSettings"/> class.
        /// </summary>
        public DeviceSettings()
        {
            // set sane defaults
            DeviceVersion = DeviceVersion.Direct3D9;
            DeviceType = DeviceType.Hardware;
            BackBufferFormat = Format.Unknown;
            BackBufferCount = 1;
            MultisampleType = MultisampleType.None;
            DepthStencilFormat = Format.Unknown;
            Windowed = true;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public DeviceSettings Clone()
        {
            // clone the settings
            DeviceSettings result = new DeviceSettings();
            result.DeviceVersion = DeviceVersion;
            result.DeviceType = DeviceType;
            result.RefreshRate = RefreshRate;
            result.BackBufferCount = BackBufferCount;
            result.BackBufferFormat = BackBufferFormat;
            result.BackBufferHeight = BackBufferHeight;
            result.BackBufferWidth = BackBufferWidth;
            result.DepthStencilFormat = DepthStencilFormat;
            result.MultisampleQuality = MultisampleQuality;
            result.MultisampleType = MultisampleType;
            result.Windowed = Windowed;

            // clone each API specific portion
            if (Direct3D9 != null)
                result.Direct3D9 = Direct3D9.Clone();
            if (Direct3D10 != null)
                result.Direct3D10 = Direct3D10.Clone();

            // return the result
            return result;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        object ICloneable.Clone()
        {
            // call the overload
            return Clone();
        }

        /// <summary>
        /// Finds valid device settings based upon the desired settings.
        /// </summary>
        /// <param name="settings">The desired settings.</param>
        /// <returns>The best valid device settings matching the input settings.</returns>
        public static DeviceSettings FindValidSettings(DeviceSettings settings)
        {
            // check the desired API version
            if (settings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                try
                {
                    // ensure that Direct3D9 is initialized
                    GraphicsDeviceManager.EnsureD3D9();
                }
                catch (Exception e)
                {
                    // wrap the exception into one more suitable for the user
                    throw new NoCompatibleDevicesException("Could not initialize Direct3D9.", e);
                }

                // enumerate available devices
                if (!Enumeration9.HasEnumerated)
                    Enumeration9.Enumerate();

                // find the best settings for the job
                DeviceSettings newSettings = settings.Clone();
                Direct3D9Settings d3d9 = FindValidD3D9Settings(settings);
                newSettings.Direct3D10 = null;
                newSettings.Direct3D9 = d3d9;
                return newSettings;
            }
            else
            {
                try
                {
                    // ensure that Direct3D10 is initialized
                    GraphicsDeviceManager.EnsureD3D10();
                }
                catch (Exception e)
                {
                    // wrap the exception into one more suitable for the user
                    throw new NoCompatibleDevicesException("Could not initialize Direct3D10.", e);
                }

                // enumerate available devices
                if (!Enumeration10.HasEnumerated)
                    Enumeration10.Enumerate();

                // find the best settings for the job
                DeviceSettings newSettings = settings.Clone();
                Direct3D10Settings d3d10 = FindValidD3D10Settings(settings);
                newSettings.Direct3D9 = null;
                newSettings.Direct3D10 = d3d10;
                return newSettings;
            }
        }

        /// <summary>
        /// Finds valid Direct3D9 device settings based upon the desired settings.
        /// </summary>
        /// <param name="settings">The desired settings.</param>
        /// <returns>The best valid device settings matching the input settings.</returns>
        static Direct3D9Settings FindValidD3D9Settings(DeviceSettings settings)
        {
            // build optimal settings
            Direct3D9Settings optimal = Direct3D9Settings.BuildOptimalSettings(settings);

            // setup for ranking combos
            SettingsCombo9 bestCombo = null;
            float bestRanking = -1.0f;

            // loop through each enumerated adapter
            foreach (AdapterInfo9 adapterInfo in Enumeration9.Adapters)
            {
                // get the desktop display mode
                DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(adapterInfo.AdapterOrdinal);

                // loop through each enumerated device
                foreach (DeviceInfo9 deviceInfo in adapterInfo.Devices)
                {
                    // loop through each settings combo
                    foreach (SettingsCombo9 combo in deviceInfo.DeviceSettings)
                    {
                        // make sure it matches the current display mode
                        if (combo.Windowed && combo.AdapterFormat != desktopMode.Format)
                            continue;

                        // rank the combo
                        float ranking = Direct3D9Settings.RankSettingsCombo(combo, optimal, desktopMode);

                        // check if we have a new best ranking
                        if (ranking > bestRanking)
                        {
                            // we do, so store the best ranking information
                            bestCombo = combo;
                            bestRanking = ranking;
                        }
                    }
                }
            }

            // check if we couldn't find a compatible device
            if (bestCombo == null)
                throw new NoCompatibleDevicesException("No compatible Direct3D9 devices found.");

            // return the new valid settings
            return Direct3D9Settings.BuildValidSettings(bestCombo, optimal);
        }

        /// <summary>
        /// Finds valid Direct3D10 device settings based upon the desired settings.
        /// </summary>
        /// <param name="settings">The desired settings.</param>
        /// <returns>The best valid device settings matching the input settings.</returns>
        static Direct3D10Settings FindValidD3D10Settings(DeviceSettings settings)
        {
            // build optimal settings
            Direct3D10Settings optimal = Direct3D10Settings.BuildOptimalSettings(settings);

            // setup for ranking combos
            SettingsCombo10 bestCombo = null;
            float bestRanking = -1.0f;

            // loop through each enumerated adapter
            foreach (AdapterInfo10 adapterInfo in Enumeration10.Adapters)
            {
                // get the desktop display mode
                SlimDX.DXGI.ModeDescription desktopMode = Direct3D10Settings.GetAdapterDisplayMode(adapterInfo.AdapterOrdinal, 0);

                // loop through each settings combo
                foreach (SettingsCombo10 combo in adapterInfo.SettingsCombos)
                {
                    // rank the combo
                    float ranking = Direct3D10Settings.RankSettingsCombo(combo, optimal, desktopMode);

                    // check if we have a new best ranking
                    if (ranking > bestRanking)
                    {
                        // we do, so store the best ranking information
                        bestCombo = combo;
                        bestRanking = ranking;
                    }
                }
            }

            // check if we couldn't find a compatible device
            if (bestCombo == null)
                throw new NoCompatibleDevicesException("No compatible Direct3D10 devices found.");

            // return the new valid settings
            return Direct3D10Settings.BuildValidSettings(bestCombo, optimal);
        }
    }
}
