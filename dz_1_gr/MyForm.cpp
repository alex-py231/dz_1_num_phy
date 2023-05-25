#include "MyForm.h"
#include "sher_eq.h"
#include<iostream>
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

double U1(double r)
{
    double a = 1;
    double b = 1;
    double c = pow(r, -2);
    return c * (-a + b * c);
}
double U(double r)
{
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
    double h = Convert::ToDouble(textBox5->Text);
    double x = Convert::ToDouble(textBox4->Text);
    double x_1, x_2, x_3;
    x_1 = Convert::ToDouble(textBox1->Text);
    x_2 = Convert::ToDouble(textBox2->Text);
    x_3 = Convert::ToDouble(textBox3->Text);
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
    double h_ = 1;
    int i = 0;
    double a, b;
    /*std::string A, B;*/
    do {
        E = h_ * (i + 1. / 2.);
        sher_eq qp1(U, yp, f, 0.001, 0.001, E, x_1, x_2, x_2, x_3);
        double E_e;
        E_e = qp1.search();
        a = qp1.get_a();
        b = qp1.get_b();
        /*richTextBox1->Text = richTextBox1->Text + "левый край:" + Convert::ToString(a) + "  правый край:" + Convert::ToString(b) + ".\n";*/
        richTextBox1->Text = richTextBox1->Text + "энергия: " + Convert::ToString(E_e) + ".\n";
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
