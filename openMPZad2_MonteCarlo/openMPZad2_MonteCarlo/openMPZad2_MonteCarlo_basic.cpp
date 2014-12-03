// openMPZad2_MonteCarlo_basic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

// funkcja dla ktorej obliczana jest calka
double f(double x) {	
	if (x != 1)
	{
		return (3*(x*x*x) + 2*(x*x) + x) / ((x*x) - 1);
	}
	else
	{
		return 0;
	}	
}



int _tmain(int argc, _TCHAR* argv[])
{	
	unsigned int n = 25; // liczba punktow
	double a = 0; // poczatek przedzialu
	double b = 0.5; // koniec przedzialu

	cout << "Podaj liczbe punktow (x1000): ";
	cin >> n;
	n *= 1000;

	cout << "Podaj poczatek przedzialu: ";
	cin >> a;

	cout << "Podaj koniec przedzialu: ";
	cin >> b;

	cout << "OK, obliczam calke dla funkcji f(x) = (3*(x*x*x) + 2*(x*x) + x) / ((x*x) - 1)" << endl;
	cout << "z parametrami: n=" << n << ", a=" << a << " oraz b=" << b << endl;
	cout << "Prosze o chwilunie cierpliwosci." << endl;
	cout << "LICZEM...\n" << endl;


	double dx = b - a;
	
	double integral;
	double sum = 0;	

	int threadNumber = 1; // numer watku
	
	clock_t start = clock();
	srand((int)time(NULL) * threadNumber);	
	
	for (int i = 1; i < n; ++i)
	{	
		sum += f( a + dx*((double)rand()/(double)(RAND_MAX+1)) );		
	}			

	integral = dx / n * sum;

	clock_t end = clock();
	cout << "Wartosc calki: " << integral << endl;
	cout << "\nObliczenie tej pieknej caleczki zajelo mi " << end - start << " ms." << endl;

	system("PAUSE");
	return 0;

}

