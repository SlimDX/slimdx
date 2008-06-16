using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DXGI;

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

        // cached window data
        int fullscreenWindowWidth;
        int fullscreenWindowHeight;
        int windowedWindowWidth;
        int windowedWindowHeight;
        WINDOWPLACEMENT windowedPlacement;
        long windowedStyle;
        bool savedTopmost;

        /// <summary>
        /// Gets the Direct3D10 factory.
        /// </summary>
        /// <value>The Direct3D10 factory.</value>
        internal static Factory Factory
        {
            get;
            private set;
        }

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
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="game"/> is <c>null</c>.</exception>
        public GraphicsDeviceManager(Game game)
        {
            // error checking
            if (game == null)
                throw new ArgumentNullException("game");

            // store the game reference
            this.game = game;

            // hook up window events
            game.Window.ScreenChanged += Window_ScreenChanged;
            game.Window.UserResized += Window_UserResized;

            // hook up game events
            game.FrameStart += game_FrameStart;
            game.FrameEnd += game_FrameEnd;
        }

        /// <summary>
        /// Ensures that Direct3D9 is initialized.
        /// </summary>
        internal static void EnsureD3D9()
        {
            // initialize Direct3D9
            Direct3D.Initialize();
        }

        /// <summary>
        /// Ensures that Direct3D10 is initialized.
        /// </summary>
        internal static void EnsureD3D10()
        {
            // create the factory, if we don't have one yet
            if (Factory == null)
                Factory = new Factory();
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
        /// Changes the device.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <param name="minimumSettings">The minimum settings.</param>
        /// <exception cref="ArgumentNullException">Thrown when the <paramref name="settings"/> is <c>null</c>.</exception>
        public void ChangeDevice(DeviceSettings settings, DeviceSettings minimumSettings)
        {
            // error checking
            if (settings == null)
                throw new ArgumentNullException("settings");

            // propogate the minimum settings
            Enumeration9.MinimumSettings = minimumSettings;
            Enumeration10.MinimumSettings = minimumSettings;

            // find valid device settings
            DeviceSettings validSettings = DeviceSettings.FindValidSettings(settings);

            // ensure that the correct window is placed into the settings
            if (validSettings.DeviceVersion == DeviceVersion.Direct3D9)
                validSettings.Direct3D9.PresentParameters.DeviceWindowHandle = game.Window.Handle;
            else
            {
                // set the output handle
                SwapChainDescription scd = validSettings.Direct3D10.SwapChainDescription;
                scd.OutputHandle = game.Window.Handle;
                validSettings.Direct3D10.SwapChainDescription = scd;
            }

            // create the device
            CreateDevice(validSettings);

            // propogate new settings into the current settings account
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // propogate settings
                CurrentSettings.BackBufferCount = CurrentSettings.Direct3D9.PresentParameters.BackBufferCount;
                CurrentSettings.BackBufferWidth = CurrentSettings.Direct3D9.PresentParameters.BackBufferWidth;
                CurrentSettings.BackBufferHeight = CurrentSettings.Direct3D9.PresentParameters.BackBufferHeight;
                CurrentSettings.BackBufferFormat = CurrentSettings.Direct3D9.PresentParameters.BackBufferFormat;
                CurrentSettings.DepthStencilFormat = CurrentSettings.Direct3D9.PresentParameters.AutoDepthStencilFormat;
                CurrentSettings.DeviceType = CurrentSettings.Direct3D9.DeviceType;
                CurrentSettings.MultisampleQuality = CurrentSettings.Direct3D9.PresentParameters.MultisampleQuality;
                CurrentSettings.MultisampleType = CurrentSettings.Direct3D9.PresentParameters.Multisample;
                CurrentSettings.RefreshRate = CurrentSettings.Direct3D9.PresentParameters.FullScreenRefreshRateInHertz;
                CurrentSettings.Windowed = CurrentSettings.Direct3D9.PresentParameters.Windowed;
            }
            else
            {
                // propogate settings
                CurrentSettings.BackBufferCount = CurrentSettings.Direct3D10.SwapChainDescription.BufferCount;
                CurrentSettings.BackBufferWidth = CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Width;
                CurrentSettings.BackBufferHeight = CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Height;
                CurrentSettings.BackBufferFormat = CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format.ToDirect3D9();
                CurrentSettings.DepthStencilFormat = CurrentSettings.Direct3D10.DepthStencilFormat.ToDirect3D9();
                CurrentSettings.DeviceType = CurrentSettings.Direct3D10.DriverType.ToDirect3D9();
                CurrentSettings.MultisampleQuality = CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality;
                CurrentSettings.MultisampleType = CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Count.ToDirect3D9();
                CurrentSettings.RefreshRate = (int)CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.RefreshRate.ToFloat();
                CurrentSettings.Windowed = CurrentSettings.Direct3D10.SwapChainDescription.IsWindowed;
            }
        }

        /// <summary>
        /// Changes the device.
        /// </summary>
        /// <param name="deviceVersion">The device version.</param>
        /// <param name="windowed">if set to <c>true</c>, the application will run in windowed mode instead of full screen.</param>
        /// <param name="desiredWidth">Desired width of the window.</param>
        /// <param name="desiredHeight">Desired height of the window.</param>
        public void ChangeDevice(DeviceVersion deviceVersion, bool windowed, int desiredWidth, int desiredHeight)
        {
            // build up device settings
            DeviceSettings desiredSettings = new DeviceSettings();
            desiredSettings.DeviceVersion = deviceVersion;
            desiredSettings.Windowed = windowed;
            desiredSettings.BackBufferWidth = desiredWidth;
            desiredSettings.BackBufferHeight = desiredHeight;

            // construct the device
            ChangeDevice(desiredSettings, null);
        }

        /// <summary>
        /// Changes the device.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <exception cref="ArgumentNullException">Thrown when the <paramref name="settings"/> is <c>null</c>.</exception>
        public void ChangeDevice(DeviceSettings settings)
        {
            // call the overload
            ChangeDevice(settings, null);
        }

        /// <summary>
        /// Toggles between full screen and windowed mode.
        /// </summary>
        public void ToggleFullScreen()
        {
            // error checking
            if (CurrentSettings == null || (Device9 == null && Device10 == null))
                throw new InvalidOperationException("No valid device.");

            // set up the new settings
            DeviceSettings newSettings = CurrentSettings.Clone();

            // flip the bit
            newSettings.Windowed = !newSettings.Windowed;

            // go back to the previous size
            int width = newSettings.Windowed ? windowedWindowWidth : fullscreenWindowWidth;
            int height = newSettings.Windowed ? windowedWindowHeight : fullscreenWindowHeight;

            // store the size
            newSettings.BackBufferWidth = width;
            newSettings.BackBufferHeight = height;

            // change the device
            ChangeDevice(newSettings);
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
        /// Handles the UserResized event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_UserResized(object sender, EventArgs e)
        {
            // skip the check for various reasons
            if (ignoreSizeChanges || (Device9 == null && Device10 == null) || CurrentSettings == null ||
                (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9 && !IsWindowed))
                return;

            // clone the settings
            DeviceSettings newSettings = CurrentSettings.Clone();

            // check the version
            if (newSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // get the client rectangle
                Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);
                if (rect.Width != newSettings.BackBufferWidth || rect.Height != newSettings.BackBufferHeight)
                {
                    // recreate the device
                    newSettings.BackBufferWidth = 0;
                    newSettings.BackBufferHeight = 0;
                    CreateDevice(newSettings);
                }
            }
            else
            {
                // TODO: Direct3D10
            }
        }

        /// <summary>
        /// Handles the ScreenChanged event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_ScreenChanged(object sender, EventArgs e)
        {
            // TODO: Do this
        }

        /// <summary>
        /// Handles the FrameEnd event of the game control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void game_FrameEnd(object sender, EventArgs e)
        {
            // check the device version
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // present the frame
                Result result = Device9.Present();
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                    deviceLost = true;
            }
            else
            {
                // TODO: Direct3D10
            }
        }

        /// <summary>
        /// Handles the FrameStart event of the game control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        void game_FrameStart(object sender, CancelEventArgs e)
        {
            // make sure we have a valid device
            if (CurrentSettings == null || (Device9 == null && Device10 == null))
            {
                // nothing to render
                e.Cancel = true;
                return;
            }

            // if the device is lost or the game is not active, sleep for a bit
            if (!game.IsActive || deviceLost)
                Thread.Sleep(50);

            // if the device is lost, see if we can do something about it
            if (deviceLost)
            {
                // test to see if it's ok to render again
                Result result = Device9.TestCooperativeLevel();
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                {
                    // device is lost but cannot be reset at this time
                    e.Cancel = true;
                    return;
                }

                // if we are windowed, check the adapter format to see if the user
                // changed the desktop format, causing a lost device
                if (IsWindowed)
                {
                    // get the current display mode
                    DisplayMode displayMode = Direct3D.GetAdapterDisplayMode(CurrentSettings.Direct3D9.AdapterOrdinal);
                    if (CurrentSettings.Direct3D9.AdapterFormat != displayMode.Format)
                    {
                        // create the new device
                        DeviceSettings newSettings = CurrentSettings.Clone();
                        ChangeDevice(newSettings);
                        e.Cancel = true;
                        return;
                    }
                }

                // try to reset the device
                result = ResetDevice();
                if (result.IsFailure)
                {
                    // device is still lost
                    e.Cancel = true;
                    return;
                }
            }

            // if we made it to this point, the device is no longer lost
            deviceLost = false;

            // update frame stats
            UpdateFrameStats();
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
                    oldSettings.Direct3D10.SwapChainDescription.SampleDescription.Count == newSettings.Direct3D10.SwapChainDescription.SampleDescription.Count &&
                    oldSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality == newSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality;
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
            // ensure that both devices are released
            ReleaseDevice9();
            ReleaseDevice10();
        }

        /// <summary>
        /// Releases the Direct3D9 device.
        /// </summary>
        void ReleaseDevice9()
        {
            // make sure we have a device
            if (Device9 == null)
                return;

            // inform the game
            if (game != null)
            {
                // inform the game
                game.UnloadContent();
                game.Release();
            }

            // release the device
            Device9.Dispose();

            // clear references
            Device9 = null;
            if (CurrentSettings != null)
                CurrentSettings.Direct3D9 = null;
        }

        /// <summary>
        /// Releases the Direct3D10 device.
        /// </summary>
        void ReleaseDevice10()
        {
            // make sure we have a device
            if (Device10 == null)
                return;

            // inform the game
            if (game != null)
            {
                // inform the game
                game.UnloadContent();
                game.Release();
            }

            // release the device
            Device10.Dispose();
            Factory.Dispose();

            // clear references
            Device10 = null;
            Factory = null;
            if (CurrentSettings != null)
                CurrentSettings.Direct3D10 = null;
        }

        /// <summary>
        /// Updates the device information.
        /// </summary>
        void UpdateDeviceInformation()
        {
            // TODO: Do this
        }

        /// <summary>
        /// Updates the device stats.
        /// </summary>
        void UpdateDeviceStats()
        {
            // TODO: Do this
        }

        /// <summary>
        /// Updates the frame stats.
        /// </summary>
        void UpdateFrameStats()
        {
            // TODO: Do this
        }

        /// <summary>
        /// Sets up the cursor.
        /// </summary>
        void SetupCursor()
        {
            // TODO: Do this
        }
    }
}
