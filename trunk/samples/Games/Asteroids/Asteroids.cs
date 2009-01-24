/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Asteroids
{
    class Asteroids : Game
    {
        const int InitialWidth = 800;
        const int InitialHeight = 600;
        const float LevelInterval = 2.0f;
        const float AlienInterval = 20.0f;

        static Random random = new Random();

        TextConsole console = new TextConsole();
        Camera camera = new Camera();
        bool[] keyState = new bool[256];
        bool[] keyStateThisFrame = new bool[256];
        bool[] keyStateNotReleased = new bool[256];
        int currentLevel;
        Explosion explosion;

        Sprite fontSprite;
        string levelText;
        SlimDX.Direct3D9.Font levelFont;
        Interpolator levelTextInterpolator;

        float alienCounter;

        public int Score
        {
            get;
            set;
        }

        public static Random Random
        {
            get { return random; }
        }

        public Vector4 WorldBounds
        {
            get;
            set;
        }

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Camera Camera
        {
            get { return camera; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public Explosion Explosion
        {
            get { return explosion; }
        }

        public Player Player
        {
            get { foreach (IGameComponent component in Components) if (component is Player)return component as Player; return null; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Asteroids"/> class.
        /// </summary>
        public Asteroids()
        {
            ClearColor = Color.Black;

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "Asteroids";
            Window.KeyDown += Window_KeyDown;
            Window.KeyUp += Window_KeyUp;

            camera.FieldOfView = (float)(Math.PI / 2);
            camera.NearPlane = 1.0f;
            camera.FarPlane = 1000.0f;
            camera.Location = new Vector3(0.0f, 0.0f, -750.0f);
            camera.Target = Vector3.Zero;

            DeviceSettings settings = new DeviceSettings();
            settings.BackBufferWidth = InitialWidth;
            settings.BackBufferHeight = InitialHeight;
            settings.DeviceVersion = DeviceVersion.Direct3D9;
            settings.Windowed = true;
#if DEBUG
            settings.EnableVSync = false;
#else
            settings.EnableVSync = true;
#endif
            settings.MultisampleType = MultisampleType.EightSamples;

            explosion = new Explosion(this);
            Components.Add(explosion);
            Resources.Add(console);

            GraphicsDeviceManager.ChangeDevice(settings);
        }

        void Window_KeyUp(object sender, KeyEventArgs e)
        {
            keyState[e.KeyValue] = false;
            keyStateNotReleased[e.KeyValue] = false;
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();

            keyState[e.KeyValue] = true;
            if (!keyStateNotReleased[e.KeyValue])
            {
                // avoid multiple presses from key repeat
                keyStateThisFrame[e.KeyValue] = true;
                keyStateNotReleased[e.KeyValue] = true;
            }

#if DEBUG
            // add new asteroids when enter is pressed
            // DEBUGGING ONLY
            if (e.KeyCode == Keys.Enter)
                Components.Add(new Alien(this));
#endif
        }

        protected override void Initialize()
        {
            base.Initialize();

            fontSprite = new Sprite(Device);
            levelFont = new SlimDX.Direct3D9.Font(Device, 40, 0, FontWeight.Bold, 0, false, CharacterSet.Default,
                Precision.Default, FontQuality.ClearTypeNatural, PitchAndFamily.DontCare, "");
        }

        protected override void LoadContent()
        {
            base.LoadContent();

            camera.AspectRatio = (float)Window.Width / Window.Height;

            float halfHeight = (float)Math.Abs(Math.Tan(camera.FieldOfView / 2) * camera.Location.Z);
            float halfWidth = halfHeight * camera.AspectRatio;
            WorldBounds = new Vector4(-halfWidth, -halfHeight, halfWidth, halfHeight);

            fontSprite.OnResetDevice();
            levelFont.OnResetDevice();
        }

        protected override void UnloadContent()
        {
            base.UnloadContent();

            fontSprite.OnLostDevice();
            levelFont.OnLostDevice();
        }

        protected override void Dispose(bool disposing)
        {
            fontSprite.Dispose();
            levelFont.Dispose();

            base.Dispose(disposing);
        }

        protected override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            // clear out dead entities
            for (int i = Components.Count - 1; i >= 0; i--)
            {
                // make sure it's dead
                Entity e = Components[i] as Entity;
                if (e != null && e.IsDead)
                {
                    // allow the entity to do last minute processing before death
                    Components.RemoveAt(i);
                    e.OnDeath();
                }
            }

            // reset the key frame list
            Array.Clear(keyStateThisFrame, 0, 256);

            alienCounter += gameTime.ElapsedGameTime;
            if (alienCounter > AlienInterval)
            {
                alienCounter = 0;
                Alien alien = new Alien(this);
                float x = Helpers.RandomFloat(0.0f, 1.0f) - 0.5f;
                float y = Helpers.RandomFloat(0.0f, 1.0f) - 0.5f;
                alien.Position = new Vector2(x * 10000.0f, y * 10000.0f);
                Components.Add(alien);
            }

            // check to see if all the asteroids are gone
            if (Asteroid.AsteroidCount == 0 && levelText == null)
            {
                // set the level text
                currentLevel++;
                levelText = "LEVEL " + currentLevel.ToString(CultureInfo.CurrentCulture);

                // rig up a trigger to start the new level
                Trigger trigger = new Trigger(LevelInterval);
                trigger.Activated += delegate
                {
                    // start the new level when the alpha of the text reaches 0
                    levelTextInterpolator = new Interpolator(a => (a - 0.01f), 1.0f, a => (a <= 0.0f));
                    levelTextInterpolator.Finished += NewLevel;
                    Interpolators.Add(levelTextInterpolator);
                };
                Triggers.Add(trigger);
            }
        }

        protected override void Draw(GameTime gameTime)
        {
            VectorModel.ViewMatrix = camera.ViewMatrix;
            VectorModel.ProjectionMatrix = camera.ProjectionMatrix;

            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            base.Draw(gameTime);

            VectorModel.FlushAll();

            fontSprite.Begin(SpriteFlags.AlphaBlend | SpriteFlags.SortTexture);

            if (!string.IsNullOrEmpty(levelText))
            {
                Rectangle rectangle = levelFont.MeasureString(fontSprite, levelText, DrawTextFormat.Center);
                Rectangle outputRectangle = new Rectangle((GraphicsDeviceManager.ScreenWidth - rectangle.Width) / 2,
                    (GraphicsDeviceManager.ScreenHeight - rectangle.Height) / 2, rectangle.Width, rectangle.Height);
                levelFont.DrawString(fontSprite, levelText, outputRectangle, DrawTextFormat.Center,
                    new Color4((levelTextInterpolator == null ? 1.0f : levelTextInterpolator.Value) * 0.8f, 1.0f, 1.0f, 1.0f));
            }

            string scoreText = Score.ToString(CultureInfo.CurrentCulture);
            Rectangle scoreRectangle = levelFont.MeasureString(fontSprite, scoreText, DrawTextFormat.Center);
            scoreRectangle = new Rectangle(GraphicsDeviceManager.ScreenWidth - scoreRectangle.Width - 10, 10, scoreRectangle.Width, scoreRectangle.Height);
            levelFont.DrawString(fontSprite, scoreText, scoreRectangle, DrawTextFormat.Center, new Color4(1.0f, 1.0f, 1.0f));

            fontSprite.End();

#if DEBUG
            console.Begin();
            console.Location = new Point(5, 5);
            console.ForegroundColor = new Color4(1.0f, 1.0f, 1.0f, 0.0f);
            console.WriteLine(GraphicsDeviceManager.DeviceInformation);
            console.WriteLine(GraphicsDeviceManager.DeviceStatistics);
            console.WriteLine(gameTime.FramesPerSecond.ToString(".00", CultureInfo.CurrentCulture));
            console.WriteLine("Asteroids: " + Asteroid.AsteroidCount);
            console.End();
#endif

            Device.EndScene();
        }

        public bool IsKeyPressed(Keys key)
        {
            return keyState[(int)key];
        }

        public bool IsKeyPressedThisFrame(Keys key)
        {
            return keyStateThisFrame[(int)key];
        }

        void NewLevel(object sender, EventArgs e)
        {
            // if this is the first level, spawn the player
            if (currentLevel == 1)
                Components.Add(new Player(this));

            // clear out the level text for now
            levelText = null;

            // spawn some asteroids for the player to deal with
            for (int i = 0; i < currentLevel; i++)
                Components.Add(new Asteroid(this, AsteroidSize.Huge));
        }
    }
}
