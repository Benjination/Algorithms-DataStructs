//Benjamin Niccum 1002111609
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int ReadFileIntoArray(int argc, char *argv[], int **AP);
void SortArray(int AP[], int count);
void PrintArray(int ArrayToPrint[], int SizeAP);

int main(int argc, char *argv[])
{
    clock_t end, start;
    int i = 0, key = 0;
    long time=0;
    int *AP;
    int count = ReadFileIntoArray(argc, argv, &AP);

    printf("Number of integers in data file: %d\nStarting with %d and ending with %d\n", count, (AP)[0], (AP)[count-1]);

    start = clock();
    SortArray(AP, count);
    end = clock();
    time = end - start;
    printf("Processed %d records. \nFirst is now %d, and last is %d\n", count, (AP)[0], (AP)[count-1]);
    printf("Sort Process for %d items took %ld tics.", count, time);

    #ifdef PRINTARRAY
    PrintArray(AP, count);
    #endif

    free(AP);
    
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
        printf("Cannot open file.");
    else
    { 
        while(fgets(str, 60, file))
            cnt++;
        fseek(file, 0, SEEK_SET);
    }
    int count = 0;
    *AP = malloc(cnt*sizeof(int));
   
    while(fgets(str, 30, file))
    {
        (*AP)[i] = atoi(str);
        i++;
        count++;
    }
    fclose(file);
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