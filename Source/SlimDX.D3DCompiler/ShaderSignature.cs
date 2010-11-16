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
using SlimDX.Direct3D;

namespace SlimDX.D3DCompiler
{
    /// <summary>
    ///   Represents a shader signature.
    /// </summary>
    public class ShaderSignature : Blob
    {
        private DataStream data;

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.D3DCompiler.ShaderSignature" /> class.
        /// </summary>
        /// <param name = "data">A <see cref = "T:SlimDX.DataStream" /> containing the raw bytes of the shader signature.</param>
        public ShaderSignature(IntPtr ptr)
            : base(ptr)
        {
        }

        /// <summary>
        ///   Extracts the input and output signatures from a compiled shader or effect.
        /// </summary>
        /// <param name = "shaderBytecode">The bytecode of the compiled shader or effect.</param>
        /// <returns>The input and output signatures of the shader or effect.</returns>
        public static ShaderSignature GetInputOutputSignature(ShaderBytecode shaderBytecode)
        {
            Blob shaderSignature;
            try
            {
                D3D.GetInputAndOutputSignatureBlob(shaderBytecode.GetBufferPointer(),
                                                   shaderBytecode.GetBufferSize(), out shaderSignature);
            }
            catch (SlimDXException ex)
            {
                return null;
            }
            return new ShaderSignature(shaderSignature.NativePointer);
        }

        /// <summary>
        ///   Extracts the input signature from a compiled shader or effect.
        /// </summary>
        /// <param name = "shaderBytecode">The bytecode of the compiled shader or effect.</param>
        /// <returns>The input signature of the shader or effect.</returns>
        public static ShaderSignature GetInputSignature(ShaderBytecode shaderBytecode)
        {
            Blob shaderSignature;
            try
            {
                D3D.GetInputSignatureBlob(shaderBytecode.GetBufferPointer(),
                                          shaderBytecode.GetBufferSize(), out shaderSignature);
            }
            catch (SlimDXException ex)
            {
                return null;
            }
            return new ShaderSignature(shaderSignature.NativePointer);
        }

        /// <summary>
        ///   Extracts the output signature from a compiled shader or effect.
        /// </summary>
        /// <param name = "shaderBytecode">The bytecode of the compiled shader or effect.</param>
        /// <returns>The output signature of the shader or effect.</returns>
        public static ShaderSignature GetOutputSignature(ShaderBytecode shaderBytecode)
        {
            Blob shaderSignature;
            try
            {
                D3D.GetOutputSignatureBlob(shaderBytecode.GetBufferPointer(),
                                           shaderBytecode.GetBufferSize(), out shaderSignature);
            }
            catch (SlimDXException ex)
            {
                return null;
            }
            return new ShaderSignature(shaderSignature.NativePointer);
        }

        /// <summary>
        ///   Gets the raw data of the shader signature.
        /// </summary>
        public DataStream Data
        {
            get { return new DataStream(this); }
        }
    }
}