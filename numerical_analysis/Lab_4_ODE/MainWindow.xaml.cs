using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab4_ODE
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public class Point
        {
            public Point() { }
            public Point(double x, double y)
            {
                X = x; Y = y;
            }
            public double X { get; set; }
            public double Y { get; set; }
        }
        public ObservableCollection<Point> AnaliticalF { get; set; }
        public ObservableCollection<Point> MethodF { get; set; }
        public ObservableCollection<Point> Errors { get; set; }

        private double PrevStep { get; set; }
        private double step;
        public double Step { get { return step; } set { PrevStep = step; step = value; StepLabel.Text = step.ToString(); ;} }


        private double initCond;
        private Interval interval;
        public MainWindow()
        {
            AnaliticalF = new ObservableCollection<Point>();
            MethodF = new ObservableCollection<Point>();
            Errors = new ObservableCollection<Point>();

            InitializeComponent();
            step = 0.05;
            PrevStep = step;
            interval = new Interval(0, 10);
            initCond = 1;
            SelectedMethod = Methods_ODE.Euler;
            StepLabel.Text = "0.05";
        }
        private Action<
            Func<double, double, double>,double, double, Collection<Point>
            >SelectedMethod;

        private Func<double, double, double> TaskODE = (x, y) => { return 0.8 * y - 0.15 * y * y; };
        private Func<double, double, double> TaskAnswer = (x,y) => {
            double tmp = Math.Exp(0.8 * x);
            return 0.8 * y * tmp / (0.8 + 0.15 * y * (tmp - 1));
        };

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Step = double.Parse(StepLabel.Text);
            }
            catch (Exception)
            {
                StepLabel.Text = "0.05";
                Step = 0.05;
            }
            int funcSize = (int)(interval.Length / Step);

            if(funcSize != MethodF.Count)
            {
                if (funcSize > MethodF.Count)
                {
                    for (int i = MethodF.Count; i < funcSize; i++)
                    {
                        MethodF.Add(new Point());
                        AnaliticalF.Add(new Point());
                        Errors.Add(new Point());
                    }
                }
                else
                {
                    for (int i = MethodF.Count-1; i > funcSize; i++)
                    { 
                        MethodF.RemoveAt(i);
                        AnaliticalF.RemoveAt(i);
                        Errors.RemoveAt(i);
                    }
                }
            }
            double h = interval.A;
            for (int j = 0; j < MethodF.Count; j ++)
            {
                MethodF[j].X = h;
                h += Step;
            }
            //double MaxError = 0; double tmpErr = 0; double tempY = 0;
            Methods_ODE.Euler(TaskODE, Step, initCond, MethodF);
            MethodF[0] = MethodF[0];
        }

        private void Methods_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(Methods.SelectedIndex == 0)
                SelectedMethod = Methods_ODE.Euler;
            //else
               // SelectedMethod = Methods_ODE.Gear3;
        }
    }
}
