using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3_NonlinearEquation.Models
{
    class Function
    {
        public Func<double, double> FuncEquation { get; private set; }
        public string fname;
        public Function(string funcName, Func<double, double> func)
        {
            fname = funcName;
            FuncEquation = func;
        }

        public override string ToString()
        {  return fname; }
    }
}
