#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 1000000
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
void  max_heapify(int a[], int i, int heapsize)
{
    int tmp, largest;
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    if ((l <= heapsize) && (a[l] > a[i]))
         largest = l;
    else
         largest = i;
    if ((r <= heapsize) && (a[r] > a[largest]))
         largest = r ;
    if (largest != i)
    {
         tmp = a[i];
         a[i] = a[largest];
         a[largest] = tmp;
         max_heapify(a, largest, heapsize);
    }

}
void  build_max_heap(int a[], int heapsize)
{
    int i;
    for (i = heapsize/2; i >= 0; i--)
    {
         max_heapify(a, i, heapsize);
    }

}
void heap_sort(int a[], int heapsize)
{
    double t;
    int g;
    int log=50000;
    t = wtime();
    int i, tmp,l=950000;
    build_max_heap(a, heapsize);
    FILE *file;
        file=fopen("file1.dat","w");
    for (i = heapsize; i > 0; i--)
    {
        if (i==l){
    		log=log+50000;
                g=t;
                t = wtime() - t;
                fprintf(file,"%d %.6f\n",log,t);
                printf("%.6f\n",t);
                t=g;
                l=l-50000;

        }
        tmp = a[i];
        a[i] = a[0];
        a[0] = tmp;
        heapsize--;
        max_heapify(a, 0, heapsize);
    }
    fclose(file);
}
int main()
{
    int i, r, heapsize;
    int *a=(int*)malloc(MAX*sizeof(int));
    double t;
    for (i=0;i<MAX;i++){
        a[i]=getrand(1,1001);
    }
    heapsize = MAX - 1;
    heap_sort(a, heapsize);

    return 0;
}
