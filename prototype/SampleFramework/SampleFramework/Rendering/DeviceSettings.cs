using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D9;
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using SlimDX;

namespace SampleFramework
{
    /// <summary>
    /// Contains settings for creating a 3D device.
    /// </summary>
    public class DeviceSettings : ICloneable
    {
        /// <summary>
        /// Contains settings for a Direct3D9 device.
        /// </summary>
        public class Direct3D9Settings : ICloneable
        {
            /// <summary>
            /// Gets or sets the adapter ordinal.
            /// </summary>
            /// <value>The adapter ordinal.</value>
            public int AdapterOrdinal
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the type of the device.
            /// </summary>
            /// <value>The type of the device.</value>
            public DeviceType DeviceType
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the adapter format.
            /// </summary>
            /// <value>The adapter format.</value>
            public SlimDX.Direct3D9.Format AdapterFormat
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the behavior flags.
            /// </summary>
            /// <value>The behavior flags.</value>
            public CreateFlags CreationFlags
            {
                get;
                set;
            }

            /// <summary>
            /// Gets the present parameters.
            /// </summary>
            /// <value>The present parameters.</value>
            public PresentParameters PresentParameters
            {
                get;
                private set;
            }

            /// <summary>
            /// Initializes a new instance of the <see cref="Direct3D9Settings"/> class.
            /// </summary>
            internal Direct3D9Settings()
            {
                // set default values
                PresentParameters = new PresentParameters();
                DeviceType = DeviceType.Hardware;
                PresentParameters.Windowed = true;
                AdapterFormat = SlimDX.Direct3D9.Format.Unknown;
                CreationFlags = CreateFlags.HardwareVertexProcessing;
                PresentParameters.BackBufferFormat = SlimDX.Direct3D9.Format.Unknown;
                PresentParameters.BackBufferCount = 1;
                PresentParameters.Multisample = MultisampleType.None;
                PresentParameters.SwapEffect = SlimDX.Direct3D9.SwapEffect.Discard;
                PresentParameters.AutoDepthStencilFormat = SlimDX.Direct3D9.Format.Unknown;
                PresentParameters.PresentFlags = SlimDX.Direct3D9.PresentFlags.DiscardDepthStencil;
                PresentParameters.PresentationInterval = PresentInterval.Default;
            }

            /// <summary>
            /// Creates a new object that is a copy of the current instance.
            /// </summary>
            /// <returns>
            /// A new object that is a copy of this instance.
            /// </returns>
            public Direct3D9Settings Clone()
            {
                // clone the object
                Direct3D9Settings result = new Direct3D9Settings();
                result.AdapterFormat = AdapterFormat;
                result.AdapterOrdinal = AdapterOrdinal;
                result.CreationFlags = CreationFlags;
                result.DeviceType = DeviceType;
                result.PresentParameters = PresentParameters.Clone();

                // return the result
                return result;
            }

            /// <summary>
            /// Creates a new object that is a copy of the current instance.
            /// </summary>
            /// <returns>
            /// A new object that is a copy of this instance.
            /// </returns>
            object ICloneable.Clone()
            {
                // call the overload
                return Clone();
            }
        }

        /// <summary>
        /// Contains settings for a Direct3D10 device.
        /// </summary>
        public class Direct3D10Settings : ICloneable
        {
            /// <summary>
            /// Gets or sets the adapter ordinal.
            /// </summary>
            /// <value>The adapter ordinal.</value>
            public int AdapterOrdinal
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the type of the driver.
            /// </summary>
            /// <value>The type of the driver.</value>
            public DriverType DriverType
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the output.
            /// </summary>
            /// <value>The output.</value>
            public int Output
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the swap chain flags.
            /// </summary>
            /// <value>The swap chain flags.</value>
            public SwapChainFlags SwapChainFlags
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the buffer count.
            /// </summary>
            /// <value>The buffer count.</value>
            public int BufferCount
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the width of the buffer.
            /// </summary>
            /// <value>The width of the buffer.</value>
            public int BufferWidth
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the height of the buffer.
            /// </summary>
            /// <value>The height of the buffer.</value>
            public int BufferHeight
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the buffer format.
            /// </summary>
            /// <value>The buffer format.</value>
            public SlimDX.DXGI.Format BufferFormat
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the refresh rate.
            /// </summary>
            /// <value>The refresh rate.</value>
            public Rational RefreshRate
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the scanline ordering.
            /// </summary>
            /// <value>The scanline ordering.</value>
            public ScanlineOrdering ScanlineOrdering
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the scaling settings.
            /// </summary>
            /// <value>The scaling settings.</value>
            public DisplayModeScaling Scaling
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets a value indicating whether the device is windowed.
            /// </summary>
            /// <value>
            /// 	<c>true</c> if the device is windowed; otherwise, <c>false</c>.
            /// </value>
            public bool IsWindowed
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the swap effect.
            /// </summary>
            /// <value>The swap effect.</value>
            public SlimDX.DXGI.SwapEffect SwapEffect
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the multisample count.
            /// </summary>
            /// <value>The multisample count.</value>
            public int MultisampleCount
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the multisample quality.
            /// </summary>
            /// <value>The multisample quality.</value>
            public int MultisampleQuality
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the creation flags.
            /// </summary>
            /// <value>The creation flags.</value>
            public DeviceCreationFlags CreationFlags
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the presentation flags.
            /// </summary>
            /// <value>The presentation flags.</value>
            public SlimDX.DXGI.PresentFlags PresentFlags
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets a value indicating whether a depth stencil surface should automatically be created.
            /// </summary>
            /// <value>
            /// 	<c>true</c> if a depth stencil surface should automatically be created; otherwise, <c>false</c>.
            /// </value>
            public bool AutoCreateDepthStencil
            {
                get;
                set;
            }

            /// <summary>
            /// Gets or sets the auto depth stencil format.
            /// </summary>
            /// <value>The auto depth stencil format.</value>
            public SlimDX.DXGI.Format AutoDepthStencilFormat
            {
                get;
                set;
            }

            /// <summary>
            /// Initializes a new instance of the <see cref="Direct3D10Settings"/> class.
            /// </summary>
            internal Direct3D10Settings()
            {
            }

            /// <summary>
            /// Creates a new object that is a copy of the current instance.
            /// </summary>
            /// <returns>
            /// A new object that is a copy of this instance.
            /// </returns>
            public Direct3D10Settings Clone()
            {
                // clone the object
                Direct3D10Settings result = new Direct3D10Settings();
                result.AdapterOrdinal = AdapterOrdinal;
                result.AutoCreateDepthStencil = AutoCreateDepthStencil;
                result.AutoDepthStencilFormat = AutoDepthStencilFormat;
                result.BufferCount = BufferCount;
                result.BufferFormat = BufferFormat;
                result.BufferHeight = BufferHeight;
                result.BufferWidth = BufferWidth;
                result.CreationFlags = CreationFlags;
                result.DriverType = DriverType;
                result.IsWindowed = IsWindowed;
                result.MultisampleCount = MultisampleCount;
                result.MultisampleQuality = MultisampleQuality;
                result.Output = Output;
                result.PresentFlags = PresentFlags;
                result.RefreshRate = RefreshRate;
                result.Scaling = Scaling;
                result.ScanlineOrdering = ScanlineOrdering;
                result.SwapChainFlags = SwapChainFlags;
                result.SwapEffect = SwapEffect;
                
                // return the result
                return result;
            }

            /// <summary>
            /// Creates a new object that is a copy of the current instance.
            /// </summary>
            /// <returns>
            /// A new object that is a copy of this instance.
            /// </returns>
            object ICloneable.Clone()
            {
                // call the overload
                return Clone();
            }
        }

        /// <summary>
        /// Gets or sets the device version.
        /// </summary>
        /// <value>The device version.</value>
        public DeviceVersion DeviceVersion
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the Direct3D9 specific settings.
        /// </summary>
        /// <value>The Direct3D9 specific settings.</value>
        public Direct3D9Settings Direct3D9
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the Direct3D10 specific settings.
        /// </summary>
        /// <value>The Direct3D10 specific settings.</value>
        public Direct3D10Settings Direct3D10
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the back buffer width.
        /// </summary>
        /// <value>The back buffer width.</value>
        public int BackBufferWidth
        {
            get
            {
                // return the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) return Direct3D9.PresentParameters.BackBufferWidth;
                else return Direct3D10.BufferWidth;
            }
            set
            {
                // set the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) Direct3D9.PresentParameters.BackBufferWidth = value;
                else Direct3D10.BufferWidth = value;
            }
        }

        /// <summary>
        /// Gets or sets the back buffer height.
        /// </summary>
        /// <value>The back buffer height.</value>
        public int BackBufferHeight
        {
            get
            {
                // return the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) return Direct3D9.PresentParameters.BackBufferHeight;
                else return Direct3D10.BufferHeight;
            }
            set
            {
                // set the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) Direct3D9.PresentParameters.BackBufferHeight = value;
                else Direct3D10.BufferHeight = value;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="DeviceSettings"/> is windowed.
        /// </summary>
        /// <value><c>true</c> if windowed; otherwise, <c>false</c>.</value>
        public bool Windowed
        {
            get
            {
                // return the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) return Direct3D9.PresentParameters.Windowed;
                else return Direct3D10.IsWindowed;
            }
            set
            {
                // set the correct value
                if (DeviceVersion == DeviceVersion.Direct3D9) Direct3D9.PresentParameters.Windowed = value;
                else Direct3D10.IsWindowed = value;
            }
        }

        /// <summary>
        /// Gets or sets the minimum pixel shader version.
        /// </summary>
        /// <value>The minimum pixel shader version.</value>
        public ShaderProfile MinimumPixelShaderVersion
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum vertex shader version.
        /// </summary>
        /// <value>The minimum vertex shader version.</value>
        public ShaderProfile MinimumVertexShaderVersion
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceSettings"/> class.
        /// </summary>
        public DeviceSettings()
        {
            // initialize the individual settings sections
            Direct3D9 = new Direct3D9Settings();
            Direct3D10 = new Direct3D10Settings();
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public DeviceSettings Clone()
        {
            // clone the object
            DeviceSettings result = new DeviceSettings();
            result.Direct3D10 = Direct3D10.Clone();
            result.Direct3D9 = Direct3D9.Clone();
            result.MinimumPixelShaderVersion = MinimumPixelShaderVersion;
            result.MinimumVertexShaderVersion = MinimumVertexShaderVersion;

            // return the result
            return result;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        object ICloneable.Clone()
        {
            // call the overload
            return Clone();
        }
    }
}
