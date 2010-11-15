using System.Linq;

namespace SlimDX.Generator
{
    /// <summary>
    /// A class with keywords name for C#
    /// </summary>
    public class CSharpKeywords
    {
        /// <summary>
        /// Returns true if the name is a C# keyword
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static bool IsKeyword(string name)
        {
            return _csharpKeywords.Contains(name);
        }

        private static readonly string[] _csharpKeywords = new[]
                                                               {
                                                                   "abstract",
                                                                   "as",
                                                                   "base",
                                                                   "bool",
                                                                   "break",
                                                                   "byte",
                                                                   "case",
                                                                   "catch",
                                                                   "char",
                                                                   "checked",
                                                                   "class",
                                                                   "const",
                                                                   "continue",
                                                                   "decimal",
                                                                   "default",
                                                                   "delegate",
                                                                   "do",
                                                                   "double",
                                                                   "else",
                                                                   "enum",
                                                                   "event",
                                                                   "explicit",
                                                                   "extern",
                                                                   "false",
                                                                   "finally",
                                                                   "fixed",
                                                                   "float",
                                                                   "for",
                                                                   "foreach",
                                                                   "goto",
                                                                   "if",
                                                                   "implicit",
                                                                   "in",
                                                                   "int",
                                                                   "interface",
                                                                   "internal",
                                                                   "is",
                                                                   "lock",
                                                                   "long",
                                                                   "namespace",
                                                                   "new",
                                                                   "null",
                                                                   "object",
                                                                   "operator",
                                                                   "out",
                                                                   "override",
                                                                   "params",
                                                                   "private",
                                                                   "protected",
                                                                   "public",
                                                                   "readonly",
                                                                   "ref",
                                                                   "return",
                                                                   "sbyte",
                                                                   "sealed",
                                                                   "short",
                                                                   "sizeof",
                                                                   "stackalloc",
                                                                   "static",
                                                                   "string",
                                                                   "struct",
                                                                   "switch",
                                                                   "this",
                                                                   "throw",
                                                                   "true",
                                                                   "try",
                                                                   "typeof",
                                                                   "uint",
                                                                   "ulong",
                                                                   "unchecked",
                                                                   "unsafe",
                                                                   "ushort",
                                                                   "using",
                                                                   "virtual",
                                                                   "volatile",
                                                                   "void",
                                                                   "while",
                                                               };

    }
}
