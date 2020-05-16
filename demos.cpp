/*
 * demos.cpp
 *
 *  Created on: 16 May 2020
 *      Author: marco
 */


#include <iostream>
#include <cmath>
#include <fstream>
#include "simple_euleroimpl.h"
using namespace std;



double odefun(double t, double x);
double dfun(double t, double x);


int main(){



	cout << "Test Eulero implicito su semplici eq. scalari: \n" << endl;
	double t0, y0, T, step;
	cout << "INSERISCI DATI: \n tempo iniziale t0: "<< endl;
	cin >> t0;
	cout << "\n dato iniziale y0: "<< endl;
	cin >> y0;
	cout << "\n tempo finale T: "<< endl;
	cin >> T;
	cout << "\n passo temporale h: "<< endl;
	cin >> step;

	simple_ode test1(t0,y0,T,odefun,dfun,step);
	double*sol = test1.euler();
	test1.stampa(sol);


	double* hrange = new double[6];
	double h = 0.1;
	for (int i = 0; i<6; i++){
		hrange[i] = h/pow(10,i);
	}

	double* soln;
	double err;
	freopen ("output_converge.txt","w",stdout); // stampa su file errore assoluto
	for (int j = 0; j<6;j++ ){
		simple_ode test1(0,1,1,odefun,dfun,hrange[j]); //sol. e' exp(-t)
		soln = test1.euler();
		err = abs(soln[test1.last_comp()] - exp(-1));
		cout << "ERRORE \t" << "\t" << err << " con h \t" << hrange[j] << endl;
	}

	fclose (stdout);
	return 0;
}


double odefun(double t, double x){
	return -x;
}

double dfun(double t, double x){
	return  -1;
}

