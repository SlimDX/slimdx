/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// This code is Copyright (c) 2009 LizardTech, a Celartem Company, 1008    //
// Western Avenue, Suite 200, Seattle, WA 98104.  Unauthorized use or      //
// distribution prohibited.  Access to and use of this code is permitted   //
// only under license from LizardTech.  Portions of the code are protected //
// by US and foreign patents and other filings. All Rights Reserved.       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

using System;
using System.Windows;
using SlimDX;
using SlimDX.Wpf;

namespace WpfSample
{
   public partial class WpfWindow : Window
   {
      MyRenderEngine m_renderEngine;
      MyDataModel m_dataModel;

	  public WpfWindow()
      {
         InitializeComponent();

         string err = SlimDXControl.ValidateDirectXPlatform();
         if (err != null && err.Length > 0)
         {
            MessageBox.Show(err);
            System.Environment.Exit(1);
         }

         m_dataModel = new MyDataModel(m_slimDXControl, "lizard", System.Drawing.Color.Blue);
         m_renderEngine = new MyRenderEngine(m_dataModel);

         this.Loaded += new RoutedEventHandler(Window_Loaded);
         this.Closed += new EventHandler(Window_Closed);
      }

      private void Window_Loaded(object sender, RoutedEventArgs e)
      {
         m_slimDXControl.Setup(m_renderEngine);
      }

      private void Window_Closed(object sender, EventArgs e)
      {
         m_slimDXControl.Shutdown();
      }

      private void MouseDownHandler(object sender, System.Windows.Input.MouseButtonEventArgs e)
      {
         if (e.LeftButton == System.Windows.Input.MouseButtonState.Pressed)
         {
            m_dataModel.Color = System.Drawing.Color.Blue;
         }
         else if (e.RightButton == System.Windows.Input.MouseButtonState.Pressed)
         {
            m_dataModel.Color = System.Drawing.Color.Red;
         }
      }

      private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
      {
         m_slimDXControl.ForceResize(e.NewSize.Width, e.NewSize.Height);
         return;
      }
   }
}
