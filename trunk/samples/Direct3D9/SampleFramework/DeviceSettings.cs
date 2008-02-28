using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    public class DeviceSettings
    {
        #region Variables

        PresentParameters presentParameters = new PresentParameters();
        int adapterOrdinal;
        DeviceType deviceType;
        Format adapterFormat;
        CreateFlags behaviorFlags;

        #endregion

        #region Properties

        public int AdapterOrdinal
        {
            get { return adapterOrdinal; }
            set { adapterOrdinal = value; }
        }

        public DeviceType DeviceType
        {
            get { return deviceType; }
            set { deviceType = value; }
        }

        public Format AdapterFormat
        {
            get { return adapterFormat; }
            set { adapterFormat = value; }
        }

        public CreateFlags BehaviorFlags
        {
            get { return behaviorFlags; }
            set { behaviorFlags = value; }
        }

        public PresentParameters PresentParameters
        {
            get { return presentParameters; }
        }

        #endregion

        #region Constructor

        public DeviceSettings()
        {
            DeviceType = DeviceType.Hardware;
            presentParameters.Windowed = true;
            AdapterFormat = Format.Unknown;
            BehaviorFlags = CreateFlags.HardwareVertexProcessing;
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
    }
}
