using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DXGI;
using SlimDX.Direct3D10;
using System.Windows.Forms;
using System.Drawing;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Handles the configuration and management of the graphics device.
    /// </summary>
    public class GraphicsDeviceManager : IDisposable
    {
        // general variables
        Game game;
        bool ignoreSizeChanges;
        bool deviceLost;
        Factory factory;

        // cached window data
        int fullscreenWindowWidth;
        int fullscreenWindowHeight;
        int windowedWindowWidth;
        int windowedWindowHeight;
        WINDOWPLACEMENT windowedPlacement;
        long windowedStyle;
        bool savedTopmost;

        /// <summary>
        /// Gets  the current device settings.
        /// </summary>
        /// <value>The current device settings.</value>
        public DeviceSettings CurrentSettings
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a value indicating whether the application is windowed.
        /// </summary>
        /// <value>
        /// <c>true</c> if the application is windowed; otherwise, <c>false</c>.
        /// </value>
        public bool IsWindowed
        {
            get { return CurrentSettings.Windowed; }
        }

        /// <summary>
        /// Gets or sets the Direct3D9 device.
        /// </summary>
        /// <value>The Direct3D9 device.</value>
        public SlimDX.Direct3D9.Device Device9
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the Direct3D10 device.
        /// </summary>
        /// <value>The Direct3D10 device.</value>
        public SlimDX.Direct3D10.Device Device10
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GraphicsDeviceManager"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        /// <param name="deviceVersion">The device version.</param>
        /// <param name="windowed">if set to <c>true</c>, the application will run in windowed mode instead of full screen.</param>
        /// <param name="desiredWidth">Desired width of the window.</param>
        /// <param name="desiredHeight">Desired height of the window.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="game"/> is <c>null</c>.</exception>
        public GraphicsDeviceManager(Game game, DeviceVersion deviceVersion, bool windowed, int desiredWidth, int desiredHeight)
        {
            // error checking
            if (game == null)
                throw new ArgumentNullException("game");

            // store the game reference
            this.game = game;

            // build up device settings
            DeviceSettings desiredSettings = new DeviceSettings();
            desiredSettings.DeviceVersion = deviceVersion;
            desiredSettings.Windowed = windowed;
            desiredSettings.BackBufferWidth = desiredWidth;
            desiredSettings.BackBufferHeight = desiredHeight;

            // construct the device
            Construct(desiredSettings);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GraphicsDeviceManager"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        /// <param name="desiredSettings">The desired settings.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="game"/> or <paramref name="desiredSettings"/> is <c>null</c>.</exception>
        public GraphicsDeviceManager(Game game, DeviceSettings desiredSettings)
        {
            // error checking
            if (game == null)
                throw new ArgumentNullException("game");
            if (desiredSettings == null)
                throw new ArgumentNullException("desiredSettings");

            // store the game reference
            this.game = game;

            // construct the device
            Construct(desiredSettings);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            // call the overload
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            // check if we should dispose of managed resources
            if (disposing)
            {
                // release the devices
                ReleaseDevice();
            }
        }

        /// <summary>
        /// Constructs this instance.
        /// </summary>
        /// <param name="desiredSettings">The desired settings.</param>
        void Construct(DeviceSettings desiredSettings)
        {
            // hook up events
            game.Window.ScreenChanged += Window_ScreenChanged;
            game.Window.UserResized += Window_UserResized;

            // find valid device settings
            DeviceSettings settings = FindValidDeviceSettings(desiredSettings);

            // create the device
            CreateDevice(settings);
        }

        /// <summary>
        /// Handles the UserResized event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_UserResized(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// Handles the ScreenChanged event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_ScreenChanged(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// Creates the device.
        /// </summary>
        /// <param name="settings">The settings.</param>
        void CreateDevice(DeviceSettings settings)
        {
            // store the old settings
            DeviceSettings oldSettings = CurrentSettings;
            CurrentSettings = settings;

            // ignore size changes
            ignoreSizeChanges = true;

            // check if we are keeping the current window size
            bool keepCurrentWindowSize = false;
            if (settings.BackBufferWidth == 0 && settings.BackBufferHeight == 0)
                keepCurrentWindowSize = true;

            // handle the window state in Direct3D9 (it will be handled for us in DXGI)
            if (settings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // check if we are going to windowed or fullscreen mode
                if (settings.Windowed)
                {
                    // check if we have old settings
                    if (oldSettings != null && !oldSettings.Windowed)
                        NativeMethods.SetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE, (uint)windowedStyle);
                }
                else
                {
                    // check if we have old settings
                    if (oldSettings == null || oldSettings.Windowed)
                    {
                        // save windowed settings
                        savedTopmost = game.Window.TopMost;
                        long style = NativeMethods.GetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE);
                        style &= ~WindowConstants.WS_MAXIMIZE & ~WindowConstants.WS_MINIMIZE;
                        windowedStyle = style;

                        // save window placement
                        windowedPlacement = new WINDOWPLACEMENT();
                        windowedPlacement.length = WINDOWPLACEMENT.Length;
                        NativeMethods.GetWindowPlacement(game.Window.Handle, ref windowedPlacement);
                    }

                    // hide the window until we are done messing with it
                    game.Window.Hide();
                    NativeMethods.SetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE, (uint)(WindowConstants.WS_POPUP | WindowConstants.WS_SYSMENU));

                    // get the placement of the window
                    WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                    placement.length = WINDOWPLACEMENT.Length;
                    NativeMethods.GetWindowPlacement(game.Window.Handle, ref placement);

                    // check if we are in the middle of a restore
                    if ((placement.flags & WindowConstants.WPF_RESTORETOMAXIMIZED) != 0)
                    {
                        // update the flags to avoid sizing issues
                        placement.flags &= ~WindowConstants.WPF_RESTORETOMAXIMIZED;
                        placement.showCmd = WindowConstants.SW_RESTORE;
                        NativeMethods.SetWindowPlacement(game.Window.Handle, ref placement);
                    }
                }
            }

            // check if we are windowed now or full screen
            if (settings.Windowed)
            {
                // check if we have old settings
                if (oldSettings != null && !oldSettings.Windowed)
                {
                    // store the old size of the window
                    fullscreenWindowWidth = oldSettings.BackBufferWidth;
                    fullscreenWindowHeight = oldSettings.BackBufferHeight;
                }
            }
            else
            {
                // check if we have old settings
                if (oldSettings != null && oldSettings.Windowed)
                {
                    // save the old windowed size
                    windowedWindowWidth = oldSettings.BackBufferWidth;
                    windowedWindowHeight = oldSettings.BackBufferHeight;
                }
            }

            // check if the device can be reset, or if we need to completely recreate it
            Result result = SlimDX.Direct3D9.ResultCode.Success;
            bool canReset = CanDeviceBeReset(oldSettings, settings);
            if (canReset)
                result = ResetDevice();

            // check if we need to do a recreate
            if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                deviceLost = true;
            else if (!canReset || result.IsFailure)
            {
                // release the old device
                if (oldSettings != null)
                    ReleaseDevice();

                // initialize the new device
                InitializeDevice();
            }

            // update device stats
            UpdateDeviceInformation();

            // check if we changed from fullscreen to windowed mode
            if (settings.DeviceVersion == DeviceVersion.Direct3D9 && oldSettings != null && !oldSettings.Windowed && settings.Windowed)
            {
                // restore old settings
                NativeMethods.SetWindowPlacement(game.Window.Handle, ref windowedPlacement);
                game.Window.TopMost = savedTopmost;
            }

            // check if we need to resize
            if (settings.Windowed && !keepCurrentWindowSize)
            {
                // check the new state of the window
                int width;
                int height;
                if (NativeMethods.IsIconic(game.Window.Handle))
                {
                    // get the placement of the window
                    WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                    placement.length = WINDOWPLACEMENT.Length;
                    NativeMethods.GetWindowPlacement(game.Window.Handle, ref placement);

                    // check if we are being restored
                    if ((placement.flags & WindowConstants.WPF_RESTORETOMAXIMIZED) != 0 && placement.showCmd == WindowConstants.SW_SHOWMINIMIZED)
                    {
                        // show the window
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);

                        // grab the client rectangle
                        Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);

                        // update the rectangle and reshow the window
                        width = rect.Width;
                        height = rect.Height;
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_MINIMIZE);
                    }
                    else
                    {
                        // grab the rectangle and adjust it
                        NativeRectangle frame = new NativeRectangle();
                        NativeMethods.AdjustWindowRect(ref frame, (uint)windowedStyle, false);
                        int frameWidth = frame.right - frame.left;
                        int frameHeight = frame.bottom - frame.top;

                        // update the size
                        width = placement.rcNormalPosition.right - placement.rcNormalPosition.left - frameWidth;
                        height = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top - frameHeight;
                    }
                }
                else
                {
                    // grab the client rectangle and adjust the size
                    Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);
                    width = rect.Width;
                    height = rect.Height;
                }

                // check if we have a different desired size
                if (width != settings.BackBufferWidth ||
                    height != settings.BackBufferHeight)
                {
                    // check the state of the window
                    if (NativeMethods.IsIconic(game.Window.Handle))
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);
                    if (NativeMethods.IsZoomed(game.Window.Handle))
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);

                    // grab the rectangle and adjust it for the new size
                    NativeRectangle rect = new NativeRectangle();
                    rect.right = settings.BackBufferWidth;
                    rect.bottom = settings.BackBufferHeight;
                    NativeMethods.AdjustWindowRect(ref rect,
                        NativeMethods.GetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE), false);

                    // set the window's size
                    NativeMethods.SetWindowPos(game.Window.Handle, IntPtr.Zero, 0, 0, rect.right - rect.left,
                        rect.bottom - rect.top, WindowConstants.SWP_NOZORDER | WindowConstants.SWP_NOMOVE);

                    // grab the client rectangle
                    Rectangle r = NativeMethods.GetClientRectangle(game.Window.Handle);
                    int clientWidth = r.Width;
                    int clientHeight = r.Height;

                    // check if the size was modified by windows
                    if (clientWidth != settings.BackBufferWidth ||
                        clientHeight != settings.BackBufferHeight)
                    {
                        // build up the new settings
                        DeviceSettings newSettings = CurrentSettings.Clone();
                        newSettings.BackBufferWidth = 0;
                        newSettings.BackBufferHeight = 0;

                        // create the device
                        CreateDevice(newSettings);
                    }
                }
            }

            // if the window is still hidden, make sure it is shown
            if (!game.Window.Visible)
                NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_SHOW);

            // set the execution state of the thread
            if (!IsWindowed)
                NativeMethods.SetThreadExecutionState(WindowConstants.ES_DISPLAY_REQUIRED | WindowConstants.ES_CONTINUOUS);
            else
                NativeMethods.SetThreadExecutionState(WindowConstants.ES_CONTINUOUS);

            // we are done with changes, allow size changes to be processed again
            ignoreSizeChanges = false;
        }

        /// <summary>
        /// Determines whether the device can be reset.
        /// </summary>
        /// <param name="oldSettings">The old settings.</param>
        /// <param name="newSettings">The new settings.</param>
        /// <returns>
        /// 	<c>true</c> if the device can be reset; otherwise, <c>false</c>.
        /// </returns>
        bool CanDeviceBeReset(DeviceSettings oldSettings, DeviceSettings newSettings)
        {
            // make sure we have old settings and that the two versions are equal
            if (oldSettings == null || oldSettings.DeviceVersion != newSettings.DeviceVersion)
                return false;

            // check the device to see if it can be reset
            if (oldSettings.DeviceVersion == DeviceVersion.Direct3D9)
                return Device9 != null &&
                    oldSettings.Direct3D9.AdapterOrdinal == newSettings.Direct3D9.AdapterOrdinal &&
                    oldSettings.Direct3D9.DeviceType == newSettings.Direct3D9.DeviceType &&
                    oldSettings.Direct3D9.CreationFlags == newSettings.Direct3D9.CreationFlags;
            else
                return Device10 != null &&
                    oldSettings.Direct3D10.AdapterOrdinal == newSettings.Direct3D10.AdapterOrdinal &&
                    oldSettings.Direct3D10.DriverType == newSettings.Direct3D10.DriverType &&
                    oldSettings.Direct3D10.CreationFlags == newSettings.Direct3D10.CreationFlags &&
                    oldSettings.Direct3D10.MultisampleCount == newSettings.Direct3D10.MultisampleCount &&
                    oldSettings.Direct3D10.MultisampleQuality == newSettings.Direct3D10.MultisampleQuality;
        }

        /// <summary>
        /// Initializes the device.
        /// </summary>
        void InitializeDevice()
        {
            // create the correct device based upon the version
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // create the device
                Device9 = new SlimDX.Direct3D9.Device(CurrentSettings.Direct3D9.AdapterOrdinal,
                    CurrentSettings.Direct3D9.DeviceType, game.Window.Handle,
                    CurrentSettings.Direct3D9.CreationFlags, CurrentSettings.Direct3D9.PresentParameters);

                // check for a device lost scenario
                if (Result.Last == SlimDX.Direct3D9.ResultCode.DeviceLost)
                {
                    // device is lost
                    deviceLost = true;
                    return;
                }
            }
            else
            {
                // TODO: Direct3D10
            }

            // update device stats
            UpdateDeviceStats();

            // update the cursor
            SetupCursor();

            // raise events
            game.Initialize();
            game.LoadContent();
        }

        /// <summary>
        /// Resets the device.
        /// </summary>
        /// <returns>The result of the operation.</returns>
        Result ResetDevice()
        {
            // raise the event
            game.UnloadContent();

            // reset the correct device based upong the version
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // make sure D3D10 is released
                ReleaseDevice10();

                // reset the device
                Device9.Reset(CurrentSettings.Direct3D9.PresentParameters);
            }
            else
            {
                // TODO: Direct3D10
            }

            // update the cursor
            SetupCursor();

            // raise the event
            game.LoadContent();

            // return the last result
            return Result.Last;
        }

        /// <summary>
        /// Releases the device.
        /// </summary>
        void ReleaseDevice()
        {
            // reelase the correct device
            if (CurrentSettings != null && CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
                ReleaseDevice9();
            else if (CurrentSettings != null)
                ReleaseDevice10();
        }

        /// <summary>
        /// Releases the Direct3D9 device.
        /// </summary>
        void ReleaseDevice9()
        {
        }

        /// <summary>
        /// Releases the Direct3D10 device.
        /// </summary>
        void ReleaseDevice10()
        {
        }

        /// <summary>
        /// Updates the device information.
        /// </summary>
        void UpdateDeviceInformation()
        {
        }

        /// <summary>
        /// Updates the device stats.
        /// </summary>
        void UpdateDeviceStats()
        {
        }

        /// <summary>
        /// Sets up the cursor.
        /// </summary>
        void SetupCursor()
        {
        }

        /// <summary>
        /// Finds valid device settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The validated device settings.</returns>
        DeviceSettings FindValidDeviceSettings(DeviceSettings settings)
        {
            // build the optimal settings for this machine
            DeviceSettings optimal = BuildOptimalSettings(settings);

            // if we haven't yet enumerated, do it now
            if (!Enumeration9.HasEnumerated)
                Enumeration9.Enumerate();

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
                        float ranking = RankSettingsCombo(combo, optimal, desktopMode);

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
                throw new InvalidOperationException("No compatible devices were found.");

            // return the new valid settings
            return BuildValidDeviceSettings(bestCombo, optimal);
        }

        /// <summary>
        /// Builds valid device settings.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>Valid device settings.</returns>
        DeviceSettings BuildValidDeviceSettings(SettingsCombo9 combo, DeviceSettings input)
        {
            // setup the new settings class
            DeviceSettings settings = new DeviceSettings();

            // set initial values for the settings (the easy ones that
            // don't require much thought)
            settings.Direct3D9.AdapterOrdinal = combo.AdapterOrdinal;
            settings.Direct3D9.DeviceType = combo.DeviceType;
            settings.Direct3D9.PresentParameters.Windowed = combo.Windowed;
            settings.Direct3D9.AdapterFormat = combo.AdapterFormat;
            settings.Direct3D9.PresentParameters.BackBufferFormat = combo.BackBufferFormat;
            settings.Direct3D9.PresentParameters.SwapEffect = input.Direct3D9.PresentParameters.SwapEffect;
            settings.Direct3D9.PresentParameters.PresentFlags =
                input.Direct3D9.PresentParameters.PresentFlags | SlimDX.Direct3D9.PresentFlags.DiscardDepthStencil;
            settings.Direct3D9.PresentParameters.DeviceWindowHandle = game.Window.Handle;

            // figure out the right behavior flags
            settings.Direct3D9.CreationFlags = input.Direct3D9.CreationFlags;
            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) == 0 &&
                ((settings.Direct3D9.CreationFlags & CreateFlags.HardwareVertexProcessing) != 0 ||
                (settings.Direct3D9.CreationFlags & CreateFlags.MixedVertexProcessing) != 0))
            {
                // software vertex processing only
                settings.Direct3D9.CreationFlags &= ~CreateFlags.HardwareVertexProcessing;
                settings.Direct3D9.CreationFlags &= ~CreateFlags.MixedVertexProcessing;
                settings.Direct3D9.CreationFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            // make sure we only have one form of vertex processing
            if ((settings.Direct3D9.CreationFlags & CreateFlags.HardwareVertexProcessing) == 0 &&
                (settings.Direct3D9.CreationFlags & CreateFlags.MixedVertexProcessing) == 0 &&
                (settings.Direct3D9.CreationFlags & CreateFlags.SoftwareVertexProcessing) == 0)
            {
                // set either hardware or software
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    settings.Direct3D9.CreationFlags |= CreateFlags.HardwareVertexProcessing;
                else
                    settings.Direct3D9.CreationFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            // figure out the best display mode
            DisplayMode bestDisplayMode = FindValidResolution(combo, input);
            settings.Direct3D9.PresentParameters.BackBufferWidth = bestDisplayMode.Width;
            settings.Direct3D9.PresentParameters.BackBufferHeight = bestDisplayMode.Height;

            // figure out the best number of back buffers
            settings.Direct3D9.PresentParameters.BackBufferCount = input.Direct3D9.PresentParameters.BackBufferCount;
            if (settings.Direct3D9.PresentParameters.BackBufferCount > 3)
                settings.Direct3D9.PresentParameters.BackBufferCount = 3;
            if (settings.Direct3D9.PresentParameters.BackBufferCount < 1)
                settings.Direct3D9.PresentParameters.BackBufferCount = 1;

            // figure out the best multisample type
            if (input.Direct3D9.PresentParameters.SwapEffect != SlimDX.Direct3D9.SwapEffect.Discard)
            {
                // we aren't using Discard, so we can't have multisampling
                settings.Direct3D9.PresentParameters.Multisample = MultisampleType.None;
                settings.Direct3D9.PresentParameters.MultisampleQuality = 0;
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
                    if (Math.Abs(type - input.Direct3D9.PresentParameters.Multisample) < Math.Abs(bestType -
                        input.Direct3D9.PresentParameters.Multisample))
                    {
                        // we have a new best, so store it
                        bestType = type;
                        bestQuality = Math.Min(quality - 1, input.Direct3D9.PresentParameters.MultisampleQuality);
                    }
                }

                // store the selected settings
                settings.Direct3D9.PresentParameters.Multisample = bestType;
                settings.Direct3D9.PresentParameters.MultisampleQuality = bestQuality;
            }

            // setup to rank depth stencil formats
            List<int> rankings = new List<int>();
            int inputDepthBitDepth = input.Direct3D9.PresentParameters.AutoDepthStencilFormat.GetDepthBits();
            int inputStencilBitDepth = input.Direct3D9.PresentParameters.AutoDepthStencilFormat.GetStencilBits();

            // loop through each possible format
            foreach (SlimDX.Direct3D9.Format format in combo.DepthStencilFormats)
            {
                // extract the bit values
                int currentBitDepth = format.GetDepthBits();
                int currentStencilDepth = format.GetStencilBits();

                // calculate and store the ranking
                int ranking = Math.Abs(currentBitDepth - inputDepthBitDepth);
                ranking += Math.Abs(currentStencilDepth - inputStencilBitDepth);
                rankings.Add(ranking);
            }

            // find the best ranking
            int bestRanking = rankings.Min();
            int bestIndex = rankings.IndexOf(bestRanking);

            // check if we found a best ranking
            if (bestIndex >= 0)
            {
                // use the ranking values
                settings.Direct3D9.PresentParameters.AutoDepthStencilFormat = combo.DepthStencilFormats[bestIndex];
                settings.Direct3D9.PresentParameters.EnableAutoDepthStencil = true;
            }
            else
            {
                // otherwise, we aren't going to use a depth stencil format
                settings.Direct3D9.PresentParameters.AutoDepthStencilFormat = SlimDX.Direct3D9.Format.Unknown;
                settings.Direct3D9.PresentParameters.EnableAutoDepthStencil = false;
            }

            // figure out the best refresh rate
            if (combo.Windowed)
                settings.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz = 0;
            else
            {
                // setup to find the best match
                int match = input.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz;
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
                settings.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz = bestDisplayMode.RefreshRate;
            }

            // use the best presentation interval we have
            if (combo.PresentIntervals.Contains(input.Direct3D9.PresentParameters.PresentationInterval))
                settings.Direct3D9.PresentParameters.PresentationInterval = input.Direct3D9.PresentParameters.PresentationInterval;
            else
                settings.Direct3D9.PresentParameters.PresentationInterval = PresentInterval.Default;

            // return the new valid device settings
            return settings;
        }

        /// <summary>
        /// Finds a valid resolution.
        /// </summary>
        /// <param name="combo">The desired settings combo.</param>
        /// <param name="input">The input settings.</param>
        /// <returns>A valid display mode containing the valid resolution.</returns>
        static DisplayMode FindValidResolution(SettingsCombo9 combo, DeviceSettings input)
        {
            // setup for finding the new best mode
            DisplayMode bestMode = new DisplayMode();

            // check if we are windowed
            if (combo.Windowed)
            {
                // if we are windowed, just use the back buffer size
                bestMode.Width = input.Direct3D9.PresentParameters.BackBufferWidth;
                bestMode.Height = input.Direct3D9.PresentParameters.BackBufferHeight;
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
                ranking = Math.Abs(mode.Width - input.Direct3D9.PresentParameters.BackBufferWidth) +
                    Math.Abs(mode.Height - input.Direct3D9.PresentParameters.BackBufferHeight);

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
                bestMode.Width = input.Direct3D9.PresentParameters.BackBufferWidth;
                bestMode.Height = input.Direct3D9.PresentParameters.BackBufferHeight;
            }

            // return the best display mode
            return bestMode;
        }

        /// <summary>
        /// Ranks a settings combo.
        /// </summary>
        /// <param name="combo">The settings combo.</param>
        /// <param name="optimal">The optimal settings.</param>
        /// <param name="desktopMode">The desktop mode.</param>
        /// <returns>The ranking of the combo.</returns>
        static float RankSettingsCombo(SettingsCombo9 combo, DeviceSettings optimal, DisplayMode desktopMode)
        {
            // rank the combo by how close it is to the desired settings
            float ranking = 0.0f;

            // rank the adapter ordinal
            if (combo.AdapterOrdinal == optimal.Direct3D9.AdapterOrdinal)
                ranking += 1000.0f;

            // rank the device type
            if (combo.DeviceType == optimal.Direct3D9.DeviceType)
                ranking += 100.0f;

            // give slight preference to hardware devices
            if (combo.DeviceType == DeviceType.Hardware)
                ranking += 0.1f;

            // rank the windowed mode
            if (combo.Windowed == optimal.Direct3D9.PresentParameters.Windowed)
                ranking += 10.0f;

            // rank the adapter format
            if (combo.AdapterFormat == optimal.Direct3D9.AdapterFormat)
                ranking += 1.0f;
            else
            {
                // rank by how close the two bit depths are
                int bitDepthDelta = Math.Abs(combo.AdapterFormat.GetColorBits() -
                    optimal.Direct3D9.AdapterFormat.GetColorBits());
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            // check if we are in fullscreen mode
            if (!combo.Windowed)
            {
                // slightly prefer matches that are in a preferred format
                bool match;
                if (desktopMode.Format.GetColorBits() >= 8)
                    match = (combo.AdapterFormat == desktopMode.Format);
                else
                    match = (combo.AdapterFormat == SlimDX.Direct3D9.Format.X8R8G8B8);

                // if we have a match, update the ranking
                if (match)
                    ranking += 0.1f;
            }

            // rank vertex processing
            if ((optimal.Direct3D9.CreationFlags & CreateFlags.HardwareVertexProcessing) != 0 &&
                (optimal.Direct3D9.CreationFlags & CreateFlags.MixedVertexProcessing) != 0)
            {
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    ranking += 1.0f;
            }

            // prefer hardware transformation and lighting
            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                ranking += 0.1f;

            // check if any of the display modes are valid
            if (combo.AdapterInfo.DisplayModes.Any(displayMode =>
                displayMode.Format == combo.AdapterFormat &&
                displayMode.Width == optimal.Direct3D9.PresentParameters.BackBufferWidth &&
                displayMode.Height == optimal.Direct3D9.PresentParameters.BackBufferHeight))
                ranking += 1.0f;

            // rank the back buffer format
            if (combo.BackBufferFormat == optimal.Direct3D9.PresentParameters.BackBufferFormat)
                ranking += 1.0f;
            else
            {
                // rank by how close the formats are
                int bitDepthDelta = Math.Abs(combo.BackBufferFormat.GetColorBits() -
                    optimal.Direct3D9.PresentParameters.BackBufferFormat.GetColorBits());
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
                if (type == optimal.Direct3D9.PresentParameters.Multisample && quality == optimal.Direct3D9.PresentParameters.MultisampleQuality)
                {
                    // update the ranking
                    ranking += 1.0f;
                    break;
                }
            }

            // check if the depth stencil formats match
            if (combo.DepthStencilFormats.Contains(optimal.Direct3D9.PresentParameters.AutoDepthStencilFormat))
                ranking += 1.0f;

            // check for a refresh rate match
            if (combo.AdapterInfo.DisplayModes.Any(displayMode =>
                displayMode.Format == combo.AdapterFormat &&
                displayMode.RefreshRate == optimal.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz))
                ranking += 1.0f;

            // check if the present intervals match
            if (combo.PresentIntervals.Contains(optimal.Direct3D9.PresentParameters.PresentationInterval))
                ranking += 1.0f;

            // return the final ranking
            return ranking;
        }

        /// <summary>
        /// Builds optimal device settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The optimal device settings</returns>
        static DeviceSettings BuildOptimalSettings(DeviceSettings settings)
        {
            // grab the desktop mode
            DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(settings.Direct3D9.AdapterOrdinal);
            DeviceSettings optimal = new DeviceSettings();

            // setup the easy values first
            optimal.Direct3D9.AdapterOrdinal = settings.Direct3D9.AdapterOrdinal;
            optimal.Direct3D9.DeviceType = settings.Direct3D9.DeviceType;
            optimal.Direct3D9.PresentParameters.Windowed = settings.Direct3D9.PresentParameters.Windowed;
            optimal.Direct3D9.CreationFlags = settings.Direct3D9.CreationFlags;
            optimal.Direct3D9.PresentParameters.BackBufferCount = settings.Direct3D9.PresentParameters.BackBufferCount;
            optimal.Direct3D9.PresentParameters.Multisample = settings.Direct3D9.PresentParameters.Multisample;
            optimal.Direct3D9.PresentParameters.MultisampleQuality = settings.Direct3D9.PresentParameters.MultisampleQuality;
            optimal.Direct3D9.PresentParameters.PresentFlags = settings.Direct3D9.PresentParameters.PresentFlags;
            optimal.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz = settings.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz;
            optimal.Direct3D9.PresentParameters.PresentationInterval = settings.Direct3D9.PresentParameters.PresentationInterval;
            optimal.Direct3D9.PresentParameters.SwapEffect = settings.Direct3D9.PresentParameters.SwapEffect;

            // figure out the optimal adapter format
            if (settings.Direct3D9.AdapterFormat == SlimDX.Direct3D9.Format.Unknown)
            {
                // depends on the windowed mode
                if (optimal.Direct3D9.PresentParameters.Windowed || desktopMode.Format.GetColorBits() >= 8)
                    optimal.Direct3D9.AdapterFormat = desktopMode.Format;
                else
                    optimal.Direct3D9.AdapterFormat = SlimDX.Direct3D9.Format.X8R8G8B8;
            }
            else
                optimal.Direct3D9.AdapterFormat = settings.Direct3D9.AdapterFormat;

            // figure out the optimal back buffer size
            if (settings.Direct3D9.PresentParameters.BackBufferWidth == 0 || settings.Direct3D9.PresentParameters.BackBufferHeight == 0)
            {
                // depends on the windowed mode
                if (optimal.Direct3D9.PresentParameters.Windowed)
                {
                    // just use a default size
                    optimal.Direct3D9.PresentParameters.BackBufferWidth = 640;
                    optimal.Direct3D9.PresentParameters.BackBufferHeight = 480;
                }
                else
                {
                    // use the desktop size
                    optimal.Direct3D9.PresentParameters.BackBufferWidth = desktopMode.Width;
                    optimal.Direct3D9.PresentParameters.BackBufferHeight = desktopMode.Height;
                }
            }
            else
            {
                // otherwise, use the specified size
                optimal.Direct3D9.PresentParameters.BackBufferWidth = settings.Direct3D9.PresentParameters.BackBufferWidth;
                optimal.Direct3D9.PresentParameters.BackBufferHeight = settings.Direct3D9.PresentParameters.BackBufferHeight;
            }

            // figure out the optimal back buffer format
            if (settings.Direct3D9.PresentParameters.BackBufferFormat == SlimDX.Direct3D9.Format.Unknown)
                optimal.Direct3D9.PresentParameters.BackBufferFormat = optimal.Direct3D9.AdapterFormat;
            else
                optimal.Direct3D9.PresentParameters.BackBufferFormat = settings.Direct3D9.PresentParameters.BackBufferFormat;

            // figure out the optimal depth stencil format
            if (settings.Direct3D9.PresentParameters.AutoDepthStencilFormat == SlimDX.Direct3D9.Format.Unknown)
            {
                // depends on the bit depth
                if (optimal.Direct3D9.PresentParameters.BackBufferFormat.GetColorBits() >= 8)
                    optimal.Direct3D9.PresentParameters.AutoDepthStencilFormat = SlimDX.Direct3D9.Format.D32;
                else
                    optimal.Direct3D9.PresentParameters.AutoDepthStencilFormat = SlimDX.Direct3D9.Format.D16;
                optimal.Direct3D9.PresentParameters.EnableAutoDepthStencil = true;
            }
            else
            {
                // otherwise, use the specified value
                optimal.Direct3D9.PresentParameters.EnableAutoDepthStencil = true;
                optimal.Direct3D9.PresentParameters.AutoDepthStencilFormat = settings.Direct3D9.PresentParameters.AutoDepthStencilFormat;
            }

            // return the optimal settings
            return optimal;
        }
    }
}
