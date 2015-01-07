// MPI_Cannon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// rozmiar macierzy (NxN)
int matrixDim = 3;
int matrixSize = matrixDim * matrixDim;

// funkcje
void printMatrix(int* M);


int main(int argc, char* argv[])
{
	
	// macierz wejsciowa A
	int* A = new int[matrixSize];
	A[0] = 3;	A[1] = 8;	A[2] = 6;
	A[3] = 7;	A[4] = 1;	A[5] = 6;
	A[6] = 8;	A[7] = 4;	A[8] = 6;

	// macierz wejsciowa B
	int* B = new int[matrixSize];
	B[0] = 4;	B[1] = 2;	B[2] = 4;
	B[3] = 1;	B[4] = 8;	B[5] = 6;
	B[6] = 4;	B[7] = 2;	B[8] = 7;
	
	// macierz wynikowa C
	int* C = new int[matrixSize];
	fill_n(C, matrixSize, 0);

	cout << "Tablica A:" << endl;
	printMatrix(A);
	cout << endl << "Tablica B:" << endl;
	printMatrix(B);
	cout << endl << "Tablica C:" << endl;
	printMatrix(C);

	// czas start
	clock_t begin_pt = clock();

	// faza przygotowawcza - pierwsze przesuniecie
	int* tempMatrix = new int[matrixDim];
	int pos = 0;

	// shift A
	for (int i = 1; i < matrixDim; ++i)
	{
		pos = i;
		for (int j = 0; j < matrixDim; ++j)
		{			
			tempMatrix[j] = A[(i * matrixDim) + (pos % matrixDim)];			
			++pos;
		}

		for (int j = 0; j < matrixDim; ++j)
		{			
			A[(i * matrixDim) + (j)] = tempMatrix[j];			
		}
	}

	// shift B
	for (int i = 1; i < matrixDim; ++i)
	{
		pos = i;
		for (int j = 0; j < matrixDim; ++j)
		{
			tempMatrix[j] = B[((pos % matrixDim) * matrixDim) + (i)];			
			++pos;
		}

		for (int j = 0; j < matrixDim; ++j)
		{
			B[(j * matrixDim) + (i)] = tempMatrix[j];
		}
	}
	
	// po shificie:
	cout << endl << "A po shifice: " << endl;
	printMatrix(A);

	cout << endl << "B po shifice: " << endl;
	printMatrix(B);


	// przemnazanie komorek w k krokach z sumowaniem z przesunieciami
	for (int k = 0; k < matrixDim; ++k)
	{	
		for (int i = 0; i < matrixDim; ++i)
		{			
			for (int j = 0; j < matrixDim; ++j)
			{					
				C[i * matrixDim + j] += A[(i * matrixDim) + ((j + k) % matrixDim)] * B[(((i + k) % matrixDim) * matrixDim) + (j)];				
			}
		}

		cout << endl << "krok " << k << ": " << endl;
		printMatrix(C);
	}

	// podsumowanie czasu
	cout << endl << "Czas trwania programu: " << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;

	// sprzatanie
	delete(A);
	delete(B);
	delete(C);
	delete(tempMatrix);
	
	system("PAUSE");
	
	return 0;
}



void printMatrix(int* M)
{
	for (int i = 0; i < matrixDim; i++)
	{
		for (int j = 0; j < matrixDim; j++)
		{
			cout << M[i * matrixDim + j] << "\t";
		}
		cout << endl;
	}
}

