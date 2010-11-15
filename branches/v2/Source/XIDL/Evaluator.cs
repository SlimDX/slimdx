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
using System.CodeDom.Compiler;
using System.Globalization;
using Microsoft.JScript;

namespace SlimDX2.Tools.XIDL
{
    /// <summary>
    /// Simple expression evaluator using JScript engine
    /// </summary>
    public class Evaluator
    {
        public static int EvalToInteger(string statement)
        {
            string s = EvalToString(statement);
            return int.Parse(s.ToString());
        }

        public static double EvalToDouble(string statement)
        {
            string s = EvalToString(statement);
            return double.Parse(s, CultureInfo.InvariantCulture);
        }

        public static string EvalToString(string statement)
        {
            object o = statement;
            try
            {
                o = _evaluator.Evaluate(statement);
            }
            catch (Exception ex)
            {
                Console.Out.WriteLine("Evaluator failed : unable to eval value [{0}]", statement);
            }
            return o.ToString();
        }

        static Evaluator()
        {
            var compiler = new JScriptCodeProvider().CreateCompiler();
            var parameters = new CompilerParameters {GenerateInMemory = true};
            var results = compiler.CompileAssemblyFromSource(parameters, _jscriptSource);
            var assembly = results.CompiledAssembly;
            var evaluatorType = assembly.GetType("Evaluator.Evaluator");
            _evaluator = Activator.CreateInstance(evaluatorType);
        }

        private static readonly dynamic _evaluator;

        private const string _jscriptSource =
            @"package Evaluator
            {
               class Evaluator
               {
                  public function Evaluate(expr : String) : String 
                  { 
                     return eval(expr); 
                  }
               }
            }";
    }
}