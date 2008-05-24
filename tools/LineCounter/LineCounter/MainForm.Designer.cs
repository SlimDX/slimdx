namespace LineCounter
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
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
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
            System.Windows.Forms.ListViewGroup listViewGroup1 = new System.Windows.Forms.ListViewGroup("Totals", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup2 = new System.Windows.Forms.ListViewGroup("Source Files", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup3 = new System.Windows.Forms.ListViewGroup("Header Files", System.Windows.Forms.HorizontalAlignment.Left);
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.sourceTree = new System.Windows.Forms.TreeView();
            this.folderIcons = new System.Windows.Forms.ImageList(this.components);
            this.outputView = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader5 = new System.Windows.Forms.ColumnHeader();
            this.fileIcons = new System.Windows.Forms.ImageList(this.components);
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.calculateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.findSolutionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer
            // 
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Location = new System.Drawing.Point(0, 0);
            this.splitContainer.Name = "splitContainer";
            // 
            // splitContainer.Panel1
            // 
            this.splitContainer.Panel1.Controls.Add(this.sourceTree);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.outputView);
            this.splitContainer.Size = new System.Drawing.Size(624, 444);
            this.splitContainer.SplitterDistance = 236;
            this.splitContainer.TabIndex = 0;
            this.splitContainer.TabStop = false;
            this.splitContainer.SplitterMoved += new System.Windows.Forms.SplitterEventHandler(this.splitContainer_SplitterMoved);
            // 
            // sourceTree
            // 
            this.sourceTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.sourceTree.ImageIndex = 0;
            this.sourceTree.ImageList = this.folderIcons;
            this.sourceTree.Location = new System.Drawing.Point(0, 0);
            this.sourceTree.Name = "sourceTree";
            this.sourceTree.SelectedImageIndex = 0;
            this.sourceTree.Size = new System.Drawing.Size(236, 444);
            this.sourceTree.TabIndex = 0;
            this.sourceTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.sourceTree_AfterSelect);
            // 
            // folderIcons
            // 
            this.folderIcons.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
            this.folderIcons.ImageSize = new System.Drawing.Size(16, 16);
            this.folderIcons.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // outputView
            // 
            this.outputView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5});
            this.outputView.Dock = System.Windows.Forms.DockStyle.Fill;
            listViewGroup1.Header = "Totals";
            listViewGroup1.Name = "listViewGroup3";
            listViewGroup2.Header = "Source Files";
            listViewGroup2.Name = "listViewGroup1";
            listViewGroup3.Header = "Header Files";
            listViewGroup3.Name = "listViewGroup2";
            this.outputView.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup1,
            listViewGroup2,
            listViewGroup3});
            this.outputView.Location = new System.Drawing.Point(0, 0);
            this.outputView.Name = "outputView";
            this.outputView.Size = new System.Drawing.Size(384, 444);
            this.outputView.SmallImageList = this.fileIcons;
            this.outputView.TabIndex = 0;
            this.outputView.UseCompatibleStateImageBehavior = false;
            this.outputView.View = System.Windows.Forms.View.Details;
            this.outputView.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.outputView_ColumnClick);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "File";
            this.columnHeader1.Width = 118;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Total Lines";
            this.columnHeader2.Width = 66;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Code Lines";
            this.columnHeader3.Width = 66;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Comments";
            this.columnHeader4.Width = 61;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Blank Lines";
            this.columnHeader5.Width = 68;
            // 
            // fileIcons
            // 
            this.fileIcons.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
            this.fileIcons.ImageSize = new System.Drawing.Size(16, 16);
            this.fileIcons.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.calculateToolStripMenuItem,
            this.findSolutionToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(153, 70);
            // 
            // calculateToolStripMenuItem
            // 
            this.calculateToolStripMenuItem.Name = "calculateToolStripMenuItem";
            this.calculateToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.calculateToolStripMenuItem.Text = "&Calculate";
            this.calculateToolStripMenuItem.Click += new System.EventHandler(this.calculateToolStripMenuItem_Click);
            // 
            // findSolutionToolStripMenuItem
            // 
            this.findSolutionToolStripMenuItem.Name = "findSolutionToolStripMenuItem";
            this.findSolutionToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.findSolutionToolStripMenuItem.Text = "&Find Project...";
            this.findSolutionToolStripMenuItem.Click += new System.EventHandler(this.findSolutionToolStripMenuItem_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Project Files|*.vcproj|All files|*.*";
            this.openFileDialog.Title = "Find Project";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 444);
            this.ContextMenuStrip = this.contextMenuStrip;
            this.Controls.Add(this.splitContainer);
            this.Name = "MainForm";
            this.Text = "Line Counter";
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel2.ResumeLayout(false);
            this.splitContainer.ResumeLayout(false);
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.TreeView sourceTree;
        private System.Windows.Forms.ListView outputView;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem calculateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem findSolutionToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ImageList folderIcons;
        private System.Windows.Forms.ImageList fileIcons;

    }
}

