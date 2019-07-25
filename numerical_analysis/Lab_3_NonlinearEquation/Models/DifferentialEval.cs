using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3_NonlinearEquation.Models
{
    class DifferentialEval
    {
        public struct Points {
            public double x;
            public double y;
        };
        public static double VariationOfParameters(double x, Points[] points)
        {
            double result = 0.0, tempSum;
            double p;
            var n = points.Length;
            for(uint i = 0; i < n; i++)
            {
                tempSum = 0.0;
                for(uint j = 0; j < n; j++)
                    if (j != i)
                    {
                        p = 1;
                        for(uint k = 0; k < n; k++)
                            if(k!=i && k != j)
                                p*= (x - points[k].x) / (points[i].x - points[k].x);
                        tempSum += p/(points[i].x - points[j].x);
                    }
                result += points[i].y * tempSum;
            }
            return result;
        }
        public static double VariationOfParameters(double x, Func<double,double> F,double a,double b)
        {
            double result = 0.0, tempSum;
            double p;
            for (double i = a; i < b; i+=0.01)//x
            {
                tempSum = 0.0;
                for (double j = a; j < b; j+=0.01)
                    if (j != i)
                    {
                        p = 1;
                        for (double k = a; k < b; k+=0.01)
                            if (k != i && k != j)
                                p *= (x - k) / (i - k);
                        tempSum += p / (i - j);
                    }
                result += F(i) * tempSum;
            }
            return result;
        }
    }
}
