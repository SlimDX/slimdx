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
        Game game;
        bool ignoreSizeChanges;
        bool deviceLost;
        bool doNotStoreBufferSize;
        bool renderingOccluded;

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
        /// Gets or sets the Direct3D9 object.
        /// </summary>
        /// <value>The Direct3D9 object.</value>
        internal static Direct3D Direct3D9Object
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
        /// Gets the width of the screen.
        /// </summary>
        /// <value>The width of the screen.</value>
        public int ScreenWidth
        {
            get { return CurrentSettings.BackBufferWidth; }
        }

        /// <summary>
        /// Gets the height of the screen.
        /// </summary>
        /// <value>The height of the screen.</value>
        public int ScreenHeight
        {
            get { return CurrentSettings.BackBufferHeight; }
        }

        /// <summary>
        /// Gets the size of the screen.
        /// </summary>
        /// <value>The size of the screen.</value>
        public Size ScreenSize
        {
            get { return new Size(CurrentSettings.BackBufferWidth, CurrentSettings.BackBufferHeight); }
        }

        /// <summary>
        /// Gets the manager for Direct3D9-specific tasks.
        /// </summary>
        /// <value>The Direct3D9 manager.</value>
        public Direct3D9Manager Direct3D9
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the manager for Direct3D10-specific tasks.
        /// </summary>
        /// <value>The Direct3D10 manager.</value>
        public Direct3D10Manager Direct3D10
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
            if (game == null)
                throw new ArgumentNullException("game");

            this.game = game;

            game.Window.ScreenChanged += Window_ScreenChanged;
            game.Window.UserResized += Window_UserResized;

            game.FrameStart += game_FrameStart;
            game.FrameEnd += game_FrameEnd;

            Direct3D9 = new Direct3D9Manager(this);
            Direct3D10 = new Direct3D10Manager(this);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Changes the device.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <param name="minimumSettings">The minimum settings.</param>
        /// <exception cref="ArgumentNullException">Thrown when the <paramref name="settings"/> is <c>null</c>.</exception>
        /// <exception cref="NoCompatibleDevicesException">Thrown when the framework cannot find a suitable graphics device.</exception>
        /// <exception cref="DeviceCreationException">Thrown when device creation fails.</exception>
        public void ChangeDevice(DeviceSettings settings, DeviceSettings minimumSettings)
        {
            if (settings == null)
                throw new ArgumentNullException("settings");

            Enumeration9.MinimumSettings = minimumSettings;
            Enumeration10.MinimumSettings = minimumSettings;

            DeviceSettings validSettings = DeviceSettings.FindValidSettings(settings);

            if (validSettings.DeviceVersion == DeviceVersion.Direct3D9)
                validSettings.Direct3D9.PresentParameters.DeviceWindowHandle = game.Window.Handle;
            else
            {
                SwapChainDescription scd = validSettings.Direct3D10.SwapChainDescription;
                scd.OutputHandle = game.Window.Handle;
                validSettings.Direct3D10.SwapChainDescription = scd;
            }

            CreateDevice(validSettings);
        }

        /// <summary>
        /// Changes the device.
        /// </summary>
        /// <param name="deviceVersion">The device version.</param>
        /// <param name="windowed">if set to <c>true</c>, the application will run in windowed mode instead of full screen.</param>
        /// <param name="desiredWidth">Desired width of the window.</param>
        /// <param name="desiredHeight">Desired height of the window.</param>
        /// <exception cref="NoCompatibleDevicesException">Thrown when the framework cannot find a suitable graphics device.</exception>
        /// <exception cref="DeviceCreationException">Thrown when device creation fails.</exception>
        public void ChangeDevice(DeviceVersion deviceVersion, bool windowed, int desiredWidth, int desiredHeight)
        {
            DeviceSettings desiredSettings = new DeviceSettings();
            desiredSettings.DeviceVersion = deviceVersion;
            desiredSettings.Windowed = windowed;
            desiredSettings.BackBufferWidth = desiredWidth;
            desiredSettings.BackBufferHeight = desiredHeight;

            ChangeDevice(desiredSettings, null);
        }

        /// <summary>
        /// Changes the device.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <exception cref="ArgumentNullException">Thrown when the <paramref name="settings"/> is <c>null</c>.</exception>
        /// <exception cref="NoCompatibleDevicesException">Thrown when the framework cannot find a suitable graphics device.</exception>
        /// <exception cref="DeviceCreationException">Thrown when device creation fails.</exception>
        public void ChangeDevice(DeviceSettings settings)
        {
            ChangeDevice(settings, null);
        }

        /// <summary>
        /// Toggles between full screen and windowed mode.
        /// </summary>
        /// <exception cref="InvalidOperationException">Thrown when no valid device has been created.</exception>
        /// <exception cref="NoCompatibleDevicesException">Thrown when the framework cannot find a suitable graphics device.</exception>
        /// <exception cref="DeviceCreationException">Thrown when device creation fails.</exception>
        public void ToggleFullScreen()
        {
            if (!EnsureDevice())
                throw new InvalidOperationException("No valid device.");

            DeviceSettings newSettings = CurrentSettings.Clone();

            newSettings.Windowed = !newSettings.Windowed;

            int width = newSettings.Windowed ? windowedWindowWidth : fullscreenWindowWidth;
            int height = newSettings.Windowed ? windowedWindowHeight : fullscreenWindowHeight;

            newSettings.BackBufferWidth = width;
            newSettings.BackBufferHeight = height;

            ChangeDevice(newSettings);
        }

        /// <summary>
        /// Ensures that the device is properly initialized and ready to render.
        /// </summary>
        /// <returns><c>true</c> if the device is in a valid state; otherwise, <c>false</c>.</returns>
        public bool EnsureDevice()
        {
            if (Direct3D10.Device != null)
                return true;

            if (Direct3D9.Device != null && !deviceLost)
                return true;

            return false;
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
                ReleaseDevice();
        }

        void CreateDevice(DeviceSettings settings)
        {
            DeviceSettings oldSettings = CurrentSettings;
            CurrentSettings = settings;

            ignoreSizeChanges = true;

            bool keepCurrentWindowSize = false;
            if (settings.BackBufferWidth == 0 && settings.BackBufferHeight == 0)
                keepCurrentWindowSize = true;

            // handle the window state in Direct3D9 (it will be handled for us in DXGI)
            if (settings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                // check if we are going to windowed or fullscreen mode
                if (settings.Windowed)
                {
                    if (oldSettings != null && !oldSettings.Windowed)
                        NativeMethods.SetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE, (uint)windowedStyle);
                }
                else
                {
                    if (oldSettings == null || oldSettings.Windowed)
                    {
                        savedTopmost = game.Window.TopMost;
                        long style = NativeMethods.GetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE);
                        style &= ~WindowConstants.WS_MAXIMIZE & ~WindowConstants.WS_MINIMIZE;
                        windowedStyle = style;

                        windowedPlacement = new WINDOWPLACEMENT();
                        windowedPlacement.length = WINDOWPLACEMENT.Length;
                        NativeMethods.GetWindowPlacement(game.Window.Handle, ref windowedPlacement);
                    }

                    // hide the window until we are done messing with it
                    game.Window.Hide();
                    NativeMethods.SetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE, (uint)(WindowConstants.WS_POPUP | WindowConstants.WS_SYSMENU));

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

            if (settings.Windowed)
            {
                if (oldSettings != null && !oldSettings.Windowed)
                {
                    fullscreenWindowWidth = oldSettings.BackBufferWidth;
                    fullscreenWindowHeight = oldSettings.BackBufferHeight;
                }
            }
            else
            {
                if (oldSettings != null && oldSettings.Windowed)
                {
                    windowedWindowWidth = oldSettings.BackBufferWidth;
                    windowedWindowHeight = oldSettings.BackBufferHeight;
                }
            }

            // check if the device can be reset, or if we need to completely recreate it
            Result result = SlimDX.Direct3D9.ResultCode.Success;
            bool canReset = CanDeviceBeReset(oldSettings, settings);
            if (canReset)
                result = ResetDevice();

            if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                deviceLost = true;
            else if (!canReset || result.IsFailure)
            {
                if (oldSettings != null)
                    ReleaseDevice();

                InitializeDevice();
            }

            UpdateDeviceInformation();

            // check if we changed from fullscreen to windowed mode
            if (settings.DeviceVersion == DeviceVersion.Direct3D9 && oldSettings != null && !oldSettings.Windowed && settings.Windowed)
            {
                NativeMethods.SetWindowPlacement(game.Window.Handle, ref windowedPlacement);
                game.Window.TopMost = savedTopmost;
            }

            // check if we need to resize
            if (settings.Windowed && !keepCurrentWindowSize)
            {
                int width;
                int height;
                if (NativeMethods.IsIconic(game.Window.Handle))
                {
                    WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                    placement.length = WINDOWPLACEMENT.Length;
                    NativeMethods.GetWindowPlacement(game.Window.Handle, ref placement);

                    // check if we are being restored
                    if ((placement.flags & WindowConstants.WPF_RESTORETOMAXIMIZED) != 0 && placement.showCmd == WindowConstants.SW_SHOWMINIMIZED)
                    {
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);

                        Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);

                        width = rect.Width;
                        height = rect.Height;
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_MINIMIZE);
                    }
                    else
                    {
                        NativeRectangle frame = new NativeRectangle();
                        NativeMethods.AdjustWindowRect(ref frame, (uint)windowedStyle, false);
                        int frameWidth = frame.right - frame.left;
                        int frameHeight = frame.bottom - frame.top;

                        width = placement.rcNormalPosition.right - placement.rcNormalPosition.left - frameWidth;
                        height = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top - frameHeight;
                    }
                }
                else
                {
                    Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);
                    width = rect.Width;
                    height = rect.Height;
                }

                // check if we have a different desired size
                if (width != settings.BackBufferWidth ||
                    height != settings.BackBufferHeight)
                {
                    if (NativeMethods.IsIconic(game.Window.Handle))
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);
                    if (NativeMethods.IsZoomed(game.Window.Handle))
                        NativeMethods.ShowWindow(game.Window.Handle, WindowConstants.SW_RESTORE);

                    NativeRectangle rect = new NativeRectangle();
                    rect.right = settings.BackBufferWidth;
                    rect.bottom = settings.BackBufferHeight;
                    NativeMethods.AdjustWindowRect(ref rect,
                        NativeMethods.GetWindowLong(game.Window.Handle, WindowConstants.GWL_STYLE), false);

                    NativeMethods.SetWindowPos(game.Window.Handle, IntPtr.Zero, 0, 0, rect.right - rect.left,
                        rect.bottom - rect.top, WindowConstants.SWP_NOZORDER | WindowConstants.SWP_NOMOVE);

                    Rectangle r = NativeMethods.GetClientRectangle(game.Window.Handle);
                    int clientWidth = r.Width;
                    int clientHeight = r.Height;

                    // check if the size was modified by Windows
                    if (clientWidth != settings.BackBufferWidth ||
                        clientHeight != settings.BackBufferHeight)
                    {
                        DeviceSettings newSettings = CurrentSettings.Clone();
                        newSettings.BackBufferWidth = 0;
                        newSettings.BackBufferHeight = 0;
                        if (newSettings.Direct3D9 != null)
                        {
                            newSettings.Direct3D9.PresentParameters.BackBufferWidth = 0;
                            newSettings.Direct3D9.PresentParameters.BackBufferHeight = 0;
                        }
                        if (newSettings.Direct3D10 != null)
                        {
                            SwapChainDescription scd = newSettings.Direct3D10.SwapChainDescription;
                            ModeDescription md = scd.ModeDescription;
                            md.Width = 0;
                            md.Height = 0;
                            scd.ModeDescription = md;
                            newSettings.Direct3D10.SwapChainDescription = scd;
                        }

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

            ignoreSizeChanges = false;
        }

        void Window_UserResized(object sender, EventArgs e)
        {
            if (ignoreSizeChanges || !EnsureDevice() ||
                (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9 && !IsWindowed))
                return;

            DeviceSettings newSettings = CurrentSettings.Clone();

            if (newSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                Rectangle rect = NativeMethods.GetClientRectangle(game.Window.Handle);
                if (rect.Width != newSettings.BackBufferWidth || rect.Height != newSettings.BackBufferHeight)
                {
                    newSettings.BackBufferWidth = 0;
                    newSettings.BackBufferHeight = 0;
                    newSettings.Direct3D9.PresentParameters.BackBufferWidth = 0;
                    newSettings.Direct3D9.PresentParameters.BackBufferHeight = 0;
                    CreateDevice(newSettings);
                }
            }
            else
            {
                bool fullscreen;
                Output output;
                Direct3D10.SwapChain.GetFullScreenState(out fullscreen, out output);
                ResizeDXGIBuffers(0, 0, fullscreen);
                game.Window.Show();
            }
        }

        void Window_ScreenChanged(object sender, EventArgs e)
        {
            if (!EnsureDevice() || !CurrentSettings.Windowed || ignoreSizeChanges)
                return;

            IntPtr windowMonitor = NativeMethods.MonitorFromWindow(game.Window.Handle, WindowConstants.MONITOR_DEFAULTTOPRIMARY);

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

            CreateDevice(newSettings);
        }

        void game_FrameEnd(object sender, EventArgs e)
        {
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                Result result = Direct3D9.Device.Present();
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                    deviceLost = true;
            }
            else
            {
                SlimDX.DXGI.PresentFlags flags = SlimDX.DXGI.PresentFlags.None;
                if (renderingOccluded)
                    flags = SlimDX.DXGI.PresentFlags.Test;
                else
                    flags = CurrentSettings.Direct3D10.PresentFlags;
                Result result = Direct3D10.SwapChain.Present(CurrentSettings.Direct3D10.SyncInterval, flags);

                if (result == SlimDX.DXGI.ResultCode.Occluded)
                    renderingOccluded = true;
                else if (result == SlimDX.DXGI.ResultCode.DeviceReset)
                    ResetDevice();
                else
                    renderingOccluded = false;
            }
        }

        void game_FrameStart(object sender, CancelEventArgs e)
        {
            if (Direct3D9.Device == null && Direct3D10.Device == null)
            {
                e.Cancel = true;
                return;
            }

            if (!game.IsActive || deviceLost)
                Thread.Sleep(50);

            if (deviceLost)
            {
                Result result = Direct3D9.Device.TestCooperativeLevel();
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                {
                    e.Cancel = true;
                    return;
                }

                // if we are windowed, check the adapter format to see if the user
                // changed the desktop format, causing a lost device
                if (IsWindowed)
                {
                    DisplayMode displayMode = GraphicsDeviceManager.Direct3D9Object.GetAdapterDisplayMode(CurrentSettings.Direct3D9.AdapterOrdinal);
                    if (CurrentSettings.Direct3D9.AdapterFormat != displayMode.Format)
                    {
                        DeviceSettings newSettings = CurrentSettings.Clone();
                        ChangeDevice(newSettings);
                        e.Cancel = true;
                        return;
                    }
                }

                result = ResetDevice();
                if (result.IsFailure)
                {
                    e.Cancel = true;
                    return;
                }
            }

            deviceLost = false;
        }

        bool CanDeviceBeReset(DeviceSettings oldSettings, DeviceSettings newSettings)
        {
            if (oldSettings == null || oldSettings.DeviceVersion != newSettings.DeviceVersion)
                return false;

            if (oldSettings.DeviceVersion == DeviceVersion.Direct3D9)
                return Direct3D9.Device != null &&
                    oldSettings.Direct3D9.AdapterOrdinal == newSettings.Direct3D9.AdapterOrdinal &&
                    oldSettings.Direct3D9.DeviceType == newSettings.Direct3D9.DeviceType &&
                    oldSettings.Direct3D9.CreationFlags == newSettings.Direct3D9.CreationFlags;
            else
                return Direct3D10.Device != null &&
                    oldSettings.Direct3D10.AdapterOrdinal == newSettings.Direct3D10.AdapterOrdinal &&
                    oldSettings.Direct3D10.DriverType == newSettings.Direct3D10.DriverType &&
                    oldSettings.Direct3D10.CreationFlags == newSettings.Direct3D10.CreationFlags &&
                    oldSettings.Direct3D10.SwapChainDescription.SampleDescription.Count == newSettings.Direct3D10.SwapChainDescription.SampleDescription.Count &&
                    oldSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality == newSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality;
        }

        void InitializeDevice()
        {
            try
            {
                if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
                {
                    EnsureD3D9();

                    Direct3D9.Device = new SlimDX.Direct3D9.Device(Direct3D9Object, CurrentSettings.Direct3D9.AdapterOrdinal,
                        CurrentSettings.Direct3D9.DeviceType, game.Window.Handle,
                        CurrentSettings.Direct3D9.CreationFlags, CurrentSettings.Direct3D9.PresentParameters);

                    if (Result.Last == SlimDX.Direct3D9.ResultCode.DeviceLost)
                    {
                        deviceLost = true;
                        return;
                    }
                }
                else
                {
                    EnsureD3D10();

                    Factory.SetWindowAssociation(IntPtr.Zero, WindowAssociationFlags.None);

                    Adapter adapter = null;
                    if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                        adapter = (Adapter)Factory.GetAdapter(CurrentSettings.Direct3D10.AdapterOrdinal);
                    Direct3D10.Device = new SlimDX.Direct3D10.Device(adapter, CurrentSettings.Direct3D10.DriverType, CurrentSettings.Direct3D10.CreationFlags);

                    if (adapter != null)
                        adapter.Dispose();

                    Direct3D10.SwapChain = new SlimDX.DXGI.SwapChain(Factory, Direct3D10.Device, CurrentSettings.Direct3D10.SwapChainDescription);

                    SetupD3D10Views();
                }
            }
            catch (Exception e)
            {
                throw new DeviceCreationException("Could not create graphics device.", e);
            }

            PropogateSettings();

            UpdateDeviceStats();

            game.Initialize();
            game.LoadContent();
        }

        Result ResetDevice()
        {
            game.UnloadContent();

            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                ReleaseDevice10();

                Result result = Direct3D9.Device.Reset(CurrentSettings.Direct3D9.PresentParameters);
                if (result == SlimDX.Direct3D9.ResultCode.DeviceLost)
                    return result;
            }
            else
            {
                ReleaseDevice9();

                DeviceSettings newSettings = CurrentSettings.Clone();
                if (IsWindowed && Direct3D10.SwapChain.Description.IsWindowed)
                {
                    SwapChainDescription scd = newSettings.Direct3D10.SwapChainDescription;
                    ModeDescription md = scd.ModeDescription;
                    md.Width = game.Window.ClientSize.Width;
                    md.Height = game.Window.ClientSize.Height;
                }

                if (Direct3D10.SwapChain.Description.IsWindowed != newSettings.Direct3D10.SwapChainDescription.IsWindowed)
                {
                    if (newSettings.Direct3D10.SwapChainDescription.IsWindowed)
                        Direct3D10.SwapChain.SetFullScreenState(false, null);
                    else
                    {
                        doNotStoreBufferSize = true;
                        Direct3D10.SwapChain.SetFullScreenState(true, null);
                        doNotStoreBufferSize = false;
                        Direct3D10.SwapChain.ResizeTarget(newSettings.Direct3D10.SwapChainDescription.ModeDescription);
                    }
                }
                else
                {
                    if (newSettings.Direct3D10.SwapChainDescription.ModeDescription.Width == Direct3D10.SwapChain.Description.ModeDescription.Width &&
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Height == Direct3D10.SwapChain.Description.ModeDescription.Height &&
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Format != Direct3D10.SwapChain.Description.ModeDescription.Format)
                        ResizeDXGIBuffers(0, 0, !newSettings.Direct3D10.SwapChainDescription.IsWindowed);
                    else if (newSettings.Direct3D10.SwapChainDescription.ModeDescription.Width != Direct3D10.SwapChain.Description.ModeDescription.Width ||
                        newSettings.Direct3D10.SwapChainDescription.ModeDescription.Height != Direct3D10.SwapChain.Description.ModeDescription.Height)
                        Direct3D10.SwapChain.ResizeTarget(newSettings.Direct3D10.SwapChainDescription.ModeDescription);
                }
            }

            PropogateSettings();
            UpdateDeviceStats();
            game.LoadContent();

            return Result.Last;
        }

        void ReleaseDevice()
        {
            ReleaseDevice9();
            ReleaseDevice10();
        }

        void ReleaseDevice9()
        {
            if (Direct3D9.Device == null)
                return;

            if (game != null)
            {
                game.UnloadContent();
                game.Dispose(true);
            }

            Direct3D9.Device.Dispose();
            Direct3D9Object.Dispose();

            Direct3D9Object = null;
            Direct3D9.Device = null;
        }

        void ReleaseDevice10()
        {
            if (Direct3D10.Device == null)
                return;

            if (game != null)
            {
                game.UnloadContent();
                game.Dispose(true);
            }

            Direct3D10.Device.ClearState();

            if (Direct3D10.DepthStencil != null)
                Direct3D10.DepthStencil.Dispose();
            Direct3D10.DepthStencil = null;
            if (Direct3D10.DepthStencilView != null)
                Direct3D10.DepthStencilView.Dispose();
            Direct3D10.DepthStencilView = null;

            if (Direct3D10.RenderTarget != null)
                Direct3D10.RenderTarget.Dispose();
            Direct3D10.RenderTarget = null;

            if (Direct3D10.RasterizerState != null)
                Direct3D10.RasterizerState.Dispose();
            Direct3D10.RasterizerState = null;

            if (Direct3D10.SwapChain != null)
            {
                Direct3D10.SwapChain.SetFullScreenState(false, null);
                Direct3D10.SwapChain.Dispose();
            }
            Direct3D10.SwapChain = null;

            Direct3D10.Device.Dispose();
            Factory.Dispose();

            Direct3D10.Device = null;
            Factory = null;
        }

        void PropogateSettings()
        {
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
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

        void UpdateDeviceInformation()
        {
            StringBuilder builder = new StringBuilder();

            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                    builder.Append("HAL");
                else if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Reference)
                    builder.Append("REF");
                else if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Software)
                    builder.Append("SW");

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

                if (CurrentSettings.Direct3D9.DeviceType == DeviceType.Hardware)
                {
                    // loop through each adapter until we find the right one
                    foreach (AdapterInfo9 adapterInfo in Enumeration9.Adapters)
                    {
                        if (adapterInfo.AdapterOrdinal == CurrentSettings.Direct3D9.AdapterOrdinal)
                        {
                            builder.AppendFormat(": {0}", adapterInfo.Description);
                            break;
                        }
                    }
                }
            }
            else
            {
                if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                    builder.Append("HARDWARE");
                else if (CurrentSettings.Direct3D10.DriverType == DriverType.Reference)
                    builder.Append("REFERENCE");
                else if (CurrentSettings.Direct3D10.DriverType == DriverType.Software)
                    builder.Append("SOFTWARE");

                if (CurrentSettings.Direct3D10.DriverType == DriverType.Hardware)
                {
                    foreach (AdapterInfo10 adapterInfo in Enumeration10.Adapters)
                    {
                        if (adapterInfo.AdapterOrdinal == CurrentSettings.Direct3D10.AdapterOrdinal)
                        {
                            builder.AppendFormat(": {0}", adapterInfo.Description);
                            break;
                        }
                    }
                }
            }

            DeviceInformation = builder.ToString();
        }

        void UpdateDeviceStats()
        {
            StringBuilder builder = new StringBuilder();

            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                builder.Append("D3D9 Vsync ");

                if (CurrentSettings.Direct3D9.PresentParameters.PresentationInterval == PresentInterval.Immediate)
                    builder.Append("off");
                else
                    builder.Append("on");

                builder.AppendFormat(" ({0}x{1}), ", CurrentSettings.Direct3D9.PresentParameters.BackBufferWidth, CurrentSettings.Direct3D9.PresentParameters.BackBufferHeight);

                if (CurrentSettings.Direct3D9.AdapterFormat == CurrentSettings.Direct3D9.PresentParameters.BackBufferFormat)
                    builder.Append(Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.AdapterFormat));
                else
                    builder.AppendFormat("backbuf {0}, adapter {1}",
                        Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.AdapterFormat),
                        Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.PresentParameters.BackBufferFormat));

                builder.AppendFormat(" ({0})", Enum.GetName(typeof(SlimDX.Direct3D9.Format), CurrentSettings.Direct3D9.PresentParameters.AutoDepthStencilFormat));

                if (CurrentSettings.Direct3D9.PresentParameters.Multisample == MultisampleType.NonMaskable)
                    builder.Append(" (Nonmaskable Multisample)");
                else if (CurrentSettings.Direct3D9.PresentParameters.Multisample != MultisampleType.None)
                    builder.AppendFormat(" ({0}x Multisample)", (int)CurrentSettings.Direct3D9.PresentParameters.Multisample);
            }
            else
            {
                builder.Append("D3D10 Vsync ");

                if (CurrentSettings.Direct3D10.SyncInterval == 0)
                    builder.Append("off");
                else
                    builder.Append("on");

                builder.AppendFormat(" ({0}x{1}), ", CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Width, CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Height);
                builder.Append(Enum.GetName(typeof(SlimDX.DXGI.Format), CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format));
                builder.AppendFormat(" (MS{0}, Q{1})", CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Count,
                    CurrentSettings.Direct3D10.SwapChainDescription.SampleDescription.Quality);
            }

            DeviceStatistics = builder.ToString();
        }

        void ResizeDXGIBuffers(int width, int height, bool fullscreen)
        {
            SwapChainDescription scd = CurrentSettings.Direct3D10.SwapChainDescription;
            scd.IsWindowed = !fullscreen;
            CurrentSettings.Direct3D10.SwapChainDescription = scd;

            if (Direct3D10.DepthStencil != null)
            {
                Direct3D10.DepthStencil.Dispose();
                Direct3D10.DepthStencil = null;
                Direct3D10.DepthStencilView.Dispose();
                Direct3D10.DepthStencilView = null;

                Direct3D10.RasterizerState.Dispose();
                Direct3D10.RasterizerState = null;
            }

            Direct3D10.RenderTarget.Dispose();
            Direct3D10.RenderTarget = null;

            SwapChainFlags flag = SwapChainFlags.None;
            if (fullscreen)
                flag = SwapChainFlags.AllowModeSwitch;

            Direct3D10.SwapChain.ResizeBuffers(CurrentSettings.Direct3D10.SwapChainDescription.BufferCount, width, height,
                CurrentSettings.Direct3D10.SwapChainDescription.ModeDescription.Format, flag);

            if (!doNotStoreBufferSize)
            {
                ModeDescription md = scd.ModeDescription;
                md.Width = game.Window.ClientSize.Width;
                md.Height = game.Window.ClientSize.Height;
                scd.ModeDescription = md;
                CurrentSettings.Direct3D10.SwapChainDescription = scd;
            }

            SetupD3D10Views();
        }

        void SetupD3D10Views()
        {
            Texture2D backBuffer = Texture2D.FromSwapChain<Texture2D>(Direct3D10.SwapChain, 0);

            SlimDX.Direct3D10.Viewport viewport = new SlimDX.Direct3D10.Viewport();
            viewport.Width = backBuffer.Description.Width;
            viewport.Height = backBuffer.Description.Height;
            viewport.MinZ = 0;
            viewport.MaxZ = 1;
            viewport.X = 0;
            viewport.Y = 0;
            Direct3D10.Device.Rasterizer.SetViewports(viewport);

            Direct3D10.RenderTarget = new RenderTargetView(Direct3D10.Device, backBuffer);

            if (CurrentSettings.Direct3D10.DepthStencilFormat != SlimDX.DXGI.Format.Unknown)
            {
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
                desc.OptionFlags = ResourceOptionFlags.None;

                DepthStencilViewDescription dsvd = new DepthStencilViewDescription();
                dsvd.Format = desc.Format;
                if (desc.SampleDescription.Count > 1)
                    dsvd.Dimension = DepthStencilViewDimension.Texture2DMultisampled;
                else
                    dsvd.Dimension = DepthStencilViewDimension.Texture2D;
                Direct3D10.DepthStencil = new Texture2D(Direct3D10.Device, desc);
                Direct3D10.DepthStencilView = new DepthStencilView(Direct3D10.Device, Direct3D10.DepthStencil, dsvd);

                RasterizerStateDescription rsDesc = new RasterizerStateDescription();
                rsDesc.FillMode = SlimDX.Direct3D10.FillMode.Solid;
                rsDesc.CullMode = CullMode.Back;
                rsDesc.IsDepthClipEnabled = true;
                if (desc.SampleDescription.Count > 1)
                    rsDesc.IsMultisampleEnabled = true;
                else
                    rsDesc.IsMultisampleEnabled = false;

                Direct3D10.RasterizerState = RasterizerState.FromDescription(Direct3D10.Device, rsDesc);
                Direct3D10.Device.Rasterizer.State = Direct3D10.RasterizerState;
            }

            Direct3D10.Device.OutputMerger.SetTargets(Direct3D10.DepthStencilView, Direct3D10.RenderTarget);
            backBuffer.Dispose();
        }

        int GetAdapterOrdinal(IntPtr screen)
        {
            if (CurrentSettings.DeviceVersion == DeviceVersion.Direct3D9)
            {
                AdapterInfo9 adapter = null;
                foreach (AdapterInfo9 a in Enumeration9.Adapters)
                {
                    if (Direct3D9Object.GetAdapterMonitor(a.AdapterOrdinal) == screen)
                    {
                        adapter = a;
                        break;
                    }
                }

                if (adapter != null)
                    return adapter.AdapterOrdinal;
            }
            else
            {
                AdapterInfo10 adapter = null;
                foreach (AdapterInfo10 a in Enumeration10.Adapters)
                {
                    foreach (OutputInfo10 o in a.Outputs)
                    {
                        if (o.OutputDescription.Name == game.Window.Screen.DeviceName)
                        {
                            adapter = a;
                            break;
                        }
                    }
                }

                if (adapter != null)
                    return adapter.AdapterOrdinal;
            }

            return -1;
        }

        static int GetOutputOrdinal(Screen screen)
        {
            foreach (AdapterInfo10 adapter in Enumeration10.Adapters)
            {
                foreach (OutputInfo10 output in adapter.Outputs)
                {
                    if (output.OutputDescription.Name == screen.DeviceName)
                        return output.OutputOrdinal;
                }
            }

            return -1;
        }

        internal static void EnsureD3D9()
        {
            if (Direct3D9Object == null)
                Direct3D9Object = new Direct3D();
        }

        internal static void EnsureD3D10()
        {
            if (Factory == null)
            {
                SlimDX.Direct3D10.Device device = new SlimDX.Direct3D10.Device(DeviceCreationFlags.None);
                device.Dispose();

                Factory = new Factory();
            }
        }
    }
}
