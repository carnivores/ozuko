// openMPZad1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
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
	clock_t end = clock();
	cout << "Czas trwania programu: " << end - start << endl;

	system("PAUSE");
	return 0;
}
