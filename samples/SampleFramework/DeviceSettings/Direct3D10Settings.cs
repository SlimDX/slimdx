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
using System.Drawing;
using SlimDX;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

namespace SampleFramework
{
    /// <summary>
    /// Contains settings for a Direct3D10 device.
    /// </summary>
    class Direct3D10Settings : ICloneable
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
        /// Gets or sets the output ordinal.
        /// </summary>
        /// <value>The output ordinal.</value>
        public int OutputOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the swap chain description.
        /// </summary>
        /// <value>The swap chain description.</value>
        public SwapChainDescription SwapChainDescription
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the creation flags.
        /// </summary>
        /// <value>The creation flags.</value>
        public DeviceCreationFlags CreationFlags
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the sync interval.
        /// </summary>
        /// <value>The sync interval.</value>
        public int SyncInterval
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the present flags.
        /// </summary>
        /// <value>The present flags.</value>
        public PresentFlags PresentFlags
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
        /// Initializes a new instance of the <see cref="Direct3D10Settings"/> class.
        /// </summary>
        public Direct3D10Settings()
        {
            // set defaults
            DriverType = DriverType.Hardware;
            PresentFlags = PresentFlags.None;
            DepthStencilFormat = Format.Unknown;
            SyncInterval = 1;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public Direct3D10Settings Clone()
        {
            // create the cloned settings
            Direct3D10Settings clone = new Direct3D10Settings();
            clone.AdapterOrdinal = AdapterOrdinal;
            clone.CreationFlags = CreationFlags;
            clone.DepthStencilFormat = DepthStencilFormat;
            clone.DriverType = DriverType;
            clone.OutputOrdinal = OutputOrdinal;
            clone.PresentFlags = PresentFlags;
            clone.SwapChainDescription = SwapChainDescription;
            clone.SyncInterval = SyncInterval;

            // return the result
            return clone;
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
        /// Gets the adapter display mode.
        /// </summary>
        /// <param name="adapterOrdinal">The adapter ordinal.</param>
        /// <param name="outputOrdinal">The output ordinal.</param>
        /// <returns>The adapter display mode.</returns>
        public static ModeDescription GetAdapterDisplayMode(int adapterOrdinal, int outputOrdinal)
        {
            // get the output info
            OutputInfo10 outputInfo = Enumeration10.GetOutputInfo(adapterOrdinal, outputOrdinal);

            // build the mode description
            ModeDescription mode = new ModeDescription();
            mode.RefreshRate = new Rational(0, 0);
            mode.Format = Format.R8G8B8A8_UNorm_SRGB;
            mode.Scaling = DisplayModeScaling.Unspecified;
            mode.ScanlineOrdering = DisplayModeScanlineOrdering.Unspecified;
            Rectangle rectangle = (Rectangle)outputInfo.OutputDescription.DesktopBounds;
            mode.Width = rectangle.Width;
            mode.Height = rectangle.Height;

            // return the result
            return mode;
        }

        /// <summary>
        /// Builds optimal Direct3D10 device settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The optimal device settings</returns>
        public static Direct3D10Settings BuildOptimalSettings(DeviceSettings settings)
        {
            // grab the desktop mode
            ModeDescription desktopMode = GetAdapterDisplayMode(0, 0);
            Direct3D10Settings optimal = new Direct3D10Settings();
            SwapChainDescription swapChainDescription = new SwapChainDescription();
            ModeDescription mode = new ModeDescription();
            SampleDescription sample = new SampleDescription();

            // set up the easy values first
            optimal.AdapterOrdinal = settings.AdapterOrdinal;
            optimal.DriverType = ConversionMethods.ToDirect3D10(settings.DeviceType);
            optimal.PresentFlags = PresentFlags.None;
            swapChainDescription.IsWindowed = settings.Windowed;
            swapChainDescription.BufferCount = settings.BackBufferCount;
            sample.Count = ConversionMethods.ToDirect3D10(settings.MultisampleType, settings.MultisampleQuality);
            sample.Quality = settings.MultisampleQuality;
            swapChainDescription.SwapEffect = SwapEffect.Discard;

            // figure out the optimal back buffer size
            if (settings.BackBufferWidth == 0 || settings.BackBufferHeight == 0)
            {
                // depends on the windowed mode
                if (settings.Windowed)
                {
                    // just use a default size
                    mode.Width = 640;
                    mode.Height = 480;
                }
                else
                {
                    // use the desktop size
                    mode.Width = desktopMode.Width;
                    mode.Height = desktopMode.Height;
                }
            }
            else
            {
                // otherwise, use the specified size
                mode.Width = settings.BackBufferWidth;
                mode.Height = settings.BackBufferHeight;
            }

            // figure out the optimal back buffer format
            if (ConversionMethods.ToDirect3D10(settings.BackBufferFormat) == Format.Unknown)
                mode.Format = desktopMode.Format;
            else
                mode.Format = ConversionMethods.ToDirect3D10(settings.BackBufferFormat);

            // figure out the usage
            swapChainDescription.Usage = Usage.RenderTargetOutput;

            // figure out the optimal depth stencil format
            if (ConversionMethods.ToDirect3D10(settings.DepthStencilFormat) == Format.Unknown)
                optimal.DepthStencilFormat = Format.D32_Float;
            else
                optimal.DepthStencilFormat = ConversionMethods.ToDirect3D10(settings.DepthStencilFormat);

            // figure out the refresh rate
            if (settings.RefreshRate == 0)
                mode.RefreshRate = new Rational(0, 0);
            else
                mode.RefreshRate = new Rational(settings.RefreshRate, 1);

            // sync interval
            if (settings.EnableVSync)
                optimal.SyncInterval = 1;
            else
                optimal.SyncInterval = 0;

            // return the optimal settings
            swapChainDescription.SampleDescription = sample;
            swapChainDescription.ModeDescription = mode;
            optimal.SwapChainDescription = swapChainDescription;
            return optimal;
        }

        /// <summary>
        /// Ranks a settings combo.
        /// </summary>
        /// <param name="combo">The settings combo.</param>
        /// <param name="optimal">The optimal settings.</param>
        /// <returns>The ranking of the combo.</returns>
        public static float RankSettingsCombo(SettingsCombo10 combo, Direct3D10Settings optimal)
        {
            // rank the combo by how close it is to the desired settings
            float ranking = 0.0f;

            // rank the adapter ordinal
            if (combo.AdapterOrdinal == optimal.AdapterOrdinal)
                ranking += 1000.0f;

            // rank the output ordinal
            if (combo.OutputOrdinal == optimal.OutputOrdinal)
                ranking += 500.0f;

            // rank the device type
            if (combo.DriverType == optimal.DriverType)
                ranking += 100.0f;

            // give slight preference to hardware devices
            if (combo.DriverType == DriverType.Hardware)
                ranking += 0.1f;

            // rank the windowed mode
            if (combo.IsWindowed == optimal.SwapChainDescription.IsWindowed)
                ranking += 10.0f;

            // rank the back buffer format
            if (combo.BackBufferFormat == optimal.SwapChainDescription.ModeDescription.Format)
                ranking += 1.0f;
            else
            {
                // rank by how close the formats are
                int bitDepthDelta = Math.Abs(ConversionMethods.GetColorBits(combo.BackBufferFormat) -
                    ConversionMethods.GetColorBits(optimal.SwapChainDescription.ModeDescription.Format));
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            // loop through each multisample type
            for (int i = 0; i < combo.MultisampleCounts.Count; i++)
            {
                // grab the type and quality
                int type = combo.MultisampleCounts[i];
                int quality = combo.MultisampleQualities[i];

                // check for a match
                if (type == optimal.SwapChainDescription.SampleDescription.Count && quality > optimal.SwapChainDescription.SampleDescription.Quality)
                {
                    // update the ranking
                    ranking += 1.0f;
                    break;
                }
            }

            // check for a resolution match
            foreach (ModeDescription mode in combo.OutputInfo.DisplayModes)
            {
                // check for a match
                if (mode.Width == optimal.SwapChainDescription.ModeDescription.Width &&
                    mode.Height == optimal.SwapChainDescription.ModeDescription.Height)
                {
                    // found it
                    ranking += 1.0f;
                    break;
                }
            }

            // check for a refresh rate match
            foreach (ModeDescription mode in combo.OutputInfo.DisplayModes)
            {
                // check for a match
                if (Math.Abs(ConversionMethods.ToFloat(mode.RefreshRate) - ConversionMethods.ToFloat(optimal.SwapChainDescription.ModeDescription.RefreshRate)) < 0.1f)
                {
                    // found it
                    ranking += 1.0f;
                    break;
                }
            }

            // return the final ranking
            return ranking;
        }

        /// <summary>
        /// Builds valid device settings.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>Valid device settings.</returns>
        public static Direct3D10Settings BuildValidSettings(SettingsCombo10 combo, Direct3D10Settings input)
        {
            // setup the new settings class
            Direct3D10Settings settings = new Direct3D10Settings();
            SwapChainDescription scd = new SwapChainDescription();
            ModeDescription mode = new ModeDescription();
            SampleDescription sample = new SampleDescription();

            // figure out the best display mode
            ModeDescription bestDisplayMode = FindValidResolution(combo, input);

            // figure out the best refresh rate
            if (combo.IsWindowed)
                bestDisplayMode.RefreshRate = new Rational(0, 0);
            else
            {
                // setup to find the best match
                Rational match = input.SwapChainDescription.ModeDescription.RefreshRate;
                bestDisplayMode.RefreshRate = new Rational(0, 0);
                if (match != new Rational(0, 0))
                {
                    // loop through each display mode to find the best ranking
                    float bestRanking = 100000;
                    foreach (ModeDescription displayMode in combo.OutputInfo.DisplayModes)
                    {
                        // make sure the display mode matches
                        if (displayMode.Width != bestDisplayMode.Width ||
                            displayMode.Height != bestDisplayMode.Height)
                            continue;

                        // calculate the ranking
                        float ranking = Math.Abs(ConversionMethods.ToFloat(displayMode.RefreshRate) - ConversionMethods.ToFloat(match));

                        // see if we have a new best ranking
                        if (ranking < bestRanking)
                        {
                            // we do, so store the ranking
                            bestDisplayMode.RefreshRate = displayMode.RefreshRate;
                            bestRanking = ranking;

                            // check if the ranking is a perfect match
                            if (bestRanking == 0)
                                break;
                        }
                    }
                }
            }

            // figure out the best number of back buffers
            int bestBackBufferCount = input.SwapChainDescription.BufferCount;
            if (bestBackBufferCount > 3)
                bestBackBufferCount = 3;
            if (bestBackBufferCount < 1)
                bestBackBufferCount = 1;

            // figure out the best multisample type
            int bestCount;
            int bestQuality;
            if (input.SwapChainDescription.SwapEffect != SwapEffect.Discard)
            {
                // we aren't using Discard, so we can't have multisampling
                bestCount = 1;
                bestQuality = 0;
            }
            else
            {
                // setup to rank the multisampling types
                bestCount = 1;
                bestQuality = 0;

                // loop through each type
                for (int i = 0; i < combo.MultisampleCounts.Count; i++)
                {
                    // grab the values
                    int type = combo.MultisampleCounts[i];
                    int quality = combo.MultisampleQualities[0];

                    // calculate the ranking
                    if (Math.Abs(type - input.SwapChainDescription.SampleDescription.Count) < Math.Abs(bestCount -
                        input.SwapChainDescription.SampleDescription.Count))
                    {
                        // we have a new best, so store it
                        bestCount = type;
                        bestQuality = Math.Min(quality - 1, input.SwapChainDescription.SampleDescription.Quality);
                    }
                }
            }

            // figure out the best sync interval
            int bestSyncInterval = 1;
            if (combo.DriverType == DriverType.Reference)
                bestSyncInterval = 0;

            // build up the mode
            mode.Width = bestDisplayMode.Width;
            mode.Height = bestDisplayMode.Height;
            mode.Format = combo.BackBufferFormat;
            mode.RefreshRate = bestDisplayMode.RefreshRate;

            // build up the sample
            sample.Count = bestCount;
            sample.Quality = bestQuality;

            // build up the swap chain description
            scd.Usage = input.SwapChainDescription.Usage | Usage.RenderTargetOutput;
            scd.BufferCount = bestBackBufferCount;
            scd.SwapEffect = input.SwapChainDescription.SwapEffect;
            scd.IsWindowed = combo.IsWindowed;
            scd.Flags = SwapChainFlags.None;
            scd.ModeDescription = mode;
            scd.SampleDescription = sample;

            // fill in the settings
            settings.AdapterOrdinal = combo.AdapterOrdinal;
            settings.DriverType = combo.DriverType;
            settings.OutputOrdinal = combo.OutputOrdinal;
            settings.SyncInterval = bestSyncInterval;
            settings.DepthStencilFormat = input.DepthStencilFormat;
            settings.CreationFlags = input.CreationFlags;
            settings.SwapChainDescription = scd;

            // return the new valid device settings
            return settings;
        }

        /// <summary>
        /// Finds a valid resolution.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>A valid display mode containing the valid resolution.</returns>
        static ModeDescription FindValidResolution(SettingsCombo10 combo, Direct3D10Settings input)
        {
            // setup for finding the new best mode
            ModeDescription bestMode = new ModeDescription();

            // check if we are windowed
            if (combo.IsWindowed)
            {
                // if we are windowed, just use the back buffer size
                bestMode.Width = input.SwapChainDescription.ModeDescription.Width;
                bestMode.Height = input.SwapChainDescription.ModeDescription.Height;
                return bestMode;
            }

            // loop through each mode to find the best ranking
            int bestRanking = 100000;
            int ranking;
            foreach (ModeDescription mode in combo.OutputInfo.DisplayModes)
            {
                // calculate the ranking
                ranking = Math.Abs(mode.Width - input.SwapChainDescription.ModeDescription.Width) +
                    Math.Abs(mode.Height - input.SwapChainDescription.ModeDescription.Height);

                // check if we found a new best ranking
                if (ranking < bestRanking)
                {
                    // we did, so store it
                    bestMode = mode;
                    bestRanking = ranking;

                    // check if we have a perfect match
                    if (bestRanking == 0)
                        break;
                }
            }

            // check if we didn't find a good match
            if (bestMode.Width == 0)
            {
                // just use the back buffer format now
                bestMode.Width = input.SwapChainDescription.ModeDescription.Width;
                bestMode.Height = input.SwapChainDescription.ModeDescription.Height;
            }

            // return the best display mode
            return bestMode;
        }
    }
}
