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

#include "../DirectXObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		ref class Effect;
		
		/// <remarks>
		/// EffectPool is a common memory space for sharing variables between effects.
		/// Using EffectPools can improve performance by reducing the number state change
		/// API calls.
		/// </remarks>
		public ref class EffectPool : public DirectXBase
		{
			DXOBJECT(ID3D10EffectPool);

		internal:
			EffectPool( ID3D10EffectPool* effectPool );
		
		public:
			
		  /// <summary>
			/// Constructs a new <see cref="EffectPool"/>.
			/// </summary>
			/// <param name="effectPool">An IntPtr to an unmanaged ID3D10EffectPool.</param>
			EffectPool( IntPtr effectPool );
			
			/// <summary>
			/// Releases object resources.
			/// </summary>
			virtual ~EffectPool() { Destruct(); }
			
			/// <summary>
			/// Get the effect that created the effect pool.
			/// </summary>
			Effect^ AsEffect();
			
			static EffectPool^ FromFile( Device^ device, String^ fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static EffectPool^ FromFile( Device^ device, String^ fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors );
			static EffectPool^ FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static EffectPool^ FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors );
			static EffectPool^ FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static EffectPool^ FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors );
		};
	}
};