/* Copyright (c) 2007-2010 SlimDX Group
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
using System.Reflection;

using SlimDX.Direct3D10;
using SlimDX.DXGI;
using System.IO;

namespace SlimDX {
    /// <summary>
    /// Provides methods to load any of the various subsystem APIs supported by SlimDX.
    /// </summary>
    public static class Loader {
        /// <summary>
        /// Loads the Direct3D 10 subsystem.
        /// </summary>
        /// <returns>An interface to the D3D10 API object.</returns>
        public static IDirect3D10Api LoadDirect3D10() {
            Assembly implementation = null;
            if( IntPtr.Size == 8 ) {
                implementation = Assembly.LoadFrom( "SlimDX.Implementation.x64.dll" );
            } else if( IntPtr.Size == 4 ) {
                implementation = Assembly.LoadFrom( "SlimDX.Implementation.x86.dll" );
            } else {
                throw new InvalidOperationException( "Cannot determine the correct SlimDX architecture to load." );
            }

            return implementation.CreateInstance( "SlimDX.Direct3D10.Direct3D10Api" ) as IDirect3D10Api;
        }

        /// <summary>
        /// Loads the DXGI subsystem.
        /// </summary>
        /// <returns>An interface to the DXGI API object.</returns>
        public static IDXGIApi LoadDXGI() {
            Assembly implementation = null;
            if( IntPtr.Size == 8 ) {
                implementation = Assembly.LoadFrom( "SlimDX.Implementation.x64.dll" );
            } else if( IntPtr.Size == 4 ) {
                implementation = Assembly.LoadFrom( "SlimDX.Implementation.x86.dll" );
            } else {
                throw new InvalidOperationException( "Cannot determine the correct SlimDX architecture to load." );
            }

            return implementation.CreateInstance( "SlimDX.DXGI.DXGIApi" ) as IDXGIApi;
        }
    }
}
