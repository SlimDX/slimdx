/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

using System;
using System.IO;
using System.Xml.XPath;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace BuildTasks {
	public class DowngradeProject : Task {
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
				Log.LogError(string.Format("Input project '{0}' does not exist.", inputProject));
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
					writer.Write("{0}{1}Version=\"8.00\"", Environment.NewLine, attributePrefix);
				}
				else if (element.Name == "VisualStudioProject" && attribute.Name == "TargetFrameworkVersion") {
					// No op.
				}
				else if (element.Name == "AssemblyReference" && attribute.Name == "MinFrameworkVersion") {
					// No op.
				}
				else if( element.Name == "ProjectReference" && attribute.Name=="Include") {
					string newValue = Path.GetFileNameWithoutExtension(attribute.Value);
					newValue += ".2005" + Path.GetExtension(attribute.Value);
					writer.Write(" Include=\"{0}\"", newValue);
				}
				else {
					writer.Write("{0}{1}{2}=\"{3}\"", Environment.NewLine, attributePrefix, attribute.Name, attribute.Value);
				}
			}

			if (element.HasChildren) {
				writer.WriteLine(">");

				foreach (XPathNavigator child in element.SelectChildren(XPathNodeType.Element)) {
					WriteElement(writer, indent + 1, child);
				}

				foreach (XPathNavigator child in element.SelectChildren(XPathNodeType.Text)) {
					writer.WriteLine(child.Value);
				}

				writer.WriteLine("{0}</{1}>", elementPrefix, element.Name);
			}
			else {
				writer.WriteLine("/>");
			}
		}
	}
}
