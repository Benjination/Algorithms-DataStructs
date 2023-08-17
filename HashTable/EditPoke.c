//Benjamin Niccum 1002111609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30
 
/* Node for storing information */
typedef struct Snake
{
    char *name;
    float length;
    float weight;
    char poison;
    char *description;
    char *region;
    int offspring; 
    struct Snake *nxt_ptr;
}
SNAKE;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(SNAKE *NewNode, SNAKE *Pokedex[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (Pokedex[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		Pokedex[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		SNAKE *TempPtr = Pokedex[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->nxt_ptr != NULL) 
		{
			TempPtr = TempPtr->nxt_ptr;
		}
		TempPtr->nxt_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(SNAKE *Pokedex[])
{
	SNAKE *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Pokedex[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->description);
				free(TempPtr->region);
				NextPtr = TempPtr->nxt_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(SNAKE *Pokedex[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Snake to delete from the Snakedex ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	SNAKE *TempPtr = Pokedex[HashIndex];
	SNAKE *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nSnake %s does not exist in the Snakedex\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Pokedex[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Pokedex[HashIndex] = TempPtr->nxt_ptr;
					printf("\nSnake %s has been deleted from the Snakedex\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->nxt_ptr = TempPtr->nxt_ptr;
					printf("\nSnake %s has been deleted from the Snakedex\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->nxt_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nSnake %s does not exist in the Snakedex\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(SNAKE *Snakedex[])
{
	int i;
	SNAKE *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Snakedex[i];

		printf("\nSnakedex[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->nxt_ptr;
			}
		}
	}
}

void ShowByLetter(SNAKE *Snakedex[])
{
	int i;
	SNAKE *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Snakedex[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->nxt_ptr;
			}
		}
	}
}

void ShowByName(SNAKE *Snakedex[])
{
	SNAKE *TempPtr = NULL;
	char length[10] = {};
	char weight[10] = {};
	char offspring[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	getchar();
	printf("\n\nEnter Snake's name ");
	fgets(LookupName, 20, stdin);
	for(int i = 0; i < strlen(LookupName); i++)
	{
		if(LookupName[i] == '\n')
			LookupName[i] = '\0';
	}
	
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Snakedex[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					
					printf("Length\t\t");
					sprintf(length, "%.2f", TempPtr->length);
					for (int i = 0; i < strlen(length); i++)
					{
						if (length[i] == '.')
						{
							printf("\' ");
						}
						else
						{
							printf("%c", length[i]);
						}
					}
					printf("\"\n");
					printf("Weight\t\t%.1f lbs\n", TempPtr->weight);
					if (TempPtr->poison == 'P')
						printf("Poisonous\t\tP\n");
					else if (TempPtr->poison == 'N')
						printf("Not-Poisonous\t\tN\n");
					else
						printf("Poison\t\t%c\n", TempPtr->poison);
					printf("Category\t%s\n", TempPtr->description);
					printf("Abilities\t%s\n", TempPtr->region);
					printf("Evolution\t%d\n", TempPtr->offspring);

				}
				TempPtr = TempPtr->nxt_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nSnake %s not found in Snakedex.\n\n", LookupName);
}

void AddNewPokemon(SNAKE *Snakedex[])
{
	int HashIndex = 0;
	SNAKE *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(SNAKE));
	NewNode->nxt_ptr = NULL;

	printf("\n\nEnter new Snake's name ");
	fgets(TempBuffer, 120, stdin);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's length as feet.inches ", NewNode->name);
	scanf("%f", &(NewNode->length));
	
	printf("\n\nEnter %s's weight as pounds.ounces ", NewNode->name);
	scanf("%f", &(NewNode->weight));
	
	printf("\n\nEnter if %s is poisonous (P/N) ", NewNode->name);
	scanf(" %c", &(NewNode->poison));
	NewNode->poison = toupper(NewNode->poison);
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
	printf("\n\nEnter %s's description ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->description = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->description, TempBuffer);

	printf("\n\nEnter %s's region ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';	
	NewNode->region = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->region, TempBuffer);

	printf("\n\nEnter %s's typical number of offspring ", NewNode->name);
	scanf("%d", &(NewNode->offspring));


	AddNode(NewNode, Snakedex);
}

int ReadFileIntoHashTable(int argc, char *argv[], SNAKE *Snakedex[])
{
	FILE *FH = NULL;
	char FileLine[200] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	SNAKE *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(SNAKE));
			NewNode->nxt_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->length = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->weight = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->poison = *token;
			
			token = strtok(NULL, "|");
			NewNode->description = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->description, token);

			token = strtok(NULL, "|");
			NewNode->region = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->region, token);

			token = strtok(NULL, "|");
			NewNode->offspring = atoi(token);
			

			AddNode(NewNode, Snakedex);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	SNAKE *Snakedex[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Snakedex);
 
	do
	{
		printf("\n\nSnakedex Menu\n\n"
			   "1. Show all Snakes in Snakedex for a given letter\n"
			   "2. Look up Snake by name\n"
			   "3. How many Snake are in the Snakedex?\n"
			   "4. Display the Snakedex\n"
			   "5. Add a new Snake\n"
			   "6. Delete a Snake from the Snakedex\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Snakedex);
				break;
			case SHOWBYNAME:
				ShowByName(Snakedex);
				break;
			case COUNT:
				printf("Your Snakedex contains %d Snakes\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Snakedex);
				break;
			case ADD:
				AddNewPokemon(Snakedex);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Snakedex))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(Snakedex);

	return 0;
}			  
