/*
 *
 *  Created on: 16 May 2020
 *      Author: marco
 */


#include <iostream>

using namespace std;


#ifndef SIMPLEMETHODS_H_
#define SIMPLEMETHODS_H_

const double tol = 1e-6;

class simple_ode{
private:
	double tin;
	double tend;
	double yin;
	double h;
	double (*fun)(double t, double x);
	double (*jfun)(double t, double x);

public:
	simple_ode(double t0, double y0, double T,double (*f)(double, double), double (*df)(double,double),double step){
			tin = t0;
			yin = y0;
			tend = T;
			fun = f;
			jfun = df;
			h = step;
		}



int last_comp(){
	return ceil((tend-tin)/h);
}

// Eulero implicito, caso scalare

double F(double x, double tn, double yn){
	return x - yn - h*fun(tn+h,x);
}

double JF(double x, double tn, double yn){
	return  1 - h*jfun(tn+h,x);
}


double ei_stepper(double tn,double yn){
	//calcola uno step da tn a tn + h
	double x0;
	x0 = yn;
	double x1;
	double delta = tol + 1;
	int it = 0;
	while (delta>tol && it < 50){
		it++;
		x1 = x0 - F(x0,tn,yn)/ JF(x0,tn,yn); // si può anche fare (*f)(x0)
		delta = abs(x1-x0);
		x0 = x1;
	}

	return x0;
}


double* euler(){
	int ts = last_comp();
	double* y = new double[ts];
	y[0] = yin;
	double tn = 0;
	for(int i =0;i<ts;i++){
		y[i+1] = ei_stepper(tn,y[i]);
		tn+=h;
	}
	return y;
}


void stampa(double* solvec){
	for (int i=0 ;i < last_comp() ;i++){
		cout << solvec[i] << endl;
		}
}



};

#endif /* SIMPLEMETHODS_h_ */

