#include <stdio.h>
#include <omp.h>

int main() 
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    omp_set_num_threads(2);

    #pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++)
        printf("Thread %d: Iteration %d\n", omp_get_thread_num(), i);

    return 0;
}
