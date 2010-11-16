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
using System.Reflection;
using System.Runtime.InteropServices;

namespace SlimDX
{
    /// <summary>
    /// Result structure for COM methods.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Result : IEquatable<Result>
    {
        private int _code;
        private static MethodInfo _methodGetErrorDescription;

        public Result(int code)
        {
            _code = code;
        }

        public Result(uint code)
        {
            _code = unchecked((int)code);
        }

        public int Code
        {
            get { return _code; }
        }

        public bool Success
        {
            get { return Code >= 0; }
        }

        public bool Failure
        {
            get { return Code < 0; }
        }

        public static implicit operator Result(int result)
        {
            return new Result(result);
        }

        public bool Equals(Result other)
        {
            return this.Code == other.Code;
        }

        public override string ToString()
        {
            if (_methodGetErrorDescription != null)
                return _methodGetErrorDescription.Invoke(null, new object[] {_code}).ToString();
            return string.Format("Unknown error (HRESULT = 0x{0:X})", _code);
        }

        public void CheckError()
        {
            if (_code < 0)
            {
                throw new SlimDX2Exception(this);
            }
        }

        static Result()
        {
            _methodGetErrorDescription = null;
            try
            {
                string prefix = typeof (Result).Namespace;
                Assembly assembly = Assembly.LoadFrom(    prefix + ".Error.dll");
                Type type = assembly.GetType(prefix + ".ErrorManager");
                _methodGetErrorDescription = type.GetMethod("GetErrorMessage", BindingFlags.Static | BindingFlags.Public);
            }
            catch (Exception ex)
            {                
            }
        }

        public static Result Ok = new Result(unchecked((int)0x00000000));
        public static Result Abord = new Result(unchecked((int)0x80004004));
        public static Result AccessDenied = new Result(unchecked((int)0x80070005));
        public static Result Fail = new Result(unchecked((int)0x80004005));
        public static Result Handle = new Result(unchecked((int)0x80070006));
        public static Result InvalidArg = new Result(unchecked((int)0x80070057));
        public static Result NoInterface = new Result(unchecked((int)0x80004002));
        public static Result NotImplemented = new Result(unchecked((int)0x80004001));
        public static Result OutOfMemory = new Result(unchecked((int)0x8007000E));
        public static Result InvalidPointer = new Result(unchecked((int)0x80004003));
        public static Result UnexpectedFailure = new Result(unchecked((int)0x8000FFFF));
    }
}