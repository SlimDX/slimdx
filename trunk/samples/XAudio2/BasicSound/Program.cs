using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.XAudio2;
using SlimDX;
using System.Threading;
using System.Runtime.InteropServices;

namespace BasicSound
{
    class Program
    {
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern short GetAsyncKeyState(int key);
        const int VK_ESCAPE = 0x1B;

        static void Main()
        {
            // initialize XAudio2
            XAudio2 device = new XAudio2();

            // create a mastering voice
            MasteringVoice masteringVoice = new MasteringVoice(device);

            // play a PCM file
            PlayPCM(device, "MusicMono.wav");

            // play a 5.1 PCM wave extensible file (Can't do this yet)
            PlayPCM(device, "MusicSurround.wav");

            // cleanup XAudio2
            masteringVoice.Dispose();
            device.Dispose();
        }

        static void PlayPCM(XAudio2 device, string fileName)
        {
            byte[] data;
            WaveFormat format;

            // read in the wav file
            using (WaveFile file = new WaveFile(fileName))
            {
                format = file.Format;
                data = new byte[file.Size];

                file.Read(data, file.Size);
            }

            // create the source voice
            SourceVoice sourceVoice = new SourceVoice(device, format);

            // build the wave sample data
            AudioBuffer buffer = new AudioBuffer();
            buffer.AudioData = data;
            buffer.AudioBytes = data.Length;
            buffer.Flags = BufferFlags.EndOfStream;

            // submit the data
            sourceVoice.SubmitSourceBuffer(buffer);

            // start the sample
            sourceVoice.Start();

            // loop until the sound is done playing
            while (sourceVoice.State.BuffersQueued > 0)
            {
                if (GetAsyncKeyState(VK_ESCAPE) != 0)
                    break;

                Thread.Sleep(10);
            }

            // cleanup the voice
            buffer.Dispose();
            sourceVoice.Dispose();

            // if we don't sleep here, we will run around and hit ourselves in the butt when we play
            // the second sample
            Thread.Sleep(1000);
        }
    }
}
