using System;
using System.Text;
using System.Net;
using System.Xml;

namespace MsdnLinkGenerator
{
	class Program
	{
		const string MsdnLinkPrefix = "http://msdn.";

		static WebClient m_client = new WebClient();
		static string[] m_searchEngines;
		static int m_currentEngine = 0;
		static int m_searchCount = 0;

		static string GetMsdnLink(string searchString)
		{
			if(string.IsNullOrEmpty(searchString))
				return null;

			try
			{
				string uri = string.Format(m_searchEngines[m_currentEngine], searchString);
				byte[] data = m_client.DownloadData(uri);
				
				//don't issue more than 50 searches in a row to the same engine
				++m_searchCount;
				if(m_searchCount >= 50)
				{
					m_currentEngine = (m_currentEngine + 1) % m_searchEngines.Length;
					m_searchCount = 0;
				}

				string pageText = Encoding.ASCII.GetString(data);
				int linkPos = pageText.IndexOf(MsdnLinkPrefix);
				if(linkPos < 0)
					return null;
				int endPos = pageText.IndexOf("\"", linkPos);
				if(endPos < 0)
					return null;

				string link = pageText.Substring(linkPos, endPos - linkPos);
				return link;
			}
			catch(System.Net.WebException)
			{
				Console.WriteLine("Failed to search, moving to a new engine...");
				++m_currentEngine;
				if(m_currentEngine >= m_searchEngines.Length)
				{
					m_currentEngine = 0;
					//take some time to let the various engines cool off
					Console.WriteLine("Pausing queries for ten minutes...");
					System.Threading.Thread.Sleep(10 * 60 * 1000);
				}

				return GetMsdnLink(searchString);
			}
		}

		static string ExtractLinkCore(string uri)
		{
			if(string.IsNullOrEmpty(uri))
				return null;

			int startPos = uri.LastIndexOf('/');
			int endPos = uri.LastIndexOf('(');
			if(startPos < 0 || endPos < 0)
				return null;

			++startPos;
			return uri.Substring(startPos, endPos - startPos);
		}

		static void ProcessXml(string file)
		{
			XmlDocument doc = new XmlDocument();
			doc.Load(file);

			int i = 0;
			XmlNodeList nodes = doc.SelectNodes("//unmanaged");
			foreach(XmlElement element in nodes)
			{
				if(element.HasAttribute("href"))
					continue;

				string text = element.InnerText;
				string link = GetMsdnLink(text);
				string core = ExtractLinkCore(link);

				if(string.IsNullOrEmpty(core))
					continue;

				XmlAttribute attrib = doc.CreateAttribute("href");
				attrib.InnerText = core;
				element.Attributes.Append(attrib);

				++i;
				Console.WriteLine("({2}/{3}) Linked \"{0}\" to document: {1}.", text, core, i, nodes.Count);

				System.Threading.Thread.Sleep(5 * 60 * 1000);
			}

			doc.Save(file);
		}

		static void Main(string[] args)
		{
			m_searchEngines = new string[]
			{
				"http://www.google.com/search?hl=en&q={0}+site%3Amsdn.microsoft.com%2Fen-us",
				//"http://search.live.com/results.aspx?q={0}+site%3Amsdn.microsoft.com%2Fen-us&form=QBLH&qs=n",
				"http://search.yahoo.com/search?p={0}+site%3Amsdn.microsoft.com%2Fen-us&fr=yfp-t-120&toggle=1&cop=mss&ei=UTF-8"
			};

			ProcessXml(@"D:\Promit\Documents\SlimDX-all\trunk\build\x86\Release\SlimDX.xml");
		}
	}
}
