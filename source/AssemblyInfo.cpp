#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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
using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute("SlimDX")];
[assembly:AssemblyDescriptionAttribute("Provides a managed wrapper around Microsoft DirectX.")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("SlimDX Group")];
[assembly:AssemblyProductAttribute("SlimDX")];
[assembly:AssemblyCopyrightAttribute("Copyright © 2007-2009 SlimDX Group")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version
//      Build Number
//      Revision
//
// You can specify all the value or you can default the Revision and Build Numbers
// by using the '*' as shown below:

[assembly:AssemblyVersionAttribute("2.0.7.41")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];

#ifdef PUBLIC
[assembly:InternalsVisibleTo("SlimDX.Windows7, PublicKey="
"00240000048000009400000006020000002400005253413100040000010001004919b163e34445"
"ac4942b40b271cf7ce3e3713abe7c6e8bb43fd19dcab991b5106a6c15460b6110ea25c2907e333"
"d56c1a92426bccffa8c4da9ed943dfcc91f8130b9b3a0a3f10ff4c9ae6ee92769ffe2d15d122e3"
"e351bbd6e2b8880e02edbec193a50a7d3088b1c80d259fe0851357fb7f1b37bd89871b709471d8"
"d801a6bd")];
[assembly:InternalsVisibleTo("SlimDX.Tests, PublicKey="
"00240000048000009400000006020000002400005253413100040000010001004919b163e34445"
"ac4942b40b271cf7ce3e3713abe7c6e8bb43fd19dcab991b5106a6c15460b6110ea25c2907e333"
"d56c1a92426bccffa8c4da9ed943dfcc91f8130b9b3a0a3f10ff4c9ae6ee92769ffe2d15d122e3"
"e351bbd6e2b8880e02edbec193a50a7d3088b1c80d259fe0851357fb7f1b37bd89871b709471d8"
"d801a6bd")];
#else
[assembly:InternalsVisibleTo("SlimDX.Windows7")];
[assembly:InternalsVisibleTo("SlimDX.Tests")];
#endif