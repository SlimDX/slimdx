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

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class XFileSaveObject;
		ref class XFile;
		ref class XFileEnumerationObject;
		ref class XFileData;

		[System::Flags]
		public enum class XFileFormat : System::Int32
		{
			Binary = D3DXF_FILEFORMAT_BINARY,
			Text = D3DXF_FILEFORMAT_TEXT,
			Compressed = D3DXF_FILEFORMAT_COMPRESSED
		};

		public ref class XFileSaveData : public ComObject
		{
			COMOBJECT(ID3DXFileSaveData);

		internal:
			XFileSaveData( ID3DXFileSaveData *object );

		public:
			XFileSaveData( System::IntPtr pointer );
			virtual ~XFileSaveData() { Destruct(); }

			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, array<System::Byte>^ data );
			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, System::IO::Stream^ data );

			Result AddDataReference( System::String^ name, System::Guid id );

			property System::Guid Id { System::Guid get(); }
			property System::String^ Name { System::String^ get(); }
			property XFileSaveObject^ SaveObject { XFileSaveObject^ get(); }
			property System::Guid Type { System::Guid get(); }
		};

		public ref class XFileSaveObject : public ComObject
		{
			COMOBJECT(ID3DXFileSaveObject);

		internal:
			XFileSaveObject( ID3DXFileSaveObject *object );

		public:
			XFileSaveObject( System::IntPtr pointer );
			virtual ~XFileSaveObject() { Destruct(); }

			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, array<System::Byte>^ data );
			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, System::IO::Stream^ data );
			XFile^ GetFile();
			Result Save();
		};

		public ref class XFile : public ComObject
		{
			COMOBJECT(ID3DXFile);

		internal:
			XFile( ID3DXFile *object );

		public:
			XFile( System::IntPtr pointer );
			XFile();
			virtual ~XFile() { Destruct(); }

			XFileEnumerationObject^ CreateEnumerationObject( System::String^ fileName, System::Runtime::InteropServices::CharSet charSet );
			XFileEnumerationObject^ CreateEnumerationObject( array<System::Byte>^ memory );
			XFileEnumerationObject^ CreateEnumerationObject( System::IO::Stream^ stream );
			XFileSaveObject^ CreateSaveObject( System::String^ fileName, System::Runtime::InteropServices::CharSet charSet, XFileFormat format );

			Result RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject );
			Result RegisterTemplates( array<System::Byte>^ memory );
			Result RegisterTemplates( System::IO::Stream^ memory );
			Result RegisterTemplates( System::String^ name );
		};

		public ref class XFileEnumerationObject : public ComObject
		{
			COMOBJECT(ID3DXFileEnumObject);

		internal:
			XFileEnumerationObject( ID3DXFileEnumObject *object );

		public:
			XFileEnumerationObject( System::IntPtr pointer );
			virtual ~XFileEnumerationObject() { Destruct(); }

			XFileData^ GetChild( int id );
			XFileData^ GetDataObject( System::Guid id );
			XFileData^ GetDataObject( System::String^ name );
			XFile^ GetFile();

			property int ChildCount { int get(); }
		};

		public ref class XFileData : public ComObject
		{
			COMOBJECT(ID3DXFileData);

		internal:
			XFileData( ID3DXFileData *data );

		public:
			XFileData( System::IntPtr pointer );
			virtual ~XFileData() { Destruct(); }

			XFileData^ GetChild( int id );
			XFileEnumerationObject^ GetEnumerationObject();

			DataStream^ Lock();
			Result Unlock();

			property int ChildCount { int get(); }
			property System::Guid Id { System::Guid get(); }
			property System::Guid Type { System::Guid get(); }
			property System::String^ Name { System::String^ get(); }
			property bool IsReference { bool get(); }
		};
	}
}