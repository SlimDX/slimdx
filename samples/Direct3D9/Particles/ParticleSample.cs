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
        const int InitialWidth = 800;
        const int InitialHeight = 600;
        const int ParticleCount = 1500;

        Camera camera = new Camera();
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Effect effect;
        Texture texture;

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public ParticleSample()
        {
            ClearColor = Color.Black;

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Particle Sample";
            Window.KeyDown += Window_KeyDown;

            camera.FieldOfView = (float)(Math.PI / 4);
            camera.NearPlane = 1.0f;
            camera.FarPlane = 1000.0f;
            camera.Location = new Vector3(0.0f, 0.0f, -100.0f);
            camera.Target = Vector3.Zero;

            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();
        }

        protected override void LoadContent()
        {
            vertexBuffer = new VertexBuffer(Device, 4 * Vector3.SizeInBytes * ParticleCount, Usage.WriteOnly, VertexFormat.Position, Pool.Default);
            indexBuffer = new IndexBuffer(Device, 6 * sizeof(int) * ParticleCount, Usage.WriteOnly, Pool.Default, false);

            using (DataStream stream = vertexBuffer.Lock(0, 0, LockFlags.None))
            {
                for (int particle = 0; particle < ParticleCount; particle++)
                {
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

                vertexBuffer.Unlock();
            }

            using (DataStream stream = indexBuffer.Lock(0, 0, LockFlags.None))
            {
                for (int particle = 0; particle < ParticleCount; particle++)
                {
                    stream.Write(0 + (4 * particle));
                    stream.Write(1 + (4 * particle));
                    stream.Write(2 + (4 * particle));
                    stream.Write(2 + (4 * particle));
                    stream.Write(1 + (4 * particle));
                    stream.Write(3 + (4 * particle));
                }

                indexBuffer.Unlock();
            }

            effect = Effect.FromFile(Device, "particle.fx", ShaderFlags.None);
            texture = Texture.FromFile(Device, "particle.dds");

            camera.AspectRatio = (float)Window.Width / Window.Height;
        }

        protected override void UnloadContent()
        {
            vertexBuffer.Dispose();
            indexBuffer.Dispose();
            effect.Dispose();
            texture.Dispose();
        }

        protected override void Draw(GameTime gameTime)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            Matrix worldMatrix = Matrix.RotationY((float)gameTime.TotalGameTime * -0.5f) * Matrix.RotationX(75.0f);

            DrawParticles(worldMatrix, camera.ViewMatrix, camera.ProjectionMatrix);

            Device.EndScene();
        }

        void DrawParticles(Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix)
        {
            Matrix viewProjectionMatrix = viewMatrix * projectionMatrix;

            effect.Technique = "Position";
            effect.SetValue("viewProjectionMatrix", Matrix.Transpose(viewProjectionMatrix));
            effect.SetValue("worldMatrix", worldMatrix);
            effect.SetValue("viewMatrix", Matrix.Transpose(viewMatrix));
            effect.SetTexture("particleTexture", texture);
            effect.SetValue("explosion", 3.45f);
            effect.SetValue("diffuseColor", new Color4(1, 1, 1, 1));

            effect.Begin();
            effect.BeginPass(0);

            Device.SetStreamSource(0, vertexBuffer, 0, Vector3.SizeInBytes);
            Device.VertexFormat = VertexFormat.Position;
            Device.Indices = indexBuffer;
            Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, ParticleCount * 4, 0, ParticleCount * 2);

            effect.EndPass();
            effect.End();
        }
    }
}
