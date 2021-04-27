#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <conio.h>
// #include <windows.h>
#include <omp.h>
#include <time.h>

int main(){
    omp_set_num_threads(3);
    #pragma omp parallel sections
    {
        #pragma omp section
        for (int i=0;i <5;i++)
            // printf("hello section 1, no thread = %d\n", omp_get_thread_num());
        #pragma omp section
        // printf("hello section 2, no thread = %d\n", omp_get_thread_num());
    }
}
