#include <stdio.h>
#include <omp.h>

int main(){
    printf("nbr threads: %d\n", omp_get_num_threads());
    #pragma omp parallel
    {
        printf("hello from %d on %d\n", omp_get_thread_num(),omp_get_num_threads());
    }
    printf("nmb threads: %d\n", omp_get_num_threads());
    return 0;
}