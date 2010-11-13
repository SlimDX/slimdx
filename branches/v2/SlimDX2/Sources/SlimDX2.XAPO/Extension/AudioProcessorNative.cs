using SlimDX2.Windows;

namespace SlimDX2.XAPO
{

    /// <summary>
    /// Native Accessor to an existing AudioProcessor instance
    /// </summary>
    public abstract partial class AudioProcessorNative
    {




        public RegistrationProperties RegistrationProperties
        {
            get {
                RegistrationProperties temp;
                GetRegistrationProperties_(out temp);
                return temp;
            }
        }

        public bool IsInputFormatSupported(WaveFormat outputFormat, WaveFormat requestedInputFormat, out WaveFormat supportedInputFormat)
        {
            return IsInputFormatSupported_(ref outputFormat, ref requestedInputFormat, out supportedInputFormat).Success;
        }

        public bool IsOutputFormatSupported(WaveFormat inputFormat, WaveFormat requestedOutputFormat, out WaveFormat supportedOutputFormat)
        {
            return IsOutputFormatSupported_(ref inputFormat, ref requestedOutputFormat, out supportedOutputFormat).Success;
        }

        public void Initialize(DataStream stream)
        {
            Initialize_(stream.DataPointer, (int)stream.Length);
        }

        public void Reset()
        {
            Reset_();
        }

        public Result LockForProcess(LockParameters[] inputLockedParameters, LockParameters[] outputLockedParameters)
        {
            return LockForProcess_(inputLockedParameters.Length, inputLockedParameters, outputLockedParameters.Length, outputLockedParameters);
        }

        public void UnlockForProcess()
        {
            UnlockForProcess_();
        }

        public void Process(BufferParameters[] inputProcessParameters, BufferParameters[] outputProcessParameters, bool isEnabled)
        {
            Process_(inputProcessParameters.Length, inputProcessParameters, outputProcessParameters.Length, outputProcessParameters, isEnabled);
        }

        public int CalcInputFrames(int outputFrameCount)
        {
            return CalcInputFrames(outputFrameCount);
        }

        public int CalcOutputFrames(int inputFrameCount)
        {
            return CalcOutputFrames(inputFrameCount);
        }
    }
}