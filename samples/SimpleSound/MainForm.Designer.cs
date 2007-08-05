namespace SimpleSound
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose( bool disposing )
		{
			if( disposing && ( components != null ) )
			{
				components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.SelectFileButton = new System.Windows.Forms.Button();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.trackBar1 = new System.Windows.Forms.TrackBar();
			this.trackBar2 = new System.Windows.Forms.TrackBar();
			this.trackBar3 = new System.Windows.Forms.TrackBar();
			this.PositionLabel = new System.Windows.Forms.Label();
			this.PanLabel = new System.Windows.Forms.Label();
			this.VolumeLabel = new System.Windows.Forms.Label();
			this.PlayButton = new System.Windows.Forms.Button();
			this.StopButton = new System.Windows.Forms.Button();
			this.LoopCheck = new System.Windows.Forms.CheckBox();
			this.FileChooser = new System.Windows.Forms.OpenFileDialog();
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar1 ) ).BeginInit();
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar2 ) ).BeginInit();
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar3 ) ).BeginInit();
			this.SuspendLayout();
			// 
			// SelectFileButton
			// 
			this.SelectFileButton.Location = new System.Drawing.Point( 12, 12 );
			this.SelectFileButton.Name = "SelectFileButton";
			this.SelectFileButton.Size = new System.Drawing.Size( 75, 23 );
			this.SelectFileButton.TabIndex = 0;
			this.SelectFileButton.Text = "Sound File...";
			this.SelectFileButton.UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point( 93, 14 );
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new System.Drawing.Size( 402, 20 );
			this.textBox1.TabIndex = 1;
			// 
			// trackBar1
			// 
			this.trackBar1.Location = new System.Drawing.Point( 93, 41 );
			this.trackBar1.Name = "trackBar1";
			this.trackBar1.Size = new System.Drawing.Size( 402, 45 );
			this.trackBar1.TabIndex = 2;
			// 
			// trackBar2
			// 
			this.trackBar2.Location = new System.Drawing.Point( 93, 92 );
			this.trackBar2.Name = "trackBar2";
			this.trackBar2.Size = new System.Drawing.Size( 402, 45 );
			this.trackBar2.TabIndex = 3;
			// 
			// trackBar3
			// 
			this.trackBar3.Location = new System.Drawing.Point( 93, 143 );
			this.trackBar3.Name = "trackBar3";
			this.trackBar3.Size = new System.Drawing.Size( 402, 45 );
			this.trackBar3.TabIndex = 4;
			// 
			// PositionLabel
			// 
			this.PositionLabel.AutoSize = true;
			this.PositionLabel.Font = new System.Drawing.Font( "Arial", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte) ( 0 ) ) );
			this.PositionLabel.Location = new System.Drawing.Point( 8, 41 );
			this.PositionLabel.Name = "PositionLabel";
			this.PositionLabel.Size = new System.Drawing.Size( 83, 22 );
			this.PositionLabel.TabIndex = 5;
			this.PositionLabel.Text = "Position:";
			// 
			// PanLabel
			// 
			this.PanLabel.AutoSize = true;
			this.PanLabel.Font = new System.Drawing.Font( "Arial", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte) ( 0 ) ) );
			this.PanLabel.Location = new System.Drawing.Point( 43, 143 );
			this.PanLabel.Name = "PanLabel";
			this.PanLabel.Size = new System.Drawing.Size( 48, 22 );
			this.PanLabel.TabIndex = 6;
			this.PanLabel.Text = "Pan:";
			// 
			// VolumeLabel
			// 
			this.VolumeLabel.AutoSize = true;
			this.VolumeLabel.Font = new System.Drawing.Font( "Arial", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte) ( 0 ) ) );
			this.VolumeLabel.Location = new System.Drawing.Point( 12, 92 );
			this.VolumeLabel.Name = "VolumeLabel";
			this.VolumeLabel.Size = new System.Drawing.Size( 80, 22 );
			this.VolumeLabel.TabIndex = 7;
			this.VolumeLabel.Text = "Volume:";
			// 
			// PlayButton
			// 
			this.PlayButton.Location = new System.Drawing.Point( 203, 194 );
			this.PlayButton.Name = "PlayButton";
			this.PlayButton.Size = new System.Drawing.Size( 75, 23 );
			this.PlayButton.TabIndex = 8;
			this.PlayButton.Text = "Play/Pause";
			this.PlayButton.UseVisualStyleBackColor = true;
			// 
			// StopButton
			// 
			this.StopButton.Location = new System.Drawing.Point( 284, 194 );
			this.StopButton.Name = "StopButton";
			this.StopButton.Size = new System.Drawing.Size( 75, 23 );
			this.StopButton.TabIndex = 9;
			this.StopButton.Text = "Stop";
			this.StopButton.UseVisualStyleBackColor = true;
			// 
			// LoopCheck
			// 
			this.LoopCheck.AutoSize = true;
			this.LoopCheck.Location = new System.Drawing.Point( 147, 198 );
			this.LoopCheck.Name = "LoopCheck";
			this.LoopCheck.Size = new System.Drawing.Size( 50, 17 );
			this.LoopCheck.TabIndex = 11;
			this.LoopCheck.Text = "Loop";
			this.LoopCheck.UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 507, 229 );
			this.Controls.Add( this.LoopCheck );
			this.Controls.Add( this.StopButton );
			this.Controls.Add( this.PlayButton );
			this.Controls.Add( this.VolumeLabel );
			this.Controls.Add( this.PanLabel );
			this.Controls.Add( this.PositionLabel );
			this.Controls.Add( this.trackBar3 );
			this.Controls.Add( this.trackBar2 );
			this.Controls.Add( this.trackBar1 );
			this.Controls.Add( this.textBox1 );
			this.Controls.Add( this.SelectFileButton );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.Text = "Simple Sound Player";
			this.Load += new System.EventHandler( this.MainForm_Load );
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar1 ) ).EndInit();
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar2 ) ).EndInit();
			( (System.ComponentModel.ISupportInitialize) ( this.trackBar3 ) ).EndInit();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button SelectFileButton;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.TrackBar trackBar1;
		private System.Windows.Forms.TrackBar trackBar2;
		private System.Windows.Forms.TrackBar trackBar3;
		private System.Windows.Forms.Label PositionLabel;
		private System.Windows.Forms.Label PanLabel;
		private System.Windows.Forms.Label VolumeLabel;
		private System.Windows.Forms.Button PlayButton;
		private System.Windows.Forms.Button StopButton;
		private System.Windows.Forms.CheckBox LoopCheck;
		private System.Windows.Forms.OpenFileDialog FileChooser;
	}
}

