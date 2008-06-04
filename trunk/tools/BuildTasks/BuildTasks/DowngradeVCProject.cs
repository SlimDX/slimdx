using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using System.Xml.XPath;

namespace BuildTasks {
	public class DowngradeVCProject : Task {
		string inputProject;
		string outputProject;

		[Required]
		public string InputProject {
			get {
				return inputProject;
			}
			set {
				inputProject = value;
			}
		}

		[Required]
		public string OutputProject {
			get {
				return outputProject;
			}
			set {
				outputProject = value;
			}
		}

		public override bool Execute() {
			if (!File.Exists(inputProject)) {
				Log.LogError(string.Format("Input .vcproj '{0}' does not exist.", inputProject));
				return false;
			}

			XPathDocument doc = new XPathDocument(inputProject);
			XPathNavigator root = doc.CreateNavigator();

			using (FileStream stream = new FileStream(outputProject, FileMode.Create))
			using (StreamWriter writer = new StreamWriter(stream)) {
				foreach (XPathNavigator element in root.SelectDescendants(XPathNodeType.Element, true)) {
					WriteElement(writer, 0, element);
					break;
				}
			}

			return true;
		}

		static void WriteElement(StreamWriter writer, int indent, XPathNavigator element) {
			string elementPrefix = new string(' ', indent * 2);
			string attributePrefix = new string(' ', indent * 2 + 2);

			writer.Write("{0}<{1}", elementPrefix, element.Name);

			foreach (XPathNavigator attribute in element.Select("@*")) {
				if (element.Name == "VisualStudioProject" && attribute.Name == "Version") {
					writer.Write("{0}{1}Version=\"8.00\"", Environment.NewLine, attributePrefix );
				}
				else if(element.Name == "VisualStudioProject" && attribute.Name == "TargetFrameworkVersion") {
					// No op.
				}
				else {
					writer.Write("{0}{1}{2}=\"{3}\"", Environment.NewLine, attributePrefix, attribute.Name, attribute.Value);
				}
			}
		
			if( element.HasChildren ) {
				writer.WriteLine(">");
				
				foreach (XPathNavigator child in element.SelectChildren(XPathNodeType.Element)) {
					WriteElement(writer, indent + 1, child);
				}
				
				writer.WriteLine("{0}</{1}>", elementPrefix, element.Name);
			}
			else {
				writer.WriteLine("/>");
			}
		}
	}
}
