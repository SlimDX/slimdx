using System;
using System.Windows.Forms;

using SlimDX;
using SlimDX.DirectSound;

namespace SimpleSound
{
	class SoundManager : IDisposable
	{
		private DirectSound m_Sound;

		public SoundManager( Control control, CooperativeLevel coopLevel )
		{
			m_Sound = new DirectSound();
			m_Sound.SetCooperativeLevel( control.Handle, coopLevel );
		}

		public void SetPrimaryBufferFormat( short channels, short frequency, short bitRate )
		{
			BufferDescription desc = new BufferDescription();
			desc.Flags = BufferFlags.PrimaryBuffer;

			using( SoundBuffer buffer = new SoundBuffer( m_Sound, desc ) )
			{
				using( WaveFormatEx format = new WaveFormatEx() )
				{
					format.FormatTag = WaveFormat.Pcm;
					format.Channels = channels;
					format.SamplesPerSecond = frequency;
					format.BitsPerSample = bitRate;
					format.BlockAlign = (short) ( bitRate / 8 * channels );
					format.AverageBytesPerSecond = frequency * format.BlockAlign;

					buffer.SetFormat( format );
				}
			}
		}

		#region IDisposable Members

		public void Dispose()
		{
			if( m_Sound != null )
				m_Sound.Dispose();
		}

		#endregion
	}
}
