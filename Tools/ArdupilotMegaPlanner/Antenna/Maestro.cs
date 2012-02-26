﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArdupilotMega.Antenna
{
    class Maestro : ITrackerOutput
    {
        public SerialPort ComPort { get; set; }
        /// <summary>
        ///  0-360
        /// </summary>
        public double TrimPan { get; set; }
        /// <summary>
        /// -90 - 90
        /// </summary>
        public double TrimTilt { get; set; }

        public int PanStartRange { get; set; }
        public int TiltStartRange { get; set; }
        public int PanEndRange { get; set; }
        public int TiltEndRange { get; set; }

        public bool PanReverse { get { return _panreverse == -1; } set { _panreverse = value == true ? -1 : 1 ;  } }
        public bool TiltReverse { get { return _tiltreverse == -1; } set { _tiltreverse = value == true ? -1 : 1; } }

        int _panreverse = 1;
        int _tiltreverse = 1;

        byte PanAddress = 0;
        byte TiltAddress = 1;

        public bool Init()
        {

            if ((PanStartRange - PanEndRange) == 0)
            {
                System.Windows.Forms.MessageBox.Show("Invalid Pan Range", "Error");
                return false;
            }

            if ((TiltStartRange - TiltEndRange) == 0)
            {
                System.Windows.Forms.MessageBox.Show("Invalid Tilt Range", "Error");
                return false;
            }

            try
            {
                ComPort.Open();
            }
            catch (Exception ex) { System.Windows.Forms.MessageBox.Show("Connect failed " + ex.Message,"Error"); return false; }

            return true;
        }
        public bool Setup() 
        {
            int target = 100;
            // speed
            var buffer = new byte[] { 0x87, PanAddress, (byte)(target & 0x7F), (byte)((target >> 7) & 0x7F) };
            ComPort.Write(buffer, 0, buffer.Length);

            buffer = new byte[] { 0x87, TiltAddress, (byte)(target & 0x7F), (byte)((target >> 7) & 0x7F) };
            ComPort.Write(buffer, 0, buffer.Length);

            // accel
            target = 3;
            buffer = new byte[] { 0x89, PanAddress, (byte)(target & 0x7F), (byte)((target >> 7) & 0x7F) };
            ComPort.Write(buffer, 0, buffer.Length);

            buffer = new byte[] { 0x89, TiltAddress, (byte)(target & 0x7F), (byte)((target >> 7) & 0x7F) };
            ComPort.Write(buffer, 0, buffer.Length);

            return true;
        }

        double wrap_180(double input)
        {
            if (input > 180)
                return input - 360;
            if (input < -180)
                return input + 360;
            return input;
        }

        public bool Pan(double Angle)
        { 
            // using a byte so it will autowrap

            double range = Math.Abs(PanStartRange - PanEndRange);

            double centerrange = (range / 2) - TrimPan;

            short PointAtAngle = Constrain(wrap_180(Angle - TrimPan), PanStartRange, PanEndRange);

            byte target = (byte)((((PointAtAngle / range) * 2.0) * 127 + 127) * _panreverse);

            Console.WriteLine("P " + Angle + " " + target + " " + PointAtAngle);

            var buffer = new byte[] { 0xff,PanAddress,target};
            ComPort.Write(buffer, 0, buffer.Length);

            return true; 
        }

        public bool Tilt(double Angle)
        {
            double range = Math.Abs(TiltStartRange - TiltEndRange);

            short PointAtAngle = Constrain((Angle - TrimTilt), TiltStartRange - TrimTilt, TiltEndRange - TrimTilt);

            byte target = (byte)((((PointAtAngle / range ) * 2) * 127 + 127) * _tiltreverse);

            Console.WriteLine("T " + Angle + " " + target + " " + PointAtAngle);

            var buffer = new byte[] { 0xff, TiltAddress, target };
            ComPort.Write(buffer, 0, buffer.Length);

            return true; 
        }

        public bool PanAndTilt(double pan, double tilt)
        {
            if (Tilt(tilt) && Pan(pan))
                return true;

            return false;
        }

        public bool Close()
        {
            ComPort.Close();
            return true;
        }

        short Constrain(double input, double min, double max)
        {
            if (input < min)
                return (short)min;
            if (input > max)
                return (short)max;
            return (short)input;
        }
    }
}