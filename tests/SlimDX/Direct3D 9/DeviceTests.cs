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

using NUnit.Framework;

using SlimDX;
using SlimDX.Direct3D9;

namespace SlimDXTests
{
	[TestFixture]
	public class DeviceTests
	{
		Form m_window;
		Direct3D m_direct3D;
		Device m_device;
		PresentParameters m_d3dpp;

		[TestFixtureSetUp]
		public void SetUp()
		{
			m_window = new Form();
			m_direct3D = new Direct3D();

			m_d3dpp = new PresentParameters();
			m_d3dpp.DeviceWindowHandle = m_window.Handle;
			m_d3dpp.AutoDepthStencilFormat = Format.D16;
			m_d3dpp.EnableAutoDepthStencil = true;

			CreateFlags createFlags = CreateFlags.SoftwareVertexProcessing | CreateFlags.FpuPreserve;
			m_device = new Device(m_direct3D, 0, DeviceType.Reference, m_window.Handle, createFlags, m_d3dpp);
		}

		[TestFixtureTearDown]
		public void TearDown()
		{
			m_device.Dispose();
			m_direct3D.Dispose();
			m_window.Dispose();
		}

		[Test]
		[ExpectedException(typeof(Direct3D9Exception), MatchType = MessageMatch.Contains, ExpectedMessage = "D3DERR_INVALIDCALL")]
		public void EndSceneFail()
		{
			m_device.EndScene();
		}

		[Test]
		public void BeginEndScene()
		{
			m_device.BeginScene();
			m_device.EndScene();
		}

		[Test]
		public void Clear()
		{
			m_device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, 0, 0.0f, 0);
		}

		[Test]
		[ExpectedException(typeof(Direct3D9Exception), MatchType = MessageMatch.Contains, ExpectedMessage = "D3DERR_INVALIDCALL")]
		public void ClearFail()
		{
			m_device.Clear(ClearFlags.Target | ClearFlags.Target | ClearFlags.Stencil, 0, 0.0f, 0);
		}

		[Test]
		public void Present()
		{
			m_device.Present();
		}

		[Test]
		public void Reset()
		{
			m_device.Reset(m_d3dpp);
		}

		[Test]
		public void RenderStates()
		{
			//Just spam out a bunch of render states, there shouldn't be any exceptions
			//This is intended to catch casting issues
			bool blendEnable = true;
			Compare alphaFunc = Compare.Always;
			int alphaRef = 50;
			float fogStart = 500.0f;

			m_device.SetRenderState(RenderState.AlphaBlendEnable, blendEnable);
			m_device.SetRenderState(RenderState.AlphaFunc, alphaFunc);
			m_device.SetRenderState(RenderState.AlphaRef, alphaRef);
			m_device.SetRenderState(RenderState.FogStart, fogStart);

			bool returnedBlendEnable = m_device.GetRenderState<bool>(RenderState.AlphaBlendEnable);
			Compare returnedAlphaFunc = m_device.GetRenderState<Compare>(RenderState.AlphaFunc);
			int returnedAlphaRef = m_device.GetRenderState<int>(RenderState.AlphaRef);
			float returnedFogStart = m_device.GetRenderState<float>(RenderState.FogStart);

			Assert.AreEqual(blendEnable, returnedBlendEnable);
			Assert.AreEqual(alphaFunc, returnedAlphaFunc);
			Assert.AreEqual(alphaRef, returnedAlphaRef);
			Assert.AreEqual(fogStart, returnedFogStart);
		}

		[Test]
		public void SamplerStates()
		{
			TextureAddress addressMode = TextureAddress.Clamp;
			TextureFilter minFilter = TextureFilter.Linear;
			int aniso = 2;
			float bias = 0.2f;

			m_device.SetSamplerState(0, SamplerState.AddressU, addressMode);
			m_device.SetSamplerState(0, SamplerState.MinFilter, minFilter);
			m_device.SetSamplerState(0, SamplerState.MaxAnisotropy, aniso);
			m_device.SetSamplerState(0, SamplerState.MipMapLodBias, bias);

			TextureAddress returnedAddressMode = m_device.GetSamplerState<TextureAddress>(0, SamplerState.AddressU);
			TextureFilter returnedMinFilter = m_device.GetSamplerState<TextureFilter>(0, SamplerState.MinFilter);
			int returnedAniso = m_device.GetSamplerState<int>(0, SamplerState.MaxAnisotropy);
			float returnedBias = m_device.GetSamplerState<float>(0, SamplerState.MipMapLodBias);

			Assert.AreEqual(addressMode, returnedAddressMode);
			Assert.AreEqual(minFilter, returnedMinFilter);
			Assert.AreEqual(aniso, returnedAniso);
			Assert.AreEqual(bias, returnedBias);
		}

		[Test]
		public void TextureStageStates()
		{
			TextureOperation texOp = TextureOperation.Add;
			float envMat00 = 0.4f;
			int texCoordIndex = 1;

			m_device.SetTextureStageState(0, TextureStage.ColorOperation, texOp);
			m_device.SetTextureStageState(0, TextureStage.BumpEnvironmentMat00, envMat00);
			m_device.SetTextureStageState(0, TextureStage.TexCoordIndex, texCoordIndex);

			TextureOperation returnedTexOp = m_device.GetTextureStageState<TextureOperation>(0, TextureStage.ColorOperation);
			float returnedEnvMat00 = m_device.GetTextureStageState<float>(0, TextureStage.BumpEnvironmentMat00);
			int returnedTexCoordIndex = m_device.GetTextureStageState<int>(0, TextureStage.TexCoordIndex);

			Assert.AreEqual(texOp, returnedTexOp);
			Assert.AreEqual(envMat00, returnedEnvMat00);
			Assert.AreEqual(texCoordIndex, returnedTexCoordIndex);
		}

		[Test]
		public void Texture()
		{
			using(Texture texture = new Texture(m_device, 32, 32, 0, Usage.None, Format.R8G8B8, Pool.Default))
			{
				m_device.SetTexture(0, texture);
				Texture returned = (Texture) m_device.GetTexture(0);
				Assert.AreSame(texture, returned);
			}
		}

		[Test]
		public void StreamSources()
		{
			using(VertexBuffer vb = new VertexBuffer(m_device, 256, Usage.None, VertexFormat.None, Pool.Default))
			{
				int offset = 0;
				int stride = 32;
				m_device.SetStreamSource(0, vb, offset, stride);

				int frequency = 5;
				StreamSource source = StreamSource.IndexedData;
				m_device.SetStreamSourceFrequency(0, frequency, StreamSource.IndexedData);

				VertexBuffer returnedVb;
				int returnedOffset;
				int returnedStride;
				m_device.GetStreamSource(0, out returnedVb, out returnedOffset, out returnedStride);

				int returnedFrequency;
				StreamSource returnedSource;
				m_device.GetStreamSourceFrequency(0, out returnedFrequency, out returnedSource);

				Assert.AreSame(vb, returnedVb);
				Assert.AreEqual(offset, returnedOffset);
				Assert.AreEqual(stride, returnedStride);

				Assert.AreEqual(source, returnedSource);
				Assert.AreEqual(frequency, returnedFrequency);
			}
		}

		[Test]
		public void Transform()
		{
			Matrix matrix = TestUtils.MakeRandomMatrix();
			Matrix matrix2 = TestUtils.MakeRandomMatrix();

			m_device.SetTransform(TransformState.World, matrix);
			m_device.SetTransform(TransformState.View, matrix);
			m_device.MultiplyTransform(TransformState.View, matrix2);
			Matrix returnedMatrix = m_device.GetTransform(TransformState.World);
			Matrix returnedMultMatrix = m_device.GetTransform(TransformState.View);

			Assert.AreEqual(matrix, returnedMatrix);
			Assert.AreEqual(matrix * matrix2, returnedMultMatrix);
		}

		[Test]
		public void RenderTarget()
		{
			using(Surface target = Surface.CreateRenderTarget(m_device, 64, 64, Format.A8R8G8B8, MultisampleType.None, 0, false))
			{
				m_device.SetRenderTarget(0, target);
				Surface returnedTarget = m_device.GetRenderTarget(0);
				Assert.AreSame(target, returnedTarget);
			}
		}

		[Test]
		public void ClipPlane()
		{
			Plane plane = TestUtils.MakeRandomPlane();

			m_device.SetClipPlane(0, plane);
			Plane returnedPlane = m_device.GetClipPlane(0);

			Assert.AreEqual(plane, returnedPlane);
		}

		[Test]
		public void Light()
		{
			bool enable = true;
			Light light = new Light();
			light.Ambient = new Color4(Color.DarkOliveGreen);
			light.Falloff = 5.0f;
			light.Range = 100.0f;
			light.Type = LightType.Spot;
			
			m_device.EnableLight(0, enable);
			m_device.SetLight(0, light);

			bool returnedEnable = m_device.IsLightEnabled(0);
			Light returnedLight = m_device.GetLight(0);

			Assert.AreEqual(enable, returnedEnable);
			Assert.AreEqual(light, returnedLight);
		}

		[Test]
		public void StateBlock()
		{
			float fogStart = 100.0f;
			float fogEnd = 1000.0f;

			m_device.BeginStateBlock();
			m_device.SetRenderState(RenderState.FogStart, fogStart);
			m_device.SetRenderState(RenderState.FogEnd, fogEnd);

			using(StateBlock stateBlock = m_device.EndStateBlock())
			{
				m_device.SetRenderState(RenderState.FogStart, 0.0f);
				m_device.SetRenderState(RenderState.FogEnd, 0.0f);

				float x = m_device.GetRenderState(RenderState.FogStart);

				stateBlock.Apply();

				float returnedFogStart = m_device.GetRenderState<float>(RenderState.FogStart);
				float returnedFogEnd = m_device.GetRenderState<float>(RenderState.FogEnd);

				Assert.AreEqual(fogStart, returnedFogStart);
				Assert.AreEqual(fogEnd, returnedFogEnd);
			}
		}

		[Test]
		public void Palette()
		{
			PaletteEntry[] palette = new PaletteEntry[256];
			Random rand = new Random(TestUtils.RandomSeed);

			for(int i = 0; i < palette.Length; ++i)
			{
				palette[i].Red = (byte) rand.Next(0, 255);
				palette[i].Blue = (byte) rand.Next(0, 255);
				palette[i].Green = (byte) rand.Next(0, 255);
			}

			m_device.SetPaletteEntries(0, palette);
			PaletteEntry[] returnedPalette = m_device.GetPaletteEntries(0);

			Assert.AreEqual(palette, returnedPalette);
		}

		[Test]
		[ExpectedException(typeof(ArgumentException))]
		public void PaletteSizeFail()
		{
			PaletteEntry[] palette = new PaletteEntry[12];
			m_device.SetPaletteEntries(0, palette);
		}
	}
}
