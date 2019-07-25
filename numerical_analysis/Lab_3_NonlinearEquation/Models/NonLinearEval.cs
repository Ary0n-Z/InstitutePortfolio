using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_3_NonlinearEquation.Models;

namespace Lab_3_NonlinearEquation.Models
{
    class NonLinearEval
    {
        //Windowed wrapper
        public static double BisectionMethodWindowed(
           Func<double, double> F, params double[] args)
        {
            double left = args[0],
                right = args[1],
                width = args[2],
                error = args[3],
                result = 0; ;
            double x = left;
            do
            {
                var rx = x + width;
                result = BisectionMethod(F, x, rx, error);
                if ((result < x + 2 * error && result > x - 2 * error) ||
                    (result < rx + 2 * error && result > rx - 2 * error))
                    x += width;
                else
                    break;
            } while (x < right);
            return result;
        }
        public static double NewtonsMethodWindowed(
          Func<double, double> F,
         params double[] args)
        {
            double left = args[0],
               right = args[1],
               width = args[2],
               error = args[3],
               result = 0;

            double x = left;
            do
            {
                var rx = x + width;
                result = NewtonsMethod(F, error, x, rx);
                if ((result < x + error && result > x - error) ||
                    (result < rx + error && result > rx - error))
                    x += width;
                else
                    break;
            } while (x < right);
            return result;
        }
        //Interval wrapper
        public static double BisectionMethod(
            Func<double, double> F,params double[] args)
        {
            double a = args[0], b = args[1], error = args[2];
            return BisectionMethod(F, a, b, error);
        }
        public static double NewtonsMethod(
         Func<double, double> F,
        params double[] args)
        {
            double a = args[0];
            double b = args[1];
            double error = args[2];
            return NewtonsMethod(F, error, a, b);
        }

        //Methods
        public static double BisectionMethod(
            Func<double, double> F,  double a, double b, double error)
        {
            double center = (a + b) / 2.0, fa, fc;
            error = error * 2.0;
            uint it = 1;
            while (b - a >= error)
            {
                center = (a + b) / 2.0;
                fa = F(a);
                fc = F(center);
                if (Math.Sign(fa) * Math.Sign(fc) > 0)
                    a = center;
                else
                    b = center;
                ViewModels.ViewModel.Results.Add(new ViewModels.ViewModel.ResultRecord(it++, center, (b - a) / 2.0));
            }
            return center;
        }
             
        public static double NewtonsMethod(
            Func<double, double> F,
            double error, double a, double b)
        {
            uint it = 1;
            double c = (a + b) / 2.0, 
                cprev, 
                alpha = 1, 
                fc = F(c), 
                fcprev;
            do
            {
                cprev = c;
                fcprev = fc;
                M: c = c - alpha * (fc / DifferentialEval.VariationOfParameters(c, F,a,b));
                fc = F(c);
                if (Math.Abs(fc) > Math.Abs(fcprev))
                {
                    alpha /= 2.0;
                    c = cprev; fc = fcprev;
                    goto M;
                }
                ViewModels.ViewModel.Results.Add(new ViewModels.ViewModel.ResultRecord(it++,c, Math.Abs(c - cprev)));
            } while (Math.Abs(c - cprev) > error);
            return c;
        }
    }
}
