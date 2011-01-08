// Copyright (c) 2007-2011 SlimDX Group
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

namespace SlimDX.Generator
{
	class MetadataService
	//TODO: Some cleanup is needed in this class.
	{
		public MetadataService(IEnumerable<string> searchPaths)
		{
			foreach (var path in searchPaths)
			{
				if (!Directory.Exists(path))
					continue;

				foreach (var file in Directory.GetFiles(path, "*.fmd"))
				{
					var data = ParseFunctionMetadata(new ConfigFile(file));
					var parts = Path.GetFileNameWithoutExtension(file).Split('.');
					if (parts.Length == 1)
					{
						unscopedFunctionMetadata[parts[0]] = data;
					}
					else
					{
						Dictionary<string, Metadata> typeSpecificMetadata = null;
						if (!scopedFunctionMetadata.TryGetValue(parts[0], out typeSpecificMetadata))
						{
							typeSpecificMetadata = new Dictionary<string, Metadata>();
							scopedFunctionMetadata[parts[0]] = typeSpecificMetadata;
						}

						typeSpecificMetadata[parts[1]] = data;
					}
				}

				foreach (var file in Directory.GetFiles(path, "*.tmd"))
				{
					var data = ParseTypeMetadata(new ConfigFile(file));
					typeMetadata[Path.GetFileNameWithoutExtension(file)] = data;
				}
			}
		}

		public Metadata FindFunctionMetadata(string name)
		{
			Metadata result = null;
			var parts = name.Split('.');
			Dictionary<string, Metadata> container = null;
			if (scopedFunctionMetadata.TryGetValue(parts[0], out container))
			{
				if (container.TryGetValue(parts[1], out result))
					return result;
			}

			if (unscopedFunctionMetadata.TryGetValue(parts[1], out result))
				return result;
			return new Metadata();
		}

		public Metadata FindTypeMetadata(string name)
		{
			Metadata result = null;
			if (typeMetadata.TryGetValue(name, out result))
				return result;
			return new Metadata();
		}

		#region Implementation

		Dictionary<string, Dictionary<string, Metadata>> scopedFunctionMetadata = new Dictionary<string, Dictionary<string, Metadata>>();
		Dictionary<string, Metadata> unscopedFunctionMetadata = new Dictionary<string, Metadata>();
		Dictionary<string, Metadata> typeMetadata = new Dictionary<string, Metadata>();

		static Metadata ParseFunctionMetadata(ConfigFile file)
		{
			var result = new Metadata();
			foreach (var option in file.GetOptions("Properties"))
			{
				//TODO: The config file should eb able to do this kind of thign
				//      and should do stuff like error checking
				var parts = option.Split('=');
				result[parts[0]] = parts[1];
			}

			return result;
		}

		static Metadata ParseTypeMetadata(ConfigFile file)
		{
			var result = new Metadata();
			foreach (var option in file.GetOptions("Properties"))
			{
				//TODO: The config file should eb able to do this kind of thign
				//      and should do stuff like error checking
				var parts = option.Split('=');
				result[parts[0]] = parts[1];
			}

			return result;
		}

		#endregion
	}
}
