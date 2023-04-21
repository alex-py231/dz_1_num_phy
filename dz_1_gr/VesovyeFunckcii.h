#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
ref class VesovyeFunckcii
{
public:
	VesovyeFunckcii(double a, double b, int N);
	void do_gauss_kvadratura();
	void get_w_x(double* x, double* w);
private:
	double a;
	double b;
	int N;
	double* wgauss;
	double* xgauss;
};

