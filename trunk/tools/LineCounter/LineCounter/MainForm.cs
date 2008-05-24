using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml.Linq;

namespace LineCounter
{
    public partial class MainForm : Form
    {
        string projectPath;

        #region Boilerplate

        const string settingsPath = "settings.txt";

        public MainForm()
        {
            InitializeComponent();

            folderIcons.Images.Add(IconReader.GetFolderIcon(IconReader.IconSize.Small, IconReader.FolderType.Closed));

            if (!File.Exists(settingsPath))
            {
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    projectPath = openFileDialog.FileName;
                    File.WriteAllText(settingsPath, projectPath);
                }
                else
                    Close();
            }
            else
                projectPath = File.ReadAllText(settingsPath);

            Calculate();
        }

        private void calculateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Calculate();
        }

        private void findSolutionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                projectPath = openFileDialog.FileName;
                File.WriteAllText(settingsPath, projectPath);
                Calculate();
            }
        }

        private void sourceTree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            UpdateLineView();
        }

        private void splitContainer_SplitterMoved(object sender, SplitterEventArgs e)
        {
            outputView.Focus();
        }

        #endregion

        void Calculate()
        {
            outputView.Items.Clear();
            sourceTree.Nodes.Clear();

            if (string.IsNullOrEmpty(projectPath) || !File.Exists(projectPath))
            {
                MessageBox.Show("Invalid or missing project file.");
                return;
            }

            TreeNode rootNode = sourceTree.Nodes.Add(Path.GetFileNameWithoutExtension(projectPath));

            XDocument project = XDocument.Load(projectPath);
            XElement rootFile = project.Element("VisualStudioProject").Element("Files");
            ProcessElement(rootFile, rootNode);
        }

        void ProcessElement(XElement element, TreeNode rootNode)
        {
            NodeInfo info = new NodeInfo();

            foreach (XElement e in element.Elements("File"))
            {
                XAttribute attribute = e.Attribute("RelativePath");
                if (attribute == null)
                    continue;

                CountedFile file = new CountedFile();
                file.Path = attribute.Value;
                ProcessFile(file);

                info.Files.Add(file);
            }

            foreach (XElement e in element.Elements("Filter"))
            {
                XAttribute attribute = e.Attribute("Name");
                if (attribute == null)
                    continue;

                TreeNode node = rootNode.Nodes.Add(attribute.Value);
                ProcessElement(e, node);

                NodeInfo localInfo = node.Tag as NodeInfo;
                if (localInfo != null)
                    info.Files.AddRange(localInfo.Files);
            }

            rootNode.Tag = info;
        }

        void ProcessFile(CountedFile file)
        {
            string fullPath = Path.Combine(Path.GetDirectoryName(projectPath), file.Path);

            if (!File.Exists(fullPath))
            {
                MessageBox.Show("Could not open file " + fullPath);
                return;
            }

            string key = Path.GetExtension(fullPath);
            int index = 0;
            if (!fileIcons.Images.ContainsKey(key))
                fileIcons.Images.Add(key, IconReader.GetFileIcon(fullPath, IconReader.IconSize.Small, false));

            index = fileIcons.Images.IndexOfKey(key);

            file.Path = fullPath;
            file.Name = Path.GetFileName(fullPath);
            file.Icon = index;
            file.FileType = key.Contains("cpp") ? FileType.SourceFile : FileType.HeaderFile;

            string[] lines = File.ReadAllLines(fullPath);

            bool inComment = false;

            foreach (string line in lines)
            {
                file.TotalLines++;

                string temp = line.Trim();

                if (string.IsNullOrEmpty(temp))
                    file.BlankLines++;
                else if (inComment)
                {
                    file.Comments++;

                    if (temp.Contains("*/"))
                        inComment = false;
                }
                else
                {
                    if (temp.StartsWith("//"))
                        file.Comments++;
                    else if (temp.Contains("/*"))
                    {
                        file.Comments++;
                        inComment = true;
                    }
                    else
                        file.CodeLines++;
                }
            }
        }

        void UpdateLineView()
        {
            outputView.Items.Clear();

            TreeNode selectedNode = sourceTree.SelectedNode;
            if (selectedNode == null)
                return;

            NodeInfo info = selectedNode.Tag as NodeInfo;
            if (info == null)
                return;

            int totalLines = 0;
            int codeLines = 0;
            int comments = 0;
            int blankLines = 0;

            ListViewItem item;

            foreach (CountedFile file in info.Files)
            {
                ListViewGroup group;
                if (file.FileType == FileType.SourceFile)
                    group = outputView.Groups[1];
                else
                    group = outputView.Groups[2];

                item = new ListViewItem(file.Name, file.Icon, group);

                item.SubItems.Add(file.TotalLines.ToString());
                item.SubItems.Add(file.CodeLines.ToString());
                item.SubItems.Add(file.Comments.ToString());
                item.SubItems.Add(file.BlankLines.ToString());

                outputView.Items.Add(item);

                totalLines += file.TotalLines;
                codeLines += file.CodeLines;
                comments += file.Comments;
                blankLines += file.BlankLines;
            }

            string key = "folder";
            int index = 0;
            if (!fileIcons.Images.ContainsKey(key))
                fileIcons.Images.Add(key, IconReader.GetFolderIcon(IconReader.IconSize.Small, IconReader.FolderType.Closed));
            index = fileIcons.Images.IndexOfKey(key);

            item = new ListViewItem(selectedNode.Text, index, outputView.Groups[0]);

            item.SubItems.Add(totalLines.ToString());
            item.SubItems.Add(codeLines.ToString());
            item.SubItems.Add(comments.ToString());
            item.SubItems.Add(blankLines.ToString());

            outputView.Items.Add(item);

            outputView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            outputView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }

        private void outputView_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            ListViewItemComparer sorter = outputView.ListViewItemSorter as ListViewItemComparer;

            if (sorter == null)
            {
                sorter = new ListViewItemComparer(e.Column);
                outputView.ListViewItemSorter = sorter;
            }
            else
            {
                if (sorter.Column == e.Column && !sorter.Descending)
                {
                    sorter.Descending = true;
                }
                else
                {
                    sorter.Descending = false;
                    sorter.Column = e.Column;
                }
            }

            if (e.Column != 0)
                sorter.Numeric = true;
            else
                sorter.Numeric = false;

            outputView.Sort();
        }
    }
}
