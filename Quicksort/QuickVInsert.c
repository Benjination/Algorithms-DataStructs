//Benjamin Niccum 1002111609

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int ReadFileIntoArray(int argc, char *argv[], int **AP);
void PrintArray(int ArrayToPrint[], int SizeAP);
void QuickSort(int A[], int low, int high);
int partition(int A[], int low, int high);
void Swap(int *a, int *b);

int main(int argc, char *argv[])
{
    clock_t end, start;
    int i = 0, key = 0;
    long time=0, avg;
    int *AP, loops = 10;
    long double sum = 0;
    long runs[100] = {};
    //Assess Number of loops 
    if((sizeof(*argv)/sizeof(argv[0])) < 2)
    {
        printf("Number of runs not specified on command line...defaulting to 10.\n");
        loops = 10;
    }
    else
    {
        loops = atoi(argv[2]);
    }
    
    for(int i = 0;i < loops;i++)
    {
        int count = ReadFileIntoArray(argc, argv, &AP);
        int low = 0, high = count -1;
    
        if(count != 0)
        {
            
            #ifdef PRINTARRAY
            PrintArray(AP, count);
            printf("\n");
            #endif
            
            //printf("Number of integers in data file: %d\n", count);
            
            start = clock();
            QuickSort(AP, low, high);
            end = clock();
            time = end - start;
            runs[i] = time;
            
            //printf("Processed %d records with Quick Sort.\n", count);
            printf("Run %d complete: %ld tics\n", i + 1, time);
            
            
            #ifdef PRINTARRAY
            PrintArray(AP, count);
            printf("\n");
            #endif
                
        }
    }   
    for (int j = 0;j< loops;j++)
    {
        sum += runs[j];
        avg = sum / loops;
    }
    printf("The average run time for %d runs is %ld.\n", loops, avg);
    free(AP);

    
    return 0;
}
   
int ReadFileIntoArray(int argc, char *argv[], int **AP)
{
    FILE *file;
    char str[40] = "", fileName[60] = "";
    int cnt = 0, i = 0;
    
    if(argc < 2)
    {
        printf("File must be provided on command line...exiting.");
        exit(0);
        //printf("Please enter Filename:");
        //scanf("%s", fileName);
        //file = fopen(fileName, "r");
    }
    else
    {
        file = fopen(argv[1], "r");
    }
    if(file == NULL)
    {
        printf("Cannot open file.\n");
        exit(0);
    }
    else
    { 
        while(fgets(str, 60, file))
            cnt++;
        fseek(file, 0, SEEK_SET);
    }
    int count = 0;
    *AP = malloc(cnt*sizeof(int));
    if (file != NULL)
    {
        while(fgets(str, 30, file))
        {
            (*AP)[i] = atoi(str);
            i++;
            count++;
        }
        fclose(file);
    }
    return count;
}
void PrintArray(int ArrayToPrint[], int SizeAP) 
{
    int i;
    for (i = 0; i < SizeAP; i++) 
        printf("%d\n", ArrayToPrint[i]);
}

void QuickSort(int A[], int low, int high)
{
    if(low < high)
    {
        int ndx = partition (A, low, high);

        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);

    }
}
int partition(int A[], int low, int high)
{
    #if QSM
    int middle = (high+low)/2;
    Swap(&A[middle], &A[high]);
    #elif QSRND
    int random = (rand() % (high-low+1)) + low;
    Swap(&A[random], &A[high]);
    #endif
    int pivot = A[high];

    int i, j = 0;
    i = low -1;
    for(j = low;j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            Swap (&(A[i]), &(A[j]));
        }
    }
    Swap(&(A[i + 1]), &(A[high]));
    return (i + 1);
    
}
void Swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;

}
