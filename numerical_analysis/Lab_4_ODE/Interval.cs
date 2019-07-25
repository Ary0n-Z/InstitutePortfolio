using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab4_ODE
{
    class Interval
    {
        public Interval(double a, double b)
        {
            A = a;
            B = b;
        }
        public double A { get; set; }
        public double B { get; set; }
        public double Length { get { return Math.Abs(B - A); } }
    }
}
