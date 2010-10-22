// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
namespace Boost.Wave
{
    public enum TokenCategory : uint
    {
        IdentifierTokenType = 0x10000000,
        ParameterTokenType = 0x11000000,
        ExtParameterTokenType = 0x11100000,
        KeywordTokenType = 0x20000000,
        OperatorTokenType = 0x30000000,
        LiteralTokenType = 0x40000000,
        IntegerLiteralTokenType = 0x41000000,
        FloatingLiteralTokenType = 0x42000000,
        StringLiteralTokenType = 0x43000000,
        CharacterLiteralTokenType = 0x44000000,
        BoolLiteralTokenType = 0x45000000,
        PPTokenType = 0x50000000,
        PPConditionalTokenType = 0x50800000,

        UnknownTokenType = 0xA0000000,
        EOLTokenType = 0xB0000000,
        EOFTokenType = 0xC0000000,
        WhiteSpaceTokenType = 0xD0000000,
        InternalTokenType = 0xE0000000,

        TokenTypeMask = 0xFF000000,
        AltTokenType = 0x00100000,
        TriGraphTokenType = 0x00200000,
        AltExtTokenType = 0x00500000, // and, bit_and etc.
        ExtTokenTypeMask = 0xFFF00000,
        ExtTokenOnlyMask = 0x00F00000,
        TokenValueMask = 0x000FFFFF,
        MainTokenMask = 0xFF0FFFFF // TokenTypeMask|TokenValueMask        
    }
}