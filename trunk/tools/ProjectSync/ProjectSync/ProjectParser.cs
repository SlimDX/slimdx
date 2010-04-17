using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.IO;

namespace ProjectSync
{
    class ProjectParser
    {
        public Dictionary<string, string> Filters
        {
            get;
            private set;
        }

        public Dictionary<string, string> IncludeFiles
        {
            get;
            private set;
        }

        public Dictionary<string, string> SourceFiles
        {
            get;
            private set;
        }

        public Dictionary<string, string> ResourceFiles
        {
            get;
            private set;
        }

        public Dictionary<string, string> OtherFiles
        {
            get;
            private set;
        }

        public ProjectParser(string path)
        {
            Filters = new Dictionary<string, string>();
            IncludeFiles = new Dictionary<string, string>();
            SourceFiles = new Dictionary<string, string>();
            ResourceFiles = new Dictionary<string, string>();
            OtherFiles = new Dictionary<string, string>();

            var filesElement = XDocument.Load(path).Element("VisualStudioProject").Element("Files");
            Parse(filesElement, null);
        }

        void Parse(XElement element, string filterBase)
        {
            foreach (var child in element.Elements())
            {
                if (child.Name == "Filter")
                {
                    string filter = (string.IsNullOrEmpty(filterBase) ? "" : filterBase + "\\") + (string)child.Attribute("Name");
                    Filters.Add(filter, "");

                    Parse(child, filter);
                }
                else
                {
                    string path = Path.Combine("..", (string)child.Attribute("RelativePath"));
                    string extension = Path.GetExtension(path);

                    if (extension == ".h")
                        IncludeFiles.Add(path, filterBase);
                    else if (extension == ".cpp")
                        SourceFiles.Add(path, filterBase);
                    else if (extension == ".resx")
                        ResourceFiles.Add(path, filterBase);
                    else
                        OtherFiles.Add(path, filterBase);
                }
            }
        }
    }
}
