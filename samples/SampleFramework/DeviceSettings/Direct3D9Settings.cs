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
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains settings for a Direct3D9 device.
    /// </summary>
    class Direct3D9Settings : ICloneable
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
        /// Gets or sets the behavior flags.
        /// </summary>
        /// <value>The behavior flags.</value>
        public CreateFlags CreationFlags
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the present parameters.
        /// </summary>
        /// <value>The present parameters.</value>
        public PresentParameters PresentParameters
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Direct3D9Settings"/> class.
        /// </summary>
        public Direct3D9Settings()
        {
            // set defaults
            PresentParameters = new PresentParameters();
            DeviceType = DeviceType.Hardware;
            PresentParameters.Windowed = true;
            AdapterFormat = Format.Unknown;
            CreationFlags = CreateFlags.HardwareVertexProcessing;
            PresentParameters.BackBufferFormat = Format.Unknown;
            PresentParameters.BackBufferCount = 1;
            PresentParameters.Multisample = MultisampleType.None;
            PresentParameters.SwapEffect = SwapEffect.Discard;
            PresentParameters.EnableAutoDepthStencil = true;
            PresentParameters.AutoDepthStencilFormat = Format.Unknown;
            PresentParameters.PresentFlags = PresentFlags.DiscardDepthStencil;
            PresentParameters.PresentationInterval = PresentInterval.Default;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public Direct3D9Settings Clone()
        {
            // create the cloned settings
            Direct3D9Settings clone = new Direct3D9Settings();
            clone.AdapterFormat = AdapterFormat;
            clone.AdapterOrdinal = AdapterOrdinal;
            clone.CreationFlags = CreationFlags;
            clone.DeviceType = DeviceType;
            clone.PresentParameters = PresentParameters.Clone();

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
        /// Builds optimal Direct3D9 device settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The optimal device settings</returns>
        public static Direct3D9Settings BuildOptimalSettings(DeviceSettings settings)
        {
            // grab the desktop mode
            DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(0);
            Direct3D9Settings optimal = new Direct3D9Settings();

            // set up the easy values first
            optimal.DeviceType = settings.DeviceType;
            optimal.PresentParameters.Windowed = settings.Windowed;
            optimal.PresentParameters.BackBufferCount = settings.BackBufferCount;
            optimal.PresentParameters.Multisample = settings.MultisampleType;
            optimal.PresentParameters.MultisampleQuality = settings.MultisampleQuality;
            optimal.PresentParameters.FullScreenRefreshRateInHertz = settings.RefreshRate;

            // figure out the optimal adapter format
            if (optimal.PresentParameters.Windowed || ConversionMethods.GetColorBits(desktopMode.Format) >= 8)
                optimal.AdapterFormat = desktopMode.Format;
            else
                optimal.AdapterFormat = Format.X8R8G8B8;

            // figure out the optimal back buffer size
            if (settings.BackBufferWidth == 0 || settings.BackBufferHeight == 0)
            {
                // depends on the windowed mode
                if (optimal.PresentParameters.Windowed)
                {
                    // just use a default size
                    optimal.PresentParameters.BackBufferWidth = 640;
                    optimal.PresentParameters.BackBufferHeight = 480;
                }
                else
                {
                    // use the desktop size
                    optimal.PresentParameters.BackBufferWidth = desktopMode.Width;
                    optimal.PresentParameters.BackBufferHeight = desktopMode.Height;
                }
            }
            else
            {
                // otherwise, use the specified size
                optimal.PresentParameters.BackBufferWidth = settings.BackBufferWidth;
                optimal.PresentParameters.BackBufferHeight = settings.BackBufferHeight;
            }

            // figure out the optimal back buffer format
            if (settings.BackBufferFormat == Format.Unknown)
                optimal.PresentParameters.BackBufferFormat = optimal.AdapterFormat;
            else
                optimal.PresentParameters.BackBufferFormat = settings.BackBufferFormat;

            // figure out the optimal depth stencil format
            if (settings.DepthStencilFormat == Format.Unknown)
            {
                // depends on the bit depth
                if (ConversionMethods.GetColorBits(optimal.PresentParameters.BackBufferFormat) >= 8)
                    optimal.PresentParameters.AutoDepthStencilFormat = Format.D32;
                else
                    optimal.PresentParameters.AutoDepthStencilFormat = Format.D16;
            }
            else
                optimal.PresentParameters.AutoDepthStencilFormat = settings.DepthStencilFormat;

            // figure out the presentation interval
            if (!settings.EnableVSync)
                optimal.PresentParameters.PresentationInterval = PresentInterval.Immediate;

            // return the optimal settings
            return optimal;
        }

        /// <summary>
        /// Ranks a settings combo.
        /// </summary>
        /// <param name="combo">The settings combo.</param>
        /// <param name="optimal">The optimal settings.</param>
        /// <param name="desktopMode">The desktop mode.</param>
        /// <returns>The ranking of the combo.</returns>
        public static float RankSettingsCombo(SettingsCombo9 combo, Direct3D9Settings optimal, DisplayMode desktopMode)
        {
            // rank the combo by how close it is to the desired settings
            float ranking = 0.0f;

            // rank the adapter ordinal
            if (combo.AdapterOrdinal == optimal.AdapterOrdinal)
                ranking += 1000.0f;

            // rank the device type
            if (combo.DeviceType == optimal.DeviceType)
                ranking += 100.0f;

            // give slight preference to hardware devices
            if (combo.DeviceType == DeviceType.Hardware)
                ranking += 0.1f;

            // rank the windowed mode
            if (combo.Windowed == optimal.PresentParameters.Windowed)
                ranking += 10.0f;

            // rank the adapter format
            if (combo.AdapterFormat == optimal.AdapterFormat)
                ranking += 1.0f;
            else
            {
                // rank by how close the two bit depths are
                int bitDepthDelta = Math.Abs(ConversionMethods.GetColorBits(combo.AdapterFormat) -
                    ConversionMethods.GetColorBits(optimal.AdapterFormat));
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            // check if we are in fullscreen mode
            if (!combo.Windowed)
            {
                // slightly prefer matches that are in a preferred format
                bool match;
                if (ConversionMethods.GetColorBits(desktopMode.Format) >= 8)
                    match = (combo.AdapterFormat == desktopMode.Format);
                else
                    match = (combo.AdapterFormat == Format.X8R8G8B8);

                // if we have a match, update the ranking
                if (match)
                    ranking += 0.1f;
            }

            // rank vertex processing
            if ((optimal.CreationFlags & CreateFlags.HardwareVertexProcessing) != 0 &&
                (optimal.CreationFlags & CreateFlags.MixedVertexProcessing) != 0)
            {
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    ranking += 1.0f;
            }

            // prefer hardware transformation and lighting
            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                ranking += 0.1f;

            // check if any of the display modes are valid
            foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
            {
                // check for a match
                if (displayMode.Format == combo.AdapterFormat &&
                    displayMode.Width == optimal.PresentParameters.BackBufferWidth &&
                    displayMode.Height == optimal.PresentParameters.BackBufferHeight)
                {
                    // found it
                    ranking += 1.0f;
                    break;
                }
            }

            // rank the back buffer format
            if (combo.BackBufferFormat == optimal.PresentParameters.BackBufferFormat)
                ranking += 1.0f;
            else
            {
                // rank by how close the formats are
                int bitDepthDelta = Math.Abs(ConversionMethods.GetColorBits(combo.BackBufferFormat) -
                    ConversionMethods.GetColorBits(optimal.PresentParameters.BackBufferFormat));
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            // slightly prefer that the back buffer format equal the adapter format
            if (combo.BackBufferFormat == combo.AdapterFormat)
                ranking += 0.1f;

            // loop through each multisample type
            for (int i = 0; i < combo.MultisampleTypes.Count; i++)
            {
                // grab the type and quality
                MultisampleType type = combo.MultisampleTypes[i];
                int quality = combo.MultisampleQualities[i];

                // check for a match
                if (type == optimal.PresentParameters.Multisample && quality == optimal.PresentParameters.MultisampleQuality)
                {
                    // update the ranking
                    ranking += 1.0f;
                    break;
                }
            }

            // check if the depth stencil formats match
            if (combo.DepthStencilFormats.Contains(optimal.PresentParameters.AutoDepthStencilFormat))
                ranking += 1.0f;

            // check for a refresh rate match
            foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
            {
                // check for a match
                if (displayMode.Format == combo.AdapterFormat &&
                    displayMode.RefreshRate == optimal.PresentParameters.FullScreenRefreshRateInHertz)
                {
                    // found it
                    ranking += 1.0f;
                    break;
                }
            }

            // check if the present intervals match
            if (combo.PresentIntervals.Contains(optimal.PresentParameters.PresentationInterval))
                ranking += 1.0f;

            // return the final ranking
            return ranking;
        }

        /// <summary>
        /// Builds valid device settings.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>Valid device settings.</returns>
        public static Direct3D9Settings BuildValidSettings(SettingsCombo9 combo, Direct3D9Settings input)
        {
            // setup the new settings class
            Direct3D9Settings settings = new Direct3D9Settings();

            // set initial values for the settings (the easy ones that
            // don't require much thought)
            settings.AdapterOrdinal = combo.AdapterOrdinal;
            settings.DeviceType = combo.DeviceType;
            settings.PresentParameters.Windowed = combo.Windowed;
            settings.AdapterFormat = combo.AdapterFormat;
            settings.PresentParameters.BackBufferFormat = combo.BackBufferFormat;
            settings.PresentParameters.SwapEffect = input.PresentParameters.SwapEffect;
            settings.PresentParameters.PresentFlags = input.PresentParameters.PresentFlags | PresentFlags.DiscardDepthStencil;

            // figure out the right behavior flags
            settings.CreationFlags = input.CreationFlags;
            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) == 0 &&
                ((settings.CreationFlags & CreateFlags.HardwareVertexProcessing) != 0 ||
                (settings.CreationFlags & CreateFlags.MixedVertexProcessing) != 0))
            {
                // software vertex processing only
                settings.CreationFlags &= ~CreateFlags.HardwareVertexProcessing;
                settings.CreationFlags &= ~CreateFlags.MixedVertexProcessing;
                settings.CreationFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            // make sure we only have one form of vertex processing
            if ((settings.CreationFlags & CreateFlags.HardwareVertexProcessing) == 0 &&
                (settings.CreationFlags & CreateFlags.MixedVertexProcessing) == 0 &&
                (settings.CreationFlags & CreateFlags.SoftwareVertexProcessing) == 0)
            {
                // set either hardware or software
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    settings.CreationFlags |= CreateFlags.HardwareVertexProcessing;
                else
                    settings.CreationFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            // figure out the best display mode
            DisplayMode bestDisplayMode = FindValidResolution(combo, input);
            settings.PresentParameters.BackBufferWidth = bestDisplayMode.Width;
            settings.PresentParameters.BackBufferHeight = bestDisplayMode.Height;

            // figure out the best number of back buffers
            settings.PresentParameters.BackBufferCount = input.PresentParameters.BackBufferCount;
            if (settings.PresentParameters.BackBufferCount > 3)
                settings.PresentParameters.BackBufferCount = 3;
            if (settings.PresentParameters.BackBufferCount < 1)
                settings.PresentParameters.BackBufferCount = 1;

            // figure out the best multisample type
            if (input.PresentParameters.SwapEffect != SwapEffect.Discard)
            {
                // we aren't using Discard, so we can't have multisampling
                settings.PresentParameters.Multisample = MultisampleType.None;
                settings.PresentParameters.MultisampleQuality = 0;
            }
            else
            {
                // setup to rank the multisampling types
                MultisampleType bestType = MultisampleType.None;
                int bestQuality = 0;

                // loop through each type
                for (int i = 0; i < combo.MultisampleTypes.Count; i++)
                {
                    // grab the values
                    MultisampleType type = combo.MultisampleTypes[i];
                    int quality = combo.MultisampleQualities[0];

                    // calculate the ranking
                    if (Math.Abs(type - input.PresentParameters.Multisample) < Math.Abs(bestType -
                        input.PresentParameters.Multisample))
                    {
                        // we have a new best, so store it
                        bestType = type;
                        bestQuality = Math.Min(quality - 1, input.PresentParameters.MultisampleQuality);
                    }
                }

                // store the selected settings
                settings.PresentParameters.Multisample = bestType;
                settings.PresentParameters.MultisampleQuality = bestQuality;
            }

            // setup to rank depth stencil formats
            List<int> rankings = new List<int>();
            int inputDepthBitDepth = ConversionMethods.GetDepthBits(input.PresentParameters.AutoDepthStencilFormat);
            int inputStencilBitDepth = ConversionMethods.GetStencilBits(input.PresentParameters.AutoDepthStencilFormat);

            // loop through each possible format
            foreach (Format format in combo.DepthStencilFormats)
            {
                // extract the bit values
                int currentBitDepth = ConversionMethods.GetDepthBits(format);
                int currentStencilDepth = ConversionMethods.GetStencilBits(format);

                // calculate and store the ranking
                int ranking = Math.Abs(currentBitDepth - inputDepthBitDepth);
                ranking += Math.Abs(currentStencilDepth - inputStencilBitDepth);
                rankings.Add(ranking);
            }

            // find the best ranking
            int bestRanking = int.MaxValue;
            foreach (int ranking in rankings)
            {
                // check for a better match
                if (ranking < bestRanking)
                    bestRanking = ranking;
            }
            int bestIndex = rankings.IndexOf(bestRanking);

            // check if we found a best ranking
            if (bestIndex >= 0)
            {
                // use the ranking values
                settings.PresentParameters.AutoDepthStencilFormat = combo.DepthStencilFormats[bestIndex];
                settings.PresentParameters.EnableAutoDepthStencil = true;
            }
            else
            {
                // otherwise, we aren't going to use a depth stencil format
                settings.PresentParameters.AutoDepthStencilFormat = Format.Unknown;
                settings.PresentParameters.EnableAutoDepthStencil = false;
            }

            // figure out the best refresh rate
            if (combo.Windowed)
                settings.PresentParameters.FullScreenRefreshRateInHertz = 0;
            else
            {
                // setup to find the best match
                int match = input.PresentParameters.FullScreenRefreshRateInHertz;
                bestDisplayMode.RefreshRate = 0;
                if (match != 0)
                {
                    // loop through each display mode to find the best ranking
                    bestRanking = 100000;
                    foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
                    {
                        // make sure the display mode matches
                        if (displayMode.Format != combo.AdapterFormat ||
                            displayMode.Width != bestDisplayMode.Width ||
                            displayMode.Height != bestDisplayMode.Height)
                            continue;

                        // calculate the ranking
                        int ranking = Math.Abs(displayMode.RefreshRate - match);

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

                // use the ranked value
                settings.PresentParameters.FullScreenRefreshRateInHertz = bestDisplayMode.RefreshRate;
            }

            // use the best presentation interval we have
            if (combo.PresentIntervals.Contains(input.PresentParameters.PresentationInterval))
                settings.PresentParameters.PresentationInterval = input.PresentParameters.PresentationInterval;
            else
                settings.PresentParameters.PresentationInterval = PresentInterval.Default;

            // return the new valid device settings
            return settings;
        }

        /// <summary>
        /// Finds a valid resolution.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>A valid display mode containing the valid resolution.</returns>
        static DisplayMode FindValidResolution(SettingsCombo9 combo, Direct3D9Settings input)
        {
            // setup for finding the new best mode
            DisplayMode bestMode = new DisplayMode();

            // check if we are windowed
            if (combo.Windowed)
            {
                // if we are windowed, just use the back buffer size
                bestMode.Width = input.PresentParameters.BackBufferWidth;
                bestMode.Height = input.PresentParameters.BackBufferHeight;
                return bestMode;
            }

            // loop through each mode to find the best ranking
            int bestRanking = 100000;
            int ranking;
            foreach (DisplayMode mode in combo.AdapterInfo.DisplayModes)
            {
                // make sure the formats match
                if (mode.Format != combo.AdapterFormat)
                    continue;

                // calculate the ranking
                ranking = Math.Abs(mode.Width - input.PresentParameters.BackBufferWidth) +
                    Math.Abs(mode.Height - input.PresentParameters.BackBufferHeight);

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
                bestMode.Width = input.PresentParameters.BackBufferWidth;
                bestMode.Height = input.PresentParameters.BackBufferHeight;
            }

            // return the best display mode
            return bestMode;
        }
    }
}
