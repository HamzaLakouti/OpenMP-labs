#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int val;
    #pragma omp parallel
    {
        val = rand();
        sleep(1);
        printf("my val: %d \n",val);
    }
    return 0;
}