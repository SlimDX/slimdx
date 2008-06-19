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
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Presents an easy to use wrapper for making games and samples.
    /// </summary>
    public abstract class Game : IDisposable
    {
        // constants
        const int WH_KEYBOARD_LL = 13;

        // static variables
        static IntPtr keyboardHook;

        // timing variables
        GameClock clock = new GameClock();
        GameTime gameTime = new GameTime();
        TimeSpan maximumElapsedTime = TimeSpan.FromMilliseconds(500.0);
        TimeSpan totalGameTime;
        TimeSpan accumulatedElapsedGameTime;
        TimeSpan lastFrameElapsedGameTime;
        TimeSpan lastFrameElapsedRealTime;
        TimeSpan targetElapsedTime = TimeSpan.FromTicks(166667);
        TimeSpan inactiveSleepTime = TimeSpan.FromMilliseconds(20.0);
        int updatesSinceRunningSlowly1 = int.MaxValue;
        int updatesSinceRunningSlowly2 = int.MaxValue;
        bool forceElapsedTimeToZero;
        bool drawRunningSlowly;

        /// <summary>
        /// Occurs when the game is disposed.
        /// </summary>
        public event EventHandler Disposed;

        /// <summary>
        /// Occurs when the game is activated.
        /// </summary>
        public event EventHandler Activated;

        /// <summary>
        /// Occurs when the game is deactivated.
        /// </summary>
        public event EventHandler Deactivated;

        /// <summary>
        /// Occurs when the game is exiting.
        /// </summary>
        public event EventHandler Exiting;

        /// <summary>
        /// Occurs when a drawing frame is about to start.
        /// </summary>
        public event CancelEventHandler FrameStart;

        /// <summary>
        /// Occurs when a drawing frame ends.
        /// </summary>
        public event EventHandler FrameEnd;

        /// <summary>
        /// Gets or sets the inactive sleep time.
        /// </summary>
        /// <value>The inactive sleep time.</value>
        public TimeSpan InactiveSleepTime
        {
            get { return inactiveSleepTime; }
            set
            {
                // error checking
                if (value < TimeSpan.Zero)
                    throw new ArgumentOutOfRangeException("value", "Inactive sleep time cannot be less than zero.");
                inactiveSleepTime = value;
            }
        }

        /// <summary>
        /// Gets or sets the target elapsed time.
        /// </summary>
        /// <value>The target elapsed time.</value>
        public TimeSpan TargetElapsedTime
        {
            get { return targetElapsedTime; }
            set
            {
                // error checking
                if (value <= TimeSpan.Zero)
                    throw new ArgumentOutOfRangeException("value", "Target elapsed time must be greater than zero.");
                targetElapsedTime = value;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the game is using a fixed time step.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the game is using a fixed time step; otherwise, <c>false</c>.
        /// </value>
        public bool IsFixedTimeStep
        {
            get;
            set;
        }

        /// <summary>
        /// Gets a value indicating whether this <see cref="Game"/> is exiting.
        /// </summary>
        /// <value><c>true</c> if exiting; otherwise, <c>false</c>.</value>
        public bool IsExiting
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is running.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is running; otherwise, <c>false</c>.
        /// </value>
        public bool IsRunning
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the game window.
        /// </summary>
        /// <value>The game window.</value>
        public GameWindow Window
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="Game"/> is active.
        /// </summary>
        /// <value><c>true</c> if active; otherwise, <c>false</c>.</value>
        public bool IsActive
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes the <see cref="Game"/> class.
        /// </summary>
        static Game()
        {
            // configure SlimDX
            Configuration.ThrowOnError = true;
            Configuration.AddResultWatch(ResultCode.DeviceLost, ResultWatchFlags.AlwaysIgnore);
            Configuration.AddResultWatch(ResultCode.WasStillDrawing, ResultWatchFlags.AlwaysIgnore);

#if DEBUG
            Configuration.DetectDoubleDispose = true;
            Configuration.EnableObjectTracking = true;
#else
            Configuration.DetectDoubleDispose = false;
            Configuration.EnableObjectTracking = false;
#endif

            // setup the application
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // disable shortcut keys
            DisableShortcutKeys();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Game"/> class.
        /// </summary>
        protected Game()
        {
            // set initial values
            IsFixedTimeStep = true;

            // create the window
            Window = new GameWindow();
            Window.ApplicationActivated += Window_ApplicationActivated;
            Window.ApplicationDeactivated += Window_ApplicationDeactivated;
            Window.Suspend += Window_Suspend;
            Window.Resume += Window_Resume;
            Window.Paint += Window_Paint;
            Window.Screensaver += Window_Screensaver;
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
        /// Exits the game.
        /// </summary>
        public void Exit()
        {
            // request the game to terminate
            IsExiting = true;
        }

        /// <summary>
        /// Runs the game.
        /// </summary>
        public void Run()
        {
            // let the application perform any necessary initialization
            Initialize();
            IsRunning = true;

            try
            {
                // reset the timing state
                gameTime.ElapsedGameTime = TimeSpan.Zero;
                gameTime.ElapsedRealTime = TimeSpan.Zero;
                gameTime.TotalGameTime = totalGameTime;
                gameTime.TotalRealTime = clock.CurrentTime;
                gameTime.IsRunningSlowly = false;

                // run the first update
                Update(gameTime);

                // run the application
                Application.Idle += Application_Idle;
                Application.Run(Window);
            }
            finally
            {
                // remove the running state
                Application.Idle -= Application_Idle;
                IsRunning = false;
                OnExiting(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Performs one complete frame for the game.
        /// </summary>
        public void Tick()
        {
            // if we are exiting, do nothing
            if (IsExiting)
                return;

            // if we are inactive, sleep for a bit
            if (!IsActive)
                Thread.Sleep((int)InactiveSleepTime.TotalMilliseconds);

            // update the clock
            clock.Step();

            // update the game time
            gameTime.TotalRealTime = clock.CurrentTime;
            gameTime.ElapsedRealTime = clock.ElapsedTime;
            lastFrameElapsedRealTime += clock.ElapsedTime;
            TimeSpan elapsedAdjustedTime = clock.ElapsedAdjustedTime;
            if (elapsedAdjustedTime < TimeSpan.Zero)
                elapsedAdjustedTime = TimeSpan.Zero;

            // check if we should force the elapsed time
            if (forceElapsedTimeToZero)
            {
                // force the time
                gameTime.ElapsedRealTime = lastFrameElapsedRealTime = elapsedAdjustedTime = TimeSpan.Zero;
                forceElapsedTimeToZero = false;
            }

            // cap the adjusted time
            if (elapsedAdjustedTime > maximumElapsedTime)
                elapsedAdjustedTime = maximumElapsedTime;

            // check if we are using a fixed or variable time step
            if (IsFixedTimeStep)
            {
                // update the timing state
                accumulatedElapsedGameTime += elapsedAdjustedTime;
                long ratio = accumulatedElapsedGameTime.Ticks / TargetElapsedTime.Ticks;
                accumulatedElapsedGameTime = TimeSpan.FromTicks(accumulatedElapsedGameTime.Ticks % TargetElapsedTime.Ticks);
                lastFrameElapsedGameTime = TimeSpan.Zero;
                if (ratio == 0)
                    return;
                TimeSpan targetElapsedTime = TargetElapsedTime;

                // check if the ratio is too large (ie. running slowly)
                if (ratio > 1)
                {
                    // running slowly
                    updatesSinceRunningSlowly2 = updatesSinceRunningSlowly1;
                    updatesSinceRunningSlowly1 = 0;
                }
                else
                {
                    // not running slowly
                    if (updatesSinceRunningSlowly1 < int.MaxValue)
                        updatesSinceRunningSlowly1++;
                    if (updatesSinceRunningSlowly2 < int.MaxValue)
                        updatesSinceRunningSlowly2++;
                }

                // check whether we are officially running slowly
                drawRunningSlowly = updatesSinceRunningSlowly2 < 20;

                // update until it's time to draw the next frame
                while (ratio > 0 && !IsExiting)
                {
                    // decrement the ratio
                    ratio -= 1;

                    try
                    {
                        // fill out the rest of the game time
                        gameTime.ElapsedGameTime = targetElapsedTime;
                        gameTime.TotalGameTime = totalGameTime;
                        gameTime.IsRunningSlowly = drawRunningSlowly;

                        // perform an update
                        Update(gameTime);
                    }
                    finally
                    {
                        // update the total clocks
                        lastFrameElapsedGameTime += targetElapsedTime;
                        totalGameTime += targetElapsedTime;
                    }
                }
            }
            else
            {
                // we can't be running slowly here
                drawRunningSlowly = false;
                updatesSinceRunningSlowly1 = int.MaxValue;
                updatesSinceRunningSlowly2 = int.MaxValue;

                // make sure we shouldn't be exiting
                if (!IsExiting)
                {
                    try
                    {
                        // fill out the rest of the game time
                        gameTime.ElapsedGameTime = lastFrameElapsedGameTime = elapsedAdjustedTime;
                        gameTime.TotalGameTime = totalGameTime;
                        gameTime.IsRunningSlowly = false;

                        // perform an update
                        Update(gameTime);
                    }
                    finally
                    {
                        // update the total clocks
                        totalGameTime += elapsedAdjustedTime;
                    }
                }
            }

            // draw the frame, but only if we aren't in the middle of sizing operations
            if (!Window.InSizeMove)
                DrawFrame();
        }

        /// <summary>
        /// Resets the elapsed time.
        /// </summary>
        public void ResetElapsedTime()
        {
            // reset the elapsed time
            forceElapsedTimeToZero = true;
            updatesSinceRunningSlowly1 = int.MaxValue;
            updatesSinceRunningSlowly2 = int.MaxValue;
        }

        /// <summary>
        /// Allows the game to perform logic processing.
        /// </summary>
        /// <param name="gameTime">The time passed since the last update.</param>
        protected virtual void Update(GameTime gameTime)
        {
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected virtual void Draw(GameTime gameTime)
        {
        }

        /// <summary>
        /// Initializes the game.
        /// </summary>
        protected internal virtual void Initialize()
        {
        }

        /// <summary>
        /// Loads graphical resources.
        /// </summary>
        protected internal virtual void LoadContent()
        {
        }

        /// <summary>
        /// Unloads graphical resources.
        /// </summary>
        protected internal virtual void UnloadContent()
        {
        }

        /// <summary>
        /// Releases the game.
        /// </summary>
        protected internal virtual void Release()
        {
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            // check if we should release managed resources
            if (disposing)
            {
                // release game data
                Release();

                // if we have an event, raise it
                if (Disposed != null)
                    Disposed(this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Activated"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnActivated(EventArgs e)
        {
            // raise the event
            if (Activated != null)
                Activated(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:Deactivated"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeactivated(EventArgs e)
        {
            // raise the event
            if (Deactivated != null)
                Deactivated(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:Exiting"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnExiting(EventArgs e)
        {
            // raise the event
            if (Exiting != null)
                Exiting(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:FrameStart"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        protected virtual void OnFrameStart(CancelEventArgs e)
        {
            // raise the event
            if (FrameStart != null)
                FrameStart(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:FrameEnd"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnFrameEnd(EventArgs e)
        {
            // raise the event
            if (FrameEnd != null)
                FrameEnd(this, e);
        }

        /// <summary>
        /// Draws a frame.
        /// </summary>
        void DrawFrame()
        {
            try
            {
                // make sure all conditions are met
                if (!IsExiting && !Window.IsMinimized)
                {
                    // start the frame
                    CancelEventArgs e = new CancelEventArgs(false);
                    OnFrameStart(e);
                    if (!e.Cancel)
                    {
                        // fill in the game time
                        gameTime.TotalRealTime = clock.CurrentTime;
                        gameTime.ElapsedRealTime = lastFrameElapsedRealTime;
                        gameTime.TotalGameTime = totalGameTime;
                        gameTime.ElapsedGameTime = lastFrameElapsedGameTime;
                        gameTime.IsRunningSlowly = drawRunningSlowly;

                        // draw the frame
                        Draw(gameTime);

                        // end the frame
                        OnFrameEnd(EventArgs.Empty);
                    }
                }
            }
            finally
            {
                // reset the elapsed counters
                lastFrameElapsedGameTime = TimeSpan.Zero;
                lastFrameElapsedRealTime = TimeSpan.Zero;
            }
        }

        /// <summary>
        /// Handles the Idle event of the Application control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Application_Idle(object sender, EventArgs e)
        {
            // loop as long as we are idle
            NativeMessage message;
            while (!NativeMethods.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                // if an exit has been requested, close the window
                if (IsExiting)
                    Window.Close();
                else
                    Tick();
            }
        }

        /// <summary>
        /// Handles the Screensaver event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="CancelEventArgs"/> instance containing the event data.</param>
        void Window_Screensaver(object sender, CancelEventArgs e)
        {
            // don't let this message pass
            e.Cancel = true;
        }

        /// <summary>
        /// Handles the ApplicationDeactivated event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_ApplicationDeactivated(object sender, EventArgs e)
        {
            // check if the state has changed
            if (IsActive)
            {
                // be sure to reenable shortcut keys
                RestoreShortcutKeys();

                // raise the event
                IsActive = false;
                OnDeactivated(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Handles the ApplicationActivated event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_ApplicationActivated(object sender, EventArgs e)
        {
            // check if the state has changed
            if (!IsActive)
            {
                // disable the shortcut keys again
                DisableShortcutKeys();

                // raise the event
                IsActive = true;
                OnActivated(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Handles the Paint event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.PaintEventArgs"/> instance containing the event data.</param>
        void Window_Paint(object sender, PaintEventArgs e)
        {
            // draw a frame
            DrawFrame();
        }

        /// <summary>
        /// Handles the Resume event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_Resume(object sender, EventArgs e)
        {
            // resume the clock
            clock.Resume();
        }

        /// <summary>
        /// Handles the Suspend event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Window_Suspend(object sender, EventArgs e)
        {
            // suspend the clock
            clock.Suspend();
        }

        /// <summary>
        /// Disables shortcut keys.
        /// </summary>
        static void DisableShortcutKeys()
        {
            // disable the shortcut keys
            StickyKeys.Disable();
            ToggleKeys.Disable();
            FilterKeys.Disable();

            // if we haven't set up the keyboard hook yet, do it now
            if (keyboardHook == IntPtr.Zero)
                keyboardHook = NativeMethods.SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc,
                    NativeMethods.GetModuleHandle(null), 0);
        }

        /// <summary>
        /// Restores the shortcut keys settings.
        /// </summary>
        static void RestoreShortcutKeys()
        {
            // restore shortcut keys
            StickyKeys.Restore();
            ToggleKeys.Restore();
            FilterKeys.Restore();

            // if we have a keyboard hook, unhook it
            if (keyboardHook != IntPtr.Zero)
            {
                // unhook the procedure
                NativeMethods.UnhookWindowsHookEx(keyboardHook);
                keyboardHook = IntPtr.Zero;
            }
        }

        /// <summary>
        /// A procedure for low level keyboard hooks.
        /// </summary>
        /// <param name="code">The hook code.</param>
        /// <param name="wparam">The first generic parameter.</param>
        /// <param name="lparam">The second generic parameter.</param>
        /// <returns>A the next hook in the chain.</returns>
        static IntPtr LowLevelKeyboardProc(int code, IntPtr wparam, IntPtr lparam)
        {
            // grab the hook info
            KBDLLHOOKSTRUCT hookInfo = (KBDLLHOOKSTRUCT)Marshal.PtrToStructure(lparam, typeof(KBDLLHOOKSTRUCT));

            // check if we should handle it
            if (code != 0)
                return NativeMethods.CallNextHookEx(keyboardHook, code, wparam, lparam);

            // check if we want to eat the message
            bool eat = false;
            if (wparam == WindowConstants.WM_KEYDOWN || wparam == WindowConstants.WM_KEYUP)
                eat = hookInfo.vkCode == WindowConstants.VK_LWIN || hookInfo.vkCode == WindowConstants.VK_RWIN;

            // return the appropriate result
            if (eat)
                return new IntPtr(1);
            else
                return NativeMethods.CallNextHookEx(keyboardHook, code, wparam, lparam);
        }
    }
}
