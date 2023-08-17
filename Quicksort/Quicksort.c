//Benjamin Niccum 1002111609
#include <stdio.h>

void QuickSort(int A[], int low, int high);
int partition(int A[], int low, int high);
void Swap(int *a, int *b);
void PrintArray(int ArrayToPrint[], int SizeAP);


int main (int argc, char *argv[])
{
    int A[6] = {2,7,4,9,3,5};
    int size = (sizeof(A))/(sizeof(A[0]));
    int low = 0, high = size -1;
    PrintArray(A, size);


    QuickSort(A, low, high);

    PrintArray(A, size);


    return 0;
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
void PrintArray(int ArrayToPrint[], int SizeAP) 
{
    int i;
    for (i = 0; i < SizeAP; i++) 
        printf("%d, ", ArrayToPrint[i]);
    printf("\n");
}