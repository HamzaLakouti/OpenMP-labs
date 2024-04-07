#include <stdio.h>
#include <omp.h>
#define N 9000000000
int main(){
    int a[N], i, j, rang, sum = 0;
    for(i=0; i<N; i++)
    a[i] = i*1;

        #pragma omp parallel
        {
            #pragma omp for reduction(+:sum)
            for(j=0; j<N; j++){
            sum += a[j];
            }
        }
        
    printf("sum = %d\n", sum);
    return 0;
}