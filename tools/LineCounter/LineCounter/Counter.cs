using System;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace LineCounter
{
    public class Counter
    {
        string inputFile;

        public List<string> Warnings = new List<string>();

        public int TotalLines
        {
            get;
            private set;
        }

        public int Comments
        {
            get;
            private set;
        }

        public int BlankLines
        {
            get;
            private set;
        }

        public int CodeLines
        {
            get;
            private set;
        }

        public int Directories
        {
            get;
            private set;
        }

        public int Files
        {
            get;
            private set;
        }

        public int Projects
        {
            get;
            private set;
        }

        public Counter(string inputFile)
        {
            this.inputFile = inputFile;
        }

        public void Calculate()
        {
            Node rootNode = new Node();
            rootNode.Name = Path.GetFileNameWithoutExtension(inputFile);

            foreach (string line in File.ReadAllLines(inputFile).Where(s => s.StartsWith("Project", false, CultureInfo.InvariantCulture)))
            {
                string project = line.Extract('"', 5, 6);
                if (!project.Contains("proj"))
                    continue;

                project = Path.Combine(Path.GetDirectoryName(inputFile), project);

                // no guarantees that vbproj actually works
                if (project.Contains(".vcproj"))
                    rootNode.ChildNodes.Add(VCProject.Process(project));
                else if (project.Contains(".csproj") || project.Contains(".vbproj"))
                    rootNode.ChildNodes.Add(CSProject.Process(project));
                else
                    Warnings.Add("Invalid project type: " + Path.GetExtension(project));
            }

            if (rootNode.ChildNodes.Count == 0)
                throw new InvalidOperationException("No valid projects found.");

            FileNode results = Count(rootNode);

            CodeLines = results.CodeLines;
            Comments = results.Comments;
            BlankLines = results.BlankLines;
            TotalLines = results.TotalLines;

            Directories = CountFolders(rootNode, false);
            Projects = rootNode.ChildNodes.Count;
            Files = CountFiles(rootNode);
        }

        internal static int CountFolders(Node node, bool countTopLevel)
        {
            int count = 0;
            foreach (Node n in node.ChildNodes)
            {
                if (!(n is FileNode))
                {
                    if (countTopLevel)
                        count++;
                    count += CountFolders(n, true);
                }
            }

            return count;
        }

        internal static int CountFiles(Node node)
        {
            int count = 0;
            foreach (Node n in node.ChildNodes)
            {
                if (n is FileNode)
                    count++;

                count += CountFiles(n);
            }

            return count;
        }

        internal static void CountFile(FileNode file)
        {
            if (!File.Exists(file.Path))
                throw new InvalidOperationException("Could not open file " + file.Path);

            file.Name = Path.GetFileName(file.Path);
            file.FileType = file.Path.EndsWith(".h") ? FileType.HeaderFile : FileType.SourceFile;

            string[] lines = File.ReadAllLines(file.Path);

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

        internal static FileNode Count(Node node)
        {
            FileNode results = new FileNode();

            foreach (Node n in node.ChildNodes)
            {
                FileNode fn = n as FileNode;
                if (fn == null)
                    fn = Count(n);

                results.BlankLines += fn.BlankLines;
                results.CodeLines += fn.CodeLines;
                results.Comments += fn.Comments;
                results.TotalLines += fn.TotalLines;
            }

            return results;
        }
    }
}
