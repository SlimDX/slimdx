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
using System.Drawing;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Particles
{
    class ParticleSample : Game
    {
        // constants
        const int InitialWidth = 800;
        const int InitialHeight = 600;
        const int ParticleCount = 1500;

        // variables
        Camera camera = new Camera();
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Effect effect;
        Texture texture;

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
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
        /// Initializes a new instance of the <see cref="ParticleSample"/> class.
        /// </summary>
        public ParticleSample()
        {
            // initialize the clear color
            ClearColor = Color.Black;

            // set up the window
            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Particle Sample";
            Window.KeyDown += Window_KeyDown;

            // initialize the camera
            camera.FieldOfView = (float)(Math.PI / 4);
            camera.NearPlane = 1.0f;
            camera.FarPlane = 1000.0f;
            camera.Location = new Vector3(0.0f, 0.0f, -100.0f);
            camera.Target = Vector3.Zero;

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
        /// Loads graphical resources.
        /// </summary>
        protected override void LoadContent()
        {
            // build vertex and index buffers
            vertexBuffer = new VertexBuffer(Device, 4 * Vector3.SizeInBytes * ParticleCount, Usage.WriteOnly, VertexFormat.Position, Pool.Default);
            indexBuffer = new IndexBuffer(Device, 6 * sizeof(int) * ParticleCount, Usage.WriteOnly, Pool.Default, false);

            // write the vertices to the vertex buffer
            using (DataStream stream = vertexBuffer.Lock(0, 0, LockFlags.None))
            {
                // create each particle
                for (int particle = 0; particle < ParticleCount; particle++)
                {
                    // create a translation matrix based upon the index of the particle
                    Matrix translation = Matrix.Translation(0.0f, 0.0f, particle);

                    // upper left corner
                    Vector3 vertex = Vector3.TransformCoordinate(new Vector3(-1.0f, -1.0f, 0.0f), translation);
                    stream.Write(vertex);

                    // upper right corner
                    vertex = Vector3.TransformCoordinate(new Vector3(-1.0f, 0.0f, 0.0f), translation);
                    stream.Write(vertex);

                    // lower right corner
                    vertex = Vector3.TransformCoordinate(new Vector3(0.0f, -1.0f, 0.0f), translation);
                    stream.Write(vertex);

                    // lower left corner
                    vertex = Vector3.TransformCoordinate(new Vector3(0.0f, 0.0f, 0.0f), translation);
                    stream.Write(vertex);
                }

                // unlock the vertex buffer
                vertexBuffer.Unlock();
            }

            // write the indices to the index buffer
            using (DataStream stream = indexBuffer.Lock(0, 0, LockFlags.None))
            {
                // create indices for each particle
                for (int particle = 0; particle < ParticleCount; particle++)
                {
                    // write each index
                    stream.Write(0 + (4 * particle));
                    stream.Write(1 + (4 * particle));
                    stream.Write(2 + (4 * particle));
                    stream.Write(2 + (4 * particle));
                    stream.Write(1 + (4 * particle));
                    stream.Write(3 + (4 * particle));
                }

                // unlock the index buffer
                indexBuffer.Unlock();
            }

            // load the effect and texture
            effect = Effect.FromFile(Device, "particle.fx", ShaderFlags.None);
            texture = Texture.FromFile(Device, "particle.dds");

            // update the camera
            camera.AspectRatio = (float)Window.Width / Window.Height;
        }

        /// <summary>
        /// Unloads graphical resources.
        /// </summary>
        protected override void UnloadContent()
        {
            // release graphical resources
            vertexBuffer.Dispose();
            indexBuffer.Dispose();
            effect.Dispose();
            texture.Dispose();
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected override void Draw(GameTime gameTime)
        {
            // start the scene
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            // calculate the world matrix
            Matrix worldMatrix = Matrix.RotationY((float)gameTime.TotalGameTime * -0.5f) * Matrix.RotationX(75.0f);

            // draw the particles
            DrawParticles(worldMatrix, camera.ViewMatrix, camera.ProjectionMatrix);

            // end the scene
            Device.EndScene();
        }

        /// <summary>
        /// Draws the particles.
        /// </summary>
        /// <param name="worldMatrix">The world matrix.</param>
        /// <param name="viewMatrix">The view matrix.</param>
        /// <param name="projectionMatrix">The projection matrix.</param>
        void DrawParticles(Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix)
        {
            // build up the view projection matrix
            Matrix viewProjectionMatrix = viewMatrix * projectionMatrix;

            // set effect values
            effect.Technique = "Position";
            effect.SetValue("viewProjectionMatrix", Matrix.Transpose(viewProjectionMatrix));
            effect.SetValue("worldMatrix", worldMatrix);
            effect.SetValue("viewMatrix", Matrix.Transpose(viewMatrix));
            effect.SetValue("particleTexture", texture);
            effect.SetValue("explosion", 3.45f);
            effect.SetValue("diffuseColor", new Color4(1, 1, 1, 1));

            // start the effect
            effect.Begin();
            effect.BeginPass(0);

            // draw the particles
            Device.SetStreamSource(0, vertexBuffer, 0, Vector3.SizeInBytes);
            Device.VertexFormat = VertexFormat.Position;
            Device.Indices = indexBuffer;
            Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, ParticleCount * 4, 0, ParticleCount * 2);

            // end the effect
            effect.EndPass();
            effect.End();
        }
    }
}
