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
using System.Text.RegularExpressions;

namespace BuildTasks {
	public class DowngradeSolution : Task {
		string inputSolution;
		string outputSolution;

		static readonly string sourceFormatVersion = "Microsoft Visual Studio Solution File, Format Version 10.00";
		static readonly string sourceToolVersion = "# Visual Studio 2008";
		static readonly string targetFormatVersion = "Microsoft Visual Studio Solution File, Format Version 9.00";
		static readonly string targetToolVersion = "# Visual Studio 2005";
		
		[Required]
		public string InputSolution {
			get {
				return inputSolution;
			}
			set {
				inputSolution = value;
			}
		}

		[Required]
		public string OutputSolution {
			get {
				return outputSolution;
			}
			set {
				outputSolution = value;
			}
		}

		public override bool Execute() {
			if (!File.Exists(inputSolution)) {
				Log.LogError(string.Format("Input solution file '{0}' does not exist.", inputSolution));
				return false;
			}
			
			string[] lines = File.ReadAllLines(inputSolution);			
			for(int index = 0; index < lines.Length; ++index) {
				if(lines[index].StartsWith(sourceFormatVersion)) {
					lines[index] = targetFormatVersion;
				} else if(lines[index].StartsWith(sourceToolVersion)) {
					lines[index] = targetToolVersion;
				}
			}
			
			File.WriteAllLines(outputSolution,lines);
			return true;
		}
	}
}
