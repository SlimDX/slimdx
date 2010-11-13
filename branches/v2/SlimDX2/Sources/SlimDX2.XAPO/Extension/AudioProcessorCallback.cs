using System;
using System.Runtime.InteropServices;
using SlimDX2.Windows;

namespace SlimDX2.XAPO
{
    /// <summary>
    /// Internal AudioProcessorCallback
    /// </summary>
    internal class AudioProcessorCallback : ComObjectCallback
    {
        private readonly AudioProcessor Callback;

        internal AudioProcessorCallback(AudioProcessor callback) : base(callback, 10)        
        {
            unsafe
            {
                Callback = callback;
                AddMethod(new GetRegistrationPropertiesDelegate(GetRegistrationPropertiesImpl));
                AddMethod(new IsInputFormatSupportedDelegate(IsInputFormatSupportedImpl));
                AddMethod(new IsOutputFormatSupportedDelegate(IsOutputFormatSupportedImpl));
                AddMethod(new InitializeDelegate(InitializeImpl));
                AddMethod(new ResetDelegate(ResetImpl));
                AddMethod(new LockForProcessDelegate(LockForProcessImpl));
                AddMethod(new UnlockForProcessDelegate(UnlockForProcessImpl));
                AddMethod(new ProcessDelegate(ProcessImpl));
                AddMethod(new CalcInputFramesDelegate(CalcInputFramesImpl));
                AddMethod(new CalcOutputFramesDelegate(CalcOutputFramesImpl));
            }
        }

        /// <unmanaged>HRESULT IXAPO::GetRegistrationProperties([Out] XAPO_REGISTRATION_PROPERTIES** ppRegistrationProperties)</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate int GetRegistrationPropertiesDelegate(out IntPtr output);
        private int GetRegistrationPropertiesImpl(out IntPtr output)
        {
            output = IntPtr.Zero;
            try
            {
                output = Marshal.AllocCoTaskMem(Utilities.SizeOf<RegistrationProperties>());
                var temp = Callback.RegistrationProperties;
                Utilities.Write(output, ref temp);
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail.Code;
            }
            return Result.Ok.Code;
        }

        /// <unmanaged>HRESULT IXAPO::IsInputFormatSupported([None] const WAVEFORMATEX* pOutputFormat,[None] const WAVEFORMATEX* pRequestedInputFormat,[Out, Optional] WAVEFORMATEX** ppSupportedInputFormat)</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate int IsInputFormatSupportedDelegate(IntPtr outputFormat, IntPtr requestedInputFormat, out IntPtr supportedInputFormat);
        private int IsInputFormatSupportedImpl(IntPtr pOutputFormat, IntPtr pRequestedInputFormat, out IntPtr pSupportedInputFormat)
        {
            pSupportedInputFormat = IntPtr.Zero;
            try
            {
                WaveFormat outputFormat = WaveFormat.MarshalFromPtr(pOutputFormat);
                WaveFormat requestedInputFormat = WaveFormat.MarshalFromPtr(pRequestedInputFormat);

                WaveFormat supportedInputFormat;
                var result = Callback.IsInputFormatSupported(outputFormat, requestedInputFormat, out supportedInputFormat);

                int sizeOfWaveFormat = Marshal.SizeOf(supportedInputFormat);
                pSupportedInputFormat = Marshal.AllocCoTaskMem(sizeOfWaveFormat);
                
                Marshal.StructureToPtr(supportedInputFormat, pSupportedInputFormat, false);

                // return XAPO_E_FORMAT_UNSUPPORTED if fail
                return result ? Result.Ok.Code : unchecked((int)0x88970001);
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail.Code;
            }
        }

        /// <unmanaged>HRESULT IXAPO::IsOutputFormatSupported([None] const WAVEFORMATEX* pInputFormat,[None] const WAVEFORMATEX* pRequestedOutputFormat,[Out, Optional] WAVEFORMATEX** ppSupportedOutputFormat)</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate int IsOutputFormatSupportedDelegate(IntPtr outputFormat, IntPtr requestedInputFormat, out IntPtr supportedInputFormat);
        private int IsOutputFormatSupportedImpl(IntPtr pInputFormat, IntPtr pRequestedOutputFormat, out IntPtr pSupportedOutputFormat)
        {
            pSupportedOutputFormat = IntPtr.Zero;
            try
            {
                WaveFormat inputFormat = WaveFormat.MarshalFromPtr(pInputFormat);
                WaveFormat requestedOutputFormat = WaveFormat.MarshalFromPtr(pRequestedOutputFormat);

                WaveFormat supportedOutputFormat;
                var result = Callback.IsOutputFormatSupported(inputFormat, requestedOutputFormat, out supportedOutputFormat);

                int sizeOfWaveFormat = Marshal.SizeOf(supportedOutputFormat);
                pSupportedOutputFormat = Marshal.AllocCoTaskMem(sizeOfWaveFormat);

                Marshal.StructureToPtr(supportedOutputFormat, pSupportedOutputFormat, false);

                // return XAPO_E_FORMAT_UNSUPPORTED if fail
                return result ? Result.Ok.Code : unchecked((int)0x88970001);
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail.Code;
            }
        }

        /// <unmanaged>HRESULT IXAPO::Initialize([In, Buffer, Optional] const void* pData,[None] UINT32 DataByteSize)</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate int InitializeDelegate(IntPtr ptr, int dataSize);
        private int InitializeImpl(IntPtr ptr, int dataSize)
        {
            try
            {
                Callback.Initialize(new DataStream(ptr, dataSize, true, true));
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail.Code;
            }
            return Result.Ok.Code;
        }

        /// <unmanaged>void IXAPO::Reset()</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void ResetDelegate();
        private void ResetImpl()
        {
            Callback.Reset();
        }

        /// <unmanaged>HRESULT IXAPO::LockForProcess([None] UINT32 InputLockedParameterCount,[In, Buffer, Optional] const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pInputLockedParameters,[None] UINT32 OutputLockedParameterCount,[In, Buffer, Optional] const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pOutputLockedParameters)</unmanaged>
        //void LockForProcess(SlimDX2.XAPO.LockforprocessParameters[] inputLockedParameters, SlimDX2.XAPO.LockforprocessParameters[] outputLockedParameters);
        private unsafe delegate int LockForProcessDelegate(
            int inputLockedParameterCount, LockParameters.__Native* pInputLockedParameters, int outputLockedParameterCount, LockParameters.__Native* pOutputLockedParameters);
        private unsafe int LockForProcessImpl(
            int inputLockedParameterCount, LockParameters.__Native* pInputLockedParameters, int outputLockedParameterCount, LockParameters.__Native* pOutputLockedParameters)
        {
            try
            {
                LockParameters[] inputLockedParameters = new LockParameters[inputLockedParameterCount];
                for (int i = 0; i < inputLockedParameters.Length; i++)
                {
                    var param = new LockParameters();                    
                    param.__MarshalFrom(&pInputLockedParameters[i]);
                    inputLockedParameters[i] = param;
                }

                LockParameters[] ouputLockedParameters = new LockParameters[outputLockedParameterCount];
                for (int i = 0; i < ouputLockedParameters.Length; i++)
                {
                    var param = new LockParameters();
                    param.__MarshalFrom(&pOutputLockedParameters[i]);
                    ouputLockedParameters[i] = param;
                }

                return Callback.LockForProcess(inputLockedParameters, ouputLockedParameters).Code;
            }
            catch (SlimDX2Exception exception)
            {
                return exception.ResultCode.Code;
            }
            catch (Exception ex)
            {
                return Result.Fail.Code;
            }
        }

        /// <summary>	
        /// Deallocates variables that were allocated with the {{LockForProcess}} method.	
        /// </summary>	
        /// <unmanaged>void IXAPO::UnlockForProcess()</unmanaged>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void UnlockForProcessDelegate();
        private void UnlockForProcessImpl()
        {
            Callback.UnlockForProcess();
        }

        /// <unmanaged>void IXAPO::Process([None] UINT32 InputProcessParameterCount,[In, Buffer, Optional] const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,[None] UINT32 OutputProcessParameterCount,[InOut, Buffer, Optional] XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,[None] BOOL IsEnabled)</unmanaged>
        private unsafe delegate void ProcessDelegate(
            int inputProcessParameterCount, BufferParameters* pInputProcessParameters, int outputProcessParameterCount, BufferParameters* inputProcessParameters,
            int isEnabled);
        private unsafe void ProcessImpl(
            int inputProcessParameterCount, BufferParameters* pInputProcessParameters, int outputProcessParameterCount, BufferParameters* pOutputProcessParameters,
            int isEnabled)
        {
            BufferParameters[] inputProcessParameters = new BufferParameters[inputProcessParameterCount];
            for (int i = 0; i < inputProcessParameters.Length; i++)
                inputProcessParameters[i] = pInputProcessParameters[i];

            BufferParameters[] outputProcessParameters = new BufferParameters[outputProcessParameterCount];
            for (int i = 0; i < outputProcessParameters.Length; i++)
                outputProcessParameters[i] = pOutputProcessParameters[i];

            Callback.Process(inputProcessParameters, outputProcessParameters, isEnabled==1);

            // Update BufferParameters output (see doc for IXAPO::Process
            // ValidFrameCount must be fill by the Process method. Most of the time ValidFrameCount in input == ValidFrameCount in output (effectively written)
            for (int i = 0; i < outputProcessParameters.Length; i++)
                pOutputProcessParameters[i].ValidFrameCount = outputProcessParameters[i].ValidFrameCount;
        }

        /// <summary>	
        /// Returns the number of input frames required to generate the given number of output frames.	
        /// </summary>	
        /// <param name="outputFrameCount">The number of output frames desired.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>UINT32 IXAPO::CalcInputFrames([None] UINT32 OutputFrameCount)</unmanaged>
        private delegate int CalcInputFramesDelegate(int outputFrameCount);
        private int CalcInputFramesImpl(int outputFrameCount)
        {
            return Callback.CalcInputFrames(outputFrameCount);
        }

        /// <summary>	
        /// Returns the number of output frames that will be generated from a given number of input frames.	
        /// </summary>	
        /// <param name="inputFrameCount">The number of input frames.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>UINT32 IXAPO::CalcOutputFrames([None] UINT32 InputFrameCount)</unmanaged>
        private delegate int CalcOutputFramesDelegate(int InputFrameCount);
        private int CalcOutputFramesImpl(int InputFrameCount)
        {
            return Callback.CalcOutputFrames(InputFrameCount);
        }
    }
}