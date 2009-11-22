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

namespace SlimDX.SampleFramework {
	/// <summary>
	/// Provides creation and management functionality for a Direct3D10 rendering device and related objects.
	/// </summary>
	public class DeviceContext10 : IDisposable {
		#region Public Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="DeviceContext10"/> class.
		/// </summary>
		/// <param name="handle">The window handle to associate with the device.</param>
		/// <param name="settings">The settings used to configure the device.</param>
		internal DeviceContext10( IntPtr handle, DeviceSettings10 settings ) {
			if( handle == IntPtr.Zero )
				throw new ArgumentException( "Value must be a valid window handle.", "handle" );
			if( settings == null )
				throw new ArgumentNullException( "settings" );

			this.settings = settings;

			factory = new SlimDX.DXGI.Factory();
			device = new SlimDX.Direct3D10.Device( factory.GetAdapter( settings.AdapterOrdinal ), SlimDX.Direct3D10.DriverType.Hardware, settings.CreationFlags );
			swapChain = new SlimDX.DXGI.SwapChain( factory, device, new SlimDX.DXGI.SwapChainDescription {
				BufferCount = 1,
				Flags = SlimDX.DXGI.SwapChainFlags.None,
				IsWindowed = true,
				ModeDescription = new SlimDX.DXGI.ModeDescription( settings.Width, settings.Height, new Rational( 60, 1 ), SlimDX.DXGI.Format.R8G8B8A8_UNorm ),
				OutputHandle = handle,
				SampleDescription = new SlimDX.DXGI.SampleDescription( 1, 0 ),
				SwapEffect = SlimDX.DXGI.SwapEffect.Discard,
				Usage = SlimDX.DXGI.Usage.RenderTargetOutput
			} );
		}

		/// <summary>
		/// Performs object finalization.
		/// </summary>
		~DeviceContext10() {
			Dispose( false );
		}

		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		public void Dispose() {
			Dispose( true );
			GC.SuppressFinalize( this );
		}

		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		protected virtual void Dispose( bool disposeManagedResources ) {
			if( disposeManagedResources ) {
				swapChain.Dispose();
				device.Dispose();
				factory.Dispose();
			}
		}

		/// <summary>
		/// Gets the underlying DXGI factory.
		/// </summary>
		public SlimDX.DXGI.Factory Factory {
			get {
				return factory;
			}
		}

		/// <summary>
		/// Gets the underlying Direct3D10 device.
		/// </summary>
		public SlimDX.Direct3D10.Device Device {
			get {
				return device;
			}
		}

		/// <summary>
		/// Gets the underlying DXGI swap chain.
		/// </summary>
		public SlimDX.DXGI.SwapChain SwapChain {
			get {
				return swapChain;
			}
		}

		#endregion
		#region Implementation Detail

		DeviceSettings10 settings;

		SlimDX.DXGI.Factory factory;
		SlimDX.Direct3D10.Device device;
		SlimDX.DXGI.SwapChain swapChain;

		#endregion
	}
}
