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
using SlimDX.Direct3D9;
using SlimDX;
using System;

namespace SkinnedMesh
{
    class SkinnedMesh : Game
    {
        const int InitialWidth = 800;
        const int InitialHeight = 600;

        Effect effect;
        Frame rootFrame;
        AnimationController animationController;
        BoundingSphere boundingSphere;
        Sprite textSprite;
        Matrix projectionMatrix;
        Matrix viewMatrix;

        float x, y, z;

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public SkinnedMesh()
        {
            ClearColor = Color.FromArgb(0, 45, 50, 170);

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Skinned Mesh Sample";
            Window.KeyDown += Window_KeyDown;

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
            else if (e.KeyCode == Keys.W)
                z += 1.0f;
            else if (e.KeyCode == Keys.S)
                z -= 1.0f;
            else if (e.KeyCode == Keys.A)
                x -= 1.0f;
            else if (e.KeyCode == Keys.D)
                x += 1.0f;
            else if (e.KeyCode == Keys.Q)
                y += 1.0f;
            else if (e.KeyCode == Keys.E)
                y -= 1.0f;
        }

        protected override void Initialize()
        {
            base.Initialize();

            effect = Effect.FromFile(Device, "SkinnedMesh.fx", ShaderFlags.None);
            rootFrame = Frame.LoadHierarchyFromX(Device, "tiny.x", MeshFlags.Managed, new CustomAllocateHierarchy(), null, out animationController);

            SetupBoneMatrices(rootFrame);
            boundingSphere = Frame.CalculateBoundingSphere(rootFrame);
        }

        protected override void LoadContent()
        {
            base.LoadContent();

            effect.OnResetDevice();
            textSprite = new Sprite(Device);

            Device.SetRenderState(RenderState.Lighting, true);
            Device.SetRenderState(RenderState.DitherEnable, true);
            Device.SetRenderState(RenderState.ZEnable, true);
            Device.SetRenderState(RenderState.CullMode, Cull.None);
            Device.SetRenderState(RenderState.Ambient, 0x33333333);
            Device.SetRenderState(RenderState.NormalizeNormals, true);
            Device.SetSamplerState(0, SamplerState.MagFilter, TextureFilter.Linear);
            Device.SetSamplerState(0, SamplerState.MinFilter, TextureFilter.Linear);

            projectionMatrix = Matrix.PerspectiveFovLH((float)Math.PI / 4, (float)GraphicsDeviceManager.ScreenWidth / (float)GraphicsDeviceManager.ScreenHeight,
                boundingSphere.Radius / 64.0f, boundingSphere.Radius * 200.0f);

            viewMatrix = Matrix.LookAtLH(new Vector3(0.0f, 0.0f, -2 * boundingSphere.Radius), new Vector3(0.0f, 0.0f, 0.0f), new Vector3(0.0f, 1.0f, 0.0f));
        }

        protected override void UnloadContent()
        {
            base.UnloadContent();

            effect.OnLostDevice();
            textSprite.Dispose();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                Frame.DestroyHierarchy(rootFrame, new CustomAllocateHierarchy());
                animationController.Dispose();
                effect.Dispose();
            }

            base.Dispose(disposing);
        }

        protected override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            if (animationController != null)
                animationController.AdvanceTime(gameTime.ElapsedGameTime, null);

            Matrix worldMatrix = Matrix.Translation(new Vector3(x, y, z));
            UpdateFrameMatrices(rootFrame, worldMatrix);
        }

        protected override void Draw(GameTime gameTime)
        {
            effect.SetValue("ViewProjectionMatrix", viewMatrix * projectionMatrix);
            effect.SetValue("LightDirection", Vector4.Normalize(new Vector4(0.0f, 1.0f, -1.0f, 0.0f)));

            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            DrawFrame(rootFrame);

            Device.EndScene();
        }

        void UpdateFrameMatrices(Frame frame, Matrix matrix)
        {
            CustomFrame cframe = frame as CustomFrame;

            cframe.CombinedTransform = cframe.TransformationMatrix * matrix;

            if (cframe.Sibling != null)
                UpdateFrameMatrices(cframe.Sibling, matrix);

            if (cframe.FirstChild != null)
                UpdateFrameMatrices(cframe.FirstChild, cframe.CombinedTransform);
        }

        void DrawFrame(Frame frame)
        {
            MeshContainer meshContainer = frame.MeshContainer;
            while (meshContainer != null)
            {
                DrawMeshContainer(meshContainer as CustomMeshContainer, frame as CustomFrame);
                meshContainer = meshContainer.NextMeshContainer;
            }

            if (frame.Sibling != null)
                DrawFrame(frame.Sibling);

            if (frame.FirstChild != null)
                DrawFrame(frame.FirstChild);
        }

        Matrix[] boneMatrices;

        void DrawMeshContainer(CustomMeshContainer meshContainer, CustomFrame frame)
        {
            boneMatrices = new Matrix[meshContainer.PaletteEntries];

            BoneCombination[] combinations = meshContainer.BoneCombinations;
            for (int i = 0; i < combinations.Length; i++)
            {
                for (int pe = 0; pe < meshContainer.PaletteEntries; pe++)
                {
                    int index = combinations[i].BoneIds[pe];
                    if (index >= 0)
                    {
                        boneMatrices[pe] = meshContainer.BoneOffsets[index] * meshContainer.BoneMatricesLookup[index].TransformationMatrix * viewMatrix;
                    }
                }

                effect.SetValue("WorldMatrices", boneMatrices);

                Color4 ambient = meshContainer.GetMaterials()[combinations[i].AttributeId].MaterialD3D.Ambient;
                Color4 diffuse = meshContainer.GetMaterials()[combinations[i].AttributeId].MaterialD3D.Diffuse;
                Color4 emissive = meshContainer.GetMaterials()[combinations[i].AttributeId].MaterialD3D.Emissive;

                Color4 finalColor = Color4.Modulate(ambient, new Color4(0.25f, 0.25f, 0.25f, 1.0f)) + emissive;

                effect.SetValue("MaterialAmbient", finalColor);
                effect.SetValue("MaterialDiffuse", diffuse);

                Device.SetTexture(0, meshContainer.Textures[combinations[i].AttributeId]);
                effect.SetValue("CurrentBoneCount", meshContainer.Influences - 1);

                int passes = effect.Begin();
                for (int pass = 0; pass < passes; pass++)
                {
                    effect.BeginPass(pass);

                    meshContainer.MeshData.Mesh.DrawSubset(i);

                    effect.EndPass();
                }

                effect.End();
            }
        }

        void SetupBoneMatrices(Frame frame)
        {
            if (frame.MeshContainer != null)
                SetupBoneMatrices(frame.MeshContainer as CustomMeshContainer);

            if (frame.Sibling != null)
                SetupBoneMatrices(frame.Sibling);

            if (frame.FirstChild != null)
                SetupBoneMatrices(frame.FirstChild);
        }

        void SetupBoneMatrices(CustomMeshContainer meshContainer)
        {
            if (meshContainer.SkinInfo == null)
                return;

            meshContainer.BoneMatricesLookup = new CustomFrame[meshContainer.SkinInfo.BoneCount];
            for (int i = 0; i < meshContainer.SkinInfo.BoneCount; i++)
            {
                CustomFrame frame = (CustomFrame)rootFrame.FindChild(meshContainer.SkinInfo.GetBoneName(i));
                meshContainer.BoneMatricesLookup[i] = frame;
            }
        }
    }
}
