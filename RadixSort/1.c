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

int findLargestNum(int * array){

  int i;
  int largestNum = -1;

  for(i = 0; i < size; i++){
    if(array[i] > largestNum)
      largestNum = array[i];
  }

  return largestNum;
}

void radixSort(int * array){
  double t,g;
  FILE *file;
  file=fopen("file1.dat","w");
  int i,l=50000;
  t = wtime();
  int *semiSorted=(int*)malloc(size*sizeof(int));
  int significantDigit = 1;
  int largestNum = findLargestNum(array);

  while (largestNum / significantDigit > 0){
    int *bucket=(int*)malloc(size*sizeof(int));
    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;

    for (i = 1; i < size; i++)
      bucket[i] += bucket[i - 1];

    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];


    for (i = 0; i < size; i++){
            if (i==l-1){
               g=t;
                t = wtime() - t;
                fprintf(file,"%d %.6f\n",l,t);
                printf("%.6f\n",t);
                t=g;
                l=l+50000;
            }
      array[i] = semiSorted[i];
    }

    significantDigit *= 10;
  }
  fclose(file);
}

int main(){
    int i;
  int *list=(int*)malloc(size*sizeof(int));
  for (i=0;i<size;i++){
        list[i]=getrand(1,1001);
    }
  radixSort(&list[0]);
  printf("\n");

  return 0;
}
