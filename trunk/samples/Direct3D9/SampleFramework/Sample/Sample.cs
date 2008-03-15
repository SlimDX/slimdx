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
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using SlimDX.Direct3D9;
using SlimDX;
using System.Threading;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    /// <summary>
    /// Presents an easy to use wrapper around Direct3D for use with SlimDX samples.
    /// </summary>
    public class Sample : IDisposable
    {
        #region Variables

        static bool disableWindowKey = true;
        static IntPtr keyboardHook = IntPtr.Zero;
        static LowLevelKeyboardProc keyboardProc = new LowLevelKeyboardProc(Sample.LowLevelKeyboardProc);

        Window window;
        bool minimized;
        bool maximized;
        bool inSizeMove;
        bool ignoreSizeChanges;
        bool deviceLost;
        IntPtr adapterMonitor;

        MenuStrip savedMenu;
        int fullscreenWindowWidth;
        int fullscreenWindowHeight;
        int windowedWindowWidth;
        int windowedWindowHeight;
        long windowedStyle;
        bool topmostWhileWindowed;
        WINDOWPLACEMENT windowedPlacement;

        Device device;
        DeviceSettings currentSettings = new DeviceSettings();

        #endregion

        #region Events

        /// <summary>
        /// Occurs once per iteration of the main loop.
        /// </summary>
        public event EventHandler MainLoop;

        /// <summary>
        /// Occurs when the device is created.
        /// </summary>
        public event EventHandler DeviceCreated;

        /// <summary>
        /// Occurs when the device is destroyed.
        /// </summary>
        public event EventHandler DeviceDestroyed;

        /// <summary>
        /// Occurs when the device is lost.
        /// </summary>
        public event EventHandler DeviceLost;

        /// <summary>
        /// Occurs when the device is reset.
        /// </summary>
        public event EventHandler DeviceReset;

        /// <summary>
        /// Occurs when the window is created.
        /// </summary>
        public event EventHandler WindowCreated;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the render window.
        /// </summary>
        /// <value>The render window.</value>
        public Window Window
        {
            get { return window; }
        }

        /// <summary>
        /// Gets a value indicating whether the application is windowed.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the application is windowed; otherwise, <c>false</c>.
        /// </value>
        public bool IsWindowed
        {
            get { return currentSettings.PresentParameters.Windowed; }
        }

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return device; }
        }

        /// <summary>
        /// Gets the current device settings.
        /// </summary>
        /// <value>The current device settings.</value>
        public DeviceSettings CurrentSettings
        {
            get { return currentSettings; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the device is lost.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the device is lost; otherwise, <c>false</c>.
        /// </value>
        public bool IsDeviceLost
        {
            get { return deviceLost; }
            set { deviceLost = value; }
        }

        #endregion

        #region Constructor

        static Sample()
        {
            try
            {
                Direct3D.Initialize();
            }
            catch (SlimDXException ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Sample"/> class.
        /// </summary>
        /// <param name="window">The render window.</param>
        /// <param name="windowed">if set to <c>true</c>, the application will run in windowed mode.</param>
        /// <param name="desiredWidth">Desired width of the window.</param>
        /// <param name="desiredHeight">Desired height of the window.</param>
        public Sample(Window window, bool windowed, int desiredWidth, int desiredHeight)
        {
            DeviceSettings settings = new DeviceSettings();
            settings.PresentParameters.BackBufferWidth = desiredWidth;
            settings.PresentParameters.BackBufferHeight = desiredHeight;
            settings.PresentParameters.Windowed = windowed;

            Construct(window, settings);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Sample"/> class.
        /// </summary>
        /// <param name="window">The render window.</param>
        /// <param name="settings">The desired device settings.</param>
        public Sample(Window window, DeviceSettings settings)
        {
            Construct(window, settings);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Sample"/> class.
        /// </summary>
        /// <param name="name">The name of the window.</param>
        /// <param name="windowed">if set to <c>true</c>, the application will run in windowed mode.</param>
        /// <param name="desiredWidth">Desired width of the window.</param>
        /// <param name="desiredHeight">Desired height of the window.</param>
        public Sample(string name, bool windowed, int desiredWidth, int desiredHeight)
        {
            window = new Window();
            window.Text = name;
            window.ClientSize = new Size(desiredWidth, desiredHeight);

            DeviceSettings settings = new DeviceSettings();
            settings.PresentParameters.BackBufferWidth = desiredWidth;
            settings.PresentParameters.BackBufferHeight = desiredHeight;
            settings.PresentParameters.Windowed = windowed;

            Construct(window, settings);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Sample"/> class.
        /// </summary>
        /// <param name="name">The name of the window.</param>
        /// <param name="settings">The desired device settings.</param>
        public Sample(string name, DeviceSettings settings)
        {
            window = new Window();
            window.Text = name;

            Construct(window, settings);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Runs the sample.
        /// </summary>
        public void Run()
        {
            Application.Run(Window);
        }

        /// <summary>
        /// Toggles the reference driver.
        /// </summary>
        public void ToggleReference()
        {
            DeviceSettings newSettings = CurrentSettings.Clone();
            if (CurrentSettings.DeviceType == DeviceType.Hardware)
                newSettings.DeviceType = DeviceType.Reference;
            else if (CurrentSettings.DeviceType == DeviceType.Reference)
                newSettings.DeviceType = DeviceType.Hardware;
            newSettings = FindValidDeviceSettings(newSettings);

            CreateDevice(newSettings);
        }

        /// <summary>
        /// Toggles between fullscreen and windowed mode.
        /// </summary>
        public void ToggleFullScreen()
        {
            DeviceSettings newSettings = CurrentSettings.Clone();
            newSettings.PresentParameters.Windowed = !newSettings.PresentParameters.Windowed;

            int width, height;
            if (newSettings.PresentParameters.Windowed)
            {
                width = windowedWindowWidth;
                height = windowedWindowHeight;
            }
            else
            {
                width = fullscreenWindowWidth;
                height = fullscreenWindowHeight;
            }

            newSettings.PresentParameters.BackBufferWidth = width;
            newSettings.PresentParameters.BackBufferHeight = height;
            newSettings = FindValidDeviceSettings(newSettings);

            CreateDevice(newSettings);
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
        /// Disables shortcut keys.
        /// </summary>
        /// <param name="disableWindowKey">if set to <c>true</c>, disable the window key as well.</param>
        public static void DisableShortcutKeys(bool disableWindowKey)
        {
            Sample.disableWindowKey = disableWindowKey;

            StickyKeys.Disable();
            ToggleKeys.Disable();
            FilterKeys.Disable();

            if (keyboardHook == IntPtr.Zero)
                keyboardHook = NativeMethods.SetWindowsHookEx(HookType.WH_KEYBOARD_LL, keyboardProc,
                    NativeMethods.GetModuleHandle(null), 0);
        }

        /// <summary>
        /// Restores the shortcut keys settings.
        /// </summary>
        public static void RestoreShortcutKeys()
        {
            StickyKeys.Restore();
            ToggleKeys.Restore();
            FilterKeys.Restore();

            if (keyboardHook != IntPtr.Zero)
            {
                NativeMethods.UnhookWindowsHookEx(keyboardHook);
                keyboardHook = IntPtr.Zero;
            }
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                ReleaseDevice();
                
                if( window != null )
                    window.Dispose();

                RestoreShortcutKeys();

                window = null;
            }
        }

        /// <summary>
        /// Raises the <see cref="E:MainLoop"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnMainLoop(EventArgs e)
        {
            if (MainLoop != null)
                MainLoop(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceCreated"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceCreated(EventArgs e)
        {
            if (DeviceCreated != null)
                DeviceCreated(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceDestroyed"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceDestroyed(EventArgs e)
        {
            if (DeviceDestroyed != null)
                DeviceDestroyed(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceLost"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceLost(EventArgs e)
        {
            if (DeviceLost != null)
                DeviceLost(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceReset"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceReset(EventArgs e)
        {
            if (DeviceReset != null)
                DeviceReset(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:WindowCreated"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnWindowCreated(EventArgs e)
        {
            if (WindowCreated != null)
                WindowCreated(this, e);
        }

        #endregion

        #region Device Settings

        void CreateDevice(DeviceSettings settings)
        {
            DeviceSettings oldSettings = currentSettings;
            currentSettings = settings;

            ignoreSizeChanges = true;

            bool keepCurrentWindowSize = false;
            if (settings.PresentParameters.BackBufferWidth == 0 && settings.PresentParameters.BackBufferHeight == 0)
                keepCurrentWindowSize = true;

            if (settings.PresentParameters.Windowed)
            {
                if (oldSettings != null && !oldSettings.PresentParameters.Windowed)
                {
                    fullscreenWindowWidth = oldSettings.PresentParameters.BackBufferWidth;
                    fullscreenWindowHeight = oldSettings.PresentParameters.BackBufferHeight;

                    NativeMethods.SetWindowLong(Window.Handle, WindowConstants.GWL_STYLE, (uint)windowedStyle);
                }

                if (savedMenu != null)
                    Window.MainMenuStrip = savedMenu;
            }
            else
            {
                if (oldSettings == null || oldSettings.PresentParameters.Windowed)
                {
                    windowedPlacement = new WINDOWPLACEMENT();
                    windowedPlacement.length = WINDOWPLACEMENT.Length;
                    NativeMethods.GetWindowPlacement(Window.Handle, ref windowedPlacement);
                    topmostWhileWindowed = (NativeMethods.GetWindowLong(Window.Handle, WindowConstants.GWL_EXSTYLE) & WindowConstants.WS_EX_TOPMOST) != 0;
                    long style = NativeMethods.GetWindowLong(Window.Handle, WindowConstants.GWL_STYLE);
                    style &= ~WindowConstants.WS_MAXIMIZE & ~WindowConstants.WS_MINIMIZE;
                    windowedStyle = style;

                    if (oldSettings != null)
                    {
                        windowedWindowWidth = oldSettings.PresentParameters.BackBufferWidth;
                        windowedWindowHeight = oldSettings.PresentParameters.BackBufferHeight;
                    }
                }

                Window.Hide();

                NativeMethods.SetWindowLong(Window.Handle, WindowConstants.GWL_STYLE, (uint)(WindowConstants.WS_POPUP | WindowConstants.WS_SYSMENU));

                savedMenu = Window.MainMenuStrip;
                Window.MainMenuStrip = null;

                WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                placement.length = WINDOWPLACEMENT.Length;
                NativeMethods.GetWindowPlacement(Window.Handle, ref placement);
                if ((placement.flags & WindowConstants.WPF_RESTORETOMAXIMIZED) != 0)
                {
                    placement.flags &= ~WindowConstants.WPF_RESTORETOMAXIMIZED;
                    placement.showCmd = ShowWindow.Restore;
                    NativeMethods.SetWindowPlacement(Window.Handle, ref placement);
                }
            }

            if (oldSettings != null && device != null &&
                oldSettings.AdapterOrdinal == settings.AdapterOrdinal &&
                oldSettings.DeviceType == settings.DeviceType &&
                oldSettings.BehaviorFlags == settings.BehaviorFlags)
            {
                Result result = ResetDevice();
                if (result == Error.DeviceLost)
                    deviceLost = true;
                else if (result == Error.DriverInternalError)
                {
                    currentSettings = oldSettings;
                    CreateDevice(currentSettings);
                    return;
                }
            }
            else
            {
                if (oldSettings != null)
                    ReleaseDevice();

                InitializeDevice();
            }

            adapterMonitor = Direct3D.GetAdapterMonitor(currentSettings.AdapterOrdinal);

            if (oldSettings != null && !oldSettings.PresentParameters.Windowed && currentSettings.PresentParameters.Windowed)
            {
                NativeMethods.SetWindowPlacement(Window.Handle, ref windowedPlacement);
                NativeMethods.SetWindowPos(Window.Handle, (topmostWhileWindowed) ? WindowConstants.HWND_TOPMOST : WindowConstants.HWND_NOTOPMOST,
                    0, 0, 0, 0, WindowConstants.SWP_NOMOVE | WindowConstants.SWP_NOSIZE | WindowConstants.SWP_NOREDRAW);
            }

            if (currentSettings.PresentParameters.Windowed && !keepCurrentWindowSize)
            {
                int width;
                int height;
                if (NativeMethods.IsIconic(Window.Handle))
                {
                    WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                    placement.length = WINDOWPLACEMENT.Length;
                    NativeMethods.GetWindowPlacement(Window.Handle, ref placement);

                    if ((placement.flags & WindowConstants.WPF_RESTORETOMAXIMIZED) != 0 && placement.showCmd == ShowWindow.ShowMinimized)
                    {
                        NativeMethods.ShowWindow(Window.Handle, ShowWindow.Restore);
                        NativeRectangle rect;
                        NativeMethods.GetClientRect(Window.Handle, out rect);
                        width = rect.right - rect.left;
                        height = rect.bottom - rect.top;
                        NativeMethods.ShowWindow(Window.Handle, ShowWindow.Minimize);
                    }
                    else
                    {
                        NativeRectangle frame = new NativeRectangle();
                        NativeMethods.AdjustWindowRect(ref frame, (uint)windowedStyle, (savedMenu != null));
                        int frameWidth = frame.right - frame.left;
                        int frameHeight = frame.bottom - frame.top;
                        width = placement.rcNormalPosition.right - placement.rcNormalPosition.left - frameWidth;
                        height = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top - frameHeight;
                    }
                }
                else
                {
                    NativeRectangle rect;
                    NativeMethods.GetClientRect(Window.Handle, out rect);
                    width = rect.right - rect.left;
                    height = rect.bottom - rect.top;
                }

                if (width != currentSettings.PresentParameters.BackBufferWidth ||
                    height != currentSettings.PresentParameters.BackBufferHeight)
                {
                    if (NativeMethods.IsIconic(Window.Handle))
                        NativeMethods.ShowWindow(Window.Handle, ShowWindow.Restore);
                    if (NativeMethods.IsZoomed(Window.Handle))
                        NativeMethods.ShowWindow(Window.Handle, ShowWindow.Restore);

                    NativeRectangle rect = new NativeRectangle();
                    rect.right = currentSettings.PresentParameters.BackBufferWidth;
                    rect.bottom = currentSettings.PresentParameters.BackBufferHeight;
                    NativeMethods.AdjustWindowRect(ref rect,
                        NativeMethods.GetWindowLong(Window.Handle, WindowConstants.GWL_STYLE),
                        (savedMenu != null));

                    NativeMethods.SetWindowPos(Window.Handle, IntPtr.Zero, 0, 0, rect.right - rect.left,
                        rect.bottom - rect.top, WindowConstants.SWP_NOZORDER | WindowConstants.SWP_NOMOVE);

                    rect = new NativeRectangle();
                    NativeMethods.GetClientRect(Window.Handle, out rect);
                    int clientWidth = rect.right - rect.left;
                    int clientHeight = rect.bottom - rect.top;
                    if (clientWidth != currentSettings.PresentParameters.BackBufferWidth ||
                        clientHeight != currentSettings.PresentParameters.BackBufferHeight)
                    {
                        DeviceSettings newSettings = currentSettings.Clone();
                        newSettings.PresentParameters.BackBufferWidth = 0;
                        newSettings.PresentParameters.BackBufferHeight = 0;
                        CreateDevice(newSettings);
                    }
                }
            }

            if (!NativeMethods.IsWindowVisible(Window.Handle))
                NativeMethods.ShowWindow(Window.Handle, ShowWindow.Show);

            if (!IsWindowed)
                NativeMethods.SetThreadExecutionState(WindowConstants.ES_DISPLAY_REQUIRED | WindowConstants.ES_CONTINUOUS);
            else
                NativeMethods.SetThreadExecutionState(WindowConstants.ES_CONTINUOUS);

            ignoreSizeChanges = false;
        }

        static int GetAdapterOrdinalFromMonitor(IntPtr monitor)
        {
            foreach (AdapterInfo adapterInfo in Enumeration.Adapters)
            {
                if (monitor == Direct3D.GetAdapterMonitor(adapterInfo.AdapterOrdinal))
                    return adapterInfo.AdapterOrdinal;
            }

            return -1;
        }

        DeviceSettings FindValidDeviceSettings(DeviceSettings settings)
        {
            DeviceSettings optimal = BuildOptimalSettings(settings);

            if (!Enumeration.HasEnumerated)
                Enumeration.Enumerate();

            SettingsCombo bestCombo = null;
            float bestRanking = -1.0f;

            foreach (AdapterInfo adapterInfo in Enumeration.Adapters)
            {
                DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(adapterInfo.AdapterOrdinal);

                foreach (DeviceInfo deviceInfo in adapterInfo.Devices)
                {
                    foreach (SettingsCombo combo in deviceInfo.DeviceSettings)
                    {
                        if (combo.Windowed && combo.AdapterFormat != desktopMode.Format)
                            continue;

                        float ranking = RankSettingsCombo(combo, optimal, desktopMode);

                        if (ranking > bestRanking)
                        {
                            bestCombo = combo;
                            bestRanking = ranking;
                        }
                    }
                }
            }

            if (bestCombo == null)
                throw new InvalidOperationException("No compatible devices were found.");

            return BuildValidDeviceSettings(bestCombo, optimal);
        }

        DeviceSettings BuildValidDeviceSettings(SettingsCombo combo, DeviceSettings input)
        {
            DeviceSettings settings = new DeviceSettings();

            settings.AdapterOrdinal = combo.AdapterOrdinal;
            settings.DeviceType = combo.DeviceType;
            settings.PresentParameters.Windowed = combo.Windowed;
            settings.AdapterFormat = combo.AdapterFormat;
            settings.PresentParameters.BackBufferFormat = combo.BackBufferFormat;
            settings.PresentParameters.SwapEffect = input.PresentParameters.SwapEffect;
            settings.PresentParameters.PresentFlags =
                input.PresentParameters.PresentFlags | PresentFlags.DiscardDepthStencil;
            settings.PresentParameters.DeviceWindowHandle = Window.Handle;

            settings.BehaviorFlags = input.BehaviorFlags;
            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) == 0 &&
                ((settings.BehaviorFlags & CreateFlags.HardwareVertexProcessing) != 0 ||
                (settings.BehaviorFlags & CreateFlags.MixedVertexProcessing) != 0))
            {
                settings.BehaviorFlags &= ~CreateFlags.HardwareVertexProcessing;
                settings.BehaviorFlags &= ~CreateFlags.MixedVertexProcessing;
                settings.BehaviorFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            if ((settings.BehaviorFlags & CreateFlags.HardwareVertexProcessing) == 0 &&
                (settings.BehaviorFlags & CreateFlags.MixedVertexProcessing) == 0 &&
                (settings.BehaviorFlags & CreateFlags.SoftwareVertexProcessing) == 0)
            {
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    settings.BehaviorFlags |= CreateFlags.HardwareVertexProcessing;
                else
                    settings.BehaviorFlags |= CreateFlags.SoftwareVertexProcessing;
            }

            DisplayMode bestDisplayMode = FindValidResolution(combo, input);
            settings.PresentParameters.BackBufferWidth = bestDisplayMode.Width;
            settings.PresentParameters.BackBufferHeight = bestDisplayMode.Height;

            settings.PresentParameters.BackBufferCount = input.PresentParameters.BackBufferCount;
            if (settings.PresentParameters.BackBufferCount > 3)
                settings.PresentParameters.BackBufferCount = 3;
            if (settings.PresentParameters.BackBufferCount < 1)
                settings.PresentParameters.BackBufferCount = 1;

            if (input.PresentParameters.SwapEffect != SwapEffect.Discard)
            {
                settings.PresentParameters.Multisample = MultisampleType.None;
                settings.PresentParameters.MultisampleQuality = 0;
            }
            else
            {
                MultisampleType bestType = MultisampleType.None;
                int bestQuality = 0;

                for (int i = 0; i < combo.MultisampleTypes.Count; i++)
                {
                    MultisampleType type = combo.MultisampleTypes[i];
                    int quality = combo.MultisampleQualities[0];

                    if (Math.Abs(type - input.PresentParameters.Multisample) < Math.Abs(bestType -
                        input.PresentParameters.Multisample))
                    {
                        bestType = type;
                        bestQuality = Math.Min(quality - 1, input.PresentParameters.MultisampleQuality);
                    }
                }

                settings.PresentParameters.Multisample = bestType;
                settings.PresentParameters.MultisampleQuality = bestQuality;
            }

            List<int> rankings = new List<int>();
            int inputDepthBitDepth = BitExtractor.GetDepthBits(input.PresentParameters.AutoDepthStencilFormat);
            int inputStencilBitDepth = BitExtractor.GetStencilBits(input.PresentParameters.AutoDepthStencilFormat);

            foreach (Format format in combo.DepthStencilFormats)
            {
                int currentBitDepth = BitExtractor.GetDepthBits(format);
                int currentStencilDepth = BitExtractor.GetStencilBits(format);

                int ranking = Math.Abs(currentBitDepth - inputDepthBitDepth);
                ranking += Math.Abs(currentStencilDepth - inputStencilBitDepth);
                rankings.Add(ranking);
            }

            int bestRanking = 100000;
            int bestIndex = -1;
            for (int i = 0; i < combo.DepthStencilFormats.Count; i++)
            {
                if (rankings[i] < bestRanking)
                {
                    bestRanking = rankings[i];
                    bestIndex = i;
                }
            }

            if (bestIndex >= 0)
            {
                settings.PresentParameters.AutoDepthStencilFormat = combo.DepthStencilFormats[bestIndex];
                settings.PresentParameters.EnableAutoDepthStencil = true;
            }
            else
            {
                settings.PresentParameters.AutoDepthStencilFormat = Format.Unknown;
                settings.PresentParameters.EnableAutoDepthStencil = false;
            }

            if (combo.Windowed)
                settings.PresentParameters.FullScreenRefreshRateInHertz = 0;
            else
            {
                int match = input.PresentParameters.FullScreenRefreshRateInHertz;
                bestDisplayMode.RefreshRate = 0;
                if (match != 0)
                {
                    bestRanking = 100000;
                    foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
                    {
                        if (displayMode.Format != combo.AdapterFormat ||
                            displayMode.Width != bestDisplayMode.Width ||
                            displayMode.Height != bestDisplayMode.Height)
                            continue;

                        int ranking = Math.Abs(displayMode.RefreshRate - match);

                        if (ranking < bestRanking)
                        {
                            bestDisplayMode.RefreshRate = displayMode.RefreshRate;
                            bestRanking = ranking;

                            if (bestRanking == 0)
                                break;
                        }
                    }
                }
                settings.PresentParameters.FullScreenRefreshRateInHertz = bestDisplayMode.RefreshRate;
            }

            if (combo.PresentIntervals.Contains(input.PresentParameters.PresentationInterval))
                settings.PresentParameters.PresentationInterval = input.PresentParameters.PresentationInterval;
            else
                settings.PresentParameters.PresentationInterval = PresentInterval.Default;

            return settings;
        }

        static DisplayMode FindValidResolution(SettingsCombo combo, DeviceSettings input)
        {
            DisplayMode bestMode = new DisplayMode();

            if (combo.Windowed)
            {
                bestMode.Width = input.PresentParameters.BackBufferWidth;
                bestMode.Height = input.PresentParameters.BackBufferHeight;
                return bestMode;
            }

            int bestRanking = 100000;
            int ranking;
            foreach (DisplayMode mode in combo.AdapterInfo.DisplayModes)
            {
                if (mode.Format != combo.AdapterFormat)
                    continue;

                ranking = Math.Abs(mode.Width - input.PresentParameters.BackBufferWidth) +
                    Math.Abs(mode.Height - input.PresentParameters.BackBufferHeight);

                if (ranking < bestRanking)
                {
                    bestMode = mode;
                    bestRanking = ranking;

                    if (bestRanking == 0)
                        break;
                }
            }

            if (bestMode.Width == 0)
            {
                bestMode.Width = input.PresentParameters.BackBufferWidth;
                bestMode.Height = input.PresentParameters.BackBufferHeight;
            }

            return bestMode;
        }

        static float RankSettingsCombo(SettingsCombo combo, DeviceSettings optimal, DisplayMode desktopMode)
        {
            float ranking = 0.0f;

            if (combo.AdapterOrdinal == optimal.AdapterOrdinal)
                ranking += 1000.0f;

            if (combo.DeviceType == optimal.DeviceType)
                ranking += 100.0f;
            if (combo.DeviceType == DeviceType.Hardware)
                ranking += 0.1f;

            if (combo.Windowed == optimal.PresentParameters.Windowed)
                ranking += 10.0f;

            if (combo.AdapterFormat == optimal.AdapterFormat)
                ranking += 1.0f;
            else
            {
                int bitDepthDelta = Math.Abs(BitExtractor.GetColorBits(combo.AdapterFormat) -
                    BitExtractor.GetColorBits(optimal.AdapterFormat));
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            if (!combo.Windowed)
            {
                bool match;
                if (BitExtractor.GetColorBits(desktopMode.Format) >= 8)
                    match = (combo.AdapterFormat == desktopMode.Format);
                else
                    match = (combo.AdapterFormat == Format.X8R8G8B8);
                if (match)
                    ranking += 0.1f;
            }

            if ((optimal.BehaviorFlags & CreateFlags.HardwareVertexProcessing) != 0 &&
                (optimal.BehaviorFlags & CreateFlags.MixedVertexProcessing) != 0)
            {
                if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                    ranking += 1.0f;
            }

            if ((combo.DeviceInfo.Capabilities.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
                ranking += 0.1f;

            foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
            {
                if (displayMode.Format != combo.AdapterFormat)
                    continue;
                if (displayMode.Width == optimal.PresentParameters.BackBufferWidth &&
                    displayMode.Height == optimal.PresentParameters.BackBufferHeight)
                {
                    ranking += 1.0f;
                    break;
                }
            }

            if (combo.BackBufferFormat == optimal.PresentParameters.BackBufferFormat)
                ranking += 1.0f;
            else
            {
                int bitDepthDelta = Math.Abs(BitExtractor.GetColorBits(combo.BackBufferFormat) -
                    BitExtractor.GetColorBits(optimal.PresentParameters.BackBufferFormat));
                float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
                ranking += scale;
            }

            if (combo.BackBufferFormat == combo.AdapterFormat)
                ranking += 0.1f;

            for (int i = 0; i < combo.MultisampleTypes.Count; i++)
            {
                MultisampleType type = combo.MultisampleTypes[i];
                int quality = combo.MultisampleQualities[i];

                if (type == optimal.PresentParameters.Multisample && quality == optimal.PresentParameters.MultisampleQuality)
                {
                    ranking += 1.0f;
                    break;
                }
            }

            if (combo.DepthStencilFormats.Contains(optimal.PresentParameters.AutoDepthStencilFormat))
                ranking += 1.0f;

            foreach (DisplayMode displayMode in combo.AdapterInfo.DisplayModes)
            {
                if (displayMode.Format != combo.AdapterFormat)
                    continue;
                if (displayMode.RefreshRate == optimal.PresentParameters.FullScreenRefreshRateInHertz)
                {
                    ranking += 1.0f;
                    break;
                }
            }

            if (combo.PresentIntervals.Contains(optimal.PresentParameters.PresentationInterval))
                ranking += 1.0f;

            return ranking;
        }

        static DeviceSettings BuildOptimalSettings(DeviceSettings settings)
        {
            DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(settings.AdapterOrdinal);
            DeviceSettings optimal = new DeviceSettings();

            optimal.AdapterOrdinal = settings.AdapterOrdinal;
            optimal.DeviceType = settings.DeviceType;
            optimal.PresentParameters.Windowed = settings.PresentParameters.Windowed;
            optimal.BehaviorFlags = settings.BehaviorFlags;
            optimal.PresentParameters.BackBufferCount = settings.PresentParameters.BackBufferCount;
            optimal.PresentParameters.Multisample = settings.PresentParameters.Multisample;
            optimal.PresentParameters.MultisampleQuality = settings.PresentParameters.MultisampleQuality;
            optimal.PresentParameters.PresentFlags = settings.PresentParameters.PresentFlags;
            optimal.PresentParameters.FullScreenRefreshRateInHertz = settings.PresentParameters.FullScreenRefreshRateInHertz;
            optimal.PresentParameters.PresentationInterval = settings.PresentParameters.PresentationInterval;
            optimal.PresentParameters.SwapEffect = settings.PresentParameters.SwapEffect;

            if (settings.AdapterFormat == Format.Unknown)
            {
                if (optimal.PresentParameters.Windowed || BitExtractor.GetColorBits(desktopMode.Format) >= 8)
                    optimal.AdapterFormat = desktopMode.Format;
                else
                    optimal.AdapterFormat = Format.X8R8G8B8;
            }
            else
                optimal.AdapterFormat = settings.AdapterFormat;

            if (settings.PresentParameters.BackBufferWidth == 0 || settings.PresentParameters.BackBufferHeight == 0)
            {
                if (optimal.PresentParameters.Windowed)
                {
                    optimal.PresentParameters.BackBufferWidth = 640;
                    optimal.PresentParameters.BackBufferHeight = 480;
                }
                else
                {
                    optimal.PresentParameters.BackBufferWidth = desktopMode.Width;
                    optimal.PresentParameters.BackBufferHeight = desktopMode.Height;
                }
            }
            else
            {
                optimal.PresentParameters.BackBufferWidth = settings.PresentParameters.BackBufferWidth;
                optimal.PresentParameters.BackBufferHeight = settings.PresentParameters.BackBufferHeight;
            }

            if (settings.PresentParameters.BackBufferFormat == Format.Unknown)
                optimal.PresentParameters.BackBufferFormat = optimal.AdapterFormat;
            else
                optimal.PresentParameters.BackBufferFormat = settings.PresentParameters.BackBufferFormat;

            if (settings.PresentParameters.AutoDepthStencilFormat == Format.Unknown)
            {
                if (BitExtractor.GetColorBits(optimal.PresentParameters.BackBufferFormat) >= 8)
                    optimal.PresentParameters.AutoDepthStencilFormat = Format.D32;
                else
                    optimal.PresentParameters.AutoDepthStencilFormat = Format.D16;
                optimal.PresentParameters.EnableAutoDepthStencil = true;
            }
            else
            {
                optimal.PresentParameters.EnableAutoDepthStencil = true;
                optimal.PresentParameters.AutoDepthStencilFormat = settings.PresentParameters.AutoDepthStencilFormat;
            }

            return optimal;
        }

        #endregion

        #region Helpers

        void window_CursorChanged(object sender, EventArgs e)
        {
            if (device != null && !IsWindowed)
                device.SetCursor(window.Cursor, false);
        }

        void window_MouseMove(object sender, MouseEventArgs e)
        {
            if (device != null && !IsWindowed)
                device.SetCursorPosition(Cursor.Position, true);
        }

        void window_ResizeEnd(object sender, EventArgs e)
        {
            CheckForWindowSizeChange();
            CheckForWindowChangingMonitors();
            inSizeMove = false;
        }

        void window_ResizeBegin(object sender, EventArgs e)
        {
            inSizeMove = true;
        }

        void window_SizeRestored(object sender, EventArgs e)
        {
            if (minimized || maximized)
            {
                minimized = false;
                maximized = false;

                CheckForWindowSizeChange();
                CheckForWindowChangingMonitors();
            }
            else if (!inSizeMove)
            {
                CheckForWindowSizeChange();
                CheckForWindowChangingMonitors();
            }
        }

        void window_SizeMaximized(object sender, EventArgs e)
        {
            minimized = false;
            maximized = true;

            CheckForWindowSizeChange();
            CheckForWindowChangingMonitors();
        }

        void window_SizeMinimized(object sender, EventArgs e)
        {
            minimized = true;
            maximized = false;
        }

        void Construct(Window window, DeviceSettings deviceSettings)
        {
            this.window = window;

            window.SizeMinimized += new EventHandler(window_SizeMinimized);
            window.SizeMaximized += new EventHandler(window_SizeMaximized);
            window.SizeRestored += new EventHandler(window_SizeRestored);
            window.ResizeBegin += new EventHandler(window_ResizeBegin);
            window.ResizeEnd += new EventHandler(window_ResizeEnd);
            window.MouseMove += new MouseEventHandler(window_MouseMove);
            window.CursorChanged += new EventHandler(window_CursorChanged);

            OnWindowCreated(EventArgs.Empty);

            deviceSettings = FindValidDeviceSettings(deviceSettings);
            CreateDevice(deviceSettings);

            Application.Idle += new EventHandler(Application_Idle);
        }

        void Application_Idle(object sender, EventArgs e)
        {
            while (NativeMethods.IsAppIdle)
            {
                if (IsDeviceLost || !Window.Active)
                    Thread.Sleep(50);

                if (IsDeviceLost)
                {
                    Result result = Device.TestCooperativeLevel();
                    if (result.IsFailure)
                    {
                        if (result == Error.DeviceLost)
                            continue;

                        if (IsWindowed)
                        {
                            DisplayMode desktopMode = Direct3D.GetAdapterDisplayMode(CurrentSettings.AdapterOrdinal);
                            if (CurrentSettings.AdapterFormat != desktopMode.Format)
                            {
                                DeviceSettings settings = CurrentSettings.Clone();
                                settings.AdapterFormat = desktopMode.Format;
                                settings = FindValidDeviceSettings(settings);
                                CreateDevice(settings);
                                continue;
                            }
                        }
                    }

                    if (ResetDevice().IsFailure)
                        continue;
                }

                IsDeviceLost = false;

                OnMainLoop(EventArgs.Empty);
            }
        }

        static IntPtr LowLevelKeyboardProc(int code, IntPtr wparam, IntPtr lparam)
        {
            KBDLLHOOKSTRUCT hookInfo = (KBDLLHOOKSTRUCT)Marshal.PtrToStructure(lparam, typeof(KBDLLHOOKSTRUCT));

            if (code != 0)
                return NativeMethods.CallNextHookEx(keyboardHook, code, wparam, lparam);

            bool eat = false;
            int value = wparam.ToInt32();
            if (value == WindowConstants.WM_KEYDOWN || value== WindowConstants.WM_KEYUP)
                eat = disableWindowKey && (hookInfo.vkCode == WindowConstants.VK_LWIN || hookInfo.vkCode == WindowConstants.VK_RWIN);

            if (eat)
                return new IntPtr(1);
            else
                return NativeMethods.CallNextHookEx(keyboardHook, code, wparam, lparam);
        }

        void InitializeDevice()
        {
            try
            {
                device = new Device(currentSettings.AdapterOrdinal, currentSettings.DeviceType,
                    Window.Handle, currentSettings.BehaviorFlags, currentSettings.PresentParameters);
            }
            catch(Direct3D9Exception)
            {
                deviceLost = true;
                return;
            }

            OnDeviceCreated(EventArgs.Empty);
            OnDeviceReset(EventArgs.Empty);
        }

        Result ResetDevice()
        {
            OnDeviceLost(EventArgs.Empty);

            Result result = device.Reset(CurrentSettings.PresentParameters);
            if (result.IsFailure)
                return result;

            OnDeviceReset(EventArgs.Empty);

            return result;
        }

        void ReleaseDevice()
        {
            if (device == null)
                return;

            OnDeviceLost(EventArgs.Empty);
            OnDeviceDestroyed(EventArgs.Empty);

            device.Dispose();
            device = null;
        }

        void CheckForWindowSizeChange()
        {
            if (ignoreSizeChanges || device == null || !IsWindowed)
                return;

            NativeRectangle rect;
            NativeMethods.GetClientRect(Window.Handle, out rect);
            if (rect.right != CurrentSettings.PresentParameters.BackBufferWidth ||
                rect.bottom != CurrentSettings.PresentParameters.BackBufferHeight)
            {
                DeviceSettings newSettings = CurrentSettings.Clone();
                newSettings.PresentParameters.BackBufferWidth = 0;
                newSettings.PresentParameters.BackBufferHeight = 0;
                CreateDevice(newSettings);
            }
        }

        void CheckForWindowChangingMonitors()
        {
            if (ignoreSizeChanges || device == null || !IsWindowed)
                return;

            IntPtr windowMonitor = NativeMethods.MonitorFromWindow(Window.Handle, WindowConstants.MONITOR_DEFAULTTOPRIMARY);
            if (windowMonitor != adapterMonitor)
            {
                int ordinal = GetAdapterOrdinalFromMonitor(windowMonitor);
                if (ordinal == -1)
                    return;

                DeviceSettings newSettings = CurrentSettings.Clone();
                newSettings.AdapterOrdinal = ordinal;
                newSettings = FindValidDeviceSettings(newSettings);

                CreateDevice(newSettings);
            }
        }

        #endregion
    }
}
