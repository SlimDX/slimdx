using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Configure
{
    public partial class MainForm : Form
    {
        #region Boilerplate

        public MainForm()
        {
            InitializeComponent();

            versionBox.SelectedItem = "March 2008";
        }

        private void browseButton_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog.ShowDialog(this) == DialogResult.OK)
                directoryBox.Text = folderBrowserDialog.SelectedPath;
        }

        private void quitButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void applyButton_Click(object sender, EventArgs e)
        {
            Apply();
        }

        string FindFile(string fileName, string startingDirectory)
        {
            string[] files = Directory.GetFiles(startingDirectory);
            foreach (string file in files)
            {
                if (Path.GetFileName(file) == fileName)
                    return file;
            }

            foreach (string directory in Directory.GetDirectories(startingDirectory))
            {
                string result = FindFile(fileName, directory);
                if (!string.IsNullOrEmpty(result))
                    return result;
            }

            return null;
        }

        #endregion

        void Apply()
        {
            bool wrapD3D10 = systemsBox.CheckedItems.Contains("Direct3D10");
            bool wrapD3D9 = systemsBox.CheckedItems.Contains("Direct3D9");
            bool wrapDI = systemsBox.CheckedItems.Contains("DirectInput");
            bool wrapDXGI = systemsBox.CheckedItems.Contains("DXGI");
            bool wrapX3DA = systemsBox.CheckedItems.Contains("X3DAudio");
            bool wrapXA2 = systemsBox.CheckedItems.Contains("XAudio2");
            bool wrapXI = systemsBox.CheckedItems.Contains("XInput");

            string path = FindFile("SlimDX.vcproj", directoryBox.Text);
            if (string.IsNullOrEmpty(path))
            {
                MessageBox.Show("Could not find SlimDX project file.");
                return;
            }

            StringBuilder output = new StringBuilder();
            string[] lines = File.ReadAllLines(path);

            foreach (string line in lines)
            {
                if (line.Contains("PreprocessorDefinitions="))
                {
                    int index = line.IndexOf("\"");
                    if (index == -1)
                    {
                        MessageBox.Show("Invalid project file.");
                        return;
                    }

                    output.Append(line.Substring(0, index + 1));

                    if (wrapD3D10)
                        output.Append("WRAP_D3D10;");
                    if (wrapD3D9)
                        output.Append("WRAP_D3D9;");
                    if (wrapDI)
                        output.Append("WRAP_DI;");
                    if (wrapDXGI)
                        output.Append("WRAP_DXGI;");
                    if (wrapX3DA)
                        output.Append("WRAP_X3DA;");
                    if (wrapXA2)
                        output.Append("WRAP_XA2;");
                    if (wrapXI)
                        output.Append("WRAP_XI;");

                    string directives = line.Substring(index + 1);
                    directives.Replace("WRAP_D3D10", string.Empty);
                    directives.Replace("WRAP_D3D9", string.Empty);
                    directives.Replace("WRAP_DI", string.Empty);
                    directives.Replace("WRAP_DXGI", string.Empty);
                    directives.Replace("WRAP_X3DA", string.Empty);
                    directives.Replace("WRAP_XA2", string.Empty);
                    directives.Replace("WRAP_XI", string.Empty);

                    output.AppendLine(line.Substring(index + 1));
                }
                else if (line.Contains("DelayLoadDLLs="))
                {
                }
                else
                    output.AppendLine(line);
            }


        }
    }
}