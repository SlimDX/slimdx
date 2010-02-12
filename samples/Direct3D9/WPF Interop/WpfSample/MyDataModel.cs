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
using System.Windows.Resources;
using SlimDX;
using SlimDX.Direct3D9;
using System.IO;
using System.Drawing;
using SlimDX.Wpf;

namespace WpfSample
{
   public class MyDataModel
   {
      private byte[] _buffer;
      private SlimDXControl _control;

      public MyDataModel(SlimDXControl slimDXControl, string imageName, Color color)
      {
         _control = slimDXControl;

         Name = imageName;
         Uri uri = new Uri("pack://application:,,,/Resources/" + imageName + ".png");

         using (Stream s = Application.GetResourceStream(uri).Stream)
         {
            _buffer = new byte[s.Length];
            s.Read(_buffer, 0, (int)s.Length);
         }

         Color = color;
      }

      public string Name
      {
         private set;
         get;
      }

      public Stream Stream
      {
         get
         {
            MemoryStream ms = new MemoryStream(_buffer);
            return ms;
         }
      }

      private Color m_color;
      public Color Color
      {
         get
         {
            return m_color;
         }
         set
         {
            if (m_color != value)
            {
               m_color = value;
               Color4 = new Color4(m_color);
               _control.ForceRendering();

            }
         }
      }

      public Color4 Color4
      {
         get;
         private set;
      }
   }

}
