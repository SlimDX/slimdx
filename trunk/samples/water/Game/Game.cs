using System;

namespace Engine
{
	public class Game
	{
		static void InitSystems()
		{
			SlimDX.Direct3D9.Direct3D.Initialize();
            SlimDX.DirectInput.DirectInput.Initialize();
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