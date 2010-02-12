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
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;
using System.Diagnostics;

namespace WpfSample
{
   /// <summary>
   /// Interaction logic for App.xaml
   /// </summary>
   public partial class App : Application
   {
      public App() :
         base()
      {
         StartTracers();
      }
      
      private static void StartTracers()
      {
         //TraceOptions traceOptions = TraceOptions.DateTime | TraceOptions.Callstack;

         TextWriterTraceListener textWriter = new TextWriterTraceListener(Console.Out);
         //textWriter.TraceOutputOptions = traceOptions;
         Trace.Listeners.Add(textWriter);

         //if (!EventLog.SourceExists("SlimDXTest3"))
         //   EventLog.CreateEventSource("SlimDXTest3", "Application");
         //EventLogTraceListener eventWriter = new EventLogTraceListener("SlimDXTest3");
         //eventWriter.TraceOutputOptions = traceOptions;
         //Trace.Listeners.Add(eventWriter);

         Trace.AutoFlush = true;
      }
   }
}
