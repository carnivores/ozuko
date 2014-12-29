// MPI_Cannon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// rozmiar macierzy (NxN)
int matrixRows = 3;
int matrixCols = 3;
int matrixSize = matrixRows * matrixCols;

// funkcje
void printMatrix(int* M);
void matrixMultAdd(int* A, int* B, int* C, int len); // w k krokach mnozy poszczegolne komorki maciezy i wynik dodaje do maciezy wynikowej



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

	// CAPTURE TIME
	clock_t begin_pt = clock();


	cout << "Tablica A:" << endl;
	printMatrix(A);
	cout << endl << "Tablica B:" << endl;
	printMatrix(B);
	cout << endl << "Tablica C:" << endl;
	printMatrix(C);


	matrixMultAdd(A, B, C, matrixRows);
	cout << endl << "Macierze pomnozone sekwencyjnie:" << endl;
	printMatrix(C);


	cout << endl << "Czas trwania programu: " << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;

	
	system("PAUSE");
	
	return 0;
}



void printMatrix(int* M)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			cout << M[i * matrixRows + j] << "\t";
		}
		cout << endl;
	}
}


void matrixMultAdd(int* A, int* B, int* C, int len)
{
	int i, j, k;
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			for (k = 0; k < len; k++) {
				C[i * len + j] += A[i * len + k] * B[k * len + j];
			}
		}
	}
}

