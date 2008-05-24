using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace LineCounter
{
    enum FileType
    {
        SourceFile,
        HeaderFile
    }

    class CountedFile
    {
        public string Name;
        public string Path;
        public int TotalLines;
        public int CodeLines;
        public int Comments;
        public int BlankLines;
        public FileType FileType;
        public int Icon;
    }

    class NodeInfo
    {
        public List<CountedFile> Files = new List<CountedFile>();
    }
}
