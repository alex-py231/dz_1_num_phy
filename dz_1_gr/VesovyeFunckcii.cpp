#include "VesovyeFunckcii.h"
VesovyeFunckcii::VesovyeFunckcii(double a, double b, int N) :a(a), b(b), N(N) // Список инициализации
{
	// Выделение памяти под массивы. 
	wgauss = new double[N];
	xgauss = new double[N];
}

void VesovyeFunckcii::do_gauss_kvadratura()
{
	int m; // половина от количество корней.
	m = (N + 1) / 2;
	double eps = 1e-5;

	double x_m_0_iter;
	double x_m_1_inter;

	double P_0;
	double P_1;
	double P;

	double dP;

	for (int i = 1; i <= m; i++)
	{
		x_m_0_iter = cos(M_PI * (i - 0.25) / (N + 0.5));
		x_m_1_inter = 1;
		while (abs((x_m_0_iter - x_m_1_inter)) > eps)
		{
			P_0 = 1;
			P_1 = x_m_0_iter;
			for (int j = 2; j <= N; j++)
			{
				P = ((2 * j - 1) * x_m_0_iter * P_1 - (j - 1) * P_0) / j;
				P_0 = P_1;
				P_1 = P;
			}
			dP = N * (P_0 - x_m_0_iter * P_1) / (1 - x_m_0_iter * x_m_0_iter);
			x_m_1_inter = x_m_0_iter;
			x_m_0_iter = x_m_1_inter - P / dP;
		}

		xgauss[i - 1] = -x_m_0_iter;
		wgauss[i - 1] = 2 / ((1 - x_m_0_iter * x_m_0_iter) * dP * dP);

		xgauss[N - i] = x_m_0_iter;
		wgauss[N - i] = wgauss[i - 1];
	}
}
void VesovyeFunckcii::get_w_x(double* x, double* w)
{
	for (int i = 0; i < N; i++)
	{
		x[i] = (b + a) / 2 + ((b - a) / 2) * xgauss[i];
		w[i] = ((b - a) / 2) * wgauss[i];
	}
}

