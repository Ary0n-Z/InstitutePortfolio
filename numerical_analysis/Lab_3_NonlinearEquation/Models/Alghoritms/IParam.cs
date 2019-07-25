using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3_NonlinearEquation.Models.Alghoritms
{
    interface IParam<T>
    {
        T Value { get; set; }
        string Name { get;}
    }
}
