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
            DeviceSettings settings = DeviceSettings.FindValidSettings(desiredSettings);

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
    }
}
