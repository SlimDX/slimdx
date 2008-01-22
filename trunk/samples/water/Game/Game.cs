using System;

using System.Windows.Forms;

namespace Engine
{
	public class Game
	{
		static void InitSystems()
		{
			try
			{
				SlimDX.Direct3D9.Direct3D.Initialize();
				SlimDX.DirectInput.DirectInput.Initialize();
			}
			catch( SlimDX.SlimDXException ex )
			{
				MessageBox.Show( ex.Message );
				Application.Exit();
			}
		}

		static void RunGame()
		{
			Core core = new Core();
			core.Run();
		}

		#region Methods
		public static void Main()
		{
			InitSystems();
			RunGame();
		}
		#endregion
	}
}