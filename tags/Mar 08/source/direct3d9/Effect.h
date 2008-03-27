/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include "Device.h"
#include "BaseEffect.h"
#include "Shader.h"
#include "EffectStateManager.h"
#include "IResettable.h"

#include "EffectPool.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		public ref class Effect : public BaseEffect, IResettable
		{
			COMOBJECT(ID3DXEffect, Effect);

		private:
			IEffectStateManagerShim *shim;
			
		public:
			virtual ~Effect() { if( shim != NULL ) delete shim; }
			static Effect^ FromPointer( System::IntPtr pointer );

			static Effect^ FromMemory( Device^ device, array<System::Byte>^ memory, array<Macro>^ preprocessorDefines, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors );

			static Effect^ FromStream( Device^ device, System::IO::Stream^stream, array<Macro>^ preprocessorDefines, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, System::IO::Stream^stream, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, System::IO::Stream^stream, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool );

			static Effect^ FromString( Device^ device, System::String^ sourceData, array<Macro>^ preprocessorDefines, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors );
			static Effect^ FromString( Device^ device, System::String^ sourceData, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors);
			static Effect^ FromString( Device^ device, System::String^ sourceData, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool);

			static Effect^ FromFile( Device^ device, System::String^ fileName, array<Macro>^ preprocessorDefines, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors );
			static Effect^ FromFile( Device^ device, System::String^ sourceData, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] System::String^ %compilationErrors);
			static Effect^ FromFile( Device^ device, System::String^ sourceData, Include^ includeFile, System::String^ skipConstants, ShaderFlags flags, EffectPool^ pool);

			int Begin( FX flags );
			Result End();
			Result BeginPass( int pass );
			Result EndPass();

			Result BeginParameterBlock();
			EffectHandle^ EndParameterBlock();
			Result ApplyParameterBlock( EffectHandle^ parameterBlock );
			Result DeleteParameterBlock( EffectHandle^ parameterBlock );

			bool IsParameterUsed( EffectHandle^ parameter, EffectHandle^ technique );
			Result CommitChanges();

			EffectHandle^ FindNextValidTechnique( EffectHandle^ technique );
			bool ValidateTechnique( EffectHandle^ technique );

			virtual Result OnLostDevice();
			virtual Result OnResetDevice();

			property EffectHandle^ Technique
			{
				EffectHandle^ get();
				void set( EffectHandle^ value );
			}

			property IEffectStateManager^ StateManager
			{
				IEffectStateManager^ get();
				void set( IEffectStateManager^ value );
			}
		};
	}
}
