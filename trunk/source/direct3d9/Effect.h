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

using namespace System::IO;
using namespace System::Runtime::InteropServices;

#include "../math/Math.h"
#include "Device.h"
#include "BaseEffect.h"
#include <vcclr.h>

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		class IncludeShim;

		public ref class Include abstract
		{
		internal:
			IncludeShim* Shim;

		protected:
			Include();

		public:
			~Include();
			!Include();

			virtual void Open() = 0;
			virtual void Close() = 0;
		};

		class IncludeShim : public ID3DXInclude
		{
		private:
			gcroot<Include^> m_WrappedInterface;

		public:
			IncludeShim( Include^ wrappedInterface );

			HRESULT WINAPI Open( D3DXINCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes );
			HRESULT WINAPI Close( LPCVOID pData );
		};

		public value class Macro
		{
		internal:
			//helper function to resolve array<Macro>^ to D3DXMACRO*
			static D3DXMACRO* Marshal( array<Macro>^ macros, [Out] array<GCHandle>^% handles );
			static void Unmarshal( D3DXMACRO* macros, array<GCHandle>^ handles );

		public:
			String^ Name;
			String^ Definition;
		};

		public ref class EffectPool sealed : public DirectXObject<ID3DXEffectPool>
		{
		public:
			EffectPool();

			//ID3DXEffectPool has no methods
		};
		
		public ref class Effect sealed : public BaseEffect
		{
		internal:
			property ID3DXEffect* EffectPointer
			{
				ID3DXEffect* get() { return (ID3DXEffect*) m_Pointer; }
			}

		public:
			Effect( ID3DXEffect* effect );

			//FromMemory
			static Effect^ FromMemory( Device^ device, array<Byte>^ memory, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );

			//FromStream
			static Effect^ FromStream( Device^ device, Stream^ stream, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromStream( Device^ device, Stream^ stream, Include^ includeFile, 
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool );

			//FromString
			static Effect^ FromString( Device^ device, String^ sourceData, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors);
			static Effect^ FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool);

			//FromFile
			static Effect^ FromFile( Device^ device, String^ fileName, array<Macro>^ preprocessorDefines, Include^ includeFile,
				String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors );
			static Effect^ FromFile( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors);
			static Effect^ FromFile( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
				ShaderFlags flags, EffectPool^ pool);

			int Begin( FX flags );
			void End();
			void BeginPass( int pass );
			void EndPass();

			void BeginParameterBlock();
			EffectHandle^ EndParameterBlock();
			void ApplyParameterBlock( EffectHandle^ parameterBlock );
			void DeleteParameterBlock( EffectHandle^ parameterBlock );

			bool IsParameterUsed( EffectHandle^ parameter, EffectHandle^ technique );
			void CommitChanges();

			EffectHandle^ FindNextValidTechnique( EffectHandle^ technique );
			bool ValidateTechnique( EffectHandle^ technique );

			property EffectHandle^ Technique
			{
				EffectHandle^ get();
				void set( EffectHandle^ value );
			}

			void OnLostDevice();
			void OnResetDevice();
		};
	}
}
