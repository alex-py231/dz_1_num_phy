#pragma once
#include<iostream>
#include"VesovyeFunckcii.h"
typedef double (*F)(double,double);
typedef double (*u)(double);
typedef double (*Eq)(u, double, double);
public ref class sher_eq
{
private:
	u U;// потециал
	Eq eq;// уравнение для поиска точек поворота
	F f;// функция ,которую мы итегрируем
	double h;// шаг
	double eps;// точность
	double E;// значение энергии на шаге
	double E_true;// истинное значение энергии
	double x_start_a, x_stop_a;// отрезок,где содержится точка поворота a
	double x_start_b, x_stop_b;// отрезок,где содержится точка поворота b
	double a, b;// координаты точек поворота
	double FindRoot(double x_start, double x_stop);// функция организовывувающая поиск точек поворота
	double S();
	
public:
	sher_eq(u U, Eq eq, F f, double eps, double h, double E_true, double x_start_a, double x_stop_a, double x_start_b, double x_stop_b)
	{
		this->U = U;
		this->eq = eq;
		this->f = f;
		this->eps = eps;
		this->h = h;
		this->E_true = E_true;
		this->x_start_a = x_start_a;
		this->x_stop_a = x_stop_a;
		this->x_start_b = x_start_b;
		this->x_stop_b = x_stop_b;
	}
	double search();
	double get_a() { return a; }
	double get_b() { return b; }
	~sher_eq() {};
};


