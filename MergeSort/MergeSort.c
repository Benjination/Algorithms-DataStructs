//Benjamin Niccum

#include <stdio.h>
#include <stdlib.h>

void mergeSort(int arr[], int L, int R);
void merge(int arr[], int left, int middle, int right);
void printArray(int ArrayToPrint[], int SizeAP) ;

int main(void)
{
    int arr[] = {12, 11, 5, 13, 7, 6};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);
    
    printf("\nSorted array is \n"); 
    printArray(arr, arr_size);

return 0;
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


void printArray(int ArrayToPrint[], int SizeAP) 
{
    int i;
    for (i = 0; i < SizeAP; i++) 
        printf("%d\n", ArrayToPrint[i]);
}
