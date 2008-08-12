using System.IO;
using System.Linq;
using System.Xml.Linq;

namespace LineCounter
{
    static class CSProject
    {
        public static Node Process(string fileName)
        {
            Node rootNode = new Node();
            rootNode.Name = Path.GetFileNameWithoutExtension(fileName);

            XNamespace ns = "http://schemas.microsoft.com/developer/msbuild/2003";
            XDocument document = XDocument.Load(fileName);
            XElement projectElement = document.Element(ns + "Project");

            foreach (XElement e in projectElement.Elements(ns + "ItemGroup"))
            {
                foreach (XElement i in e.Elements(ns + "Compile"))
                {
                    string file = i.Attribute("Include").Value;
                    string path = Path.Combine(Path.GetDirectoryName(fileName), file);

                    Node currentNode = rootNode;

                    while (file.Contains('\\'))
                    {
                        int index = file.IndexOf('\\');
                        string directory = file.Substring(0, index);
                        file = file.Substring(index + 1);

                        bool found = false;
                        foreach (Node node in currentNode.ChildNodes)
                        {
                            if (node.Name == directory)
                            {
                                found = true;
                                currentNode = node;
                                break;
                            }
                        }

                        if (!found)
                        {
                            Node node = new Node();
                            node.Name = directory;
                            currentNode.ChildNodes.Add(node);
                            currentNode = node;
                        }
                    }

                    FileNode fileNode = new FileNode();
                    fileNode.Path = path;
                    Counter.CountFile(fileNode);

                    currentNode.ChildNodes.Add(fileNode);
                }
            }

            return rootNode;
        }
    }
}
