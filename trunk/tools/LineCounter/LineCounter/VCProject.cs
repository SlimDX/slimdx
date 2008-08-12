using System.IO;
using System.Xml.Linq;

namespace LineCounter
{
    static class VCProject
    {
        static string projectPath;

        public static Node Process(string fileName)
        {
            projectPath = fileName;

            Node rootNode = new Node();
            rootNode.Name = Path.GetFileNameWithoutExtension(fileName);

            XDocument project = XDocument.Load(fileName);
            XElement rootFile = project.Element("VisualStudioProject").Element("Files");
            ProcessElement(rootFile, rootNode);

            return rootNode;
        }

        static void ProcessElement(XElement element, Node rootNode)
        {
            foreach (XElement e in element.Elements("File"))
            {
                XAttribute attribute = e.Attribute("RelativePath");
                if (attribute == null)
                    continue;

                FileNode file = new FileNode();
                file.Path = Path.Combine(Path.GetDirectoryName(projectPath), attribute.Value);
                Counter.CountFile(file);

                rootNode.ChildNodes.Add(file);
            }

            foreach (XElement e in element.Elements("Filter"))
            {
                XAttribute attribute = e.Attribute("Name");
                if (attribute == null)
                    continue;

                Node node = new Node();
                node.Name = attribute.Value;
                ProcessElement(e, node);
            }
        }
    }
}
