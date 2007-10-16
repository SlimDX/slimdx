using System;
using System.IO;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;

using DX = SlimDX;
using D3D = SlimDX.Direct3D;
using D3D10 = SlimDX.Direct3D10;

namespace MiniTri
{
  [StructLayout(LayoutKind.Sequential)]
  public struct Message
  {
    public IntPtr hWnd;
    public uint msg;
    public IntPtr wParam;
    public IntPtr lParam;
    public uint time;
    public Point p;
  }

  [StructLayout(LayoutKind.Sequential)]
  struct Vertex
  {
    public DX.Vector4 PositionRhw;
    public int Color;
  }

  class Program
  {
    static Form RenderForm;

    static D3D10.Device device;

    static D3D10.SwapChain swapChain;
    static D3D10.RenderTargetView renderTargetView;

    static D3D10.InputLayout inputLayout;
    static D3D10.Effect effect;
    static D3D10.EffectTechnique technique;
    static D3D10.EffectPass pass;
    
    static D3D.Viewport viewport;

    static D3D10.Buffer vertices;


    [DllImport("User32.dll",CharSet = CharSet.Auto)]
    static extern bool PeekMessage(out Message msg,IntPtr hWnd,uint messageFilterMin,uint messageFilterMax,uint flags);

    private static bool AppStillIdle
    {
      get
      {
        Message msg;
        return !PeekMessage(out msg,IntPtr.Zero,0,0,0);
      }
    }

    private static void Application_Idle(object sender,EventArgs e)
    {
      while(AppStillIdle)
      {
        renderTargetView.Clear(new D3D.ColorValue(0.0f,0.0f,0.0f));
        
        device.InputAssembler.SetInputLayout(inputLayout);
        device.InputAssembler.SetPrimitiveTopology(D3D10.PrimitiveTopology.TriangleList);
        device.InputAssembler.SetVertexBuffers(0,new D3D10.VertexBufferBinding(vertices,sizeof(float) * 3,0));

        for(int p = 0; p < technique.PassCount; ++p)
        {
          technique.GetPassByIndex(p).Apply();
          device.Draw(3,0);
        }
        
        swapChain.Present(0,D3D10.PresentFlags.None);
      }
    }

    static void Main(string[] args)
    {
      using(RenderForm = new Form())
      {
        // Create the device.
        device = new D3D10.Device(D3D10.DriverType.Hardware,D3D10.DeviceCreationFlags.Debug);

        // Create a swap chain.
        D3D10.SwapChainDescription swapChainDescription = new D3D10.SwapChainDescription();
        swapChainDescription.BufferCount = 1;
        swapChainDescription.Width = RenderForm.ClientSize.Width;
        swapChainDescription.Height = RenderForm.ClientSize.Height;
        swapChainDescription.Format = D3D10.Format.R8G8B8A8_UNorm;
        swapChainDescription.RefreshRate = new D3D10.Rational(60,1);
        swapChainDescription.Scaling = D3D10.DisplayModeScaling.Unspecified;
        swapChainDescription.ScanlineOrdering = D3D10.DisplayModeScanlineOrdering.Unspecified;
        swapChainDescription.Usage = D3D10.SurfaceUsage.RenderTargetOutput;
        swapChainDescription.Flags = D3D10.SwapChainFlags.None;
        swapChainDescription.OutputHandle = RenderForm.Handle;
        swapChainDescription.Windowed = true;
        swapChainDescription.SwapEffect = D3D10.SwapEffect.Discard;
        swapChainDescription.SampleCount = 1;
        swapChainDescription.SampleQuality = 0;
        swapChain = new D3D10.SwapChain(device,swapChainDescription);

        // Attach a render target view to the swap chain's back buffer.
        using(D3D10.Texture2D backBuffer = swapChain.GetBuffer(0))
        {
          renderTargetView = new D3D10.RenderTargetView(device,backBuffer);
        }
        
        // Prepare the viewport.
        viewport.X = RenderForm.ClientRectangle.Left;
        viewport.Y = RenderForm.ClientRectangle.Top;
        viewport.Width = RenderForm.ClientSize.Width;
        viewport.Height = RenderForm.ClientSize.Height;
        viewport.MinZ = 0.0f;
        viewport.MaxZ = 1.0f;
        
        // Bind the viewport and render target.
        device.Rasterizer.SetViewports(viewport);
        device.OutputMerger.SetTargets(renderTargetView);
        
        // Create the vertices.
        DX.DataStream verticesData = new DX.DataStream(sizeof(float) * 9,false,true);
        verticesData.Write(0.0f);
        verticesData.Write(0.5f);
        verticesData.Write(0.5f);
        
        verticesData.Write(0.5f);
        verticesData.Write(-0.5f);
        verticesData.Write(0.5f);
        
        verticesData.Write(-0.5f);
        verticesData.Write(-0.5f);
        verticesData.Write(0.5f);

        
        // Rewind the stream so D3D10 reads from the proper point.
        verticesData.Seek(0,SeekOrigin.Begin);
        vertices = new D3D10.Buffer(device,sizeof(float) * 9,verticesData,D3D10.ResourceUsage.Immutable,D3D10.BindFlags.VertexBuffer,D3D10.CpuAccessFlags.None,D3D10.ResourceOptionFlags.None);
        
        // Create the shader.
        effect = D3D10.Effect.FromFile(device,"MiniTri10.fx","fx_4_0");
        technique = effect.GetTechniqueByIndex(0);
        pass = technique.GetPassByIndex(0);
        
        // Create the input layout.
        D3D10.InputElement[] inputElements = new D3D10.InputElement[]
          {
            new D3D10.InputElement("POSITION",0,D3D10.Format.R32G32B32_Float,0,0)
          };

        inputLayout = new D3D10.InputLayout(device,inputElements,pass.Signature);

        // Main loop.
        Application.Idle += Application_Idle;
        Application.Run(RenderForm);

        // Clean up.
        if(vertices != null)
          vertices.Dispose();
        if(renderTargetView != null)
          renderTargetView.Dispose();
        if(swapChain != null)
          swapChain.Dispose();
        if(device != null)
          device.Dispose();
      }
    }
  }
}
