#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 500000

void merge(int a[], int l, int m, int r) 
{
    int *t=malloc((r-l+1)*sizeof(int)), i=l, j=m+1, k=0;
    while(i<=m && j<=r) t[k++]=(a[i]<a[j])?a[i++]:a[j++];
    while(i<=m) t[k++]=a[i++];
    while(j<=r) t[k++]=a[j++];
    for(i=l,k=0; i<=r; i++) a[i]=t[k++];
    free(t);
}

void sort(int a[], int l, int r, int d) 
{
    if(l>=r) return;
    int m=(l+r)/2;
    if(d) 
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            sort(a,l,m,d-1);
            #pragma omp section
            sort(a,m+1,r,d-1);
        }
    } 
    else 
    {
        sort(a,l,m,0);
        sort(a,m+1,r,0);
    }
    merge(a,l,m,r);
}

int main() 
{
    int *a=malloc(N*sizeof(int)), *b=malloc(N*sizeof(int));
    for(int i=0;i<N;i++) a[i]=b[i]=rand();

    double t=omp_get_wtime();
    sort(a,0,N-1,0);
    printf("Sequential: %f s\n",omp_get_wtime()-t);

    t=omp_get_wtime();
    sort(b,0,N-1,2);
    printf("Parallel: %f s\n",omp_get_wtime()-t);

    free(a); free(b);
    return 0;
}
