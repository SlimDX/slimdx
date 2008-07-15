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
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Xml;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Manages a collection of interface dialogs.
    /// </summary>
    public class InterfaceManager : IDisposable
    {
        // texture variables
        string textureFileName;
        Stream textureStream;

        // other variables
        Dialog mouseOverDialog;
        StateBlock stateBlock;
        List<CachedFont> fonts = new List<CachedFont>();

        /// <summary>
        /// Gets or sets the stored layouts.
        /// </summary>
        /// <value>The stored layouts.</value>
        public Dictionary<string, DrawingElement[]> StoredLayouts
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the current modal dialog.
        /// </summary>
        /// <value>The current modal dialog.</value>
        public Dialog ModalDialog
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the interface texture.
        /// </summary>
        /// <value>The interface texture.</value>
        public Texture Texture
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the drawing sprite.
        /// </summary>
        /// <value>The drawing sprite.</value>
        public Sprite Sprite
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the rendering device.
        /// </summary>
        /// <value>The rendering device.</value>
        public Device Device
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the control to which the interface is attached.
        /// </summary>
        /// <value>The attached control.</value>
        public System.Windows.Forms.Control Control
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the registered dialogs.
        /// </summary>
        /// <value>The dialogs.</value>
        public DialogCollection Dialogs
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the default font.
        /// </summary>
        /// <value>The default font.</value>
        public CachedFont DefaultFont
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="InterfaceManager"/> class.
        /// </summary>
        /// <param name="control">The control to which the interface will attach.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="control"/> is <c>null</c>.</exception>
        public InterfaceManager(System.Windows.Forms.Control control)
        {
            // error checking
            if (control == null)
                throw new ArgumentNullException("control");

            // store variables
            Control = control;

            // hook up events
            Control.KeyDown += Control_KeyDown;
            Control.KeyUp += Control_KeyUp;
            Control.MouseMove += Control_MouseMove;
            Control.MouseDown += Control_MouseDown;
            Control.MouseUp += Control_MouseUp;
            Control.MouseWheel += Control_MouseWheel;

            // create the collections
            Dialogs = new DialogCollection(this);
            StoredLayouts = new Dictionary<string, DrawingElement[]>();

            // add the default font
            DefaultFont = AddFont("Arial", 14, FontWeight.Normal);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="InterfaceManager"/> class.
        /// </summary>
        /// <param name="device">The rendering device.</param>
        /// <param name="control">The control to which the interface will attach.</param>
        /// <param name="textureFileName">Name of the texture file.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="device"/>, <paramref name="control"/>, or <paramref name="textureFileName"/> is <c>null</c>.</exception>
        public InterfaceManager(Device device, System.Windows.Forms.Control control, string textureFileName)
            : this(control)
        {
            // error checking
            if (device == null)
                throw new ArgumentNullException("device");
            if (string.IsNullOrEmpty(textureFileName))
                throw new ArgumentNullException("textureFileName");

            // store variables
            Device = device;

            // add the texture
            SetTexture(textureFileName);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="InterfaceManager"/> class.
        /// </summary>
        /// <param name="device">The rendering device.</param>
        /// <param name="control">The control to which the interface will attach.</param>
        /// <param name="textureStream">The texture stream.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="device"/>, <paramref name="control"/>, or <paramref name="textureStream"/> is <c>null</c>.</exception>
        public InterfaceManager(Device device, System.Windows.Forms.Control control, Stream textureStream)
            : this(control)
        {
            // error checking
            if (device == null)
                throw new ArgumentNullException("device");
            if (textureStream == null)
                throw new ArgumentNullException("textureStream");

            // store variables
            Device = device;

            // add the texture
            SetTexture(textureStream);
        }

        /// <summary>
        /// Loads layout information from XML.
        /// </summary>
        /// <param name="fileName">Name of the XML file.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="fileName"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidDataException">Thrown when the layout XML is invalid in some way.</exception>
        public void LoadXml(string fileName)
        {
            // error checking
            if (string.IsNullOrEmpty(fileName))
                throw new ArgumentNullException("fileName");

            // open the document and pass to the loader
            XmlDocument document = new XmlDocument();
            document.Load(fileName);
            LoadXml(document);
        }

        /// <summary>
        /// Loads layout information from XML.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="stream"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidDataException">Thrown when the layout XML is invalid in some way.</exception>
        public void LoadXml(Stream stream)
        {
            // error checking
            if (stream == null)
                throw new ArgumentNullException("stream");

            // open the document and pass to the loader
            XmlDocument document = new XmlDocument();
            document.Load(stream);
            LoadXml(document);
        }

        /// <summary>
        /// Creates a control using stored layout information.
        /// </summary>
        /// <param name="name">The name of the control to create.</param>
        /// <returns>The created control.</returns>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="name"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown when the desired type does not meet the specified requirements for a control.</exception>
        public Control CreateControl(string name)
        {
            // call the overload
            return CreateControl(name, false);
        }

        /// <summary>
        /// Creates a control using stored layout information.
        /// </summary>
        /// <param name="name">The name of the control to create.</param>
        /// <param name="localName">if set to <c>true</c>, the specified name is a local name.</param>
        /// <returns>The created control.</returns>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="name"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown when the desired type does not meet the specified requirements for a control.</exception>
        public Control CreateControl(string name, bool localName)
        {
            // error checking
            if (string.IsNullOrEmpty(name))
                throw new ArgumentNullException("name");

            // check if we have a local name
            if (localName)
                name = "SampleFramework." + name;

            // try to find the control type
            Type type = Type.GetType(name, false);
            if (type == null)
                throw new InvalidOperationException("Could not find control type \"" + name + "\"");

            // make sure it's a valid control
            if (!typeof(Control).IsAssignableFrom(type))
                throw new InvalidOperationException("The control type \"" + name + "\" must inherit from the Control class.");

            // make sure it has valid constructors
            ConstructorInfo constructor = type.GetConstructor(new Type[] { typeof(DrawingElement[]) });
            if (constructor == null)
                throw new InvalidOperationException("The control type \"" + name + "\" must define a public constructor that takes an array of DrawingElement objects.");
            constructor = type.GetConstructor(new Type[] { });
            if (constructor == null)
                throw new InvalidOperationException("The control type \"" + name + "\" must define a default constructor.");

            // try to find information about the control in the dictionary
            if (StoredLayouts.ContainsKey(name))
            {
                // create the object using the stored data
                int length = StoredLayouts[name].Length;
                DrawingElement[] elements = new DrawingElement[length];
                for (int i = 0; i < length; i++)
                    elements[i] = StoredLayouts[name][i].Clone();
                return (Control)Activator.CreateInstance(type, new object[] { elements });
            }
            else
            {
                // otherwise, default construct the object
                return (Control)Activator.CreateInstance(type);
            }
        }

        /// <summary>
        /// Adds a font to be managed by the interface.
        /// </summary>
        /// <param name="faceName">Name of the type face.</param>
        /// <param name="height">The height.</param>
        /// <param name="weight">The weight.</param>
        /// <returns>The cached font.</returns>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="faceName"/> is <c>null</c>.</exception>
        public CachedFont AddFont(string faceName, int height, FontWeight weight)
        {
            // error checking
            if (string.IsNullOrEmpty(faceName))
                throw new ArgumentNullException("faceName");

            // check if we have such a font already
            foreach (CachedFont font in fonts)
                if (font.FaceName == faceName && font.Height == height && font.Weight == weight)
                    return font;

            // otherwise, create the new font to be managed
            CachedFont f = new CachedFont(Device, faceName, height, weight);
            fonts.Add(f);
            return f;
        }

        /// <summary>
        /// Sets the texture.
        /// </summary>
        /// <param name="textureFileName">Name of the texture file.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="textureFileName"/> is <c>null</c>.</exception>
        public void SetTexture(string textureFileName)
        {
            // error checking
            if (string.IsNullOrEmpty(textureFileName))
                throw new ArgumentNullException("textureFileName");

            // cache the name for later use
            this.textureFileName = textureFileName;
            textureStream = null;

            // create the texture
            ImageInformation info;
            Texture = Texture.FromFile(Device, textureFileName, D3DX.Default, D3DX.Default, 1, Usage.None, Format.Unknown,
                Pool.Managed, Filter.Default, Filter.Default, 0, out info);
        }

        /// <summary>
        /// Sets the texture.
        /// </summary>
        /// <param name="textureStream">The texture stream.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="textureStream"/> is <c>null</c>.</exception>
        public void SetTexture(Stream textureStream)
        {
            // error checking
            if (textureStream == null)
                throw new ArgumentNullException("textureStream");

            // cache the stream for later use
            this.textureStream = textureStream;
            textureFileName = null;

            // create the texture
            ImageInformation info;
            Texture = Texture.FromStream(Device, textureStream, 0, D3DX.Default, D3DX.Default, 1, Usage.None, Format.Unknown,
                Pool.Managed, Filter.Default, Filter.Default, 0, out info);
        }

        /// <summary>
        /// Called to initialize the manager.
        /// </summary>
        /// <param name="device">The device.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="device"/> is <c>null</c>.</exception>
        public void Initialize(Device device)
        {
            // error checking
            if (device == null)
                throw new ArgumentNullException("device");
            Device = device;

            // make sure the texture is created properly
            if (Texture == null)
            {
                // figure out which to use, stream or file
                if (textureStream != null)
                    SetTexture(textureStream);
                else if (textureFileName != null)
                    SetTexture(textureFileName);
            }

            // make sure each font has been generated appropriately
            foreach (CachedFont font in fonts)
            {
                // create the font
                font.Device = device;
                font.Create();
            }

            // make sure the sprite is created
            if (Sprite == null)
                Sprite = new Sprite(Device);
        }

        /// <summary>
        /// Called when the application is ready for the manager to load graphical content.
        /// </summary>
        public void LoadContent()
        {
            // reset each font
            foreach (CachedFont font in fonts)
                font.Font.OnResetDevice();

            // reset the sprite
            if (Sprite != null)
                Sprite.OnResetDevice();

            // recreate the stateblock
            stateBlock = new StateBlock(Device, StateBlockType.All);
        }

        /// <summary>
        /// Called when the application is ready for the manager to unload graphical content.
        /// </summary>
        public void UnloadContent()
        {
            // release each font
            foreach (CachedFont font in fonts)
                font.Font.OnLostDevice();

            // release the sprite
            if (Sprite != null)
                Sprite.OnLostDevice();

            // release the state block
            if (stateBlock != null)
                stateBlock.Dispose();
            stateBlock = null;
        }

        /// <summary>
        /// Releases all resources held by the manager.
        /// </summary>
        public void Release()
        {
            // release the texture
            if (Texture != null)
                Texture.Dispose();
            Texture = null;

            // release each font
            foreach (CachedFont font in fonts)
                font.Release();

            // release the sprite
            if (Sprite != null)
                Sprite.Dispose();
            Sprite = null;
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            // call the overload
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Updates the interface.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        public void Update(float elapsedTime)
        {
            // update the dialogs
            for (int i = Dialogs.Count - 1; i >= 0; i--)
            {
                // update it if it is visible and enabled
                if (Dialogs[i].IsEnabled && Dialogs[i].IsVisible)
                    Dialogs[i].Update(elapsedTime);

                // if this is modal, end the loop now
                if (Dialogs[i].IsModal)
                    break;
            }
        }

        /// <summary>
        /// Renders the interface.
        /// </summary>
        public void Render()
        {
            // if we have nothing to render, don't bother doing anything
            List<Dialog> visibleDialogs = new List<Dialog>();
            foreach (Dialog dialog in Dialogs)
            {
                // if the dialog is visible, add it to the list
                if (dialog.IsVisible)
                    visibleDialogs.Add(dialog);
            }

            // make sure we have at least one visible dialog
            if (visibleDialogs.Count == 0)
                return;

            // store the current state
            stateBlock.Capture();

            // clear shaders
            Device.VertexShader = null;
            Device.PixelShader = null;

            // set common render states
            Device.SetRenderState(RenderState.AlphaBlendEnable, true);
            Device.SetRenderState(RenderState.SourceBlend, Blend.SourceAlpha);
            Device.SetRenderState(RenderState.DestinationBlend, Blend.InverseSourceAlpha);
            Device.SetRenderState(RenderState.AlphaTestEnable, false);
            Device.SetRenderState(RenderState.SeparateAlphaBlendEnable, false);
            Device.SetRenderState(RenderState.BlendOperation, BlendOperation.Add);
            Device.SetRenderState(RenderState.ColorWriteEnable, ColorWriteEnable.All);
            Device.SetRenderState(RenderState.ShadeMode, ShadeMode.Gouraud);
            Device.SetRenderState(RenderState.FogEnable, false);
            Device.SetRenderState(RenderState.ZWriteEnable, false);
            Device.SetRenderState(RenderState.FillMode, FillMode.Solid);
            Device.SetRenderState(RenderState.CullMode, Cull.Counterclockwise);
            Device.SetRenderState(RenderState.ZEnable, false);

            // set common texture stage states
            Device.SetTextureStageState(0, TextureStage.ResultArg, TextureArgument.Current);
            Device.SetTextureStageState(1, TextureStage.ColorOperation, TextureOperation.Disable);
            Device.SetTextureStageState(1, TextureStage.AlphaOperation, TextureOperation.Disable);

            // set common sampler states
            Device.SetSamplerState(0, SamplerState.MinFilter, TextureFilter.Linear);

            // set the current texture
            Device.SetTexture(0, Texture);

            // render all visible dialogs
            foreach (Dialog dialog in visibleDialogs)
                dialog.Render();

            // restore the state
            stateBlock.Apply();
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            // check if we should dispose of managed resources
            if (disposing)
                Release();
        }

        /// <summary>
        /// Handles the MouseWheel event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        void Control_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let the modal dialog handle this
                ModalDialog.OnMouseWheel(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - ModalDialog.X, e.Y - ModalDialog.Y, e.Delta));
                return;
            }

            // make sure the mouse over dialog is still valid
            if (mouseOverDialog != null && (!mouseOverDialog.IsEnabled || !mouseOverDialog.IsVisible))
                mouseOverDialog = null;

            // if we have a mouse over dialog, let it know that the mouse wheel just moved
            if (mouseOverDialog != null)
                mouseOverDialog.OnMouseWheel(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverDialog.X, e.Y - mouseOverDialog.Y, e.Delta));
        }

        /// <summary>
        /// Handles the MouseUp event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        void Control_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let the modal dialog handle this
                if (ModalDialog == mouseOverDialog)
                    ModalDialog.OnMouseUp(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - ModalDialog.X, e.Y - ModalDialog.Y, e.Delta));
                return;
            }

            // make sure the mouse over dialog is still valid
            if (mouseOverDialog != null && (!mouseOverDialog.IsEnabled || !mouseOverDialog.IsVisible))
                mouseOverDialog = null;

            // if we have a mouse over dialog, let it know that the mouse just went up
            if (mouseOverDialog != null)
                mouseOverDialog.OnMouseUp(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverDialog.X, e.Y - mouseOverDialog.Y, e.Delta));
        }

        /// <summary>
        /// Handles the MouseDown event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        void Control_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let the modal dialog handle this
                if (ModalDialog == mouseOverDialog)
                    ModalDialog.OnMouseDown(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - ModalDialog.X, e.Y - ModalDialog.Y, e.Delta));
                return;
            }

            // make sure the mouse over dialog is still valid
            if (mouseOverDialog != null && (!mouseOverDialog.IsEnabled || !mouseOverDialog.IsVisible))
                mouseOverDialog = null;

            // if we have a mouse over dialog, let it know that the mouse just went down
            if (mouseOverDialog != null)
                mouseOverDialog.OnMouseDown(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverDialog.X, e.Y - mouseOverDialog.Y, e.Delta));
        }

        /// <summary>
        /// Handles the MouseMove event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        void Control_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let this dialog handle it
                if (ModalDialog.Bounds.Contains(e.Location))
                {
                    // check if the mouse was already there, or just entered
                    if (ModalDialog == mouseOverDialog)
                        ModalDialog.OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - ModalDialog.X, e.Y - ModalDialog.Y, e.Delta));
                    else
                    {
                        // just entered
                        ModalDialog.OnMouseEnter(EventArgs.Empty);
                        ModalDialog.OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - ModalDialog.X, e.Y - ModalDialog.Y, e.Delta));
                    }
                }
                else if (ModalDialog == mouseOverDialog)
                {
                    // no longer mouse over
                    ModalDialog.OnMouseLeave(EventArgs.Empty);
                    mouseOverDialog = null;
                }
                return;
            }

            // make sure the mouse over dialog is still valid
            if (mouseOverDialog != null && (!mouseOverDialog.IsEnabled || !mouseOverDialog.IsVisible))
                mouseOverDialog = null;

            // if we have a mouse over dialog stored already, see if the mouse has left it yet
            if (mouseOverDialog != null)
            {
                // check if the mouse is still over, or if it has left
                if (mouseOverDialog.Bounds.Contains(e.Location))
                {
                    // we found the right dialog already
                    mouseOverDialog.OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverDialog.X, e.Y - mouseOverDialog.Y, e.Delta));
                    return;
                }
                else
                {
                    // the mouse has left
                    mouseOverDialog.OnMouseLeave(EventArgs.Empty);
                    mouseOverDialog = null;
                }
            }

            // otherwise, check to see if the mouse is now over another dialog
            for (int i = Dialogs.Count - 1; i >= 0; i--)
            {
                // make sure the dialog is both visible and enabled
                if (!Dialogs[i].IsVisible || !Dialogs[i].IsEnabled)
                    continue;

                // check to see if the mouse has entered this dialog
                if (Dialogs[i].Bounds.Contains(e.Location))
                {
                    // yes it has, update the state accordingly
                    mouseOverDialog = Dialogs[i];
                    Dialogs[i].OnMouseEnter(EventArgs.Empty);
                    Dialogs[i].OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverDialog.X, e.Y - mouseOverDialog.Y, e.Delta));
                    break;
                }
            }
        }

        /// <summary>
        /// Handles the KeyUp event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Control_KeyUp(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let this dialog handle it
                ModalDialog.OnKeyUp(e);
                return;
            }

            // otherwise, let the next top level dialog handle the event
            for (int i = Dialogs.Count - 1; i >= 0; i--)
            {
                // only let visible, enabled dialogs handle this
                if (Dialogs[i].IsVisible && Dialogs[i].IsEnabled)
                {
                    // handle it
                    Dialogs[i].OnKeyUp(e);
                    break;
                }
            }
        }

        /// <summary>
        /// Handles the KeyDown event of the Control control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Control_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            // check if we have a modal dialog that can handle this
            if (ModalDialog != null)
            {
                // let this dialog handle it
                ModalDialog.OnKeyDown(e);
                return;
            }

            // otherwise, let the next top level dialog handle the event
            for (int i = Dialogs.Count - 1; i >= 0; i--)
            {
                // only let visible, enabled dialogs handle this
                if (Dialogs[i].IsVisible && Dialogs[i].IsEnabled)
                {
                    // handle it
                    Dialogs[i].OnKeyDown(e);
                    break;
                }
            }
        }

        /// <summary>
        /// Loads layout information from XML.
        /// </summary>
        /// <param name="document">The document.</param>
        void LoadXml(XmlDocument document)
        {
            // make sure we have a valid SlimUI document
            XmlNode rootNode = document["SlimUI"];
            if (rootNode == null)
                throw new InvalidDataException("Invalid XML layout document (requires a SlimUI root element)");

            try
            {
                // check for a global layout element
                XmlNode node = rootNode["GlobalLayout"];
                if (node != null)
                    ProcessLayout(node);
            }
            catch (FormatException e)
            {
                // throw a more specific exception
                throw new InvalidDataException("Some data in the XML document could not be parsed.", e);
            }

            // check for an interface element
            XmlNode interfaceNode = rootNode["Interface"];
            if (interfaceNode != null)
                ProcessInterface(interfaceNode);
        }

        /// <summary>
        /// Processes the interface element.
        /// </summary>
        /// <param name="interfaceElement">The interface element.</param>
        void ProcessInterface(XmlNode interfaceElement)
        {
            // check for all dialog elements
            foreach (XmlNode dialogElement in interfaceElement)
            {
                // make sure we have a dialog element here
                if (dialogElement.Name != "Dialog")
                    continue;

                // create the dialog
                Dialog dialog = Dialogs.Add();
                Type dialogType = typeof(Dialog);

                // load all properties for the dialog
                foreach (XmlAttribute attribute in dialogElement.Attributes)
                {
                    // search for a property of the given name
                    PropertyInfo info = dialogType.GetProperty(attribute.Name);
                    if (info == null)
                        throw new InvalidDataException("The specified dialog property \"" + attribute.Name + "\" is not a valid property.");

                    // special case the handling of fonts
                    if (info.PropertyType == typeof(CachedFont))
                        info.SetValue(dialog, ParseFont(attribute.Value), null);
                    else
                    {
                        // set the property's value
                        TypeConverter converter = TypeDescriptor.GetConverter(info.PropertyType);
                        object value = converter.ConvertFromString(attribute.Value);
                        info.SetValue(dialog, value, null);
                    }
                }

                // load all controls
                foreach (XmlNode controlElement in dialogElement)
                {
                    // grab the name of the control (full name is optional)
                    string name;
                    XmlAttribute fullName = controlElement.Attributes["FullName"];
                    if (fullName != null)
                        name = fullName.Value;
                    else
                        name = "SampleFramework." + controlElement.Name;

                    // create the control
                    Control control = CreateControl(name);
                    Type controlType = control.GetType();

                    // load all properties for the control
                    foreach (XmlAttribute attribute in controlElement.Attributes)
                    {
                        // skip the FullName property
                        if (attribute.Name == "FullName")
                            continue;

                        // search for a property of the given name
                        PropertyInfo info = controlType.GetProperty(attribute.Name);
                        if (info == null)
                            throw new InvalidDataException("The specified control property \"" + attribute.Name + "\" is not a valid property.");

                        // special case the handling of fonts
                        if (info.PropertyType == typeof(CachedFont))
                            info.SetValue(control, ParseFont(attribute.Value), null);
                        else
                        {
                            // set the property's value
                            TypeConverter converter = TypeDescriptor.GetConverter(info.PropertyType);
                            object value = converter.ConvertFromString(attribute.Value);
                            info.SetValue(control, value, null);
                        }
                    }

                    // check if the control has any content nodes to process
                    if (controlElement.HasChildNodes)
                        control.LoadXmlContent(controlElement.ChildNodes);

                    // add the control to the dialog
                    dialog.Controls.Add(control);
                }
            }
        }

        /// <summary>
        /// Processes the layout element.
        /// </summary>
        /// <param name="layout">The layout element.</param>
        void ProcessLayout(XmlNode layout)
        {
            // process each child element
            foreach (XmlNode element in layout)
            {
                // grab the name of the control (full name is optional)
                string name;
                XmlAttribute fullName = element.Attributes["FullName"];
                if (fullName != null)
                    name = fullName.Value;
                else
                    name = "SampleFramework." + element.Name;

                // process each element
                List<DrawingElement> actualElements = new List<DrawingElement>();
                foreach (XmlNode drawingElement in element)
                {
                    // check for element nodes
                    if (drawingElement.Name != "Element")
                        continue;

                    // process the element
                    actualElements.Add(ProcessElement(drawingElement));
                }

                // store the information away until we need to actually create one of these controls
                StoredLayouts.Add(name, actualElements.ToArray());
            }
        }

        /// <summary>
        /// Processes a drawing element.
        /// </summary>
        /// <param name="element">The drawing element.</param>
        /// <returns>The created drawing element.</returns>
        DrawingElement ProcessElement(XmlNode element)
        {
            // grab the name (optional)
            string name = null;
            XmlAttribute nameAttribute = element.Attributes["Name"];
            if (nameAttribute != null)
                name = nameAttribute.Value;

            // create the element
            DrawingElement drawingElement = new DrawingElement(name);

            // load the blend colors
            drawingElement.FontColor = ReadBlendColor(element, "FontColor");
            drawingElement.TextureColor = ReadBlendColor(element, "TextureColor");

            // check for a texture rectangle
            XmlNode textureRectangleElement = element["TextureRectangle"];
            if (textureRectangleElement != null)
                drawingElement.TextureRectangle = ToObject<Rectangle>(textureRectangleElement.InnerText);

            // check for a text format
            XmlNode textFormat = element["TextFormat"];
            if (textFormat != null)
            {
                try
                {
                    // try to parse the data
                    DrawTextFormat format = (DrawTextFormat)Enum.Parse(typeof(DrawTextFormat), textFormat.InnerText, true);
                    drawingElement.TextFormat = format;
                }
                catch (ArgumentNullException e)
                {
                    // throw a more specific exception
                    throw new InvalidDataException("The specified text format is empty.", e);
                }
                catch (ArgumentException e)
                {
                    // throw a more specific exception
                    throw new InvalidDataException("The specified text format \"" + textFormat.InnerText + "\" is not a valid text format.", e);
                }
            }

            // check for a font
            XmlNode fontElement = element["Font"];
            if (fontElement != null)
                drawingElement.CachedFont = ParseFont(fontElement.InnerText);

            // return the created element
            return drawingElement;
        }

        /// <summary>
        /// Parses a font.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>The parsed font.</returns>
        CachedFont ParseFont(string value)
        {
            // error checking
            if (string.IsNullOrEmpty(value))
                throw new InvalidDataException("Specified font is empty.");

            // require 2 or 3 values in a comma delimited list
            string[] values = value.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
            if (values.Length != 3 && values.Length != 2)
                throw new InvalidDataException("Specified font \"" + value + "\" is not a valid font.");

            // get the three values
            string faceName = values[0];
            int height = int.Parse(values[1], CultureInfo.CurrentCulture);
            FontWeight weight = FontWeight.Normal;

            // check if we should get the weight
            if (values.Length == 3)
            {
                try
                {
                    // get the weight
                    weight = (FontWeight)Enum.Parse(typeof(FontWeight), values[2], true);
                }
                catch (ArgumentException e)
                {
                    // throw a more specific exception
                    throw new InvalidDataException("Specified font weight \"" + values[2] + "\" is not a valid font weight.", e);
                }
            }

            // create the font
            return AddFont(faceName, height, weight);
        }

        /// <summary>
        /// Reads a blend color from an XML definition.
        /// </summary>
        /// <param name="parent">The parent element.</param>
        /// <param name="name">The color name.</param>
        /// <returns>The read blend color.</returns>
        static BlendColor ReadBlendColor(XmlNode parent, string name)
        {
            // read the element
            BlendColor result = new BlendColor();
            XmlNode element = parent[name];
            if (element == null)
                return result;

            // check for a default value (optional)
            XmlAttribute attribute = element.Attributes["Default"];
            if (attribute != null)
            {
                // create the object using the default value
                Color4 defaultColor = ToObject<Color4>(attribute.Value);
                result = new BlendColor(defaultColor);
            }

            // read each state specifier
            foreach (XmlNode stateElement in element)
            {
                // check for state elements
                if (stateElement.Name != "State")
                    continue;

                // grab the name (NOT optional)
                XmlAttribute stateNameAttribute = stateElement.Attributes["Name"];
                if (stateNameAttribute == null || string.IsNullOrEmpty(stateNameAttribute.Value))
                    throw new InvalidDataException("State element for font color is missing a name attribute");

                // grab the real values
                Color4 value = ToObject<Color4>(stateElement.InnerText);
                ControlState actualState;

                try
                {
                    // grab the control state
                    actualState = (ControlState)Enum.Parse(typeof(ControlState), stateNameAttribute.Value, true);
                }
                catch (ArgumentException e)
                {
                    // throw a more specific exception
                    throw new InvalidDataException("The specified state name \"" + stateNameAttribute.Value + "\" is not a valid state name.", e);
                }

                // add the state to the color
                result.States[(int)actualState] = value;
            }

            // return the result
            return result;
        }

        /// <summary>
        /// Converts a string to an arbitrary object by looking up its type converter.
        /// </summary>
        /// <typeparam name="T">The type of the object to convert to.</typeparam>
        /// <param name="value">The value.</param>
        /// <returns>The converted object.</returns>
        static T ToObject<T>(string value)
        {
            // look up the type converter to convert the value
            TypeConverter converter = TypeDescriptor.GetConverter(typeof(T));
            return (T)converter.ConvertFromString(null, CultureInfo.InvariantCulture, value);
        }
    }
}
