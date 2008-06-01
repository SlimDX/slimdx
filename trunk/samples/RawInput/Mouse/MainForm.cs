using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using SlimDX.RawInput;
using SlimDX;
using System.Globalization;

namespace Mouse
{
    public partial class MainForm : Form
    {
        Device mouse;

        public MainForm()
        {
            InitializeComponent();

            // setup the device
            mouse = new Device(UsagePage.Generic, UsageId.Mouse, DeviceFlags.None);
            mouse.MouseInput += mouse_MouseInput;
        }

        void mouse_MouseInput(object sender, MouseInputEventArgs e)
        {
            buttonsLabel.Text = Enum.Format(typeof(MouseButtonFlags), e.ButtonFlags, "G");
            extraLabel.Text = e.ExtraInformation.ToString(CultureInfo.CurrentCulture);
            rawButtonsLabel.Text = e.RawButtons.ToString(CultureInfo.CurrentCulture);
            locationLabel.Text = new Point(e.X, e.Y).ToString();
            stateLabel.Text = Enum.Format(typeof(MouseState), e.State, "G");
            wheelLabel.Text = e.WheelDelta.ToString(CultureInfo.CurrentCulture);
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            // make sure the device is disposed
            if (mouse != null)
                mouse.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
