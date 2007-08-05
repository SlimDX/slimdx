using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace SimpleTriangle
{
	public partial class RenderForm : Form
	{
		public RenderForm()
		{
			InitializeComponent();

			this.ClientSize = new Size( 800, 600 );
		}

		public void PrepareMainLoop()
		{
			Application.Idle += new EventHandler( Application_Idle );
		}

		private bool AppStillIdle
		{
			get
			{
				NativeMethods.Message msg;
				return !NativeMethods.PeekMessage( out msg, IntPtr.Zero, 0, 0, 0 );
			}
		}

		//This is our actual loop function
		private void Application_Idle( object sender, EventArgs e )
		{
			while( Program.RunLoop && AppStillIdle )
			{
				Program.MainLoop();
			}
		}
	}
}