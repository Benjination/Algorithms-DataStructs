#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASHTABLESIZE 10
#define VALUESIZE 20

int MyHashFunction(char hashValue[VALUESIZE]);

int main(void)
{
    char HashValue[VALUESIZE];
    printf("Enter value ");
    scanf("%s", HashValue);
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
    return 0;
}
//end of main body

int MyHashFunction(char hashValue[VALUESIZE])
{
    int value = 0;
    int num[20];
    for(int i = 0;i < strlen(hashValue);i++)
    {
        value += hashValue[i];
    }
    

return value % HASHTABLESIZE;
}
