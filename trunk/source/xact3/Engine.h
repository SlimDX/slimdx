/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include "../ComObject.h"
#include "../multimedia/WaveFormatExtensible.h"

#include "RuntimeParameters.h"
#include "RendererDetails.h"
#include "Enums.h"

namespace SlimDX
{
	using namespace Multimedia;

	namespace XACT3
	{
		public ref class Engine : public ComObject
		{
			COMOBJECT(IXACT3Engine, Engine);

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="Engine"/> class.
			/// </summary>
			/// <unmanaged>XACT3CreateEngine</unmanaged>
			Engine();
			//Engine( CreationFlags flags );

			/// <summary>
			/// Gets details about a specific renderer.
			/// </summary>
			/// <param name="rendererIndex">Index of the renderer to retrieve information from.</param>
			/// <returns>A new <see cref="RendererDetails"/> object that contains details of the renderer.</returns>
			/// <unmanaged>IXACT3Engine::GetRendererDetails</unmanaged>
			RendererDetails GetRendererDetails(int rendererIndex);

			/// <summary>
			/// Initialize the XACT engine using common default settings.
			/// </summary>
			/// <unmanaged>IXACT3Engine::Initialize</unmanaged>
			//Result Initialize( RuntimeParameters parameters );

			/// <summary>
			/// Shut down the XACT engine and free any resources in use.
			/// </summary>
			/// <unmanaged>IXACT3Engine::ShutDown</unmanaged>
			Result ShutDown();

			/// <summary>
			/// Performs periodic work that is required by the XACT engine. Typically this should be called every 30 to 100 milliseconds.
			/// </summary>
			/// <unmanaged>IXACT3Engine::DoWork</unmanaged>
			Result DoWork();

			/// <summary>
			/// Get the sound category index that corresponds to a friendly name string.
			/// </summary>
			/// <param name="friendlyName">A <see cref="String"/> describing the category's friendly name.</param>
			/// <returns>The category index for the friendly name if successful, otherwise -1.</returns>
			/// <unmanaged>IXACT3Engine::GetCategory</unmanaged>
			int GetCategory(String^ friendlyName);

			/// <summary>
			/// Stop a sound category.
			/// </summary>
			/// <param name="category">Index of the category to stop, as returned by <see cref="GetCategory"/>.</param>
			/// <param name="flags"><see cref="StopFlags"/> that specify how the cetegory is stopped.</param>
			/// <unmanaged>IXACT3Engine::Stop</unmanaged>
			Result Stop(int category, StopFlags flags);

			/// <summary>
			/// Set the volume of a sound category.
			/// </summary>
			/// <param name="category">Index of the category for which to set the volume, as returned by <see cref="GetCategory"/>.</param>
			/// <param name="volume">The volume level to set. This is a floating point scale where 0.0 means -96db, 1.0 means 0db and 2.0 means +6db.</param>
			/// <unmanaged>IXACT3Engine::SetVolume</unmanaged>
			Result SetVolume(int category, float volume);

			/// <summary>
			/// Pause a sound category.
			/// </summary>
			/// <param name="category">Index of the category to pause, as returned by <see cref="GetCategory"/>.</param>
			/// <param name="pause">The action to take. If true, playback is paused, if false, playback is resumed.</param>
			/// <unmanaged>IXACT3Engine::Pause</unmanaged>
			Result Pause(int category, bool pause);

			/// <summary>
			/// Get the corresponding index for a global variable name string.
			/// </summary>
			/// <param name="friendlyName">A <see cref="String"/> that contains the friendly name of the global variable.</param>
			/// <returns>The index for the global variable if it exists, otherwise -1.</returns>
			/// <unmanaged>IXACT3Engine::GetGlobalVariableIndex</unmanaged>
			int GetGlobalVariableIndex(String^ friendlyName);

			/// <summary>
			/// Get the value for a global variable.
			/// </summary>
			/// <param name="index">The index of the global variable.</param>
			/// <returns>The value that is currently held by the global variable.</returns>
			/// <unmanaged>IXACT3Engine::GetGlobalVariable</unmanaged>
			float GetGlobalVariable(int index);

			/// <summary>
			/// Set the value of a global variable.
			/// </summary>
			/// <param name="index">The index of the global variable.</param>
			/// <param name="value">The new value of the global variable.</param>
			/// <unmanaged>IXACT3Engine::SetGlobalVariable</unmanaged>
			Result SetGlobalVariable(int index, float value);

			/// <summary>
			/// Gets the total number of audio rendering devices that are available in the system.
			/// </summary>
			/// <unmanaged>IXACT3Engine::GetRendererCount</unmanaged>
			property int RendererCount { int get(); }

			/// <summary>
			/// Gets a <see cref="WaveFormatExtensible"/> object that represents the final mix format.
			/// </summary>
			/// <unmanaged>IXACT3Engine::GetFinalMixFormat</unmanaged>
			property WaveFormatExtensible^ FinalMixFormat { WaveFormatExtensible^ get(); }
		};
	}
}
