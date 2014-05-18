/*
* Copyright (c) 2007-2014 SlimDX Group
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
#include "stdafx.h"

#include "../Utilities.h"

#include "Direct3D11Exception.h"

#include "Device11.h"
#include "Resource11.h"
#include "ShaderResourceView11.h"
#include "TextureLoader.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D11
{
	Resource^ TextureLoader::LoadDDS(Device^ device, String^ fileName)
	{
		if (device == nullptr)
			throw gcnew ArgumentNullException("device");
		if (String::IsNullOrEmpty(fileName))
			throw gcnew ArgumentNullException("fileName");

		ID3D11Resource *texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);

		HRESULT hr = DirectX::CreateDDSTextureFromFile(device->InternalPointer, pinnedName, &texture, NULL); 
		if (RECORD_D3D11(hr).IsFailure)
			return nullptr;

		return Resource::FromPointer(texture);
	}

	Resource^ TextureLoader::LoadDDS(Device^ device, String^ fileName, [Out] ShaderResourceView^ %resourceView, [Out] AlphaMode %alphaMode)
	{
		if (device == nullptr)
			throw gcnew ArgumentNullException("device");
		if (String::IsNullOrEmpty(fileName))
			throw gcnew ArgumentNullException("fileName");

		ID3D11Resource *texture;
		ID3D11ShaderResourceView *view;
		DirectX::DDS_ALPHA_MODE mode;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);

		HRESULT hr = DirectX::CreateDDSTextureFromFile(device->InternalPointer, pinnedName, &texture, &view, 0, &mode); 
		if (RECORD_D3D11(hr).IsFailure)
			return nullptr;

		alphaMode = static_cast<AlphaMode>(mode);
		resourceView = ShaderResourceView::FromPointer(view);
		return Resource::FromPointer(texture);
	}

	Resource^ TextureLoader::LoadDDS(Device^ device, Stream^ data)
	{
		if (device == nullptr)
			throw gcnew ArgumentNullException("device");
		if (data == nullptr)
			throw gcnew ArgumentNullException("data");

		int ddsDataSize = 0;
		bool cleanUp = true;
		std::unique_ptr<char> dataPtr;
		char *ddsData = Utilities::ReadStream(data, ddsDataSize, cleanUp);
		if (cleanUp)
			dataPtr.reset(ddsData);

		ID3D11Resource *texture;
		HRESULT hr = DirectX::CreateDDSTextureFromMemory(device->InternalPointer, reinterpret_cast<uint8_t*>(ddsData), ddsDataSize, &texture, NULL); 
		if (RECORD_D3D11(hr).IsFailure)
			return nullptr;

		return Resource::FromPointer(texture);
	}

	Resource^ TextureLoader::LoadDDS(Device^ device, Stream^ data, [Out] ShaderResourceView^ %resourceView, [Out] AlphaMode %alphaMode)
	{
		if (device == nullptr)
			throw gcnew ArgumentNullException("device");
		if (data == nullptr)
			throw gcnew ArgumentNullException("data");

		int ddsDataSize = 0;
		bool cleanUp = true;
		std::unique_ptr<char> dataPtr;
		char *ddsData = Utilities::ReadStream(data, ddsDataSize, cleanUp);
		if (cleanUp)
			dataPtr.reset(ddsData);

		ID3D11Resource *texture;
		ID3D11ShaderResourceView *view;
		DirectX::DDS_ALPHA_MODE mode;

		HRESULT hr = DirectX::CreateDDSTextureFromMemory(device->InternalPointer, reinterpret_cast<uint8_t*>(ddsData), ddsDataSize, &texture, &view, 0, &mode); 
		if (RECORD_D3D11(hr).IsFailure)
			return nullptr;

		alphaMode = static_cast<AlphaMode>(mode);
		resourceView = ShaderResourceView::FromPointer(view);
		return Resource::FromPointer(texture);
	}
}
}