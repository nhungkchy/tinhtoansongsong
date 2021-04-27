#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <conio.h>
// #include <windows.h>
#include <omp.h>
#include <time.h>

int main(){
    int i;
    int x = 10;
    int y = 100;
    int z = 100;
    #pragma omp parallel
    {
        #pragma omp for private (i) firstprivate(x) lastprivate(y) reduction(+:z)
        for(i=0; i<10; i++){
            x += 1;
            y = x + i;
            z = x + i;
        }
    }
    printf("Frist private x = %d\n",x);
    printf("Last private y = %d\n",y);
    printf("reduction z= %d\n",z);
}
