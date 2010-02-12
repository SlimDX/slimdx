/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// This code is Copyright (c) 2009 LizardTech, a Celartem Company, 1008    //
// Western Avenue, Suite 200, Seattle, WA 98104.  Unauthorized use or      //
// distribution prohibited.  Access to and use of this code is permitted   //
// only under license from LizardTech.  Portions of the code are protected //
// by US and foreign patents and other filings. All Rights Reserved.       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

// uncomment this to force your Vista or Win7 box to act more like an XP box...
#define USE_XP_MODE

// uncomment this to render each and every frame, as opposed to only when the user signals an update is needed
//#define USE_PERFRAME_MODE

using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;
using SlimDX;
using SlimDX.Direct3D9;
using System.Diagnostics;

[assembly: CLSCompliant(true)]
namespace SlimDX.Wpf
{
   public partial class SlimDXControl : ContentControl
   {
      private IRenderEngine m_renderEngine;
      public IRenderEngine RenderEngine
      {
         private set
         {
            m_renderEngine = value;

            this.DeviceCreated += new EventHandler(m_renderEngine.OnDeviceCreated);
            this.DeviceDestroyed += new EventHandler(m_renderEngine.OnDeviceDestroyed);
            this.DeviceLost += new EventHandler(m_renderEngine.OnDeviceLost);
            this.DeviceReset += new EventHandler(m_renderEngine.OnDeviceReset);
            this.MainLoop += new EventHandler(m_renderEngine.OnMainLoop);
         }
         get
         {
            return m_renderEngine;
         }
      }

      public SlimDXControl()
      {
         InitializeComponent();

#if USE_PERFRAME_MODE
         AlwaysRender = true;
#else
         AlwaysRender = false;
#endif
      }

      public void Setup(IRenderEngine renderEngine)
      {
         Initialize(true);
         RenderEngine = renderEngine;
      }

      // we use it for 3D
      private Direct3D _direct3D;
      private Direct3DEx _direct3DEx;
      private Device _device;
      private DeviceEx _deviceEx;
      private Surface _backBufferSurface;
	  // device settings
	  Format _adapterFormat = Format.X8R8G8B8;
	  Format _backbufferFormat = Format.A8R8G8B8;
	  Format _depthStencilFormat = Format.D16;
	  CreateFlags _createFlags = CreateFlags.Multithreaded;


      private PresentParameters _pp;

      private bool _startThread;
      private bool _sizeChanged;

      public Image Image
      {
         get { return this._image; }
      }

      #region Properties
      // some public properties
      public bool UseDeviceEx
      {
         get;
         private set;
      }

      public Direct3D Direct3D
      {
         get
         {
            if (UseDeviceEx)
               return _direct3DEx;
            else
               return _direct3D;
         }
      }

      public Device Device
      {
         get
         {
            if (UseDeviceEx)
               return _deviceEx;
            else
               return _device;
         }
      }

	  public bool Available
	  {
		  get;
		  private set;
	  }
      #endregion

      #region Events

      /// <summary>
      /// Occurs once per iteration of the main loop.
      /// </summary>
      public event EventHandler MainLoop;

      /// <summary>
      /// Occurs when the device is created.
      /// </summary>
      public event EventHandler DeviceCreated;

      /// <summary>
      /// Occurs when the device is destroyed.
      /// </summary>
      public event EventHandler DeviceDestroyed;

      /// <summary>
      /// Occurs when the device is lost.
      /// </summary>
      public event EventHandler DeviceLost;

      /// <summary>
      /// Occurs when the device is reset.
      /// </summary>
      public event EventHandler DeviceReset;

	   //can't figure out how to access remote session status through .NET
	   [System.Runtime.InteropServices.DllImport("user32")]
	  static extern int GetSystemMetrics(int smIndex);
	  const int SM_REMOTESESSION = 0x1000;

      /// <summary>
      /// Raises the OnInitialize event.
      /// </summary>
      protected virtual void OnInitialize()
      {
      }

      /// <summary>
      /// Raises the <see cref="E:MainLoop"/> event.
      /// </summary>
      protected virtual void OnMainLoop(EventArgs e)
      {
         if (MainLoop != null)
            MainLoop(this, e);
      }

      /// <summary>
      /// Raises the DeviceCreated event.
      /// </summary>
      /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
      protected virtual void OnDeviceCreated(EventArgs e)
      {
         if (DeviceCreated != null)
            DeviceCreated(this, e);
         ForceRendering();
      }

      /// <summary>
      /// Raises the DeviceDestroyed event.
      /// </summary>
      /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
      protected virtual void OnDeviceDestroyed(EventArgs e)
      {
         if (DeviceDestroyed != null)
            DeviceDestroyed(this, e);
      }

      /// <summary>
      /// Raises the DeviceLost event.
      /// </summary>
      /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
      protected virtual void OnDeviceLost(EventArgs e)
      {
         if (DeviceLost != null)
            DeviceLost(this, e);
      }

      /// <summary>
      /// Raises the DeviceReset event.
      /// </summary>
      /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
      protected virtual void OnDeviceReset(EventArgs e)
      {
         if (DeviceReset != null)
            DeviceReset(this, e);
      }

      #endregion

      protected override void OnInitialized(EventArgs e)
      {
         base.OnInitialized(e);
         InitializeDirect3D();
      }

      protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
      {
         base.OnRenderSizeChanged(sizeInfo);
         _sizeChanged = true;
      }

      void InitializeDirect3D()
      {
		  Available = false;
		  // assume that we can't run at all under terminal services
		  if(GetSystemMetrics(SM_REMOTESESSION) != 0)
			  return;

#if USE_XP_MODE
         _direct3D = new Direct3D();
         UseDeviceEx = false;
#else
         try
         {
            _direct3DEx = new Direct3DEx();
            UseDeviceEx = true;
         }
         catch
         {
            _direct3D = new Direct3D();
            UseDeviceEx = false;
         }
#endif

		  bool result = Direct3D.CheckDeviceType(0, DeviceType.Hardware, _adapterFormat, _backbufferFormat, true);
		  if(!result)
			  return;

		 result = Direct3D.CheckDepthStencilMatch(0, DeviceType.Hardware, _adapterFormat, _backbufferFormat, _depthStencilFormat);
		 if(!result)
			 return;

		 Capabilities deviceCaps = Direct3D.GetDeviceCaps(0, DeviceType.Hardware);
		 if((deviceCaps.DeviceCaps & DeviceCaps.HWTransformAndLight) != 0)
			 _createFlags |= CreateFlags.HardwareVertexProcessing;
		 else
			 _createFlags |= CreateFlags.SoftwareVertexProcessing;

		 Available = true;
      }

      /// <summary>
      /// Initializes the various Direct3D objects we'll be using.
      /// </summary>
      private void Initialize(bool startThread)
      {
		  if(!Available)
			  return;

         try
         {
            _startThread = startThread;

            ReleaseDevice();
            HwndSource hwnd = new HwndSource(0, 0, 0, 0, 0, _d3dimage.PixelWidth, _d3dimage.PixelHeight, "SlimDXControl", IntPtr.Zero);

            _pp = new PresentParameters();
            _pp.SwapEffect = SwapEffect.Copy;
            _pp.DeviceWindowHandle = hwnd.Handle;
            _pp.Windowed = true;
            _pp.BackBufferWidth = ((int)Width < 0) ? 1 : (int)Width;
            _pp.BackBufferHeight = ((int)Height < 0) ? 1 : (int)Height;
            _pp.BackBufferFormat = _backbufferFormat;
            _pp.AutoDepthStencilFormat = _depthStencilFormat;

            if (UseDeviceEx)
            {
               // under remote desktop (Windows Server 2008, x86 mode), this will throw
               _deviceEx = new DeviceEx((Direct3DEx)Direct3D, 0,
                  DeviceType.Hardware,
                  hwnd.Handle,
                  _createFlags,
                  _pp);
            }
            else
            {
               _device = new Device(Direct3D, 0,
                  DeviceType.Hardware,
                  hwnd.Handle,
                  _createFlags,
                  _pp);
            }

            // call the users one
            OnDeviceCreated(EventArgs.Empty);
            OnDeviceReset(EventArgs.Empty);

            // only if startThread is true
            if (_startThread)
            {
               CompositionTarget.Rendering += OnRendering;     // BUG: we don't want to render every frame, only when something has changed!
               _d3dimage.IsFrontBufferAvailableChanged += new DependencyPropertyChangedEventHandler(OnIsFrontBufferAvailableChanged);
            }
            _d3dimage.Lock();
            _backBufferSurface = Device.GetBackBuffer(0, 0);
            _d3dimage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, _backBufferSurface.ComPointer);
            _d3dimage.Unlock();
         }
         catch (Direct3D9Exception ex)
         {
            MessageBox.Show(ex.Message, "Caught Direct3D9Exception in SlimDXControl.Initialize()");     // BUG: remove this
            throw;
         }
         catch (Exception ex)
         {
            MessageBox.Show(ex.Message, "Caught Exception in SlimDXControl.Initialize()");     // BUG: remove this
            throw;
         }

         return;
      }

      #region Shutdown and Release
      public void Shutdown()
      {
         ReleaseDevice();
         ReleaseDirect3D();
      }

      private void ReleaseDevice()
      {
         if (_device != null)
         {
            if (!_device.Disposed)
            {
               _device.Dispose();
               _device = null;
               OnDeviceDestroyed(EventArgs.Empty);
            }
         }

         if (_deviceEx != null)
         {
            if (!_deviceEx.Disposed)
            {
               _deviceEx.Dispose();
               _device = null;
               OnDeviceDestroyed(EventArgs.Empty);
            }
         }

         _d3dimage.Lock();
         _d3dimage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, IntPtr.Zero);
         _d3dimage.Unlock();

         ReleaseBackBuffer();
      }

      private void ReleaseDirect3D()
      {
         if (_direct3D != null && !_direct3D.Disposed)
         {
            _direct3D.Dispose();
            _direct3D = null;
         }

         if (_direct3DEx != null && !_direct3DEx.Disposed)
         {
            _direct3DEx.Dispose();
            _direct3DEx = null;
         }
      }
      #endregion

      #region Support for controlling on-demand vs. per-frame rendering
      private static object _locker = new object();

      // set this to true when something has changed, to signal that the rendering loop should not be skipped
      private bool _needsRendering;
      public void ForceRendering()
      {
         lock (_locker)
         {
            _needsRendering = true;
         }
      }

      public bool ResetForceRendering()
      {
         bool ret;
         lock (_locker)
         {
            ret = _needsRendering;
            _needsRendering = false;
         }
         return ret;
      }

      // set this to true to always render every frame, i.e. ignore the NeedsRendering flag
      public bool AlwaysRender { get; set; }
      #endregion

      public void ForceResize(double width, double height)
      {
         Width = width;
         Height = height;
         _sizeChanged = true;
      }

      private void OnRendering(object sender, EventArgs e)
      {
         Debug.Assert(_d3dimage.IsFrontBufferAvailable);
		 if(!Available)
			 return;

         try
         {
            if (Device == null)
            {
               Initialize(_startThread);
               ForceRendering();
            }

            if (_sizeChanged)
            {
               _pp.BackBufferWidth = (int)Width;
               _pp.BackBufferHeight = (int)Height;
               ReleaseBackBuffer();
			   OnDeviceLost(EventArgs.Empty);
               Device.Reset(_pp);               // BUG: under WinXP mode, this throws when doing a window maximize/resize
               OnDeviceReset(EventArgs.Empty);
			   Debug.WriteLine("resize");
               _sizeChanged = false;
               ForceRendering();
            }

			bool needsRendering = ResetForceRendering();
            _d3dimage.Lock();
            if (_d3dimage.IsFrontBufferAvailable && (needsRendering || AlwaysRender))
            {
               Result result = Device.TestCooperativeLevel();
               if (result.IsFailure)
               {
                  throw new Direct3D9Exception("Device.TestCooperativeLevel() failed");
               }

               Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, new Color4(System.Drawing.Color.Black), 0, 0);
               Device.BeginScene();
               // call the users method
               OnMainLoop(EventArgs.Empty);

               Device.EndScene();
               Device.Present();

            }
            _backBufferSurface = Device.GetBackBuffer(0, 0);
            _d3dimage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, _backBufferSurface.ComPointer);
            _d3dimage.AddDirtyRect(new Int32Rect(0, 0, _d3dimage.PixelWidth, _d3dimage.PixelHeight));
            _d3dimage.Unlock();
         }
         catch (Direct3D9Exception ex)
         {
            MessageBox.Show(ex.Message, "Caught Direct3D9Exception in SlimDXControl.OnRendering()");     // BUG: remove this
            Initialize(_startThread);
         }
         catch (Exception ex)
         {
            MessageBox.Show(ex.Message, "Caught Exception in SlimDXControl.OnRendering()");     // BUG: remove this
            throw;
         }

         return;
      }

      #region front & back buffer management
      private void ReleaseBackBuffer()
      {
         if (_backBufferSurface != null && !_backBufferSurface.Disposed)
         {
            _backBufferSurface.Dispose();
            _backBufferSurface = null;

            _d3dimage.Lock();
            _d3dimage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, IntPtr.Zero);
            _d3dimage.Unlock();
         }
      }

      void OnIsFrontBufferAvailableChanged(object sender, DependencyPropertyChangedEventArgs e)
      {
         try
         {
            if (_d3dimage.IsFrontBufferAvailable)
            {
               Initialize(_startThread);
            }
            else
            {
               // we reach here under remote desktop (Windows Server 2008, x64 mode)
               CompositionTarget.Rendering -= OnRendering;
               throw new Direct3D9Exception("_d3dimage.IsFrontBufferAvailable is false");
            }
         }
         catch (Exception ex)
         {
            MessageBox.Show(ex.Message, "Caught Exception in SlimDXControl.OnIsFrontBufferAvailableChanged()");     // BUG: remove this
            throw;
         }
      }
      #endregion

      private void ContentControl_SizeChanged(object sender, SizeChangedEventArgs e)
      {
         ForceResize(e.NewSize.Width, e.NewSize.Height);
      }

      private static void TestForDirectXPlatform()
      {
         // BUG: this is function is insufficient, as it doesn't catch the remote desktop cases

         try
         {
            Direct3DEx d3dEx = new Direct3DEx();
            d3dEx.Dispose();
         }
         catch
         {
            Direct3D d3d = new Direct3D();
            d3d.Dispose();
         }

         return;
      }

      // returns null if success, otherwise an error string
      public static string ValidateDirectXPlatform()
      {
         string mssg = null;

         try
         {
            TestForDirectXPlatform();
         }
         catch (Exception e)  // yes, we want to catch ANYTHING that might happen here
         {
            //throw new InvalidOperationException("Could not initialize Direct3D9.", e);
            string nl = Environment.NewLine;
            mssg = "Unable to initialize DirectX.";
            mssg += nl;
            mssg += "Please verify that you have the latest version of DirectX installed on your machine.  The runtime libraries ";
            mssg += "may be installed directly from the web here: http://www.microsoft.com/downloads/details.aspx?FamilyID=04ac064b-00d1-474e-b7b1-442d8712d553.";
            mssg += nl;
            mssg += "[error text: " + e.Message + "]";
         }
         
         return mssg;
      }
   }
}
