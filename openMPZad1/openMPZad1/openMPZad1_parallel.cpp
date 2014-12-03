// openMPZad1_parallel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <ctime>
using namespace std;

int f(int i) {
	int i4_huge = 2147483647;
	int j, k, value = i;
	for (j = 1; j <= 5; ++j) {
		k = value / 127773;
		value = 16807 * (value - k * 127773) - k * 2836;
		if (value <= 0)
			value = value + i4_huge;
	}
	return value;
}

int main(int argc, char *argv[]) {

	int c = 0;
	int numberOfThreads = 1;

	int counter = 0;
	const int N = 200000000;

	clock_t start = clock();


	if (argv[1] != NULL)
	{
		c = atoi(argv[1]);
	}

	if (argv[2] != NULL)
	{
		numberOfThreads = atoi(argv[2]);
	}

	cout << "OpenMP Zadanie 1. Wersja rownolegla." << endl;
	cout << "Liczba watkow: " << numberOfThreads << endl;
	cout << "Liczba usera: " << c << "." << endl;
	

	omp_set_num_threads(numberOfThreads);
	
#pragma omp parallel for shared(c, N, counter)
	for (int i = 0; i < N; ++i)
	{
		if (f(i) == c)
		{
			++counter;
		}
	}

	cout << "Liczba zgodnych wartosci: " << counter << endl;

	clock_t end = clock();
	cout << "Czas trwania programu: " << end - start << endl;

	system("PAUSE");
	return 0;
}
