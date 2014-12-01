#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <omp.h>
#include <time.h>
#include <ctime>

#define N 1948027565
#define A 1948027525
//SMALLEST1948027545
//4294967295

using namespace std;

unsigned short int my_hash(string str, unsigned int scale){
	unsigned int x = 0;
	for (unsigned int i = 0; i < str.length(); ++i){
		x <<= 3;
		x ^= str.at(i);
	}
	return (scale / x) % 41;
}

bool check_duplicate(vector<unsigned short int> hashes, unsigned short int hash_value){
	int occur = 0;
	for (int i = 0; i < hashes.size(); ++i){
		if (hashes.at(i) == hash_value){
			++occur;
		}
	}
	if (occur > 0){
		return true;
	}
	return false;
}

bool check_all_duplicates(vector<unsigned short int> hashes){
	for (unsigned short int i = 0; i < hashes.size(); ++i){
		for (unsigned short int j = 0; j < hashes.size(); ++j){
			if (i != j && hashes.at(i) == hashes.at(j)){
				return true;
			}
		}
	}
	return false; // NO DUPLICATES
}

void print_result(vector<unsigned short int> hashes, vector<string> strings){
	for (int i = 0; i < strings.size(); ++i){
		cout << strings.at(i) << " = " << hashes.at(i) << endl;
	}
}

int main(){

	int i = 0;
	int j = 0;
	int k = 0;

	int gfound = 0;

	int tid = 0;
	int ncheck = 0;
	int found = 0;
	vector<unsigned short int> hashes;
	unsigned short int hash_value;
	int harr[40];
	for (int i = 0; i < 40; ++i){
		harr[i] = 0;
	}

	static const string arr[] = { "and", "as", "assert", "break", "class", "continue", "def", "del", "elif", "else", "except", "exec", "finally", "for", "from", "if", "import", "in", "is", "lambda", "not", "or", "pass", "print", "raise", "return", "try", "while", "with", "yield", "global" };
	vector<string> strings(arr, arr + sizeof(arr) / sizeof(arr[0]));


		//pragma omp for nowait
		for (i = 1948027435; i < N; i++){
			hashes.clear();

			for (int j = 0; j < 40; ++j){
				harr[j] = 0;
			}

			// FOR EACH OF STRINGS
			for (j = 0; j < strings.size(); ++j){

				// GET HASH
				hash_value = my_hash(strings.at(j), i);

				// ADD ONLY IF UNIQUE
				if (harr[hash_value] == 0){
					hashes.push_back(hash_value);
					harr[hash_value] = 1;
				}
				else {
					//cout << "breaking after " << j << endl;
					break;
				}
				if (j == 30){
					for (k = 0; k < sizeof(harr) / sizeof(harr[0]); ++k){
						cout << harr[0] << " ";
					}
					cout << endl;
				}

			}
			//cout << i << " -> " << hashes.size() << "| " << strings.size() << endl;
			// IF J REACHED MAXIMUM VALUE - WE HAVE A WINNER
			if (hashes.size() == strings.size()){
				cout << "[^] Value found: " << i << endl;
			}
			tid = omp_get_thread_num();
			if (i != 0 && i % 100000000 == 0){
				cout << "Thread [" << tid << "] -----------------------------" << i << endl;
			}



	}


	std:cout << endl << gfound << endl;

	return 0;
}
