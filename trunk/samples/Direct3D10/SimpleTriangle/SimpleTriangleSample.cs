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
using System.Drawing;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D10;
using System.Runtime.InteropServices;

namespace SimpleTriangle
{
    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector4 PositionRhw;
        public int Color;
    }

    /// <summary>
    /// The top level game object. Manages the entire game.
    /// </summary>
    class SimpleTriangleSample : Game
    {
        // constants
        const int InitialWidth = 800;
        const int InitialHeight = 600;

        Effect effect;
        EffectTechnique technique;
        EffectPass pass;
        InputLayout layout;
        Buffer vertices;

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D10.Device; }
        }

        /// <summary>
        /// Gets or sets the clear color.
        /// </summary>
        /// <value>The clear color.</value>
        public Color ClearColor
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimpleTriangleSample"/> class.
        /// </summary>
        public SimpleTriangleSample()
        {
            // initialize the clear color
            ClearColor = Color.Black;

            // set up the window
            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Simple Triangle Sample";
            Window.KeyDown += Window_KeyDown;

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D10, true, InitialWidth, InitialHeight);
        }

        /// <summary>
        /// Handles the KeyDown event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();
        }

        /// <summary>
        /// Initializes the game.
        /// </summary>
        protected override void Initialize()
        {
            base.Initialize();

            // load the effect
            effect = Effect.FromFile(Device, "SimpleTriangle.fx", "fx_4_0", ShaderFlags.None, EffectFlags.None, null, null);
            technique = effect.GetTechniqueByIndex(0);
            pass = technique.GetPassByIndex(0);

            // set up the graphical data
            InputElement[] inputElements = new InputElement[]
			{
				new InputElement("POSITION", 0, SlimDX.DXGI.Format.R32G32B32A32_Float, 0, 0),
				new InputElement("COLOR", 0, SlimDX.DXGI.Format.R8G8B8A8_UNorm, 16, 0)
			};
            layout = new InputLayout(Device, inputElements, pass.Description.Signature);

            // create the vertices
            DataStream stream = new DataStream(3 * Marshal.SizeOf(typeof(Vertex)), true, true);
            stream.Write(new Vector4(0.0f, 0.5f, 0.5f, 1.0f));
            stream.Write(Color.Red.ToArgb());
            stream.Write(new Vector4(0.5f, -0.5f, 0.5f, 1.0f));
            stream.Write(Color.Blue.ToArgb());
            stream.Write(new Vector4(-0.5f, -0.5f, 0.5f, 1.0f));
            stream.Write(Color.Green.ToArgb());

            // Important: when specifying initial buffer data like this, the buffer will
            // read from the current DataStream position; we must rewind the stream to 
            // the start of the data we just wrote.
            stream.Position = 0;

            // create the buffer description
            BufferDescription bufferDescription = new BufferDescription();
            bufferDescription.BindFlags = BindFlags.VertexBuffer;
            bufferDescription.CpuAccessFlags = CpuAccessFlags.None;
            bufferDescription.OptionFlags = ResourceOptionFlags.None;
            bufferDescription.SizeInBytes = 3 * Marshal.SizeOf(typeof(Vertex));
            bufferDescription.Usage = ResourceUsage.Default;

            // create the vertex buffer
            vertices = new Buffer(Device, stream, bufferDescription);
            stream.Close();
        }

        /// <summary>
        /// Releases the game.
        /// </summary>
        protected override void Release()
        {
            base.Release();

            Device.ClearState();
            effect.Dispose();
            vertices.Dispose();
            layout.Dispose();
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected override void Draw(GameTime gameTime)
        {
            Device.ClearRenderTargetView(GraphicsDeviceManager.Direct3D10.RenderTarget, ClearColor);

            Device.InputAssembler.SetInputLayout(layout);
            Device.InputAssembler.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
            Device.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertices, Marshal.SizeOf(typeof(Vertex)), 0));

            for (int p = 0; p < technique.Description.PassCount; p++)
            {
                pass.Apply();
                Device.Draw(3, 0);
            }

            GraphicsDeviceManager.Direct3D10.SwapChain.Present(0, SlimDX.DXGI.PresentFlags.None);
        }
    }
}
