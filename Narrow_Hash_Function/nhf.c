#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N     4294967295

// -
unsigned int hash(const char* string, unsigned int scale){
        unsigned int x = 0;
        for ( unsigned int i = 0; string[i] != 0; ++i ){
                x <<= 3;
                x ^= string[i];
        }
        return (scale/x) % 41;
}

int check( unsigned int* arr; int index){
        unsigned int arr_size = (int)( sizeof(arr) / sizeof(arr[0]));
        for (int m = 0; m < index; ++m){
                if (arr[m] == arr[index]){
                        return 1;
                }
        }
        return 0;
}

int main ()
{
        unsigned int i = 0;
        int tid = 0;
        int ncheck = 0;
        unsigned int arr[31];
        #pragma omp parallel private(i,tid,check, arr)
        {

                #pragma omp for nowait
                for (i=0; i < N; i++)
                {
                        //check = 0;
                        unsigned int arr_size = (int)( sizeof(arr) / sizeof(arr[0]));
                        for (int m = 0; m < arr_size; ++m){
                                arr[m] = -1;
                        }

                        arr[0]=hash("and\0",i);

                        arr[1]=hash("as\0",i);
                        if ( check(arr, 1) == 1){
                                break;
                        }
                        arr[2]=hash("assert\0",i);
                        if ( check(arr, 2) == 1) break;
                        arr[3]=hash("break\0",i);
                        if ( check(arr, 3) == 1) break;
                        arr[4]=hash("class\0",i);
                        if ( check(arr, 4) == 1) break;
                        arr[5]=hash("continue\0",i);
                        if ( check(arr, 5) == 1) break;
                        arr[6]=hash("def\0",i);
                        if ( check(arr, 6) == 1) break;
                        arr[7]=hash("del\0",i);
                        if ( check(arr, 7) == 1) break;
                        arr[8]=hash("elif\0",i);
                        if ( check(arr, 8) == 1) break;
                        arr[9]=hash("else\0",i);if ( check(arr, 9) == 1) break;
                        arr[10]=hash("except\0",i);if ( check(arr, 10) == 1) break;
                        arr[11]=hash("exec\0",i);if ( check(arr, 11) == 1) break;
                        arr[12]=hash("finally\0",i);if ( check(arr, 12) == 1) break;
                        arr[13]=hash("for\0",i);if ( check(arr, 13) == 1) break;
                        arr[14]=hash("from\0",i);if ( check(arr, 14) == 1) break;
                        arr[15]=hash("if\0",i);if ( check(arr, 15) == 1) break;
                        arr[16]=hash("import\0",i);if ( check(arr, 16) == 1) break;
                        arr[17]=hash("in\0",i);if ( check(arr, 17) == 1) break;
                        arr[18]=hash("is\0",i);if ( check(arr, 18) == 1) break;
                        arr[19]=hash("lambda\0",i);if ( check(arr, 19) == 1) break;
                        arr[20]=hash("not\0",i);if ( check(arr, 20) == 1) break;
                        arr[21]=hash("or\0",i);if ( check(arr, 21) == 1) break;
                        arr[22]=hash("pass\0",i);if ( check(arr, 22) == 1) break;
                        arr[23]=hash("print\0",i);if ( check(arr, 23) == 1) break;
                        arr[24]=hash("raise\0",i);if ( check(arr, 24) == 1) break;
                        arr[25]=hash("return\0",i);if ( check(arr, 25) == 1) break;
                        arr[26]=hash("try\0",i);if ( check(arr, 26) == 1) break;
                        arr[27]=hash("while\0",i);if ( check(arr, 27) == 1) break;
                        arr[28]=hash("with\0",i);if ( check(arr, 28) == 1) break;
                        arr[29]=hash("yield\0",i);if ( check(arr, 29) == 1) break;
                        arr[30]=hash("global\0",i);if ( check(arr, 30) == 1) break;

                        for (int j = 0; j < arr_size; ++j)
                        {
                                for(int k = 0; k < arr_size; ++k){
                                        if (arr[j] != arr[k])
                                        {
                                                ++ncheck;
                                        }
                                }
                        }

                        if (ncheck > 928)
                        {
                        //      printf("Check %u\n", check);
                                //printf("\nNumber found %u\n", i);
                                printf("%u,", i);
                                // for (int d = 0; d < arr_size; ++d)
                                // {
                                //      printf("\narr[%d] = %d\t", d, arr[d]);
                                // }
                        }
                        // tid = omp_get_thread_num();
                         if (i%10000000 == 0)
                         {
                                        //printf("\n%u", i);
                                        printf(".");
                                        //printf("thread:%u -> %u\n", tid, i);
                         }

                }

        }  /* end of parallel section */

        return 0;
}