#include "sher_eq.h"
double sher_eq::FindRoot(double x_start, double x_stop)
{
    double c;
    double a1 = x_start;
    double b1 = x_stop;
    while ((b1 - a1) / 2. > eps)
    {
        c = (a1 + b1) / 2;
        if ((this->eq(U, E, a1) * eq(U, E, c) > 0))
        {
            a1= c;
        }
        else
        {
            b1 = c;
        }
    }
    return c;
}
//double sher_eq::S()
//{
//    double sum = 0;
//    double h = 0.0001;
//    int n = (this->b - a) / h;
//    for (int i = 0; i < n; i++)
//    {
//        sum += f(a + (i * h), E) * h;
//    }
//    return sum;
//}
double sher_eq::S()
{
    int n = 4;
    double* x = new double[n];
    double* w = new double[n];
    VesovyeFunckcii vs(a, b, n);
    vs.do_gauss_kvadratura();
    vs.get_w_x(x, w);

    double SUM = 0;

    for (int i = 0; i < n; i++)
    {
        SUM += w[i] * f(x[i], E);
    }
    return SUM;
}
void sher_eq::search()
{
    bool N = true;
    double res;
    do {
        E += h;
        /*cout << E_ << endl;*/

       /* cout << h << endl;*/
        a = FindRoot(x_start_a, x_stop_a);
        b = FindRoot(x_start_b, x_stop_b);
        res = S();
        /*cout << res << endl;*/
        /*cout << a << "  " << b << endl;*/
        if (res < E_true && abs(res - E_true) > eps)
        {
            if (h < 0)
            {
                h *= -1;
            }
        }
        else if (res > E_true && abs(res - E_true) > eps)
        {
            if (h > 0)
            {
                h *= -1;
                h /= 2;
            }

        }
        else
        {
            N = false;
        }
    } while (N == true);
}
