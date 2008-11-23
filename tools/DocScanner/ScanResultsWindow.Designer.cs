namespace DocScanner
{
	partial class ScanResultsWindow
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if(disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ScanResultsWindow));
			this.ResultsList = new System.Windows.Forms.ListBox();
			this.ItemContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.CopyMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.CopyAllMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.ItemContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// ResultsList
			// 
			this.ResultsList.Anchor = ((System.Windows.Forms.AnchorStyles) ((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.ResultsList.FormattingEnabled = true;
			this.ResultsList.Location = new System.Drawing.Point(13, 13);
			this.ResultsList.Name = "ResultsList";
			this.ResultsList.Size = new System.Drawing.Size(303, 420);
			this.ResultsList.TabIndex = 0;
			this.ResultsList.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ResultsList_MouseUp);
			// 
			// ItemContextMenu
			// 
			this.ItemContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CopyMenuItem,
            this.CopyAllMenuItem});
			this.ItemContextMenu.Name = "ItemContextMenu";
			this.ItemContextMenu.Size = new System.Drawing.Size(120, 48);
			// 
			// CopyMenuItem
			// 
			this.CopyMenuItem.Name = "CopyMenuItem";
			this.CopyMenuItem.Size = new System.Drawing.Size(119, 22);
			this.CopyMenuItem.Text = "Copy";
			this.CopyMenuItem.Click += new System.EventHandler(this.CopyMenuItem_Click);
			// 
			// CopyAllMenuItem
			// 
			this.CopyAllMenuItem.Name = "CopyAllMenuItem";
			this.CopyAllMenuItem.Size = new System.Drawing.Size(119, 22);
			this.CopyAllMenuItem.Text = "Copy All";
			this.CopyAllMenuItem.Click += new System.EventHandler(this.CopyAllMenuItem_Click);
			// 
			// ScanResultsWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(328, 444);
			this.Controls.Add(this.ResultsList);
			this.Icon = ((System.Drawing.Icon) (resources.GetObject("$this.Icon")));
			this.Name = "ScanResultsWindow";
			this.Text = "ScanResults";
			this.ItemContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListBox ResultsList;
		private System.Windows.Forms.ContextMenuStrip ItemContextMenu;
		private System.Windows.Forms.ToolStripMenuItem CopyMenuItem;
		private System.Windows.Forms.ToolStripMenuItem CopyAllMenuItem;
	}
}