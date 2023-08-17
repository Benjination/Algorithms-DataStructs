//Benjamin Niccum 1002111609

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int ReadFileIntoArray(int argc, char *argv[], int **AP);
void SortArray(int AP[], int count);
void PrintArray(int ArrayToPrint[], int SizeAP);
void mergeSort(int arr[], int L, int R);
void merge(int arr[], int left, int middle, int right);


int main(int argc, char *argv[])
{
    clock_t end, start;
    int i = 0, key = 0;
    long time=0;
    int *AP;
    int count = ReadFileIntoArray(argc, argv, &AP);

    if(count != 0)
    {
        #ifdef PRINTARRAY
        PrintArray(AP, count);
        printf("\n");
        #endif
        
        printf("Number of integers in data file: %d\n", count);
        
        start = clock();
        mergeSort(AP, 0, count - 1);
        end = clock();
        time = end - start;
        
        printf("Processed %d records with Merge Sort.\n", count);
        printf("Sort Process for %d items took %ld tics.\n\n", count, time);
        
        #ifdef PRINTARRAY
        PrintArray(AP, count);
        printf("\n");
        #endif
        
        free(AP);
    }

    count = ReadFileIntoArray(argc, argv, &AP);

    if (count != 0)
    {
        #ifdef PRINTARRAY
        PrintArray(AP, count);
        printf("\n");
        #endif
        
        printf("Number of integers in data file: %d\n", count);
        
        start = clock();
        SortArray(AP, count);
        end = clock();
        time = end - start;
        
        printf("Processed %d records with Insertion sort.\n", count);
        printf("Sort Process for %d items took %ld tics.\n\n", count, time);
        
        #ifdef PRINTARRAY
        PrintArray(AP, count);
        printf("\n");
        #endif
        
        free(AP);
    }

    
    return 0;
}
   
int ReadFileIntoArray(int argc, char *argv[], int **AP)
{
    FILE *file;
    char str[40] = "", fileName[60] = "";
    int cnt = 0, i = 0;
    
    if(argc == 1)
    {
        printf("Please enter Filename:");
        scanf("%s", fileName);
        file = fopen(fileName, "r");
    }
    else
    {
        file = fopen(argv[1], "r");
    }
    if(file == NULL)
        printf("Cannot open file.\n");
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
void SortArray(int AP[], int count)
{
    int key=0, i=0;
    for(int j=1;j<count;j++)
    {
        key = (AP)[j];
        i = j-1;
        while(i>(-1) && (AP)[i]> key)
        {
            (AP)[i+1] = (AP)[i];
            i=i-1;
        }
        (AP)[i+1] = key;
    }
}
void PrintArray(int ArrayToPrint[], int SizeAP) 
{
    int i;
    for (i = 0; i < SizeAP; i++) 
        printf("%d\n", ArrayToPrint[i]);
}
void mergeSort(int arr[], int L, int R)
{
    if (L < R) 
    {

        int M = (L+R)/2;
        mergeSort(arr, L, M);
        mergeSort(arr, M+1, R);
        merge(arr, L, M, R);
    } 
}
void merge(int arr[], int left, int middle, int right)
{
    int i, j, k = left;
    int n1 = middle - left + 1; 
    int n2 = right - middle;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i=0; 
    j=0;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++; 
        }
    k++; 
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
