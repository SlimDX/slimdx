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
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text.RegularExpressions;
using SlimDX.Generator.ObjectModel;
using System.Text;

namespace SlimDX.Generator
{
	class TemplateEngine
	{
		#region Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="TemplateEngine"/> class.
		/// </summary>
		/// <param name="templateSearchPaths">The template search paths.</param>
		public TemplateEngine(IEnumerable<string> templateSearchPaths)
		{
			if (templateSearchPaths == null)
				throw new ArgumentNullException("templateSearchPaths");

			foreach (var path in templateSearchPaths)
			{
				searchPaths.Add(path);
				searchPaths.UnionWith(Directory.EnumerateDirectories(path, "*", SearchOption.AllDirectories));
			}

			if (searchPaths.Count == 0)
				throw new ArgumentException("At least one template search path must be specified.", "templateSearchPaths");
		}

		Regex directiveRegex = new Regex(@"\$\((.*?)\)", RegexOptions.Compiled);

		/// <summary>
		/// Applies the specified template to the given source object, using the template source instead
		/// of looking up the template file.
		/// </summary>
		/// <param name="templateText">The template text.</param>
		/// <param name="source">The object used as a data source during evaluation.</param>
		/// <returns>The generated string.</returns>
		public string Apply(string templateText, object source)
		{
			if (string.IsNullOrEmpty(templateText))
				throw new ArgumentException("Value may not be null or empty.", "template");
			if (source == null)
				throw new ArgumentNullException("source");

			var builder = new StringBuilder();
			foreach (var line in templateText.Split(new[] { Environment.NewLine }, StringSplitOptions.None))
			{
				// Iteratively replacing matches in this fashion ensures that the line sent to
				// EvaluateDirective always contains fully evaluated text before the matched
				// directive. This allows for correct handling of multiple directives per line.
				var result = line;
				var collection = directiveRegex.Matches(line);
				for (int matchIndex = 0; matchIndex < collection.Count; ++matchIndex)
					result = directiveRegex.Replace(result, m => EvaluateDirective(m, result, source), 1);

				// Restore the original newline that was stripped away by the split.
				builder.AppendLine(result);
			}

			return builder.ToString();
		}

		/// <summary>
		/// Applies the specified template to the given source object.
		/// </summary>
		/// <param name="templateName">The text template.</param>
		/// <param name="source">The object used as a data source during evaluation.</param>
		/// <returns>The generated string.</returns>
		public string ApplyByName(string templateName, object source)
		{
			if (string.IsNullOrEmpty(templateName))
				throw new ArgumentException("Value may not be null or empty.", "template");
			if (source == null)
				throw new ArgumentNullException("source");

			// Object model instances have metadata that can redirect the applied template.
			var element = source as BaseElement;
			if (element != null)
			{
				if (element.Metadata["Omit"] != null)
					return string.Empty;
				templateName = element.Metadata["OverrideTemplate"] ?? templateName;
			}

			var templateFile = FindTemplate(templateName);
			if (templateFile == null)
				throw new FileNotFoundException(string.Format("No template named '{0}' exists.", templateName));

			return Apply(File.ReadAllText(templateFile), source);
		}

		/// <summary>
		/// Registers a callback to be invoked when evaluating a callback token.
		/// </summary>
		/// <param name="token">The token name.</param>
		/// <param name="callback">The callback to invoke.</param>
		public void RegisterCallback(string token, Func<TemplateEngine, object, string> callback)
		{
			if (string.IsNullOrEmpty(token))
				throw new ArgumentException("Value may not be null or empty.", "token");
			if (callback == null)
				throw new ArgumentNullException("callback");

			callbacks[token] = callback;
		}

		/// <summary>
		/// Registers all of the methods defined on a type as callbacks to be invoked when evaluating a callback token.
		/// </summary>
		/// <param name="type">The type containing the methods to register.</param>
		public void RegisterCallbacks(Type type)
		{
			foreach (var method in type.GetMethods(BindingFlags.Public | BindingFlags.Static | BindingFlags.DeclaredOnly))
			{
				if (method.ReturnType != callbackReturn)
					continue;
				if (!method.GetParameters().Select(p => p.ParameterType).SequenceEqual(callbackSignature))
					continue;

				RegisterCallback(method.Name, (Func<TemplateEngine, object, string>)Delegate.CreateDelegate(typeof(Func<TemplateEngine, object, string>), method));
			}
		}

		#endregion

		#region Implementation

		const string callbackGlyph = "@";
		const string separatorGlyph = ".";

		static readonly Type[] callbackSignature = new[] { typeof(TemplateEngine), typeof(object) };
		static readonly Type callbackReturn = typeof(string);

		HashSet<string> searchPaths = new HashSet<string>();

		Dictionary<string, Func<TemplateEngine, object, string>> callbacks = new Dictionary<string, Func<TemplateEngine, object, string>>();

		Regex valueRegex = new Regex(@"[^:]*", RegexOptions.Compiled);
		Regex handlerRegex = new Regex(@"\:(.*)", RegexOptions.Compiled);
		Regex suffixRegex = new Regex(@" (.*)", RegexOptions.Compiled);

		/// <summary>
		/// Searches for a template with the specified name.
		/// </summary>
		/// <param name="templateName">The name of the desired template.</param>
		/// <returns>The full path to the matching template file, or null if no template was found.</returns>
		string FindTemplate(string templateName)
		{
			var fileName = string.Format("{0}.txt", templateName);
			foreach (var path in searchPaths)
			{
				var file = Path.Combine(path, fileName);
				if (File.Exists(file))
					return file;
			}

			return null;
		}

		/// <summary>
		/// Processes a regular expression match for a template directive during template application.
		/// </summary>
		/// <param name="source">The data source used to fill out the template.</param>
		/// <param name="match">The match object for the directive.</param>
		/// <returns>The evaluated directive's value.</returns>
		string EvaluateDirective(Match match, string line, object source)
		{
			// Group 0 is the entire match; group 1 is the first one defined by the expression.
			var directive = match.Groups[1].Value;
			var valueMatch = valueRegex.Match(directive);
			var value = ResolveValue(valueMatch.Value, source);

			// The handler delegate allows the various options for value printing
			// (through a callback, a template, or directly via ToString()) to be
			// invoke transparently in the final output stage.
			Func<object, string> handler = x => x.ToString();
			var handlerMatch = handlerRegex.Match(directive);
			if (handlerMatch.Success)
			{
				var handlerName = handlerMatch.Groups[1].Value;
				if (handlerName.StartsWith(callbackGlyph))
					handler = x => ResolveCallback(handlerName, x).ToString();
				else
					handler = x => ApplyByName(handlerName, x);
			}

			var builder = new StringBuilder();
			var enumerable = QueryForIEnumerable(value);
			if (enumerable == null)
			{
				builder.Append(handler(value));
			}
			else
			{
				foreach (var item in enumerable)
					builder.AppendLine(handler(item));
			}

			// Once the values have been resolved, the prefix needs to be attached to each
			// line of the final output.
			var prefix = line.Substring(0, match.Index);
			var lines = builder.ToString().Split(new[] { Environment.NewLine }, StringSplitOptions.None);
			builder.Clear();
			for (var lineIndex = 0; lineIndex < lines.Length; ++lineIndex)
			{
				// Skip prefix attachment for the first item; it's already in the source text.
				if (lineIndex > 0)
					builder.Append(prefix);
				builder.AppendLine(lines[lineIndex]);
			}

			return builder.ToString().TrimEnd();
		}

		object ResolveCallback(string callbackName, object source)
		{
			Func<TemplateEngine, object, string> callback = null;
			callbackName = callbackName.Remove(0, callbackGlyph.Length);
			if (!callbacks.TryGetValue(callbackName, out callback))
				throw new InvalidOperationException(string.Format("No callback registered for '{0}'.", callbackName));
			return callback(this, source);
		}

		object ResolveValue(string value, object source)
		{
			if (value.StartsWith(callbackGlyph))
				return ResolveCallback(value, source);

			return ResolveProperty(value, source);
		}

		/// <summary>
		/// Gets the value of the indicated property from the source object.
		/// </summary>
		/// <param name="key">The name of the property to get.</param>
		/// <param name="source">The source object.</param>
		/// <returns>The value of the specified property.</returns>
		static object ResolveProperty(string name, object source)
		{
			// if the name has a period, it indicates a sub-property of the element
			int period = name.IndexOf(separatorGlyph);
			string subName = null;
			if (period >= 0)
			{
				subName = name.Substring(period + 1);
				name = name.Substring(0, period);
			}

			var value = source.GetType().GetProperty(name).GetValue(source, null);
			if (subName != null)
				value = ResolveProperty(subName, value);

			return value;
		}

		static IEnumerable QueryForIEnumerable(object source)
		{
			// While technically enumerable, we don't want to treat strings as such.
			if (source is string)
				return null;

			var enumerable = source as IEnumerable;
			if (enumerable == null)
			{
				var iter = source as IEnumerator;
				if (iter != null)
					enumerable = Iterate(iter);
			}

			return enumerable;
		}

		static IEnumerable Iterate(IEnumerator iterator)
		{
			while (iterator.MoveNext())
				yield return iterator.Current;
		}

		#endregion
	}
}
