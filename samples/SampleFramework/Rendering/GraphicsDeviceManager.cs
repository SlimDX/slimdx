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
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D10;
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
        bool doNotStoreBufferSize;
        bool renderingOccluded;

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
        /// Gets the current device settings.
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
        /// Gets the Direct3D9 device.
        /// </summary>
        /// <value>The Direct3D9 device.</value>
        public SlimDX.Direct3D9.Device Device9
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 device.
        /// </summary>
        /// <value>The Direct3D10 device.</value>
        public SlimDX.Direct3D10.Device Device10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 swap chain.
        /// </summary>
        /// <value>The Direct3D10 swap chain.</value>
        public SlimDX.DXGI.SwapChain SwapChain10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 render target.
        /// </summary>
        /// <value>The Direct3D10 render target.</value>
        public RenderTargetView RenderTarget10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 depth stencil view.
        /// </summary>
        /// <value>The Direct3D10 depth stencil view.</value>
        public DepthStencilView DepthStencilView10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 depth stencil surface.
        /// </summary>
        /// <value>The Direct3D10 depth stencil surface.</value>
        public Texture2D DepthStencil10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the Direct3D10 rasterizer state.
        /// </summary>
        /// <value>The Direct3D10 rasterizer state.</value>
        public RasterizerState RasterizerState10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the static frame statistics.
        /// </summary>
        /// <value>The static frame statistics.</value>
        public string DeviceStatistics
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the device information.
        /// </summary>
        /// <value>The device information.</value>
        public string DeviceInformation
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
            {
                // try to create a test device
                SlimDX.Direct3D10.Device device = new SlimDX.Direct3D10.Device(DeviceCreationFlags.None);
                device.Dispose();

                // create the factory
                Factory = new Factory();
            }
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
                CurrentSettings.BackBufferFormat = ConversionMethods.ToDirect3D9(CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format);
                CurrentSettings.DepthStencilFormat = ConversionMethods.ToDirect3D9(CurrentSettings.Direct3D10.DepthStencilFormat);
                CurrentSettings.DeviceType = ConversionMethods.ToDirect3D9(CurrentSettings.Direct3D10.DriverType);
                CurrentSettings.MultisampleQuality = CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality;
                CurrentSettings.MultisampleType = ConversionMethods.ToDirect3D9(CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Count);
                CurrentSettings.RefreshRate = (int)ConversionMethods.ToFloat(CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.RefreshRate);
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
        /// Ensures that the device is properly initialized and ready to render.
        /// </summary>
        /// <returns><c>true</c> if the device is in a valid state; otherwise, <c>false</c>.</returns>
        public bool EnsureDevice()
        {
            // make sure we have a device
            if (Device10 != null)
                return true;

            // if we have a D3D9 device, ensure that it is not lost
            if (Device9 != null && !deviceLost)
                return true;

            // otherwise, no good
            return false;
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
                        if (newSettings.Direct3D9 != null)
                        {
                            // clear out the old size information
                            newSettings.Direct3D9.PresentParameters.BackBufferWidth = 0;
                            newSettings.Direct3D9.PresentParameters.BackBufferHeight = 0;
                        }
                        if (newSettings.Direct3D10 != null)
                        {
                            // clear out the old size information
                            SwapChainDescription scd = newSettings.Direct3D10.SwapChainDescription;
                            ModeDescription md = scd.ModeDescription;
                            md.Width = 0;
                            md.Height = 0;
                            scd.ModeDescription = md;
                            newSettings.Direct3D10.SwapChainDescription = scd;
                        }

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
                    newSettings.Direct3D9.PresentParameters.BackBufferWidth = 0;
                    newSettings.Direct3D9.PresentParameters.BackBufferHeight = 0;
                    CreateDevice(newSettings);
                    newSettings.BackBufferWidth = newSettings.Direct3D9.PresentParameters.BackBufferWidth;
                    newSettings.BackBufferHeight = newSettings.Direct3D9.PresentParameters.BackBufferHeight;
                }
            }
            else
            {
                // update the window size
                bool fullscreen;
                Output output;
                SwapChain10.GetFullScreenState(out fullscreen, out output);
                ResizeDXGIBuffers(0, 0, fullscreen);
                game.Window.Show();
            }
        }

        /// <summary>
        /// Handles the ScreenChanged event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_ScreenChanged(object sender, EventArgs e)
        {
            // skip the check for various reasons
            if (CurrentSettings == null || (Device9 == null && Device10 == null) || !CurrentSettings.Windowed ||
                ignoreSizeChanges)
                return;

            // check for changes
            IntPtr windowMonitor = NativeMethods.MonitorFromWindow(game.Window.Handle, WindowConstants.MONITOR_DEFAULTTOPRIMARY);

            // get the new ordinals
            DeviceSettings newSettings = CurrentSettings.Clone();
            int adapterOrdinal = GetAdapterOrdinal(windowMonitor);
            if (adapterOrdinal == -1)
                return;
            if (newSettings.DeviceVersion == DeviceVersion.Direct3D9)
                newSettings.Direct3D9.AdapterOrdinal = adapterOrdinal;
            else
            {
                newSettings.Direct3D10.AdapterOrdinal = adapterOrdinal;
                newSettings.Direct3D10.OutputOrdinal = GetOutputOrdinal(game.Window.Screen);
                if (newSettings.Direct3D10.OutputOrdinal == -1)
                    return;
            }

            // change the device
            CreateDevice(newSettings);
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
                // present the frame
                SlimDX.DXGI.PresentFlags flags = SlimDX.DXGI.PresentFlags.None;
                if (renderingOccluded)
                    flags = SlimDX.DXGI.PresentFlags.Test;
                else
                    flags = CurrentSettings.Direct3D10.PresentFlags;
                Result result = SwapChain10.Present(CurrentSettings.Direct3D10.SyncInterval, flags);

                // check the result for errors or status updates
                // TODO: Uncomment the following lines
                //if (result == SlimDX.DXGI.ResultCode.Occluded)
                //    renderingOccluded = true;
                //else if (result == SlimDX.DXGI.ResultCode.DeviceReset)
                //    ResetDevice();
                //else
                //    renderingOccluded = false;
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
            try
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
                    // clear window associations
                    Factory.SetWindowAssociation(IntPtr.Zero, WindowAssociationFlags.None);

                    // create the device
                    Adapter adapter = null;
                    if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                        adapter = Factory.GetAdapter(CurrentSettings.Direct3D10.AdapterOrdinal);
                    Device10 = new SlimDX.Direct3D10.Device(adapter, CurrentSettings.Direct3D10.DriverType, CurrentSettings.Direct3D10.CreationFlags);

                    // create the swap chain
                    SwapChain10 = new SlimDX.DXGI.SwapChain(Factory, Device10, CurrentSettings.Direct3D10.SwapChainDescription);

                    // setup render target and views
                    SetupD3D10Views();
                }
            }
            catch (Exception e)
            {
                // wrap the exception in one more user-friendly
                throw new DeviceCreationException("Could not create graphics device.", e);
            }

            // update device stats
            UpdateDeviceStats();

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
                Result result = Device9.Reset(CurrentSettings.Direct3D9.PresentParameters);
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                    return result;
            }
            else
            {
                // make sure D3D9 is released
                ReleaseDevice9();

                // resize the render target, just in case the size has changed
                DeviceSettings newSettings = CurrentSettings.Clone();
                if (IsWindowed && SwapChain10.Description.IsWindowed)
                {
                    // set the size of the swap chain to be the size of the window
                    SwapChainDescription scd = newSettings.Direct3D10.SwapChainDescription;
                    ModeDescription md = scd.ModeDescription;
                    md.Width = game.Window.ClientSize.Width;
                    md.Height = game.Window.ClientSize.Height;
                }

                // check if the app is trying to switch full screen state
                if (SwapChain10.Description.IsWindowed != newSettings.Direct3D10.SwapChainDescription.IsWindowed)
                {
                    // set the fullscreen state
                    if (newSettings.Direct3D10.SwapChainDescription.IsWindowed)
                        SwapChain10.SetFullScreenState(false, null);
                    else
                    {
                        // change the state, and then change the resolution to match
                        doNotStoreBufferSize = true;
                        SwapChain10.SetFullScreenState(true, null);
                        doNotStoreBufferSize = false;
                        SwapChain10.ResizeTarget(newSettings.Direct3D10.SwapChainDescription.ModeDescription);
                    }
                }
                else
                {
                    // check if we need to resize the buffers
                    if (newSettings.Direct3D10.SwapChainDescription.ModeDescription.Width == SwapChain10.Description.ModeDescription.Width &&
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Height == SwapChain10.Description.ModeDescription.Height &&
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Format != SwapChain10.Description.ModeDescription.Format)
                        ResizeDXGIBuffers(0, 0, !newSettings.Direct3D10.SwapChainDescription.IsWindowed);
                    else if (newSettings.Direct3D10.SwapChainDescription.ModeDescription.Width != SwapChain10.Description.ModeDescription.Width ||
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Height != SwapChain10.Description.ModeDescription.Height)
                        SwapChain10.ResizeTarget(newSettings.Direct3D10.SwapChainDescription.ModeDescription);
                }
            }

            // update device stats
            UpdateDeviceStats();

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

            // release the old depth stencil stuff
            if (DepthStencil10 != null)
                DepthStencil10.Dispose();
            DepthStencil10 = null;
            if (DepthStencilView10 != null)
                DepthStencilView10.Dispose();
            DepthStencilView10 = null;

            // release the old render target view
            if (RenderTarget10 != null)
                RenderTarget10.Dispose();
            RenderTarget10 = null;

            // release the old rasterizer state
            if (RasterizerState10 != null)
                RasterizerState10.Dispose();
            RasterizerState10 = null;

            // release the swap chain
            if (SwapChain10 != null)
            {
                SwapChain10.SetFullScreenState(false, null);
                SwapChain10.Dispose();
            }
            SwapChain10 = null;

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
            // build up the device information
            StringBuilder builder = new StringBuilder();

            // check the device version
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // print out device description
                if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                    builder.Append("HAL");
                else if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Reference)
                    builder.Append("REF");
                else if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Software)
                    builder.Append("SW");

                // print out the vertex processing information
                if ((CurrentSettings.Direct3D9.CreationFlags & CreateFlags.HardwareVertexProcessing) != 0)
                    if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                        builder.Append(" (hw vp)");
                    else
                        builder.Append(" (simulated hw vp)");
                else if ((CurrentSettings.Direct3D9.CreationFlags & CreateFlags.MixedVertexProcessing) != 0)
                    if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                        builder.Append(" (mixed vp)");
                    else
                        builder.Append(" (simulated mixed vp)");
                else
                    builder.Append(" (sw vp)");

                // append the adapter description
                if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                {
                    // loop through each adapter until we find the right one
                    foreach (AdapterInfo9 adapterInfo in Enumeration9.Adapters)
                    {
                        // check for a match
                        if (adapterInfo.AdapterOrdinal == CurrentSettings.Direct3D9.AdapterOrdinal)
                        {
                            // found it
                            builder.AppendFormat(": {0}", adapterInfo.Description);
                            break;
                        }
                    }
                }
            }
            else
            {
                // print out device description
                if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                    builder.Append("HARDWARE");
                else if (CurrentSettings.Direct3D10.DriverType == DriverType.Reference)
                    builder.Append("REFERENCE");
                else if (CurrentSettings.Direct3D10.DriverType == DriverType.Software)
                    builder.Append("SOFTWARE");

                // append the adapter description
                if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                {
                    // loop through each adapter until we find the right one
                    foreach (AdapterInfo10 adapterInfo in Enumeration10.Adapters)
                    {
                        // check for a match
                        if (adapterInfo.AdapterOrdinal == CurrentSettings.Direct3D10.AdapterOrdinal)
                        {
                            // found it
                            builder.AppendFormat(": {0}", adapterInfo.Description);
                            break;
                        }
                    }
                }
            }

            // store the device information
            DeviceInformation = builder.ToString();
        }

        /// <summary>
        /// Updates the device stats.
        /// </summary>
        void UpdateDeviceStats()
        {
            // build up the static frame stats
            StringBuilder builder = new StringBuilder();

            // check the device version
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // initial information
                builder.Append("D3D9 Vsync ");

                // print out the vsync status
                if (CurrentSettings.Direct3D9.PresentParameters.PresentationInterval == PresentInterval.Immediate)
                    builder.Append("off");
                else
                    builder.Append("on");

                // print out the resolution
                builder.AppendFormat(" ({0}x{1}), ", CurrentSettings.Direct3D9.PresentParameters.BackBufferWidth, CurrentSettings.Direct3D9.PresentParameters.BackBufferHeight);

                // print out the back buffer and adapter format
                if (CurrentSettings.Direct3D9.AdapterFormat == CurrentSettings.Direct3D9.PresentParameters.BackBufferFormat)
                    builder.Append(Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.AdapterFormat));
                else
                    builder.AppendFormat("backbuf {0}, adapter {1}",
                        Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.AdapterFormat),
                        Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.PresentParameters.BackBufferFormat));

                // print out the depth / stencil format
                builder.AppendFormat(" ({0})", Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.PresentParameters.AutoDepthStencilFormat));

                // print out the multisample state
                if (CurrentSettings.Direct3D9.PresentParameters.Multisample == MultisampleType.NonMaskable)
                    builder.Append(" (Nonmaskable Multisample)");
                else if (CurrentSettings.Direct3D9.PresentParameters.Multisample != MultisampleType.None)
                    builder.AppendFormat(" ({0}x Multisample)", (int)CurrentSettings.Direct3D9.PresentParameters.Multisample);
            }
            else
            {
                // initial information
                builder.Append("D3D10 Vsync ");

                // print out the vsync status
                if (CurrentSettings.Direct3D10.SyncInterval == 0)
                    builder.Append("off");
                else
                    builder.Append("on");

                // print out the resolution
                builder.AppendFormat(" ({0}x{1}), ", CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Width, CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Height);

                // print out the back buffer format
                builder.Append(Enum.GetName(typeof(SlimDX.DXGI.Format), CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format));

                // print out the multisample state
                builder.AppendFormat(" (MS{0}, Q{1})", CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Count,
                    CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality);
            }

            // store the static frame stats
            DeviceStatistics = builder.ToString();
        }

        /// <summary>
        /// Resizes the DXGI buffers.
        /// </summary>
        void ResizeDXGIBuffers(int width, int height, bool fullscreen)
        {
            // set the windowed state
            SwapChainDescription scd = CurrentSettings.Direct3D10.SwapChainDescription;
            scd.IsWindowed = !fullscreen;
            CurrentSettings.Direct3D10.SwapChainDescription = scd;

            // release the old depth stencil stuff
            DepthStencil10.Dispose();
            DepthStencil10 = null;
            DepthStencilView10.Dispose();
            DepthStencilView10 = null;

            // release the old render target view
            RenderTarget10.Dispose();
            RenderTarget10 = null;

            // release the old rasterizer state
            RasterizerState10.Dispose();
            RasterizerState10 = null;

            // figure out which flags we want
            SwapChainFlags flag = SwapChainFlags.None;
            if (fullscreen)
                flag = SwapChainFlags.AllowModeSwitch;

            // resize the buffers
            SwapChain10.ResizeBuffers(CurrentSettings.Direct3D10.SwapChainDescription.BufferCount, width, height,
                CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format, flag);

            // check if we should store the size
            if (!doNotStoreBufferSize)
            {
                // store the size
                ModeDescription md = scd.ModeDescription;
                md.Width = game.Window.ClientSize.Width;
                md.Height = game.Window.ClientSize.Height;
                scd.ModeDescription = md;
                CurrentSettings.Direct3D10.SwapChainDescription = scd;
            }

            // set up the views
            SetupD3D10Views();
        }

        /// <summary>
        /// Sets up the Direct3D10 render target and viewport.
        /// </summary>
        void SetupD3D10Views()
        {
            // grab the back buffer and description
            Texture2D backBuffer = SwapChain10.GetBuffer<Texture2D>(0);

            // set up the viewport to match the back buffer
            Viewport viewport = new Viewport();
            viewport.Width = backBuffer.Description.Width;
            viewport.Height = backBuffer.Description.Height;
            viewport.MinZ = 0;
            viewport.MaxZ = 1;
            viewport.X = 0;
            viewport.Y = 0;
            Device10.Rasterizer.SetViewports(viewport);

            // create the render target view
            RenderTarget10 = new RenderTargetView(Device10, backBuffer);

            // set up the depth / stencil surface
            Texture2DDescription desc = new Texture2DDescription();
            desc.Width = backBuffer.Description.Width;
            desc.Height = backBuffer.Description.Height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = CurrentSettings.Direct3D10.DepthStencilFormat;
            desc.SampleDescription = CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription;
            desc.Usage = ResourceUsage.Default;
            desc.BindFlags = BindFlags.DepthStencil;
            desc.CpuAccessFlags = CpuAccessFlags.None;

            // create the surface and view
            DepthStencilViewDescription dsvd = new DepthStencilViewDescription();
            dsvd.Format = desc.Format;
            if (desc.SampleDescription.Count > 1)
                dsvd.Dimension = DepthStencilViewDimension.Texture2DMultisampled;
            else
                dsvd.Dimension = DepthStencilViewDimension.Texture2D;
            DepthStencil10 = new Texture2D(Device10, desc);
            DepthStencilView10 = new DepthStencilView(Device10, DepthStencil10, dsvd);

            // create a default rasterizer state
            RasterizerStateDescription rsDesc = new RasterizerStateDescription();
            rsDesc.FillMode = SlimDX.Direct3D10.FillMode.Solid;
            rsDesc.CullMode = CullMode.Back;
            if (desc.SampleDescription.Count > 1)
                rsDesc.IsMultisampleEnabled = true;
            else
                rsDesc.IsMultisampleEnabled = false;

            // create the rasterizer state
            RasterizerState10 = RasterizerState.FromDescription(Device10, rsDesc);
            Device10.Rasterizer.State = RasterizerState10;

            // set the render targets
            Device10.OutputMerger.SetTargets(DepthStencilView10, RenderTarget10);

            // clean up the back buffer
            backBuffer.Dispose();
        }

        /// <summary>
        /// Gets the adapter ordinal from the given screen.
        /// </summary>
        /// <param name="screen">The screen.</param>
        /// <returns>The ordinal of the adapter that renders to the given screen.</returns>
        int GetAdapterOrdinal(IntPtr screen)
        {
            // check the current device status
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // loop through the adapters until we find the right one
                AdapterInfo9 adapter = null;
                foreach (AdapterInfo9 a in Enumeration9.Adapters)
                {
                    // check for a matching ordinal
                    if (Direct3D.GetAdapterMonitor(a.AdapterOrdinal) == screen)
                    {
                        // found a match
                        adapter = a;
                        break;
                    }
                }

                // return the found adapter
                if (adapter != null)
                    return adapter.AdapterOrdinal;
            }
            else
            {
                // loop through the adapters until we find the right one
                AdapterInfo10 adapter = null;
                foreach (AdapterInfo10 a in Enumeration10.Adapters)
                {
                    // loop through the outputs to look for a name
                    foreach (OutputInfo10 o in a.Outputs)
                    {
                        // check for a match
                        if (o.OutputDescription.Name == game.Window.Screen.DeviceName)
                        {
                            // found a match
                            adapter = a;
                            break;
                        }
                    }
                }

                // return the found adapter
                if (adapter != null)
                    return adapter.AdapterOrdinal;
            }

            // otherwise, not found
            return -1;
        }

        /// <summary>
        /// Gets the output ordinal from the given screen.
        /// </summary>
        /// <param name="screen">The screen.</param>
        /// <returns>The ordinal of the output that renders to the given screen.</returns>
        static int GetOutputOrdinal(Screen screen)
        {
            // find the right monitor
            foreach (AdapterInfo10 adapter in Enumeration10.Adapters)
            {
                // loop through each output
                foreach (OutputInfo10 output in adapter.Outputs)
                {
                    // check for a match
                    if (output.OutputDescription.Name == screen.DeviceName)
                        return output.OutputOrdinal;
                }
            }

            // otherwise, we couldn't find it
            return -1;
        }
    }
}
