using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_3_NonlinearEquation.Models.Alghoritms;

namespace Lab_3_NonlinearEquation.Models.Alghoritms
{
    class AlghoritmParam<T> : IParam<T>
    {
        public T Value { get; set; }
        public string Name { get; private set; }
        public AlghoritmParam(string name, T value)
        {
            Name = name;
            Value = value;
        }

    }
}
