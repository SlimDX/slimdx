// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using HtmlAgilityPack;
using ICSharpCode.SharpZipLib.Zip;

namespace SlimDX2.Tools.HeaderToXIDL
{
    /// <summary>
    /// MSDN Documentation query class
    /// </summary>
    public class MsdnDoc
    {
        private static Regex stripSpace = new Regex(@"[\r\n]+\s+", RegexOptions.Multiline);
        private static Regex beginWithSpace = new Regex(@"^\s+");
        private ZipFile _zipFile;
        private bool isZipUpdated;

        /// <summary>
        /// Documentation item
        /// </summary>
        public class Item
        {
            public Item()
            {
                Items = new List<string>();
            }

            public List<string> Items { get; set; }

            public string Description { get; set; }

            public string Remarks { get; set; }

            public string Return { get; set; }
        }

        public MsdnDoc()
        {
            ArchiveName = "MSDNDoc.zip";
            UseArchive = true;
        }

        /// <summary>
        /// Archive to use to save the documentation
        /// </summary>
        public string ArchiveName { get; set; }

        /// <summary>
        /// Output path for the archive / Directory
        /// </summary>
        public string OutputPath { get; set; }

        /// <summary>
        /// Set to true to use a zip for cacing documentation
        /// </summary>
        public bool UseArchive { get; set; }

        /// <summary>
        /// Begin to request MSDN
        /// </summary>
        public void Begin()
        {
            string fullPath = (OutputPath ?? ".") + Path.DirectorySeparatorChar + ArchiveName;

            string outputDirectory = Path.GetDirectoryName(fullPath);

            if (!Directory.Exists(outputDirectory))
                Directory.CreateDirectory(outputDirectory);

            if (UseArchive)
            {
                isZipUpdated = false;

                string archiveFullPath = outputDirectory + Path.DirectorySeparatorChar + ArchiveName;

                if (File.Exists(archiveFullPath))
                    _zipFile = new ZipFile(archiveFullPath);
                else
                    _zipFile = ZipFile.Create(archiveFullPath);
            }
        }

        /// <summary>
        /// End request to MSDN. Archive is saved if any updated occured between Begin/End.
        /// </summary>
        public void End()
        {
            if (UseArchive)
            {
                if (isZipUpdated)
                    _zipFile.CommitUpdate();
                _zipFile.Close();
            }
        }

        /// <summary>
        /// Get the documentation for a particular prefix (include name) and a full name item
        /// </summary>
        /// <param name="prefixName"></param>
        /// <param name="name"></param>
        /// <returns></returns>
        public Item GetDocumentation(string prefixName, string name)
        {
            // Handle name with ends A or W
            if (name.EndsWith("A") || name.EndsWith("W"))
            {
                string previouewChar = new string(name[name.Length - 2], 1);

                if (previouewChar.ToUpper() != previouewChar)
                {
                    name = name.Substring(0, name.Length - 1);
                }
            }
            string doc = GetDocumentationFromCacheOrMsdn(prefixName, name);
            return MsdnDoc.ParseDocumentation(doc);
        }

        /// <summary>
        /// Internal ZipEntryStreamSource in order to add a string to a zip
        /// </summary>
        internal class ZipEntryStreamSource : IStaticDataSource
        {
            private Stream stream;
            public ZipEntryStreamSource(string doc)
            {
                byte[] byteArray = Encoding.ASCII.GetBytes( doc );
                stream = new MemoryStream( byteArray ); 
            }

            public Stream GetSource()
            {
                return stream;
            }
        }

        /// <summary>
        /// Handles documentation from zip/directory
        /// </summary>
        /// <param name="prefixName"></param>
        /// <param name="name"></param>
        /// <returns></returns>
        private string GetDocumentationFromCacheOrMsdn(string prefixName, string name)
        {
            string fileName = prefixName + "-" + name.Replace("::", "-") + ".html";

            string doc;

            if (UseArchive)
            {
                var zipEntry = _zipFile.GetEntry(fileName);
                if (zipEntry != null)
                {
                    var streamInput = new StreamReader(_zipFile.GetInputStream(zipEntry));
                    doc = streamInput.ReadToEnd();
                    streamInput.Close();
                }
                else
                {
                    // Begin update if zip is not updated
                    if (!isZipUpdated)
                    {
                        _zipFile.BeginUpdate();
                        isZipUpdated = true;
                    }

                    doc = GetDocumentationFromMsdn(name);
                    
                    _zipFile.Add(new ZipEntryStreamSource(doc), fileName);
                }
            } else
            {
                fileName = OutputPath + Path.DirectorySeparatorChar + fileName;

                if (!File.Exists(fileName))
                {
                    doc = GetDocumentationFromMsdn(name);
                    File.WriteAllText(fileName, doc);
                }
                else
                {
                    doc = File.ReadAllText(fileName);
                }
            }
            return doc;
        }

        /// <summary>
        /// Parse HtmlNode to extract a string from it. Replace anchors href with {{ }} 
        /// and code with [[ ]]
        /// </summary>
        /// <param name="htmlNode"></param>
        /// <returns></returns>
        private static string ParseNode(HtmlNode htmlNode)
        {
            StringBuilder documentation = new StringBuilder();

            if (htmlNode.Name == "a")
            {
                StringBuilder inside = new StringBuilder();
                foreach (var node in htmlNode.ChildNodes)
                    inside.Append(ParseNode(node).Trim());
                string insideStr = inside.ToString();

                if (!string.IsNullOrEmpty(insideStr) && insideStr != "Copy")
                {
                    documentation.Append("{{");
                    documentation.Append(insideStr);
                    documentation.Append("}}");
                }
                return documentation.ToString();
            }
            else if (htmlNode.Name == "pre")
            {
                return "[[" + ParseNode(htmlNode.FirstChild) + "]]\r\n";
            }
            else if (htmlNode.NodeType == HtmlNodeType.Text)
            {
                string text = htmlNode.InnerText;
                if (beginWithSpace.Match(text).Success)
                    text = beginWithSpace.Replace(text, " ");
                if (stripSpace.Match(text).Success)
                    text = stripSpace.Replace(text, " ");
                return text;
            }

            foreach (var node in htmlNode.ChildNodes)
            {
                string text = ParseNode(node);
                //if (documentation.Length > 0 && documentation[documentation.Length - 1] == '.' && !string.IsNullOrEmpty(text))
                //{
                //    documentation.Append(" ");
                //}
                documentation.Append(text);
            }
            return documentation.ToString();
        }

        private static string GetTextUntilNextHeader(HtmlNode htmlNode)
        {
            htmlNode = htmlNode.NextSibling;

            StringBuilder builder = new StringBuilder();
            while (htmlNode != null && htmlNode.Name != "h3")
            {
                builder.Append(ParseNode(htmlNode));
                htmlNode = htmlNode.NextSibling;
            }

            return builder.ToString();
        }

        /// <summary>
        /// Parse a MSDN documentation file
        /// </summary>
        /// <param name="documentationToParse"></param>
        /// <returns></returns>
        private static Item ParseDocumentation(string documentationToParse)
        {
            HtmlDocument htmlDocument = new HtmlDocument();
            //            htmlDocument.Load("Documentation\\d3d11-ID3D11Device-CheckCounter.html");
            htmlDocument.LoadHtml(documentationToParse);

            var element = htmlDocument.GetElementbyId("mainSection");

            // Page not found?
            if (element == null)
            {
                return new Item();
            }

            Item item = new Item();
            var firstNode = element.ChildNodes.FindFirst("p");
            if (firstNode != null)
                item.Description = ParseNode(firstNode);

            HtmlNode firstElement = element.ChildNodes.FindFirst("dl");
            if (firstElement != null)
            {
                List<string> currentDoc = new List<string>();
                var nodes = firstElement.ChildNodes;
                int ddCount = 0;
                foreach (HtmlNode htmlNode in nodes)
                {
                    if (htmlNode.Name == "dt")
                    {
                        if (currentDoc.Count > 0)
                        {
                            item.Items.Add(currentDoc[currentDoc.Count - 1]);
                            currentDoc.Clear();
                        }
                    }
                    else if (htmlNode.Name == "dd")
                    {
                        currentDoc.Add(ParseNode(htmlNode));
                    }
                }
                if (currentDoc.Count > 0)
                    item.Items.Add(currentDoc[currentDoc.Count - 1]);
            }
            var headerCollection = element.SelectNodes("//h3");
            if (headerCollection != null)
            {
                foreach (HtmlNode htmlNode in headerCollection)
                {
                    string text = ParseNode(htmlNode);
                    if (text.StartsWith("Remarks"))
                        item.Remarks = GetTextUntilNextHeader(htmlNode);
                    else if (text.StartsWith("Return"))
                        item.Return = GetTextUntilNextHeader(htmlNode);
                }
            }
            return item;
        }

        /// <summary>
        /// Get MSDN documentation using an http query
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private static string GetDocumentationFromMsdn(string name)
        {
            try
            {
                Console.WriteLine("Get MSDN Documentation for [{0}]", name);
                string url_format =
                    "http://msdn.microsoft.com/query/dev10.query?appId=Dev10IDEF1&l=EN-US&k=k%28{0}%29;k%28DevLang-%22C%2B%2B%22%29;k%28TargetOS-WINDOWS%29&rd=true";

                string url = string.Format(url_format, name);

                // Create web request

                var request = (HttpWebRequest) WebRequest.Create(url);

                // Set value for request headers

                request.Method = "GET";
                request.ProtocolVersion = HttpVersion.Version11;
                request.AllowAutoRedirect = true;
                request.Accept = "*/*";
                request.UserAgent = "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)";
                request.Headers.Add("Accept-Language", "en-us");
                request.KeepAlive = true;

                StreamReader responseStream = null;
                HttpWebResponse webResponse = null;
                string webResponseStream = string.Empty;

                // Get response for http web request
                webResponse = (HttpWebResponse) request.GetResponse();
                responseStream = new StreamReader(webResponse.GetResponseStream());
                webResponseStream = responseStream.ReadToEnd();

                return webResponseStream;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }
            return "";
        }
    }
}