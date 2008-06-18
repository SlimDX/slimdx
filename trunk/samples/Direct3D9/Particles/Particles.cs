using System;
using System.Collections.Generic;
using System.Text;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework.Particles
{
    class Particles : Sample
    {
        Camera camera;

        public Particles()
        {
            camera = new Camera();
            Initialize("Particles", true, 800, 600);
        }

        private void RenderParticles(Matrix world, Matrix projection, Matrix view)
        {
            Matrix viewProjection = camera.View * camera.Projection;

            effect.Technique = "Position";
            effect.SetValue("matViewProjection", Matrix.Transpose(viewProjection));
            effect.SetValue("matWorld", world);
            effect.SetValue("matView", Matrix.Transpose(camera.View));
            effect.SetValue("tex", texture);
            effect.SetValue("explosion", 3.45f);
            effect.SetValue("turnCount", 4);
            effect.SetValue("diffuse", new Color4(1, 1, 1, 1));

            effect.Begin(FX.None);

            effect.BeginPass(0);

            this.Device.SetStreamSource(0, vbuffer, 0, System.Runtime.InteropServices.Marshal.SizeOf(typeof(Vector3)));
            this.Device.VertexFormat = VertexFormat.Position;
            this.Device.Indices = ibuffer;
            this.Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, this.Count * Quad.VertexCount, 0, Quad.IndexCount * this.Count / 3);

            effect.EndPass();
            effect.End();

        }

        protected override void OnMainLoop(EventArgs e)
        {
            base.OnMainLoop(e);

            this.Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, new Color4(0, 0, 0), 1, 0);

            if (this.Device.BeginScene() == ResultCode.Success)
            {
                DateTime current = DateTime.Now;

                float time = (float)current.Second + (float)current.Millisecond / 1000f;

                Matrix world = Matrix.RotationY(-time * 0.5f);
                world *= Matrix.RotationX(75);

                RenderParticles(world, camera.Projection, camera.View);

                if (this.Device.EndScene() == ResultCode.Success)
                {
                    this.Device.Present();
                }
            }
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

        protected override void OnDeviceReset(EventArgs e)
        {
            base.OnDeviceReset(e);

            Device device = this.Device;
            Quad q = new Quad();

            vertexSize = System.Runtime.InteropServices.Marshal.SizeOf(typeof(Vector3)) * this.Count * Quad.VertexCount;

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
