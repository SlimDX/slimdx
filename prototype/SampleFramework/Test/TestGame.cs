using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SampleFramework;

namespace Test
{
    class TestGame : Game
    {
        GraphicsDeviceManager graphicsManager;

        public TestGame()
        {
            graphicsManager = new GraphicsDeviceManager(this, DeviceVersion.Direct3D9, true, 800, 600);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (graphicsManager != null)
                    graphicsManager.Dispose();
                graphicsManager = null;
            }

            base.Dispose(disposing);
        }
    }
}
