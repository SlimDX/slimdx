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
using System.Runtime.InteropServices;
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

        Camera camera;

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Device9; }
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

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);

            camera = new Camera();
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

        void RenderParticles(Matrix world, Matrix projection, Matrix view)
        {
            Matrix viewProjection = view * projection;

            effect.Technique = "Position";
            effect.SetValue("matViewProjection", Matrix.Transpose(viewProjection));
            effect.SetValue("matWorld", world);
            effect.SetValue("matView", Matrix.Transpose(view));
            effect.SetValue("tex", texture);
            effect.SetValue("explosion", 3.45f);
            effect.SetValue("turnCount", 4);
            effect.SetValue("diffuse", new Color4(1, 1, 1, 1));

            effect.Begin(FX.None);

            effect.BeginPass(0);

            Device.SetStreamSource(0, vbuffer, 0, Marshal.SizeOf(typeof(Vector3)));
            Device.VertexFormat = VertexFormat.Position;
            Device.Indices = ibuffer;
            Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, Count * Quad.VertexCount, 0, Quad.IndexCount * Count / 3);

            effect.EndPass();
            effect.End();
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

            DateTime current = DateTime.Now;

            float time = (float)current.Second + (float)current.Millisecond / 1000f;

            Matrix world = Matrix.RotationY(-time * 0.5f);
            world *= Matrix.RotationX(75);

            RenderParticles(world, camera.Projection, camera.View);

            Device.EndScene();
        }

        #region Shader Code

        const string src = @"
float4x4 matViewProjection : ViewProjection;
float4x4 matView : View;
float4x4 matWorld : World;
float4 diffuse;
float explosion;
float turnCount;

texture tex;

sampler2D partText = sampler_state
{
   Texture = (tex);
};

struct VS_INPUT 
{
   float4 Position : POSITION0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texture  : TEXCOORD0;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   float3 pos = Input.Position;

   // vertex position by dividing the circle count
   float g = (pos.z) / ( 360 * 3.14 / 180 * 5 );

   // spiral extending
   float extend = g * 3.8f;

   // position vertex
   pos.x = sin( g ) * (extend);
   pos.y = 0;   
   pos.z = cos( g ) * (extend);

   // add some randomization
   pos.x += sin( pos.z * g * 7 ) * 0.103 * extend;
   pos.y += cos( pos.z * g * 3 ) * 0.102 * extend * 1.5f;
   pos.z += cos( pos.z * g * 2 ) * 0.106 * extend;

   // transform to object space
   pos = mul( pos, matWorld );

   // transform to view space
   pos += 4.0f * (Input.Position.x * matView[0] + Input.Position.y * matView[1]);
   
   // sprite transformation
   Output.Position = mul( matViewProjection, float4(pos,1) );
   
   // use xy as texture coordinate
   Output.Texture = Input.Position.xy;
   
   return( Output );
}

float4 ps_main(float2 texCoord:TEXCOORD) : COLOR0
{
   return (1 - pow(dot(texCoord, texCoord), explosion)) * tex2D(partText,texCoord).a * diffuse;
}

technique Position
{
   pass Pass_0
   {
      DESTBLEND = ONE;
      SRCBLEND = ONE;
      ZENABLE = TRUE;
      ZWRITEENABLE = FALSE;
      CULLMODE = NONE;
      ALPHABLENDENABLE = TRUE;

      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }
}
";
        #endregion

        int Count = 1500;
        int vertexSize;

        VertexBuffer vbuffer;
        IndexBuffer ibuffer;
        Effect effect;
        Texture texture;

        /// <summary>
        /// Loads graphical resources.
        /// </summary>
        protected override void LoadContent()
        {
            Device device = this.Device;
            Quad q = new Quad();

            vertexSize = Marshal.SizeOf(typeof(Vector3)) * this.Count * Quad.VertexCount;

            // Build quad array
            ibuffer = new IndexBuffer(device, 4 * this.Count * Quad.IndexCount, Usage.WriteOnly, Pool.Default, false);

            vbuffer = new VertexBuffer(device, vertexSize, Usage.WriteOnly, VertexFormat.Position, Pool.Default);

            using (DataStream s = vbuffer.Lock(0, 0, LockFlags.None))
            {
                Matrix m = Matrix.Identity;

                // order quads by z index
                for (int c = 0; c < this.Count; c++)
                {
                    m = Matrix.Translation(0f, 0f, c);

                    // copy quad vertices
                    for (int vi = 0; vi < Quad.VertexCount; vi++)
                    {
                        // Center texture (cause quad uses -1 to 1 coordinates but we use them as texture coordinate)
                        Vector3 v = Vector3.TransformCoordinate(Vector3.Subtract(q.Vertices[vi] * 0.5f, new Vector3(0.5f, 0.5f, 0)), m);

                        s.Write(v);
                    }
                }

                vbuffer.Unlock();
            }

            // copy quad indices
            using (DataStream s = ibuffer.Lock(0, 0, LockFlags.None))
            {
                for (int c = 0; c < this.Count; c++)
                {
                    for (int i = 0; i < Quad.IndexCount; i++)
                    {
                        s.Write(q.Indices[i] + (Quad.VertexCount * c));
                    }
                }

                ibuffer.Unlock();
            }

            // load shader
            this.effect = Effect.FromString(device, src, ShaderFlags.PartialPrecision);

            // load particle texture
            this.texture = Texture.FromFile(device, "particle.dds");
        }
    }
}
