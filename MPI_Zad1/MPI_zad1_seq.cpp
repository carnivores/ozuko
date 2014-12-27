#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;

int f(int i) {
	int i4_huge = 2147483647;
	int j, k, value = i;
	for (j = 1; j <= 5; j++) {
		k = value / 127773;
		value = 16807 * (value - k * 127773) - k * 2836;
		if (value <= 0)
			value = value + i4_huge;
	}
	return value;
}

int main(int argc, char *argv[]) {
	int c = 1055;
	
	int counter = 0;	
	const int N = 200000000;

	// CAPTURE TIME
	clock_t begin_pt = clock();

	// pobranie parametru
	if (argv[1] != NULL)
	{
		c = atoi(argv[1]);
	}

	cout << "MPI Zadanie 1. Wersja sekwencyjna." << endl;
	cout << "Liczba usera: " << c << "." << endl;

	// obliczenia
	for (int i = 0; i < N; i++)
	{
		if (f(i) == c)
		{
			counter++;
		}
	}
	
	// podsumowanie
	cout << "Liczba zgodnych wartosci: " << counter << endl;	
	cout << "Czas trwania programu: " << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;

	return 0;
}


