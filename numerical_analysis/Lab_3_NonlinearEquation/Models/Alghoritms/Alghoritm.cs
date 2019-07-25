using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_3_NonlinearEquation.Models.Alghoritms;

namespace Lab_3_NonlinearEquation.Models
{
    class Alghoritm
    {
        public delegate double AlgoritmFunc(Func<double,double> F,params double[] args);
        private AlgoritmFunc uargs;
        public System.Collections.ObjectModel.ObservableCollection<AlghoritmParam<double>> Params { get; set; }
        public string Name{get; private set;}
        public Alghoritm(string name, AlgoritmFunc args)
        {
            Name = name;
            uargs = args;
            Params = new System.Collections.ObjectModel.ObservableCollection<AlghoritmParam<double>>();
        }

        public double Call(Function function)
        {

            var query =
                from p in Params
                select p.Value;
            return uargs.Invoke(function.FuncEquation, query.ToArray()); ;


        }
    }
}
