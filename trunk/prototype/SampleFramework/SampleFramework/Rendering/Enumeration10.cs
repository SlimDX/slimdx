using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DXGI;
using SlimDX.Direct3D10;

namespace SampleFramework
{
    /// <summary>
    /// Contains information about a Direct3D10 adapter.
    /// </summary>
    class AdapterInfo10
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
        /// Gets or sets the adapter description.
        /// </summary>
        /// <value>The adapter description.</value>
        public AdapterDescription AdapterDescription
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the description.
        /// </summary>
        /// <value>The description.</value>
        public string Description
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the adapter.
        /// </summary>
        /// <value>The adapter.</value>
        public Adapter Adapter
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the supported outputs.
        /// </summary>
        /// <value>The supported outputs.</value>
        public List<OutputInfo10> Outputs
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the supported devices.
        /// </summary>
        /// <value>The supported devices.</value>
        public List<DeviceInfo10> Devices
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the unique settings combinations.
        /// </summary>
        /// <value>The unique settings combinations.</value>
        public List<SettingsCombo10> SettingsCombos
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AdapterInfo10"/> class.
        /// </summary>
        public AdapterInfo10()
        {
            // create lists
            Outputs = new List<OutputInfo10>();
            Devices = new List<DeviceInfo10>();
            SettingsCombos = new List<SettingsCombo10>();
        }
    }

    /// <summary>
    /// Contains information about a Direct3D10 output.
    /// </summary>
    class OutputInfo10
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
        /// Gets or sets the output ordinal.
        /// </summary>
        /// <value>The output ordinal.</value>
        public int OutputOrdinal
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the output.
        /// </summary>
        /// <value>The output.</value>
        public Output Output
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the output description.
        /// </summary>
        /// <value>The output description.</value>
        public OutputDescription OutputDescription
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the supported display modes.
        /// </summary>
        /// <value>The supported display modes.</value>
        public List<ModeDescription> DisplayModes
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="OutputInfo10"/> class.
        /// </summary>
        public OutputInfo10()
        {
            // create the lists
            DisplayModes = new List<ModeDescription>();
        }
    }

    /// <summary>
    /// Contains information about a Direct3D10 device.
    /// </summary>
    class DeviceInfo10
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
        /// Initializes a new instance of the <see cref="DeviceInfo10"/> class.
        /// </summary>
        public DeviceInfo10()
        {
        }
    }

    /// <summary>
    /// Contains a unique combination of Direct3D10 device settings.
    /// </summary>
    public class SettingsCombo10
    {
    }

    static class Enumeration10
    {
    }
}
