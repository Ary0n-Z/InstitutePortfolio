using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_3_NonlinearEquation.Models;

namespace Lab_3_NonlinearEquation.ViewModels
{
    class ViewModel : ViewModelBase
    {
        public class ResultRecord
        {
            public ResultRecord(uint iteration,  double x, double error)
            {
                Iteration = iteration;
                X = x;
                Error = error;
            }
            public uint Iteration { get; set; }
            public double X { get; set; }
            public double Error { get; set; }
        }
        public ObservableCollection<Function> Functions { get; private set; }
        public ObservableCollection<Alghoritm> Alghoritms { get; private set; }
        static private ObservableCollection<ResultRecord> results = new ObservableCollection<ResultRecord>();
        static public ObservableCollection<ResultRecord> Results { get {return results; } private set { } }

        public int SelectedFunction { get; set; } = -1;
        public int SelectedAlghoritms { get; set; } = -1;


        public ViewModel()
        {
            Functions = new ObservableCollection<Function>();
            Functions.Add(new Function("f(x) = x * sin(2 * x)",(x)=>x* Math.Sin(2.0*x)));
            Functions.Add(new Function("f(x) = 2^(3*x)",(x) => Math.Pow(2.0,(3.0*x))));
            Functions.Add(new Function("f(x) = e^(2*x) * sin(x)",(x)=> Math.Exp(2.0*x)*Math.Sin(x)));
            Alghoritms = new ObservableCollection<Alghoritm>();
            var a = new Alghoritm("Bisection Method",NonLinearEval.BisectionMethod);
            a.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("a", 0.0));
            a.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("b", 0.0));
            a.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Error", 0.001));
            Alghoritms.Add(a);
            var b = new Alghoritm("Newtons Method", NonLinearEval.NewtonsMethod);
            b.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("a", 0.0));
            b.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("b", 0.0));
            b.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Error", 0.001));
            Alghoritms.Add(b);

            var c = new Alghoritm("Bisection Method Windowed", NonLinearEval.BisectionMethodWindowed);
            c.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Left edge", 0.0));
            c.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Right edge", 0.0));
            c.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Width", 0.0));
            c.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Error", 0.001));
            Alghoritms.Add(c);
            var d = new Alghoritm("Newtons Method Windowed", NonLinearEval.NewtonsMethodWindowed);
            d.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Left edge", 0.0));
            d.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Right edge", 0.0));
            d.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Width", 0.0));
            d.Params.Add(new Models.Alghoritms.AlghoritmParam<double>("Error", 0.001));
            Alghoritms.Add(d);
            CalcCommand = new RelayCommand(CallSelectedAlgorihm);
        }
        public RelayCommand CalcCommand { get; private set; }

        private void CallSelectedAlgorihm()
        {
            if (SelectedAlghoritms >= 0 && SelectedFunction >= 0)
            {
                Results.Clear();
                Alghoritms[SelectedAlghoritms].Call(Functions[SelectedFunction]);
            }//TODO: Error!
        }
    }
}
