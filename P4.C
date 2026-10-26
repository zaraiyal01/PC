#include <stdio.h>
#include <omp.h>

int prime(int n) 
{
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return n >= 2;
}

int main() 
{
    int n, s=0, p=0;
    double t;

    printf("Enter n: ");
    scanf("%d", &n);

    t = omp_get_wtime();

    for (int i=1; i<=n; i++) s += prime(i);
    printf("Serial: %d, Time: %f\n", s, omp_get_wtime()-t);

    t = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:p)
    for (int i=1; i<=n; i++) p += prime(i);
    printf("Parallel: %d, Time: %f\n", p, omp_get_wtime()-t);

    return 0;
}
