using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SimpleSound
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void MainForm_Load( object sender, EventArgs e )
		{
			Program.SoundManager = new SoundManager( this, SlimDX.DirectSound.CooperativeLevel.Priority );
			Program.SoundManager.SetPrimaryBufferFormat( 2, 22050, 16 );
		}
	}
}