#include "MyForm.h"
#include "sher_eq.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

double U(double r)
{
    double a = 1;
    double b = 1;
    double c = pow(r, -2);
    return c * (-a + b * c);
}
double U1(double r)
{
    double b = 1;
    return r * r;
}
double f(double r, double E)
{
    double M = 1;
    return 2 * M * sqrt(abs(E - U(r)));
}
double yp(double(*f)(double), double E, double r)
{
    return U(r) - E;
}
void main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	dz1gr::MyForm form;
	Application::Run(% form);
}

System::Void dz1gr::MyForm::plorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    int n = 100;
 /*   double* x = new double[n];
    double* y = new double[n];*/
    double h = 0.03;
    double x = 0.8;
    double y;
    /*double h = 0.02;
    double x = -1;
    double y;
    for (int i = 0; i < n; i++)
    {
        x += h;
        y = U(x);
        this->chart1->Series[0]->Points->AddXY(x, y);
    }*/
    for (int i = 0; i < n; i++)
    {
        x += h;
        y = U(x);
        this->chart1->Series[0]->Points->AddXY(x, y);
    }
    
    double E ;
    double h_ = 0.1;
    int i = 0;
    double a, b;
    do {
        E = h_ * (i + 1. / 2.);
        sher_eq qp1(U, yp, f, 0.001, 0.001, E, 0, 1.41, 1.41, 10);
        qp1.search();
        a = qp1.get_a();
        b = qp1.get_b();
        this->chart1->Series[i + 1]->Points->AddXY(a, U(a));
        this->chart1->Series[i + 1]->Points->AddXY(b, U(b));
        h = (b - a) / n;
        x = a;
        for (int j = 0; j < n; j++)
        {
            y = U(x) - U(a);
            this->chart2->Series[i]->Points->AddXY(x, y);
            x += h;
        }
        for (int j = 0; j < n + 1; j++)
        {
            y = U(x) - U(a);
            this->chart2->Series[i]->Points->AddXY(x, abs(y));
            x -= h;
        }
        qp1.~sher_eq();
        i++;
    } while (i < 6);
}
