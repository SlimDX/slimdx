using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using SlimDX;

namespace BasicSound
{
    [StructLayout(LayoutKind.Sequential)]
    struct MMCKINFO
    {
        public int id;
        public int size;
        public int type;
        public int offset;
        public int flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct MMIOINFO
    {
        public int flags;
        public int procId;
        public IntPtr proc;
        public int errorRet;
        public IntPtr task;
        public int bufferLength;

        public IntPtr buffer;
        public IntPtr next;
        public IntPtr endRead;
        public IntPtr endWrite;

        public int bufferOffset;
        public int diskOffset;

        public int info1;
        public int info2;
        public int info3;
        public int reserved1;
        public int reserved2;
        public IntPtr handle;
    }

    [StructLayout(LayoutKind.Sequential)]
    class PCMWAVEFORMAT
    {
        public short wFormatTag;
        public short nChannels;
        public int nSamplesPerSec;
        public int nAvgBytesPerSec;
        public short nBlockAlign;
        public short wBitsPerSample;
    }

    class WaveFile : IDisposable
    {
        const int MMIO_ALLOCBUF = 0x00010000;
        const int MMIO_READ = 0;
        const int MMIO_FINDCHUNK = 0x0010;

        const int SEEK_SET = 0;

        const int WAVE_FORMAT_PCM = 1;

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern IntPtr mmioOpen(string fileName, IntPtr info, int openFlags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioClose(IntPtr handle, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioDescend(IntPtr handle, ref MMCKINFO info, ref MMCKINFO parent, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioDescend(IntPtr handle, ref MMCKINFO info, IntPtr parent, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioAscend(IntPtr handle, ref MMCKINFO info, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioRead(IntPtr handle, IntPtr data, long length);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioSeek(IntPtr handle, long offset, int origin);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioGetInfo(IntPtr handle, ref MMIOINFO info, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioAdvance(IntPtr handle, ref MMIOINFO info, int flags);

        [DllImport("winmm.dll", CharSet = CharSet.Auto)]
        static extern int mmioSetInfo(IntPtr handle, ref MMIOINFO info, int flags);

        int mmioFOURCC(char c1, char c2, char c3, char c4)
        {
            return (c4 << 24) | (c3 << 16) | (c2 << 8) | (c1);
        }

        IntPtr fileHandle = IntPtr.Zero;
        MMCKINFO fileInfo;
        MMCKINFO dataChunk;
        WaveFormatExtended fileFormat;

        public WaveFormatExtended Format
        {
            get { return fileFormat; }
        }

        public int DataSize
        {
            get { return dataChunk.size; }
        }

        public WaveFile(string fileName)
        {
            if (string.IsNullOrEmpty(fileName))
                throw new ArgumentNullException("fileName");

            fileHandle = mmioOpen(fileName, IntPtr.Zero, MMIO_ALLOCBUF | MMIO_READ);
            if (fileHandle == IntPtr.Zero)
                throw new FileNotFoundException("The wave file could not be found", fileName);

            try
            {
                ReadHeader();
                ResetFile();
            }
            catch(InvalidOperationException)
            {
                mmioClose(fileHandle, 0);
                throw new InvalidDataException("Invalid wave file");
            }
        }

        public int Read(byte[] data, int length)
        {
            MMIOINFO info = new MMIOINFO();

            long ret;
            if ((ret = mmioGetInfo(fileHandle, ref info, 0)) != 0)
                throw new InvalidOperationException();

            int dataIn = length;
            if (dataIn > dataChunk.size)
                dataIn = dataChunk.size;

            dataChunk.size -= dataIn;

            unsafe
            {
                for (int i = 0; i < dataIn; i++)
                {
                    fixed (byte* bufferPtr = &data[i])
                    {
                        if (info.next == info.endRead)
                        {
                            if (mmioAdvance(fileHandle, ref info, MMIO_READ) != 0)
                                throw new InvalidOperationException();

                            if (info.next == info.endRead)
                                throw new InvalidOperationException();
                        }

                        byte* nextPtr = (byte*)info.next;

                        *bufferPtr = *nextPtr;
                        nextPtr++;
                        info.next = new IntPtr(nextPtr);
                    }
                }
            }

            if (mmioSetInfo(fileHandle, ref info, 0) != 0)
                throw new InvalidOperationException();

            return dataIn;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (fileHandle != IntPtr.Zero)
                {
                    mmioClose(fileHandle, 0);
                    fileHandle = IntPtr.Zero;
                }
            }
        }

        void ReadHeader()
        {
            MMCKINFO info = new MMCKINFO();
            PCMWAVEFORMAT data = new PCMWAVEFORMAT();

            int size = Marshal.SizeOf(data);

            if (mmioDescend(fileHandle, ref fileInfo, IntPtr.Zero, 0) != 0)
                throw new InvalidOperationException();

            if (fileInfo.id != mmioFOURCC('R', 'I', 'F', 'F') ||
                fileInfo.type != mmioFOURCC('W', 'A', 'V', 'E'))
                throw new InvalidOperationException();

            info.id = mmioFOURCC('f', 'm', 't', ' ');
            if (mmioDescend(fileHandle, ref info, ref fileInfo, MMIO_FINDCHUNK) != 0)
                throw new InvalidOperationException();

            if (info.size < size)
                throw new InvalidOperationException();

            IntPtr pointer = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(data, pointer, false);

            if (mmioRead(fileHandle, pointer, size) != size)
            {
                Marshal.FreeHGlobal(pointer);
                throw new InvalidOperationException();
            }

            Marshal.PtrToStructure(pointer, data);

            if (data.wFormatTag == WAVE_FORMAT_PCM)
            {
                fileFormat = new WaveFormatExtended();
                fileFormat.AverageBytesPerSecond = data.nAvgBytesPerSec;
                fileFormat.BitsPerSample = data.wBitsPerSample;
                fileFormat.BlockAlignment = data.nBlockAlign;
                fileFormat.Channels = data.nChannels;
                fileFormat.FormatTag = (WaveFormatTag)data.wFormatTag;
                fileFormat.SamplesPerSecond = data.nSamplesPerSec;
                fileFormat.Size = 0;
            }
            else
            {
                Marshal.FreeHGlobal(pointer);
                throw new NotImplementedException();
            }

            Marshal.FreeHGlobal(pointer);

            if (mmioAscend(fileHandle, ref info, 0) != 0)
                throw new InvalidOperationException();
        }

        void ResetFile()
        {
            if (mmioSeek(fileHandle, fileInfo.offset + Marshal.SizeOf(typeof(int)), SEEK_SET) == -1)
                throw new InvalidOperationException();

            dataChunk = new MMCKINFO();
            dataChunk.id = mmioFOURCC('d', 'a', 't', 'a');
            if (mmioDescend(fileHandle, ref dataChunk, ref fileInfo, MMIO_FINDCHUNK) != 0)
                throw new InvalidOperationException();
        }
    }
}
