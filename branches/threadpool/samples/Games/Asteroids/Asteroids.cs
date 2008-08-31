/*
* Copyright (c) 2007-2008 SlimDX Group
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
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Asteroids
{
    /// <summary>
    /// The top level game object. Manages the entire Asteroids game.
    /// </summary>
    class Asteroids : Game
    {
        // constants
        const int InitialWidth = 800;
        const int InitialHeight = 600;
        const float LevelInterval = 2.0f;

        // static data
        static Random random = new Random();

        // variables
        List<Interpolator> interpolators = new List<Interpolator>();
        List<Entity> entities = new List<Entity>();
        List<Trigger> triggers = new List<Trigger>();
        TextConsole console = new TextConsole();
        Camera camera = new Camera();
        bool[] keyState = new bool[256];
        bool[] keyStateThisFrame = new bool[256];
        bool[] keyStateNotReleased = new bool[256];
        int currentLevel;

        // fonts
        Sprite fontSprite;
        string levelText;
        SlimDX.Direct3D9.Font levelFont;
        Interpolator levelTextInterpolator;

        /// <summary>
        /// Gets the random number generator.
        /// </summary>
        /// <value>The random number generator.</value>
        public static Random Random
        {
            get { return random; }
        }

        /// <summary>
        /// Gets the entities.
        /// </summary>
        /// <value>The entities.</value>
        public List<Entity> Entities
        {
            get { return entities; }
        }

        /// <summary>
        /// Gets the triggers.
        /// </summary>
        /// <value>The triggers.</value>
        public List<Trigger> Triggers
        {
            get { return triggers; }
        }

        /// <summary>
        /// Gets the interpolators.
        /// </summary>
        /// <value>The interpolators.</value>
        public List<Interpolator> Interpolators
        {
            get { return interpolators; }
        }

        /// <summary>
        /// Gets or sets the world bounds.
        /// </summary>
        /// <value>The world bounds.</value>
        public Vector4 WorldBounds
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        /// <summary>
        /// Gets or sets the clear color.
        /// </summary>
        /// <value>The clear color.</value>
        public Color ClearColor
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Asteroids"/> class.
        /// </summary>
        public Asteroids()
        {
            // initialize settings
            ClearColor = Color.Black;

            // set up the window
            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "Asteroids";
            Window.KeyDown += Window_KeyDown;
            Window.KeyUp += Window_KeyUp;

            // initialize the camera
            camera.FieldOfView = (float)(Math.PI / 2);
            camera.NearPlane = 1.0f;
            camera.FarPlane = 1000.0f;
            camera.Location = new Vector3(0.0f, 0.0f, -750.0f);
            camera.Target = Vector3.Zero;

            // set up device settings
            DeviceSettings settings = new DeviceSettings();
            settings.BackBufferWidth = InitialWidth;
            settings.BackBufferHeight = InitialHeight;
            settings.DeviceVersion = DeviceVersion.Direct3D9;
            settings.Windowed = true;
            settings.EnableVSync = false;
            settings.MultisampleType = MultisampleType.EightSamples;

            // create resources
            Resources.Add(console);

            // create game objects
            Entities.Add(new Player(this));

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(settings);
        }

        /// <summary>
        /// Handles the KeyUp event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Window_KeyUp(object sender, KeyEventArgs e)
        {
            // update the pressed keys
            keyState[e.KeyValue] = false;
            keyStateNotReleased[e.KeyValue] = false;
        }

        /// <summary>
        /// Handles the KeyDown event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();

            // update the pressed keys
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
                Entities.Add(new Asteroid(this, AsteroidSize.Huge));
#endif
        }

        /// <summary>
        /// Initializes the game.
        /// </summary>
        protected override void Initialize()
        {
            // call the base method
            base.Initialize();

            // create fonts
            fontSprite = new Sprite(Device);
            levelFont = new SlimDX.Direct3D9.Font(Device, 40, 0, FontWeight.Bold, 0, false, CharacterSet.Default,
                Precision.Default, FontQuality.ClearTypeNatural, PitchAndFamily.DontCare, "");
        }

        /// <summary>
        /// Loads all graphical content.
        /// </summary>
        protected override void LoadContent()
        {
            // call the base method
            base.LoadContent();

            // update the camera
            camera.AspectRatio = (float)Window.Width / Window.Height;

            // recreate the world bounds
            float halfHeight = (float)Math.Abs(Math.Tan(camera.FieldOfView / 2) * camera.Location.Z);
            float halfWidth = halfHeight * camera.AspectRatio;
            WorldBounds = new Vector4(-halfWidth, -halfHeight, halfWidth, halfHeight);

            // reload fonts
            fontSprite.OnResetDevice();
            levelFont.OnResetDevice();
        }

        /// <summary>
        /// Unloads graphical resources.
        /// </summary>
        protected override void UnloadContent()
        {
            // call the base method
            base.UnloadContent();

            // unload fonts
            fontSprite.OnLostDevice();
            levelFont.OnLostDevice();
        }

        /// <summary>
        /// Releases the game.
        /// </summary>
        protected override void Release()
        {
            // call the base method
            base.Release();

            // release fonts
            fontSprite.Dispose();
            levelFont.Dispose();
        }

        /// <summary>
        /// Allows the game to perform logic processing.
        /// </summary>
        /// <param name="gameTime">The time passed since the last update.</param>
        protected override void Update(GameTime gameTime)
        {
            // call the base method
            base.Update(gameTime);

            // process each trigger
            for (int i = triggers.Count - 1; i >= 0; i--)
            {
                // check if the trigger has a predicate that is allowing us to proceed
                Trigger trigger = triggers[i];
                if (trigger.ActivationPredicate != null && trigger.ActivationPredicate())
                {
                    // activate the trigger
                    trigger.Activate();
                    if (!trigger.Repeat)
                        triggers.RemoveAt(i);
                }
                else
                {
                    // set the start time if it doesn't yet have one
                    if (trigger.StartTime == 0)
                        trigger.StartTime = gameTime.TotalGameTime;
                    else if (gameTime.TotalGameTime - trigger.StartTime > trigger.Duration)
                    {
                        // activate the trigger
                        trigger.Activate();
                        if (!trigger.Repeat)
                            triggers.RemoveAt(i);
                        else
                            trigger.StartTime = gameTime.TotalGameTime;
                    }
                }
            }

            // process each interpolator
            for (int i = interpolators.Count - 1; i >= 0; i--)
            {
                // make sure it isn't dead
                Interpolator interpolator = Interpolators[i];
                if (interpolator.IsFinished)
                    Interpolators.RemoveAt(i);
                else
                    interpolator.Update();
            }

            // update game objects
            foreach (Entity entity in entities)
                entity.Update(gameTime);

            // clear out dead entities
            for (int i = Entities.Count - 1; i >= 0; i--)
            {
                // make sure it's dead
                Entity e = Entities[i];
                if (e.IsDead)
                {
                    // allow the entity to do last minute processing before death
                    Entities.RemoveAt(i);
                    e.OnDeath();
                }
            }

            // reset the key frame list
            Array.Clear(keyStateThisFrame, 0, 256);

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
                    interpolators.Add(levelTextInterpolator);
                };
                Triggers.Add(trigger);
            }
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected override void Draw(GameTime gameTime)
        {
            // call the base method
            base.Draw(gameTime);

            // start the scene
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            // update the vector matrices
            VectorModel.ViewMatrix = camera.ViewMatrix;
            VectorModel.ProjectionMatrix = camera.ProjectionMatrix;

            // draw the game objects
            foreach (Entity entity in entities)
                entity.Draw();

            // flush all vector data
            VectorModel.FlushAll();

            // start drawing text
            fontSprite.Begin(SpriteFlags.AlphaBlend | SpriteFlags.SortTexture);

            // draw the level text, if we have any
            if (!string.IsNullOrEmpty(levelText))
            {
                // center the text in the screen
                Rectangle rectangle = levelFont.MeasureString(fontSprite, levelText, DrawTextFormat.Center);
                Rectangle outputRectangle = new Rectangle((GraphicsDeviceManager.ScreenWidth - rectangle.Width) / 2,
                    (GraphicsDeviceManager.ScreenHeight - rectangle.Height) / 2, rectangle.Width, rectangle.Height);
                levelFont.DrawString(fontSprite, levelText, outputRectangle, DrawTextFormat.Center,
                    new Color4((levelTextInterpolator == null ? 1.0f : levelTextInterpolator.Value) * 0.8f, 1.0f, 1.0f, 1.0f));
            }

            // stop drawing text
            fontSprite.End();

#if DEBUG
            // set up the debug console
            console.Begin();
            console.Location = new Point(5, 5);
            console.ForegroundColor = new Color4(1.0f, 1.0f, 1.0f, 0.0f);

            // draw debug text
            console.WriteLine(GraphicsDeviceManager.DeviceInformation);
            console.WriteLine(GraphicsDeviceManager.DeviceStatistics);
            console.WriteLine(gameTime.FramesPerSecond.ToString(".00", CultureInfo.CurrentCulture));
            console.WriteLine("Asteroids: " + Asteroid.AsteroidCount);

            // end text drawing
            console.End();
#endif

            // end the scene
            Device.EndScene();
        }

        /// <summary>
        /// Determines whether the given key is pressed.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>
        /// <c>true</c> if the given key is pressed; otherwise, <c>false</c>.
        /// </returns>
        public bool IsKeyPressed(Keys key)
        {
            // check the key state array
            return keyState[(int)key];
        }

        /// <summary>
        /// Determines whether the given key is pressed this frame
        /// <param name="key">The key.</param>
        /// <returns>
        /// <c>true</c> if the given key is pressed this frame; otherwise, <c>false</c>.
        /// </returns>
        public bool IsKeyPressedThisFrame(Keys key)
        {
            // check the key state array
            return keyStateThisFrame[(int)key];
        }

        /// <summary>
        /// Starts a new level.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void NewLevel(object sender, EventArgs e)
        {
            // clear out the level text for now
            levelText = null;

            // spawn some asteroids for the player to deal with
            for (int i = 0; i < currentLevel; i++)
                Entities.Add(new Asteroid(this, AsteroidSize.Huge));
        }
    }
}
