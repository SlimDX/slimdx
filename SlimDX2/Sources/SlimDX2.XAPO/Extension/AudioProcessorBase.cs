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
using System;
using SlimDX2.Windows;

namespace SlimDX2.XAPO
{
    public abstract partial class AudioProcessorBase<T> : AudioProcessor, ParameterProvider where T : struct
    {
        private RegistrationProperties _registrationProperies;
        private T _parameters;

        private WaveFormat _inputFormatLocked;
        private WaveFormat _outputFormatLocked;
        private int _maxFrameCountLocked;


        public AudioProcessorBase()
        {           
        }

        ///<summary>
        /// Return parameters
        ///</summary>
        public virtual T Parameters
        {
            get { return _parameters; }
            set { _parameters = value; }
        }

        protected WaveFormat InputFormatLocked
        {
            get { return _inputFormatLocked; }
        }

        protected WaveFormat OutputFormatLocked
        {
            get { return _outputFormatLocked; }
        }

        protected int MaxFrameCountLocked
        {
            get { return _maxFrameCountLocked; }
        }

        public RegistrationProperties RegistrationProperties
        {
            get { return _registrationProperies; }
            protected set { _registrationProperies = value;  }
        }

        public bool IsInputFormatSupported(WaveFormat outputFormat, WaveFormat requestedInputFormat, out WaveFormat supportedInputFormat)
        {
            supportedInputFormat = requestedInputFormat;
            return true;            
        }

        public bool IsOutputFormatSupported(WaveFormat inputFormat, WaveFormat requestedOutputFormat, out WaveFormat supportedOutputFormat)
        {
            supportedOutputFormat = requestedOutputFormat;
            return true;
        }

        public void Initialize(DataStream stream)
        {           
        }

        public void Reset()
        {
        }

        public Result LockForProcess(LockParameters[] inputLockedParameters, LockParameters[] outputLockedParameters)
        {
            _inputFormatLocked = inputLockedParameters[0].Format;
            _outputFormatLocked = outputLockedParameters[0].Format;
            _maxFrameCountLocked = inputLockedParameters[0].MaxFrameCount;
            return Result.Ok;
        }

        public void UnlockForProcess()
        {
        }

        public abstract void Process(BufferParameters[] inputProcessParameters, BufferParameters[] outputProcessParameters, bool isEnabled);

        public int CalcInputFrames(int outputFrameCount)
        {
            return outputFrameCount;
        }

        public int CalcOutputFrames(int inputFrameCount)
        {
            return inputFrameCount;
        }

        void ParameterProvider.SetParameters(DataStream parameters)
        {
            Utilities.Read(parameters.DataPointer, ref _parameters);
        }

        void ParameterProvider.GetParameters(DataStream parameters)
        {
            Utilities.Write(parameters.DataPointer, ref _parameters);
        }
    }
}