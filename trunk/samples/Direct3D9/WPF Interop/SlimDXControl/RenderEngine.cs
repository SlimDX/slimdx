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
using System.Diagnostics;

namespace SlimDX.Wpf
{
   public interface IRenderEngine
   {
      void OnDeviceCreated(object sender, EventArgs e);
	  void OnDeviceDestroyed(object sender, EventArgs e);
	  void OnDeviceLost(object sender, EventArgs e);
	  void OnDeviceReset(object sender, EventArgs e);
	  void OnMainLoop(object sender, EventArgs e);
   }
}
