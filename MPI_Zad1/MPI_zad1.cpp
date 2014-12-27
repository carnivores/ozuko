#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include "mpi.h"

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

	int process_id, number_of_processes;
	int startval, endval, accum;
	MPI_Status status;

	// CAPTURE TIME
	clock_t begin_pt = clock();

	// INIT
	MPI_Init(&argc, &argv);

	// GET NUMBER OF PROCESSESS
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);

	// GET PROCESS ID
	MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

	// pobranie parametru
	if (argv[1] != NULL)
	{
		c = atoi(argv[1]);
	}

	if (process_id == 0)
	{
		cout << "MPI Zadanie 1." << endl;
		cout << "Liczba usera: " << c << "." << endl;
		cout << "Liczba procesow: " << number_of_processes << "." << endl;
	}
	
	startval = N * process_id / number_of_processes + 1;
	endval   = N * (process_id+1) / number_of_processes;

	// obliczenia
	for (int i = startval; i < endval; ++i)
	{
		if (f(i) == c)
		{
			counter++;
		}
	}

	// bariera dla zakoczenia obliczen
	MPI_Barrier(MPI_COMM_WORLD);

	// aktualizacja globalnego countera
	if (number_of_processes > 1)
	{
		if(process_id != 0)
		{
			MPI_Send(&counter, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		else
		{
			for(int j = 1; j < number_of_processes; ++j)d
			{
				MPI_Recv(&accum, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
				counter = counter + accum;
			}
		}
	}
	
	// wyswietlenie podsumowania
	if (process_id == 0)
	{
		cout << "Liczba zgodnych wartosci: " << counter << endl;	
		cout << "Czas trwania programu: " << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;
	}

	// Finish
	MPI_Finalize();

	return 0;
}


