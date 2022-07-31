using CSCore.CoreAudioAPI;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO.Ports;
using System.Threading;

namespace PhysiMix
{
    class Program
    {
        static SerialPort _serialPort;
        private static void Main(string[] args)
        {
            _serialPort = new SerialPort();
            _serialPort.PortName = "COM3";//Set your board COM
            _serialPort.BaudRate = 115200;
            _serialPort.DataBits = 8;
            _serialPort.StopBits = StopBits.One;
            _serialPort.Parity = Parity.None;
            _serialPort.Handshake = Handshake.None;
            _serialPort.Open();



            while (true)
            {
                using (var sessionManager = GetDefaultAudioSessionManager2(DataFlow.Render))
                {
                    using (var sessionEnumerator = sessionManager.GetSessionEnumerator())
                    {
                        string msg = "";
                        string dataString = _serialPort.ReadLine();
                        Console.WriteLine(dataString);
                        string[] data = dataString.Split(';');
                        foreach (var session in sessionEnumerator)
                        {
                            using (var simpleVolume = session.QueryInterface<SimpleAudioVolume>())
                            using (var sessionControl = session.QueryInterface<AudioSessionControl2>())
                            {
                                if ("System.Diagnostics.Process (" + data[0] + ")" == sessionControl.Process.ToString() && data.Length == 2)
                                {
                                    int volume = 0;
                                    for (int i = 0; i != 100; i++)
                                    {
                                        if (data[1].Contains(i.ToString()))
                                        {
                                            volume = i;
                                        }
                                    }
                                    simpleVolume.MasterVolume = volume / 100f;
                                }
                                string text = sessionControl.Process.ToString();
                                msg = text.Substring(text.IndexOf('(') + 1, text.IndexOf(')') - 1 - text.IndexOf('(')) + "," + msg;
                            }
                        }
                        _serialPort.WriteLine(msg + ";");
                        Thread.Sleep(500);
                    }
                }
            }
        }

        private static AudioSessionManager2 GetDefaultAudioSessionManager2(DataFlow dataFlow)
        {
            using (var enumerator = new MMDeviceEnumerator())
            {
                using (var device = enumerator.GetDefaultAudioEndpoint(dataFlow, Role.Multimedia))
                {
                    Debug.WriteLine("DefaultDevice: " + device.FriendlyName);
                    var sessionManager = AudioSessionManager2.FromMMDevice(device);
                    return sessionManager;
                }
            }
        }
    }
}
