using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Lab4_ODE.MainWindow;

namespace Lab4_ODE
{
    static class Methods_ODE
    {
        public static void Euler
            (Func<double, double, double> Ode,
            double h, double Y, Collection<Point> resultBuffer)
        {
            double t = 0;
            for (int i = 0; i < resultBuffer.Count; i++)
            {
                resultBuffer[i].Y = Y;
                t += h;
                Y = Y + h * Ode(t, Y);
            }
        }
        public static double EulerPrediction
          (Func<double, double, double> Ode,
          double t, double y)
        {
            return (y + t * Ode(t, y));
        }
        //public static double[] Gear3
        //   (Func<double, double, double> Ode,
        //   double h, Interval interval, double Y)
        //{
        //    uint N = (uint)(interval.Length / h);
        //    Interval firstValues = new Interval(interval.A, interval.A + 3 * h);
        //    double[] resultFunction = new double[N];
        //    Array.Copy(Euler(Ode, h, firstValues, Y),resultFunction,3);

        //    double t = 3 * h;
        //    Y = resultFunction[2];
        //    double predictionY;
        //    for (uint i = 3; i < N; i++)
        //    {
        //        predictionY = EulerPrediction(Ode, t, Y);
        //        Y = (1.0/11.0)*(18.0 * resultFunction[i - 1] - 9.0 * resultFunction[i - 2] + 2.0 * resultFunction[i - 3])
        //          + (6.0 * h * Ode((t + h), predictionY) )/ 11.0;
        //        resultFunction[i] = Y;
        //        t += h;
        //    }
        //    return resultFunction; 
        //}
    }
}
