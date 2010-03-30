using System;
using System.Text;
using SlimDX.DXGI;
using SlimDX.Direct3D10;
using Device = SlimDX.Direct3D10.Device;

namespace SimpleEnumeration {
    class Program {
        static void Main() {
            using (var factory = new Factory()) {
                PrintAdapters(factory);
            }
        }

        private static void PrintAdapters(Factory factory) {
            var adapterCount = factory.GetAdapterCount();

            for (var adapterIndex = 0; adapterIndex < adapterCount; ++adapterIndex) {
                using (var adapter = factory.GetAdapter(adapterIndex)) {

                    Console.WriteLine("Adapter Index: {0}", adapterIndex);

                    foreach (var descProperty in adapter.Description.GetType().GetProperties()) {
                        Console.WriteLine("    {0}: {1}", ParseName(descProperty.Name), descProperty.GetValue(adapter.Description, null));
                    }

                    PrintAdapterOutputs(adapter);
                    PrintDeviceInformation(adapter);
                }
            }
        }

        private static void PrintDeviceInformation(Adapter adapter) {
            using (var device = new Device(adapter, DriverType.Hardware, DeviceCreationFlags.None)) {
                PrintSupportedQualityLevels(device);
                PrintSupportedFormats(device);
            }
        }

        private static void PrintSupportedFormats(Device device) {
            Console.WriteLine("    Format Support:");
            foreach (var format in Enum.GetValues(typeof(Format))) {
                Console.WriteLine("        Format: {0}", format);
                var formatSupport = device.CheckFormatSupport((Format)format);
                Console.WriteLine("            Format support: {0}", formatSupport);
            }
        }

        private static void PrintSupportedQualityLevels(Device device) {
            Console.WriteLine("    Multi-Sample Support:");
            for (var sampleCount = 1; sampleCount <= 32; sampleCount *= 2) {
                var qualityLevels = device.CheckMultisampleQualityLevels(Format.R8G8B8A8_UNorm, sampleCount);
                Console.WriteLine("        Sample Count: {0}", sampleCount);

                if (qualityLevels != 0)
                    Console.WriteLine("            Max Quality Level: {0}", qualityLevels);
                else {
                    Console.WriteLine("            Not supported");
                }
            }
        }

        private static void PrintAdapterOutputs(Adapter adapter) {
            var outputCount = adapter.GetOutputCount();

            for (var outputIndex = 0; outputIndex < outputCount; ++outputIndex) {
                using (var output = adapter.GetOutput(outputIndex)) {

                    Console.WriteLine("    Output Index: {0}", outputIndex);
                    foreach (var descProperty in output.Description.GetType().GetProperties()) {
                        Console.WriteLine("        {0}: {1}", ParseName(descProperty.Name), descProperty.GetValue(output.Description, null));
                    }

                    PrintDisplayModes(output, Format.R8G8B8A8_UNorm);
                }
            }
        }

        private static void PrintDisplayModes(Output output, Format format) {
            Console.WriteLine("        Display modes for format: {0}", format);

            var displayModes = output.GetDisplayModeList(format, 0);

            foreach (var displayMode in displayModes) {
                foreach (var descProperty in displayMode.GetType().GetProperties()) {
                    Console.WriteLine("            {0}: {1}", ParseName(descProperty.Name), descProperty.GetValue(displayMode, null));
                }
                Console.WriteLine();
            }
        }

        static string ParseName(string name) {
            var sb = new StringBuilder(name.Length + 2);
            sb.Append(name[0]);

            for (var i = 1; i < name.Length; ++i) {
                if (char.IsUpper(name[i])) {
                    sb.Append(' ');
                }
                sb.Append(name[i]);
            }

            return sb.ToString();
        }
    }
}
