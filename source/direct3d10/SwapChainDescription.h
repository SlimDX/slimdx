/*
* Copyright (c) 2007 SlimDX Group
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
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "Rational.h"

namespace SlimDX
{
	namespace Direct3D10
	{		
		[StructLayout( LayoutKind::Sequential )]
		public value class SwapChainDescription
		{
		private:
			int width;
            int height;
            Rational refreshRate;
            Format format;
            DisplayModeScanlineOrdering scanlineOrdering;
            DisplayModeScaling scaling;
            int sampleCount;
            int sampleQuality;
            SurfaceUsage usage;
            int bufferCount;
            IntPtr outputHandle;
            bool windowed;
            SwapEffect swapEffect;
            SwapChainFlags flags;

		public:
			property int Width
            {
                int get() { return width; }
                void set( int value ) { width = value; }
            }

            property int Height
            {
                int get() { return height; }
                void set( int value ) { height = value; }
            }

            property Rational RefreshRate
            {
                Rational get() { return refreshRate; }
                void set( Rational value ) { refreshRate = value; }
            }

            property SlimDX::Direct3D10::Format Format
            {
                SlimDX::Direct3D10::Format get() { return format; }
                void set( SlimDX::Direct3D10::Format value ) { format = value; }
            }

            property DisplayModeScanlineOrdering ScanlineOrdering
            {
                DisplayModeScanlineOrdering get() { return scanlineOrdering; }
                void set( DisplayModeScanlineOrdering value ) { scanlineOrdering = value; }
            }

            property DisplayModeScaling Scaling
            {
                DisplayModeScaling get() { return scaling; }
                void set( DisplayModeScaling value ) { scaling = value; }
            }

            property int SampleCount
            {
                int get() { return sampleCount; }
                void set( int value ) { sampleCount = value; }
            }

            property int SampleQuality
            {
                int get() { return sampleQuality; }
                void set( int value ) { sampleQuality = value; }
            }

            property SurfaceUsage Usage
            {
                SurfaceUsage get() { return usage; }
                void set( SurfaceUsage value ) { usage = value; }
            }

            property int BufferCount
            {
                int get() { return bufferCount; }
                void set( int value ) { bufferCount = value; }
            }

            property IntPtr OutputHandle
            {
                IntPtr get() { return outputHandle; }
                void set( IntPtr value ) { outputHandle = value; }
            }

            property bool Windowed
            {
                bool get() { return windowed; }
                void set( bool value ) { windowed = value; }
            }

            property SlimDX::Direct3D10::SwapEffect SwapEffect
            {
                SlimDX::Direct3D10::SwapEffect get() { return swapEffect; }
                void set( SlimDX::Direct3D10::SwapEffect value ) { swapEffect = value; }
            }

            property SwapChainFlags Flags
            {
                SwapChainFlags get() { return flags; }
                void set( SwapChainFlags value ) { flags = value; }
            }
		};
	}
};