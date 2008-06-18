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
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Contains settings for a Direct3D device.
    /// </summary>
    public class DeviceSettings : ICloneable
    {
        #region Variables

        int adapterOrdinal;
        DeviceType deviceType;
        Format adapterFormat;
        CreateFlags behaviorFlags;
        PresentParameters presentParameters = new PresentParameters();

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the adapter ordinal.
        /// </summary>
        /// <value>The adapter ordinal.</value>
        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        /// <summary>
        /// Gets or sets the type of the device.
        /// </summary>
        /// <value>The type of the device.</value>
        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        /// <summary>
        /// Gets or sets the adapter format.
        /// </summary>
        /// <value>The adapter format.</value>
        public Format AdapterFormat
        {
            get { return adapterFormat; }
            set { adapterFormat = value; }
        }

        /// <summary>
        /// Gets or sets the behavior flags.
        /// </summary>
        /// <value>The behavior flags.</value>
        public CreateFlags BehaviorFlags
        {
            get { return behaviorFlags; }
            set { behaviorFlags = value; }
        }

        /// <summary>
        /// Gets the present parameters.
        /// </summary>
        /// <value>The present parameters.</value>
        public PresentParameters PresentParameters
        {
            get { return presentParameters; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceSettings"/> class.
        /// </summary>
        public DeviceSettings()
        {
            // set defaults
            deviceType = DeviceType.Hardware;
            presentParameters.Windowed = true;
            adapterFormat = Format.Unknown;
            behaviorFlags = CreateFlags.HardwareVertexProcessing;
            presentParameters.BackBufferFormat = Format.Unknown;
            presentParameters.BackBufferCount = 1;
            presentParameters.Multisample = MultisampleType.None;
            presentParameters.SwapEffect = SwapEffect.Discard;
            presentParameters.AutoDepthStencilFormat = Format.Unknown;
            presentParameters.PresentFlags = PresentFlags.DiscardDepthStencil;
            presentParameters.PresentationInterval = PresentInterval.Default;
        }

        #endregion

        #region Methods

        /// <summary>
        /// Clones this instance.
        /// </summary>
        /// <returns>The cloned device settings.</returns>
        public DeviceSettings Clone()
        {
            DeviceSettings clone = new DeviceSettings();
            clone.AdapterFormat = AdapterFormat;
            clone.AdapterOrdinal = AdapterOrdinal;
            clone.BehaviorFlags = BehaviorFlags;
            clone.DeviceType = DeviceType;
            clone.PresentParameters.AutoDepthStencilFormat = PresentParameters.AutoDepthStencilFormat;
            clone.PresentParameters.BackBufferCount = PresentParameters.BackBufferCount;
            clone.PresentParameters.BackBufferFormat = PresentParameters.BackBufferFormat;
            clone.PresentParameters.BackBufferHeight = PresentParameters.BackBufferHeight;
            clone.PresentParameters.BackBufferWidth = PresentParameters.BackBufferWidth;
            clone.PresentParameters.DeviceWindowHandle = PresentParameters.DeviceWindowHandle;
            clone.PresentParameters.EnableAutoDepthStencil = PresentParameters.EnableAutoDepthStencil;
            clone.PresentParameters.FullScreenRefreshRateInHertz = PresentParameters.FullScreenRefreshRateInHertz;
            clone.PresentParameters.Multisample = PresentParameters.Multisample;
            clone.PresentParameters.MultisampleQuality = PresentParameters.MultisampleQuality;
            clone.PresentParameters.PresentationInterval = PresentParameters.PresentationInterval;
            clone.PresentParameters.PresentFlags = PresentParameters.PresentFlags;
            clone.PresentParameters.SwapEffect = PresentParameters.SwapEffect;
            clone.PresentParameters.Windowed = PresentParameters.Windowed;

            return clone;
        }

        #endregion

        #region ICloneable Members

        object ICloneable.Clone()
        {
            return Clone();
        }

        #endregion
    }
}
