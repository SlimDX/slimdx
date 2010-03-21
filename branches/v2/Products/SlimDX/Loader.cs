using System;
using System.Reflection;

using SlimDX.Direct3D10;
using SlimDX.DXGI;
using System.IO;

namespace SlimDX {
    public static class Loader {
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
