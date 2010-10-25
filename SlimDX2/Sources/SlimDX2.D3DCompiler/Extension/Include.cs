using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;

namespace SlimDX2.D3DCompiler
{
    public partial interface Include
    {
        /// <summary>	
        /// A user-implemented method for opening and reading the contents of a shader #include file.	
        /// </summary>	
        /// <param name="type">A <see cref="SlimDX2.D3DCompiler.IncludeType"/>-typed value that indicates the location of the #include file. </param>
        /// <param name="fileName">Name of the #include file.</param>
        /// <param name="parentStream">Pointer to the container that includes the #include file.</param>
        /// <param name="stream">Stream that is associated with fileName to be read. This reference remains valid until <see cref="SlimDX2.D3DCompiler.Include.Close"/> is called.</param>
        /// <unmanaged>HRESULT Open([None] D3D_INCLUDE_TYPE IncludeType,[None] const char* pFileName,[None] LPCVOID pParentData,[None] LPCVOID* ppData,[None] UINT* pBytes)</unmanaged>
        //SlimDX2.Result Open(SlimDX2.D3DCompiler.IncludeType includeType, string fileNameRef, IntPtr pParentData, IntPtr dataRef, IntPtr bytesRef);
        void Open(IncludeType type, string fileName, Stream parentStream, out Stream stream);

        /// <summary>	
        /// A user-implemented method for closing a shader #include file.	
        /// </summary>	
        /// <remarks>	
        /// If <see cref="SlimDX2.D3DCompiler.Include.Open"/> was successful, Close is guaranteed to be called before the API using the <see cref="SlimDX2.D3DCompiler.Include"/> interface returns.	
        /// </remarks>	
        /// <param name="stream">This is a reference that was returned by the corresponding <see cref="SlimDX2.D3DCompiler.Include.Open"/> call.</param>
        /// <unmanaged>HRESULT Close([None] LPCVOID pData)</unmanaged>
        void Close(Stream stream);
    }

    /// <summary>
    /// Internal Include Callback
    /// </summary>
    internal class IncludeCallback : SlimDX2.CppObject
    {
        private Include _callback;
        private Dictionary<IntPtr, Frame> _frames;
        private OpenCallBack _openCallBack;
        private CloseCallBack _closeCallBack;

        struct Frame
        {
            public Frame(Stream stream, GCHandle handle)
            {
                Stream = stream;
                Handle = handle;
            }

            public Stream Stream;
            public GCHandle Handle;

            public void Close()
            {
                Handle.Free();
            }
        }

        public IncludeCallback(Include callback)
        {
            _callback = callback;
            // Allocate object layout in memory 
            // - 1 pointer to VTBL table
            // - following that the VTBL itself - with 2 function pointers for Open and Close methods
            NativePointer = Marshal.AllocHGlobal(IntPtr.Size * 3);

            // Write pointer to vtbl
            IntPtr vtblPtr = IntPtr.Add(NativePointer, IntPtr.Size);
            Marshal.WriteIntPtr(NativePointer, vtblPtr);
            _openCallBack = new OpenCallBack(Open);
            Marshal.WriteIntPtr(vtblPtr, Marshal.GetFunctionPointerForDelegate(_openCallBack));
            _closeCallBack = new CloseCallBack(Close);
            Marshal.WriteIntPtr(IntPtr.Add(vtblPtr, IntPtr.Size), Marshal.GetFunctionPointerForDelegate(_closeCallBack));

            _frames = new Dictionary<IntPtr, Frame>();
        }

        ~IncludeCallback()
        {
            _openCallBack = null;
            _closeCallBack = null;
            Marshal.FreeHGlobal(NativePointer);            
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate SlimDX2.Result OpenCallBack(IntPtr thisPtr, SlimDX2.D3DCompiler.IncludeType includeType, IntPtr fileNameRef, IntPtr pParentData, ref IntPtr dataRef, ref int bytesRef);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate SlimDX2.Result CloseCallBack(IntPtr thisPtr, IntPtr pData);

        /// <summary>	
        /// A user-implemented method for opening and reading the contents of a shader #include file.	
        /// </summary>	
        /// <param name="includeType">A <see cref="SlimDX2.D3DCompiler.IncludeType"/>-typed value that indicates the location of the #include file. </param>
        /// <param name="fileNameRef">Name of the #include file.</param>
        /// <param name="pParentData">Pointer to the container that includes the #include file.</param>
        /// <param name="dataRef">Pointer to the buffer that Open returns that contains the include directives. This pointer remains valid until <see cref="SlimDX2.D3DCompiler.Include.Close"/> is called.</param>
        /// <param name="bytesRef">Pointer to the number of bytes that Open returns in ppData.</param>
        /// <returns>The user-implemented method should return S_OK. If Open fails when reading the #include file, the application programming interface (API) that caused Open to be called fails. This failure can occur in one of the following situations:The high-level shader language (HLSL) shader fails one of the D3D10CompileShader*** functions.The effect fails one of the D3D10CreateEffect*** functions.</returns>
        /// <unmanaged>HRESULT Open([None] D3D_INCLUDE_TYPE IncludeType,[None] const char* pFileName,[None] LPCVOID pParentData,[None] LPCVOID* ppData,[None] UINT* pBytes)</unmanaged>
        public SlimDX2.Result Open(IntPtr thisPtr, SlimDX2.D3DCompiler.IncludeType includeType, IntPtr fileNameRef, IntPtr pParentData, ref IntPtr dataRef, ref int bytesRef)
        {
            unsafe
            {
                try
                {
                    Stream stream = null;
                    Stream parentStream = null;

                    if (_frames.ContainsKey(pParentData))
                        parentStream = _frames[pParentData].Stream;

                    _callback.Open(includeType, new String((sbyte*)fileNameRef), parentStream, out stream);
                    if (stream == null)
                        return Result.Fail;

                    GCHandle handle;

                    if (stream is DataStream)
                    {
                        // Magic shortcut if we happen to get a DataStream
                        DataStream data = (DataStream)stream;
                        dataRef = data.PositionPointer;
                        bytesRef = (int)data.Length;
                        handle = new GCHandle();
                    }
                    else
                    {
                        // Read the stream into a byte array and pin it
                        byte[] data = SlimDX2.Utilities.ReadStream(stream);
                        handle = GCHandle.Alloc(data, GCHandleType.Pinned);
                        dataRef = handle.AddrOfPinnedObject();
                        bytesRef = data.Length;
                    }

                    _frames.Add(dataRef, new Frame(stream, handle));

                    return Result.Ok;
                }
                catch (SlimDX2Exception exception)
                {
                    return exception.ResultCode.Code;
                }
                catch (Exception ex)
                {
                    return Result.Fail;
                }
            }
        }

        /// <summary>	
        /// A user-implemented method for closing a shader #include file.	
        /// </summary>	
        /// <remarks>	
        /// If <see cref="SlimDX2.D3DCompiler.Include.Open"/> was successful, Close is guaranteed to be called before the API using the <see cref="SlimDX2.D3DCompiler.Include"/> interface returns.	
        /// </remarks>	
        /// <param name="pData">Pointer to the buffer that contains the include directives. This is the pointer that was returned by the corresponding <see cref="SlimDX2.D3DCompiler.Include.Open"/> call.</param>
        /// <returns>The user-implemented Close method should return S_OK. If Close fails when it closes the #include file, the application programming interface (API) that caused Close to be called fails. This failure can occur in one of the following situations:The high-level shader language (HLSL) shader fails one of the D3D10CompileShader*** functions.The effect fails one of the D3D10CreateEffect*** functions.</returns>
        /// <unmanaged>HRESULT Close([None] LPCVOID pData)</unmanaged>
        public SlimDX2.Result Close(IntPtr thisPtr, IntPtr pData)
        {
            try
            {
                Frame frame;
                if (_frames.TryGetValue(pData, out frame))
                {
                    _frames.Remove(pData);
                    _callback.Close(frame.Stream);
                    frame.Close();
                }
                return Result.Ok;
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail;
            }
        }
    }
}
