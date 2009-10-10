/*
* Copyright (c) 2007-2009 SlimDX Group
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
using SlimDX;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

namespace SampleFramework
{
	class Direct3D10Settings : ICloneable
	{
		private int m_AdapterOrdinal;
		public int AdapterOrdinal
		{
			get { return m_AdapterOrdinal; }
			set { m_AdapterOrdinal = value; }
		}

		private DriverType m_DriverType;
		public DriverType DriverType
		{
			get { return m_DriverType; }
			set { m_DriverType = value; }
		}

		private int m_OutputOrdinal;
		public int OutputOrdinal
		{
			get { return m_OutputOrdinal; }
			set { m_OutputOrdinal = value; }
		}

		private SwapChainDescription m_SwapChainDescription;
		public SwapChainDescription SwapChainDescription
		{
			get { return m_SwapChainDescription; }
			set { m_SwapChainDescription = value; }
		}

		private DeviceCreationFlags m_CreationFlags;
		public DeviceCreationFlags CreationFlags
		{
			get { return m_CreationFlags; }
			set { m_CreationFlags = value; }
		}

		private int m_SyncInterval;
		public int SyncInterval
		{
			get { return m_SyncInterval; }
			set { m_SyncInterval = value; }
		}

		private PresentFlags m_PresentFlags;
		public PresentFlags PresentFlags
		{
			get { return m_PresentFlags; }
			set { m_PresentFlags = value; }
		}

		private Format m_DepthStencilFormat;
		public Format DepthStencilFormat
		{
			get { return m_DepthStencilFormat; }
			set { m_DepthStencilFormat = value; }
		}

		public Direct3D10Settings()
		{
			DriverType = DriverType.Hardware;
			PresentFlags = PresentFlags.None;
			DepthStencilFormat = Format.Unknown;
			SyncInterval = 1;
		}

		public Direct3D10Settings Clone()
		{
			Direct3D10Settings clone = new Direct3D10Settings();
			clone.AdapterOrdinal = AdapterOrdinal;
			clone.CreationFlags = CreationFlags;
			clone.DepthStencilFormat = DepthStencilFormat;
			clone.DriverType = DriverType;
			clone.OutputOrdinal = OutputOrdinal;
			clone.PresentFlags = PresentFlags;
			clone.SwapChainDescription = SwapChainDescription;
			clone.SyncInterval = SyncInterval;

			return clone;
		}

		object ICloneable.Clone()
		{
			return Clone();
		}

		public static ModeDescription GetAdapterDisplayMode(int adapterOrdinal, int outputOrdinal)
		{
			OutputInfo10 outputInfo = Enumeration10.GetOutputInfo(adapterOrdinal, outputOrdinal);

			ModeDescription mode = new ModeDescription();
			mode.RefreshRate = new Rational(0, 0);
			mode.Format = Format.R8G8B8A8_UNorm;
			mode.Scaling = DisplayModeScaling.Unspecified;
			mode.ScanlineOrdering = DisplayModeScanlineOrdering.Unspecified;
			mode.Width = 640;
			mode.Height = 480;

			if(outputInfo != null)
			{
				Rectangle rectangle = outputInfo.OutputDescription.DesktopBounds;
				mode.Width = rectangle.Width;
				mode.Height = rectangle.Height;
			}

			if(mode.Format == Format.B8G8R8A8_UNorm)
				mode.Format = Format.R8G8B8A8_UNorm;

			return mode;
		}

		public static Direct3D10Settings BuildOptimalSettings(DeviceSettings settings)
		{
			ModeDescription desktopMode = GetAdapterDisplayMode(0, 0);
			Direct3D10Settings optimal = new Direct3D10Settings();
			SwapChainDescription swapChainDescription = new SwapChainDescription();
			ModeDescription mode = new ModeDescription();
			SampleDescription sample = new SampleDescription();

			optimal.AdapterOrdinal = settings.AdapterOrdinal;
			optimal.DriverType = ConversionMethods.ToDirect3D10(settings.DeviceType);
			optimal.PresentFlags = PresentFlags.None;
			swapChainDescription.IsWindowed = settings.Windowed;
			swapChainDescription.BufferCount = settings.BackBufferCount;
			sample.Count = ConversionMethods.ToDirect3D10(settings.MultisampleType, settings.MultisampleQuality);
			sample.Quality = settings.MultisampleQuality;
			swapChainDescription.SwapEffect = SwapEffect.Discard;

			if(settings.BackBufferWidth == 0 || settings.BackBufferHeight == 0)
			{
				if(settings.Windowed)
				{
					mode.Width = 640;
					mode.Height = 480;
				}
				else
				{
					mode.Width = desktopMode.Width;
					mode.Height = desktopMode.Height;
				}
			}
			else
			{
				mode.Width = settings.BackBufferWidth;
				mode.Height = settings.BackBufferHeight;
			}

			if(ConversionMethods.ToDirect3D10(settings.BackBufferFormat) == Format.Unknown)
				mode.Format = desktopMode.Format;
			else
				mode.Format = ConversionMethods.ToDirect3D10(settings.BackBufferFormat);

			swapChainDescription.Usage = Usage.RenderTargetOutput;
			optimal.DepthStencilFormat = ConversionMethods.ToDirect3D10(settings.DepthStencilFormat);

			if(settings.RefreshRate == 0)
				mode.RefreshRate = new Rational(0, 0);
			else
				mode.RefreshRate = new Rational(settings.RefreshRate, 1);

			if(settings.EnableVSync)
				optimal.SyncInterval = 1;
			else
				optimal.SyncInterval = 0;

			swapChainDescription.SampleDescription = sample;
			swapChainDescription.ModeDescription = mode;
			optimal.SwapChainDescription = swapChainDescription;
			return optimal;
		}

		public static float RankSettingsCombo(SettingsCombo10 combo, Direct3D10Settings optimal)
		{
			float ranking = 0.0f;

			if(combo.AdapterOrdinal == optimal.AdapterOrdinal)
				ranking += 1000.0f;

			if(combo.OutputOrdinal == optimal.OutputOrdinal)
				ranking += 500.0f;

			if(combo.DriverType == optimal.DriverType)
				ranking += 100.0f;

			if(combo.DriverType == DriverType.Hardware)
				ranking += 0.1f;

			if(combo.IsWindowed == optimal.SwapChainDescription.IsWindowed)
				ranking += 10.0f;

			if(combo.BackBufferFormat == optimal.SwapChainDescription.ModeDescription.Format)
				ranking += 1.0f;
			else
			{
				int bitDepthDelta = Math.Abs(ConversionMethods.GetColorBits(combo.BackBufferFormat) -
					ConversionMethods.GetColorBits(optimal.SwapChainDescription.ModeDescription.Format));
				float scale = Math.Max(0.9f - bitDepthDelta * 0.2f, 0.0f);
				ranking += scale;
			}

			for(int i = 0; i < combo.MultisampleCounts.Count; i++)
			{
				int type = combo.MultisampleCounts[i];
				int quality = combo.MultisampleQualities[i];

				if(type == optimal.SwapChainDescription.SampleDescription.Count && quality > optimal.SwapChainDescription.SampleDescription.Quality)
				{
					ranking += 1.0f;
					break;
				}
			}

			foreach(ModeDescription mode in combo.OutputInfo.DisplayModes)
			{
				if(mode.Width == optimal.SwapChainDescription.ModeDescription.Width &&
					mode.Height == optimal.SwapChainDescription.ModeDescription.Height)
				{
					ranking += 1.0f;
					break;
				}
			}

			foreach(ModeDescription mode in combo.OutputInfo.DisplayModes)
			{
				if(Math.Abs(ConversionMethods.ToFloat(mode.RefreshRate) - ConversionMethods.ToFloat(optimal.SwapChainDescription.ModeDescription.RefreshRate)) < 0.1f)
				{
					ranking += 1.0f;
					break;
				}
			}

			return ranking;
		}

		public static Direct3D10Settings BuildValidSettings(SettingsCombo10 combo, Direct3D10Settings input)
		{
			Direct3D10Settings settings = new Direct3D10Settings();
			SwapChainDescription scd = new SwapChainDescription();
			ModeDescription mode = new ModeDescription();
			SampleDescription sample = new SampleDescription();

			ModeDescription bestDisplayMode = FindValidResolution(combo, input);

			if(combo.IsWindowed)
				bestDisplayMode.RefreshRate = new Rational(0, 0);
			else
			{
				Rational match = input.SwapChainDescription.ModeDescription.RefreshRate;
				bestDisplayMode.RefreshRate = new Rational(0, 0);
				if(match != new Rational(0, 0))
				{
					float bestRanking = 100000;
					foreach(ModeDescription displayMode in combo.OutputInfo.DisplayModes)
					{
						if(displayMode.Width != bestDisplayMode.Width ||
							displayMode.Height != bestDisplayMode.Height)
							continue;

						float ranking = Math.Abs(ConversionMethods.ToFloat(displayMode.RefreshRate) - ConversionMethods.ToFloat(match));

						if(ranking < bestRanking)
						{
							bestDisplayMode.RefreshRate = displayMode.RefreshRate;
							bestRanking = ranking;

							if(bestRanking == 0)
								break;
						}
					}
				}
			}

			int bestBackBufferCount = input.SwapChainDescription.BufferCount;
			if(bestBackBufferCount > 3)
				bestBackBufferCount = 3;
			if(bestBackBufferCount < 1)
				bestBackBufferCount = 1;

			int bestCount;
			int bestQuality;
			if(input.SwapChainDescription.SwapEffect != SwapEffect.Discard)
			{
				bestCount = 1;
				bestQuality = 0;
			}
			else
			{
				bestCount = 1;
				bestQuality = 0;

				for(int i = 0; i < combo.MultisampleCounts.Count; i++)
				{
					int type = combo.MultisampleCounts[i];
					int quality = combo.MultisampleQualities[0];

					if(Math.Abs(type - input.SwapChainDescription.SampleDescription.Count) < Math.Abs(bestCount -
						input.SwapChainDescription.SampleDescription.Count))
					{
						bestCount = type;
						bestQuality = Math.Min(quality - 1, input.SwapChainDescription.SampleDescription.Quality);
					}
				}
			}

			int bestSyncInterval = input.SyncInterval;
			if(combo.DriverType == DriverType.Reference)
				bestSyncInterval = 0;

			mode.Width = bestDisplayMode.Width;
			mode.Height = bestDisplayMode.Height;
			mode.Format = combo.BackBufferFormat;
			mode.RefreshRate = bestDisplayMode.RefreshRate;

			sample.Count = bestCount;
			sample.Quality = bestQuality;

			scd.Usage = input.SwapChainDescription.Usage | Usage.RenderTargetOutput;
			scd.BufferCount = bestBackBufferCount;
			scd.SwapEffect = input.SwapChainDescription.SwapEffect;
			scd.IsWindowed = combo.IsWindowed;
			scd.Flags = SwapChainFlags.None;
			scd.ModeDescription = mode;
			scd.SampleDescription = sample;

			settings.AdapterOrdinal = combo.AdapterOrdinal;
			settings.DriverType = combo.DriverType;
			settings.OutputOrdinal = combo.OutputOrdinal;
			settings.SyncInterval = bestSyncInterval;
			settings.DepthStencilFormat = input.DepthStencilFormat;
			settings.CreationFlags = input.CreationFlags;
			settings.SwapChainDescription = scd;

			return settings;
		}

		static ModeDescription FindValidResolution(SettingsCombo10 combo, Direct3D10Settings input)
		{
			ModeDescription bestMode = new ModeDescription();

			if(combo.IsWindowed)
			{
				bestMode.Width = input.SwapChainDescription.ModeDescription.Width;
				bestMode.Height = input.SwapChainDescription.ModeDescription.Height;
				return bestMode;
			}

			int bestRanking = 100000;
			int ranking;
			foreach(ModeDescription mode in combo.OutputInfo.DisplayModes)
			{
				ranking = Math.Abs(mode.Width - input.SwapChainDescription.ModeDescription.Width) +
					Math.Abs(mode.Height - input.SwapChainDescription.ModeDescription.Height);

				if(ranking < bestRanking)
				{
					bestMode = mode;
					bestRanking = ranking;

					if(bestRanking == 0)
						break;
				}
			}

			if(bestMode.Width == 0)
			{
				bestMode.Width = input.SwapChainDescription.ModeDescription.Width;
				bestMode.Height = input.SwapChainDescription.ModeDescription.Height;
			}

			return bestMode;
		}
	}
}
