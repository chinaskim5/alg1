#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define size 1000000
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



int main(){
    double t,g;
    int i,j,minindex,temp,l=50000;
    int *A=(int*)malloc(size*sizeof(int));

    for (i=0;i<size;i++){
        A[i]=getrand(1,1001);
    }
     t = wtime();
     FILE *file;
    file=fopen("file1.dat","w");
        for (i=0;i<size-1;i++){
            minindex=i;
            for (j=i+1;j<size;j++){
                if (A[j]<A[minindex]){
                    minindex=j;
                }
            }
            if (minindex != i){
                temp=A[i];
                A[i]=A[minindex];
                A[minindex]=temp;
            }
            if (i == l-2){
                g=t;
                t = wtime() - t;
                fprintf(file,"%d %.6f\n",l,t);
                printf("%.6f\n",t);
                t=g;
                l=l+50000;
            }
        }
        fclose(file);

return 0;
}
