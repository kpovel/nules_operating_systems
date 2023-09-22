using System;
using System.ServiceProcess;

namespace lab4._2
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            var scDevices = ServiceController.GetDevices();

            int numAdapter = 0,
                numFileSystem = 0,
                numKernel = 0,
                numRecognizer = 0;

            Console.WriteLine("Device driver services on the local computer:");

            foreach (ServiceController scTemp in scDevices)
            {
                Console.WriteLine(" [{0}] {1}", scTemp.Status, scTemp.DisplayName);
                Console.WriteLine("\tType = {0}", scTemp.ServiceType);

                // Update counters using the service type bit flags.
                if ((scTemp.ServiceType & ServiceType.Adapter) != 0)
                {
                    numAdapter++;
                }

                if ((scTemp.ServiceType & ServiceType.FileSystemDriver) != 0)
                {
                    numFileSystem++;
                }

                if ((scTemp.ServiceType & ServiceType.KernelDriver) != 0)
                {
                    numKernel++;
                }

                if ((scTemp.ServiceType & ServiceType.RecognizerDriver) != 0)
                {
                    numRecognizer++;
                }
            }

            Console.WriteLine();
            Console.WriteLine("Total of {0} device driver services", scDevices.Length);
            Console.WriteLine("  {0} are adapter drivers", numAdapter);
            Console.WriteLine("  {0} are file system drivers", numFileSystem);
            Console.WriteLine("  {0} are kernel drivers", numKernel);
            Console.WriteLine("  {0} are file system recognizer drivers", numRecognizer);
        }
    }
}