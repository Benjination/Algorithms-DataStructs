//Benjamin Niccum 1002111609


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX 50 //Max number of vertices


typedef struct
{
    char label[6];
    int distance;
    int previous;
    int visited;
}
Vertex;

void Djikstra(int VertexCount, int adjMatrix[MAX][MAX], Vertex *VertexArray, int CurrentVertex);

int main(int argc, char *argv[])
{
    int VertexCount = 0;
    FILE *file;
   
    Vertex VertexArray[10];
    int StartVertex = 0;
    int adjMatrix[MAX][MAX];
    char startLabel[6];
    for(int i = 0;i < MAX;i++)
    {
        for(int j =0;j < MAX;j++)
        {
            adjMatrix[i][j] = -1;
        }
    }
    if(argc < 2)
    {
        printf("Program must be run with a filename. Ex: ./a.out graph.txt");
        exit(0);
    }
    else
    {
        char fileName[30];
        strcpy(fileName, argv[1]);

        file = fopen(fileName, "r");
        if (file == NULL)
        {
            printf("Error opening file: %s\n", fileName);
            exit(0);
        }
    }
    char line[60];
    char *label, *vert,  *dist;
    int vertNum1, distNum1, vertNum2, distNum2;
    while(fgets(line,60,file))
    {
       
        label = strtok(line, ",");
        strcpy(VertexArray[VertexCount].label, label);
        VertexArray[VertexCount].visited = 0;
        VertexArray[VertexCount].distance = INT_MAX;
        VertexArray[VertexCount].previous = -1;

        vert = strtok(NULL, ",");
        while(vert != NULL)
        {
            dist = strtok(NULL, ",");
            vertNum1 = atoi(vert);
            distNum1 = atoi(dist);
            adjMatrix[VertexCount][vertNum1] = distNum1;
            //VertexArray[VertexCount].distance = distNum1;
            //VertexArray[vertNum1].previous = VertexCount;
            vert = strtok(NULL, ",");
        }
        VertexCount++;
    }
    
  
    #ifdef PRINTIT
    printf("\n");
    for(int i = 0;i < VertexCount;i++)
    {
        for(int j = 0;j < VertexCount;j++)
        {
            printf("%5d\t", adjMatrix[i][j]);
        }
        printf("\n");
    }
    #endif

    printf("\nWhat is the starting vertex?");
    scanf("%s", startLabel);
    for(int i = 0;i < VertexCount;i++)
    {
        if(strcmp(VertexArray[i].label, startLabel) == 0)
        {
            StartVertex = i;
        }
    }
    Djikstra(VertexCount, adjMatrix, VertexArray, StartVertex);

    #ifdef PRINTIT
    printf("\n\nI\tL\tD\tP\tV\n");
    for(int i = 0;i < VertexCount;i++)
        {
            printf("%d\t%s\t%d\t%d\t%d\n", i, VertexArray[i].label, VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
        }
    #endif

    char endLabel[6];
    char string[20];
    int pathLen;
    getchar();
    printf("\nWhat is the destination vertex?");
    scanf("%s", endLabel);

    int len = 0;
    while(strcmp(endLabel, VertexArray[len].label) != 0)
        len++;

    printf("\nThe path from %s to %s is %s", startLabel, endLabel, startLabel);

    int i = 0, j = 0, cnt = 0;
    char pathArr[50][MAX];
    char tempLabel[6];
    strcpy(tempLabel, endLabel);
    while (strcmp(tempLabel, startLabel) != 0)
    {
        i = 0;
        while(strcmp(VertexArray[i].label, tempLabel) != 0)
        {
            i++;
        }
        strcpy(tempLabel, VertexArray[VertexArray[i].previous].label);
        strcpy(pathArr[cnt], tempLabel);
        cnt++;
    }
    for(int i = cnt;i > 0;i--)
        printf("->%s", pathArr[i-2]);

    printf("%s and has a distance of %d.\n", endLabel, VertexArray[len].distance);
    
    return 0;
}
//end of main body

void Djikstra(int VertexCount, int adjMatrix[MAX][MAX], Vertex *VertexArray, int StartVertex)
{
    int dofu, cofuv, dofv, SmallestVertexIndex; 
    int CurrentVertex = StartVertex; 
    VertexArray[StartVertex].distance = 0; 
    VertexArray[StartVertex].previous = -1; 
    VertexArray[StartVertex].visited = 1;

    for (int x = 0; x < VertexCount-1; x++)
    {
        for(int i = 0; i < VertexCount; i++)
        {
            //relaxing the edges
            if(adjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
            {
                dofu = VertexArray[CurrentVertex].distance;
                cofuv = adjMatrix[CurrentVertex][i];
                dofv = VertexArray[i].distance;

                if(dofu + cofuv < dofv)
                {
                    dofv = dofu + cofuv;
                    VertexArray[i].distance = dofv;
                    VertexArray[i].previous = CurrentVertex;
                }
            }
        }
        for(int i = 0; i < VertexCount; i++)
        {
            //finding the smallest
            SmallestVertexIndex = -1;
            int SmallestVertex = MAX;
            for(int i = 0; i < VertexCount; i++)
            {
                if (!VertexArray[i].visited)
                {
                    if (VertexArray[i].distance < SmallestVertex) 
                    {
                        SmallestVertex = VertexArray[i].distance;
                        SmallestVertexIndex = i;
                    }
                }
            }
        }
        CurrentVertex = SmallestVertexIndex;
        VertexArray[CurrentVertex].visited = 1;
    }
}
