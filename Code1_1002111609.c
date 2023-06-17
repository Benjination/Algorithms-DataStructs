//Benjamin Niccum 1002111609
/* Coding Assignment 1 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int number;
    struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    NODE *TempPtr, *PrevPtr, *NewNode;
    
    PrevPtr = NULL;
    TempPtr = *LinkedListHead;
    
    
    while (TempPtr != NULL)
    {
        PrevPtr = TempPtr;
        TempPtr = TempPtr->next_ptr;
    }
    
    NewNode = malloc(sizeof(NODE));
    NewNode->number = Number;
    NewNode->next_ptr = TempPtr;

    /* If PrevPtr is still NULL, then we are at the start of the list */
    if (PrevPtr == NULL)
    {
        *LinkedListHead = NewNode;
    }
    else
    {
        PrevPtr->next_ptr = NewNode;
    }
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
    FILE *readFile;
    char str[10] = {};
    int num, cnt = 0, sum = 0;
    if(argc == 1)
    {
        printf("File must be provided on command line...exiting");
        exit(0);
    }
    else
    {
        readFile = fopen(argv[1], "r");
        while(fgets(str, 60, readFile))
            {
                num = atoi(str);
                AddNodeToLL(num, LLH);
                cnt++;
                sum += num;
            }
        printf("%d records were read for a total sum of %d", cnt, sum);
    }
}

void PrintLL(NODE *LLH)
{
    NODE *TempPtr, *PrevPtr;
    PrevPtr = NULL;
    TempPtr = LLH;

    while (TempPtr != NULL)
    {    
        printf("%p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        PrevPtr = TempPtr;
        TempPtr = TempPtr->next_ptr;
    }
}

void FreeLL(NODE **LLH)
{
    NODE *TempPtr;
    int num = 0, sum = 0, cnt = 0;

    while ((*LLH) != NULL)
    {
        
        TempPtr = (*LLH);
        num = TempPtr->number;
        cnt++;
        sum += num;

        #ifdef PRINT
        printf("\nFreeing %p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        #endif
        
        free(*LLH);
        (*LLH) = TempPtr->next_ptr;

    }
    printf("%d nodes were deleted for a total sum of %d", cnt, sum);
}

int main(int argc, char *argv[])
{
    NODE *LLH = NULL;
    clock_t end, start;
    
    /* capture the clock in a start time */
    start = clock();
    ReadFileIntoLL(argc, argv, &LLH);
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld tics to write the file into the linked list\n", end-start);

    /* capture the clock in a start time */
    start = clock();
    #ifdef PRINT
    PrintLL(LLH);
    #endif
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld tics to print the linked list\n", end-start);
    
    /* capture the clock in a start time */
    start = clock();
    FreeLL(&LLH);
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld tics to free the linked list\n", end-start);
    
    return 0;
}
