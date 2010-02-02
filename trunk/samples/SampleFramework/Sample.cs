/*
* Copyright (c) 2007-2010 SlimDX Group
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
using System.Windows.Forms;
using SlimDX.Direct3D9;
using SlimDX.Windows;

namespace SlimDX.SampleFramework {
    /// <summary>
    /// Implements core application logic of a SlimDX sample.
    /// 
    /// The Sample class provides a minimal wrapper around window setup, user
    /// interaction, and OS-level details, but provides very little abstraction
    /// of the underlying DirectX functionality. The reason for this is that the 
    /// purpose of a SlimDX sample is to illustrate how a particular technique 
    /// might be implemented using SlimDX; providing high level rendering abstractions
    /// in the sample framework simplify obfuscates that.
    /// 
    /// A sample is implemented by overriding various base class methods (those prefixed
    /// with "on"). 
    /// </summary>
    public class Sample : IDisposable {
        #region Public Interface

        /// <summary>
        /// Gets the width of the renderable area of the sample window.
        /// </summary>
        public int WindowWidth {
            get { return configuration.WindowWidth; }
        }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FrameDelta { get; private set; }

        /// <summary>
        /// Gets the height of the renderable area of the sample window.
        /// </summary>
        public int WindowHeight {
            get { return configuration.WindowHeight; }
        }

        public UserInterface UserInterface {
            get { return userInterface; }
        }

        /// <summary>
        /// Represents a Direct3D9 Context, only valid after calling InitializeDevice(DeviceSettings9)
        /// </summary>
        public DeviceContext9 Context9 { get; private set; }

        /// <summary>
        /// Represents a Direct3D10 Context, only valid after calling InitializeDevice(DeviceSettings10)
        /// </summary>
        public DeviceContext10 Context10 { get; private set; }

        /// <summary>
        /// Represents a Direct2D Context, only valid after calling InitializeDevice(DeviceSettings2D)
        /// </summary>
        public DeviceContext2D Context2D { get; private set; }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">If true, managed resources should be
        /// disposed of in addition to unmanaged resources.</param>
        protected virtual void Dispose(bool disposeManagedResources) {
            if (disposeManagedResources) {
                if (userInterfaceRenderer != null) {
                    userInterfaceRenderer.Dispose();
                }

                apiContext.Dispose();
                form.Dispose();
            }
        }

        /// <summary>
        /// Runs the sample.
        /// </summary>
        public void Run() {
            configuration = OnConfigure();
            form = new RenderForm(configuration.WindowTitle) {
                ClientSize = new Size(configuration.WindowWidth, configuration.WindowHeight)
            };

            currentFormWindowState = form.WindowState;

            bool isFormClosed = false;
            bool formIsResizing = false;

            form.MouseClick += HandleMouseClick;
            form.KeyDown += HandleKeyDown;
            form.KeyUp += HandleKeyUp;
            form.Resize += (o, args) => {
                               if (form.WindowState != currentFormWindowState)
                                   HandleResize(o, args);
                               currentFormWindowState = form.WindowState;
                           };

            form.ResizeBegin += (o, args) => { formIsResizing = true; };
            form.ResizeEnd += (o, args) => {
                                  formIsResizing = false;
                                  HandleResize(o, args);
                              };

            form.Closed += (o, args) => { isFormClosed = true; };

            userInterface = new UserInterface();
            var stats = new Element();
            stats.SetBinding("Label", framesPerSecond);
            userInterface.Container.Add(stats);

            OnInitialize();
            OnResourceLoad();

            clock.Start();
            MessagePump.Run(form, () => {
                                      if (isFormClosed) {
                                          return;
                                      }

                                      Update();

                                      if (!formIsResizing)
                                          Render();
                                  });

            OnResourceUnload();
        }

        /// <summary>
        /// In a derived class, implements logic to control the configuration of the sample
        /// via a <see cref="SampleConfiguration"/> object.
        /// </summary>
        /// <returns>A <see cref="SampleConfiguration"/> object describing the desired configuration of the sample.</returns>
        protected virtual SampleConfiguration OnConfigure() {
            return new SampleConfiguration();
        }

        /// <summary>
        /// In a derived class, implements logic to initialize the sample.
        /// </summary>
        protected virtual void OnInitialize() {}

        protected virtual void OnResourceLoad() {}

        protected virtual void OnResourceUnload() {}

        /// <summary>
        /// In a derived class, implements logic to handle the case of the window being minimized.
        /// </summary>
        protected virtual void OnMinimize() {}

        /// <summary>
        /// In a derived class, implements logic to handle the case of the window being maximized.
        /// </summary>
        protected virtual void OnMaximize() {}

        /// <summary>
        /// In a derived class, implements logic to update any relevant sample state.
        /// </summary>
        protected virtual void OnUpdate() {}

        /// <summary>
        /// In a derived class, implements logic to render the sample.
        /// </summary>
        protected virtual void OnRender() {}

        /// <summary>
        /// In a derived class, implements logic that should occur before all
        /// other rendering.
        /// </summary>
        protected virtual void OnRenderBegin() {}

        /// <summary>
        /// In a derived class, implements logic that should occur after all
        /// other rendering.
        /// </summary>
        protected virtual void OnRenderEnd() {}

        /// <summary>
        /// Initializes a <see cref="DeviceContext2D">Direct2D device context</see> according to the specified settings.
        /// The base class retains ownership of the context and will dispose of it when appropriate.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The initialized device context.</returns>
        protected void InitializeDevice(DeviceSettings2D settings) {
            var result = new DeviceContext2D(form.Handle, settings);
            //userInterfaceRenderer = new UserInterfaceRenderer9( result.Device, settings.Width, settings.Height );
            apiContext = result;
            Context2D = result;
        }

        /// <summary>
        /// Initializes a <see cref="DeviceContext9">Direct3D9 device context</see> according to the specified settings.
        /// The base class retains ownership of the context and will dispose of it when appropriate.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The initialized device context.</returns>
        protected void InitializeDevice(DeviceSettings9 settings) {
            var result = new DeviceContext9(form.Handle, settings);
            userInterfaceRenderer = new UserInterfaceRenderer9(result.Device, settings.Width, settings.Height);
            apiContext = result;
            Context9 = result;
        }

        /// <summary>
        /// Initializes a <see cref="DeviceContext10">Direct3D10 device context</see> according to the specified settings.
        /// The base class retains ownership of the context and will dispose of it when appropriate.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The initialized device context.</returns>
        protected void InitializeDevice(DeviceSettings10 settings) {
            var result = new DeviceContext10(form.Handle, settings);
            userInterfaceRenderer = new UserInterfaceRenderer10(result.Device, settings.Width, settings.Height);
            apiContext = result;
            Context10 = result;
        }

        /// <summary>
        /// Quits the sample.
        /// </summary>
        protected void Quit() {
            form.Close();
        }

        #endregion

        #region Implementation Detail

        private readonly Clock clock = new Clock();
        private readonly Bindable<float> framesPerSecond = new Bindable<float>();
        private IDisposable apiContext;
        private SampleConfiguration configuration;
        private FormWindowState currentFormWindowState;
        private RenderForm form;
        private float frameAccumulator;
        private int frameCount;
        private UserInterface userInterface;
        private UserInterfaceRenderer userInterfaceRenderer;

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~Sample() {
            Dispose(false);
        }

        /// <summary>
        /// Updates sample state.
        /// </summary>
        private void Update() {
            FrameDelta = clock.Update();
            userInterface.Container.Update();
            OnUpdate();
        }

        /// <summary>
        /// Renders the sample.
        /// </summary>
        private void Render() {
            frameAccumulator += FrameDelta;
            ++frameCount;
            if (frameAccumulator >= 1.0f) {
                framesPerSecond.Value = frameCount/frameAccumulator;

                frameAccumulator = 0.0f;
                frameCount = 0;
            }

            OnRenderBegin();
            OnRender();
            if (userInterfaceRenderer != null) {
                userInterfaceRenderer.Render(userInterface);
            }
            OnRenderEnd();
        }

        /// <summary>
        /// Handles a mouse click event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        private void HandleMouseClick(object sender, MouseEventArgs e) {}

        /// <summary>
        /// Handles a key down event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        private void HandleKeyDown(object sender, KeyEventArgs e) {}

        /// <summary>
        /// Handles a key up event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        private void HandleKeyUp(object sender, KeyEventArgs e) {}

        private void HandleResize(object sender, EventArgs e) {
            if (form.WindowState == FormWindowState.Minimized) {
                OnMinimize();
                return;
            }

            if (form.WindowState == FormWindowState.Maximized)
                OnMaximize();

            OnResourceUnload();

            configuration.WindowWidth = form.ClientSize.Width;
            configuration.WindowHeight = form.ClientSize.Height;

            if (Context9 != null) {
                userInterfaceRenderer.Dispose();

                Context9.PresentParameters.BackBufferWidth = configuration.WindowWidth;
                Context9.PresentParameters.BackBufferHeight = configuration.WindowHeight;

                Context9.Device.Reset(Context9.PresentParameters);

                userInterfaceRenderer = new UserInterfaceRenderer9(Context9.Device, form.ClientSize.Width, form.ClientSize.Height);
            }
            else if (Context10 != null) {
                userInterfaceRenderer.Dispose();

                Context10.SwapChain.ResizeBuffers(1, WindowWidth, WindowHeight, Context10.SwapChain.Description.ModeDescription.Format, Context10.SwapChain.Description.Flags);


                userInterfaceRenderer = new UserInterfaceRenderer10(Context10.Device, form.ClientSize.Width, form.ClientSize.Height);
            }

            OnResourceLoad();
        }

        #endregion
    }
}