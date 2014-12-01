#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <omp.h>
#include <time.h>
#include <ctime>


#define N 1948027440
#define M 1948027450


using namespace std;

unsigned short int my_hash(string str, unsigned int scale){
	unsigned int x = 0;
	for (unsigned int i = 0; i < str.length(); ++i){
		x <<= 3;
		x ^= str.at(i);
	}
	return (scale / x) % 41;
}


void print_result(vector<unsigned short int> hashes, vector<string> strings){
	for (int i = 0; i < strings.size(); ++i){
		cout << strings.at(i) << " = " << hashes.at(i) << endl;
	}
}

int main(){

	string arr[31] = { "and", "as", "assert", "break",
		"class", "continue", "def", "del",
		"elif", "else", "except", "exec",
		"finally", "for", "from", "if",
		"import", "in", "is", "lambda",
		"not", "or", "pass", "print",
		"raise", "return", "try", "while",
		"with", "yield", "global" };

	bool hashes[41];
	int i, j, h, tid, counter;
	clock_t begin_pt = clock();

	//cout << "Entering" << endl;
#pragma omp parallel private(i,j,h, tid, counter, hashes)
	{
	#pragma omp for nowait
		for (i = 0; i < 1948027450; ++i){
			//cout << "---" << endl;
			for (j = 0; j < sizeof(hashes) / sizeof(hashes[0]); ++j){
				hashes[j] = false;
			}
			for (int j = 0; j < (sizeof(arr) / sizeof(arr[0])); ++j){
				h = my_hash(arr[j], i);
				//cout << arr[j] << " " << h << endl;
				if (hashes[h] == false){
					hashes[h] = true;
					//cout << "\tAdding " << h << endl;
				}
				else {
					//cout << "\tCollision detected " << h << endl;
					goto next;
				}
			}
			counter = 0;
			for (j = 0; j < sizeof(hashes) / sizeof(hashes[0]); ++j){
				if (hashes[j] != false){
					++counter;
				}
			}
			if (counter == 31){
				cout << "Value detected :" << i << endl;
			}
			if ((i % 10000000) == 0){
				tid = omp_get_thread_num();
				cout << "Thread " << tid << " value: " << i << endl;
			}
			next:
			i;
		}
	}
	std::cout << "Time spent solving " << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;
	system("PAUSE");
	return 0;
}
