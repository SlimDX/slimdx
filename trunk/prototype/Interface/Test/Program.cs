using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing;
using SlimDX;
using SlimDX.Direct3D9;
using Interface;

namespace Test
{
    [StructLayout(LayoutKind.Sequential)]
    struct Message
    {
        public IntPtr hWnd;
        public uint msg;
        public IntPtr wParam;
        public IntPtr lParam;
        public uint time;
        public Point p;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector4 PositionRhw;
        public int Color;
    }

    static class Program
    {
        static Form RenderForm;
        static Device Device;
        static InterfaceManager InterfaceManager;
        static Timer Timer;

        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool PeekMessage(out Message msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);

        static bool AppStillIdle
        {
            get
            {
                Message msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        [STAThread]
        static void Main()
        {
            RenderForm = new Form();
            RenderForm.ClientSize = new Size(800, 600);
            RenderForm.Text = "SlimDX - User Interface Sample";

            Direct3D.Initialize();

            PresentParameters presentParams = new PresentParameters();
            presentParams.BackBufferHeight = RenderForm.ClientRectangle.Height;
            presentParams.BackBufferWidth = RenderForm.ClientRectangle.Width;
            presentParams.DeviceWindowHandle = RenderForm.Handle;

            Device = new Device(0, DeviceType.Hardware, RenderForm.Handle, CreateFlags.HardwareVertexProcessing, presentParams);

            InterfaceManager = new InterfaceManager(Device, RenderForm, "dxutcontrols.dds");
            InterfaceManager.LoadXml("layout.xml");

            InterfaceManager.OnDeviceCreated(Device);
            InterfaceManager.OnDeviceReset();

            Timer = new Timer();
            Timer.Start();

            Application.Idle += new EventHandler(Application_Idle);
            Application.Run(RenderForm);

            InterfaceManager.OnDeviceLost();
            InterfaceManager.OnDeviceDestroyed();

            if (Device != null)
                Device.Dispose();

            RenderForm.Dispose();
        }

        static void Application_Idle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                float elapsedTime = (float)Timer.GetElapsedTime();

                Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.FromArgb(0, 45, 50, 170), 1.0f, 0);
                Device.BeginScene();

                InterfaceManager.Update(elapsedTime);
                InterfaceManager.Render();

                Device.EndScene();
                Device.Present();
            }
        }
    }
}
