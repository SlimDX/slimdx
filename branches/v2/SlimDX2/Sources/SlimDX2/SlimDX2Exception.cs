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
using System.Runtime.Serialization;
using System.Security.Permissions;

namespace SlimDX2
{
    /// <summary>
    ///   The base class for errors that occur in SlimDX2.
    /// </summary>
    /// <unmanaged>None</unmanaged>
    [Serializable]
    public class SlimDX2Exception : Exception
    {
        private Result m_Result;

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.SlimDX2Exception" /> class.
        /// </summary>
        public SlimDX2Exception()
            : base("A SlimDX2 exception occurred.")
        {
            Result result = new Result(-2147467259);
            this.m_Result = result;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.SlimDX2Exception" /> class.
        /// </summary>
        /// <param name = "result">The result code that caused this exception.</param>
        public SlimDX2Exception(Result result)
            : base(result.ToString())
        {
            this.m_Result = result;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.SlimDX2Exception" /> class.
        /// </summary>
        /// <param name = "message">The message describing the exception.</param>
        public SlimDX2Exception(string message)
            : base(message)
        {
            Result result = new Result(-2147467259);
            this.m_Result = result;
        }

        protected SlimDX2Exception(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            this.m_Result = (Result) info.GetValue("Result", typeof (Result));
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.SlimDX2Exception" /> class.
        /// </summary>
        /// <param name = "message">The message describing the exception.</param>
        /// <param name = "innerException">The exception that caused this exception.</param>
        public SlimDX2Exception(string message, Exception innerException)
            : base(message, innerException)
        {
            Result result = new Result(-2147467259);
            this.m_Result = result;
        }

        /// <summary>
        ///   When overridden in a derived class, sets the <see cref = "T:System.Runtime.Serialization.SerializationInfo" /> with information about the exception.
        /// </summary>
        /// <param name = "info">The <see cref = "T:System.Runtime.Serialization.SerializationInfo" /> that holds the serialized object data about the exception being thrown.</param>
        /// <param name = "context">The <see cref = "T:System.Runtime.Serialization.StreamingContext" /> that contains contextual information about the source or destination.</param>
        [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.SerializationFormatter)]
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("Result", this.m_Result);
            base.GetObjectData(info, context);
        }

        /// <summary>
        ///   Gets the <see cref = "T:SlimDX2.Result">Result code</see> for the exception. This value indicates
        ///   the specific type of failure that occured within SlimDX2.
        /// </summary>
        public Result ResultCode
        {
            get { return this.m_Result; }
        }
    }
}