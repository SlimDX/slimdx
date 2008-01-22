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

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class XFileSaveObject;
		ref class XFile;
		ref class XFileEnumerationObject;
		ref class XFileData;

		[Flags]
		public enum class XFileFormat : Int32
		{
			Binary = D3DXF_FILEFORMAT_BINARY,
			Text = D3DXF_FILEFORMAT_TEXT,
			Compressed = D3DXF_FILEFORMAT_COMPRESSED
		};

		public ref class XFileSaveData : public SlimDXObject
		{
			DXOBJECT(ID3DXFileSaveData);

		internal:
			XFileSaveData( ID3DXFileSaveData *object );

		public:
			XFileSaveData( IntPtr pointer );
			virtual ~XFileSaveData() { Destruct(); }

			XFileSaveData^ AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data );
			XFileSaveData^ AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data );

			void AddDataReference( String^ name, Guid id );

			property Guid Id { Guid get(); }
			property String^ Name { String^ get(); }
			property XFileSaveObject^ SaveObject { XFileSaveObject^ get(); }
			property Guid Type { Guid get(); }
		};

		public ref class XFileSaveObject : public SlimDXObject
		{
			DXOBJECT(ID3DXFileSaveObject);

		internal:
			XFileSaveObject( ID3DXFileSaveObject *object );

		public:
			XFileSaveObject( IntPtr pointer );
			virtual ~XFileSaveObject() { Destruct(); }

			XFileSaveData^ AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data );
			XFileSaveData^ AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data );
			XFile^ GetFile();
			void Save();
		};

		public ref class XFile : public SlimDXObject
		{
			DXOBJECT(ID3DXFile);

		internal:
			XFile( ID3DXFile *object );

		public:
			XFile( IntPtr pointer );
			XFile();
			virtual ~XFile() { Destruct(); }

			XFileEnumerationObject^ CreateEnumerationObject( String^ fileName, CharSet charSet );
			XFileEnumerationObject^ CreateEnumerationObject( array<Byte>^ memory );
			XFileEnumerationObject^ CreateEnumerationObject( Stream^ stream );
			XFileSaveObject^ CreateSaveObject( String^ fileName, CharSet charSet, XFileFormat format );

			void RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject );
			void RegisterTemplates( array<Byte>^ memory );
			void RegisterTemplates( Stream^ memory );
			void RegisterTemplates( String^ name );
		};

		public ref class XFileEnumerationObject : public SlimDXObject
		{
			DXOBJECT(ID3DXFileEnumObject);

		internal:
			XFileEnumerationObject( ID3DXFileEnumObject *object );

		public:
			XFileEnumerationObject( IntPtr pointer );
			virtual ~XFileEnumerationObject() { Destruct(); }

			XFileData^ GetChild( int id );
			XFileData^ GetDataObject( Guid id );
			XFileData^ GetDataObject( String^ name );
			XFile^ GetFile();

			property int ChildCount { int get(); }
		};

		public ref class XFileData : public SlimDXObject
		{
			DXOBJECT(ID3DXFileData);

		internal:
			XFileData( ID3DXFileData *data );

		public:
			XFileData( IntPtr pointer );
			virtual ~XFileData() { Destruct(); }

			XFileData^ GetChild( int id );
			XFileEnumerationObject^ GetEnumerationObject();

			DataStream^ Lock();
			void Unlock();

			property int ChildCount { int get(); }
			property Guid Id { Guid get(); }
			property Guid Type { Guid get(); }
			property String^ Name { String^ get(); }
			property bool IsReference { bool get(); }
		};
	}
}