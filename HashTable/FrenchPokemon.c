// Coding Assignment 6 - Donna French - 100074079

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 37
 
/* Node for storing information */
typedef struct Pokemon 
{
	char *name;
	float height;
	float weight;
	char gender;
	char *category;
	char *abilities;
	int evolution;
	int national_pokedex_number;
	struct Pokemon *next_ptr;
}
POKEMON;
 
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

void AddNode(POKEMON *NewNode, POKEMON *Pokedex[])
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
		POKEMON *TempPtr = Pokedex[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(POKEMON *Pokedex[])
{
	POKEMON *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Pokedex[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->category);
				free(TempPtr->abilities);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(POKEMON *Pokedex[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Pokemon to delete from the Pokedex ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	POKEMON *TempPtr = Pokedex[HashIndex];
	POKEMON *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nPokemon %s does not exist in the Pokedex\n\n", LookupName);
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
					Pokedex[HashIndex] = TempPtr->next_ptr;
					printf("\nPokemon %s has been deleted from the Pokedex\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nPokemon %s has been deleted from the Pokedex\n\n", TempPtr->name);
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
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nPokemon %s does not exist in the Pokedex\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(POKEMON *Pokedex[])
{
	int i;
	POKEMON *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Pokedex[i];

		printf("\nPokedex[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(POKEMON *Pokedex[])
{
	int i;
	POKEMON *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Pokedex[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(POKEMON *Pokedex[])
{
	POKEMON *TempPtr = NULL;
	char height[10] = {};
	char feet[10] = {};
	char inches[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Pokemon's name ");
	scanf("%s", LookupName);
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Pokedex[i];

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
					
					printf("Height\t\t");
					sprintf(height, "%.2f", TempPtr->height);
					for (int i = 0; i < strlen(height); i++)
					{
						if (height[i] == '.')
						{
							printf("\' ");
						}
						else
						{
							printf("%c", height[i]);
						}
					}
					printf("\"\n");
					printf("Weight\t\t%.1f lbs\n", TempPtr->weight);
					if (TempPtr->gender == 'B')
						printf("Gender\t\tM F\n");
					else if (TempPtr->gender == 'U')
						printf("Genger\t\tUnknown\n");
					else
						printf("Gender\t\t%c\n", TempPtr->gender);
					printf("Category\t%s\n", TempPtr->category);
					printf("Abilities\t%s\n", TempPtr->abilities);
					printf("Evolution\t%d\n", TempPtr->evolution);
					printf("Natl Pokedex #\t%d\n", TempPtr->national_pokedex_number);

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nPokemon %s not found in Pokedex\n\n", LookupName);
}

void AddNewPokemon(POKEMON *Pokedex[])
{
	int HashIndex = 0;
	POKEMON *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(POKEMON));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Pokemon's name ");
	scanf("%s", TempBuffer);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's height as feet.inches ", NewNode->name);
	scanf("%f", &(NewNode->height));
	
	printf("\n\nEnter %s's weight as pounds.ounces ", NewNode->name);
	scanf("%f", &(NewNode->weight));
	
	printf("\n\nEnter %s's possible gender (M/F/B/U) ", NewNode->name);
	scanf(" %c", &(NewNode->gender));
	NewNode->gender = toupper(NewNode->gender);
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
	printf("\n\nEnter %s's category ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->category = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->category, TempBuffer);

	printf("\n\nEnter %s's abilities ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';	
	NewNode->abilities = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->abilities, TempBuffer);

	printf("\n\nEnter %s's evolution ", NewNode->name);
	scanf("%d", &(NewNode->evolution));

	printf("\n\nEnter %s's National Pokedex Number ", NewNode->name);
	scanf("%d", &(NewNode->national_pokedex_number));

	AddNode(NewNode, Pokedex);
}

int ReadFileIntoHashTable(int argc, char *argv[], POKEMON *Pokedex[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	POKEMON *NewNode;

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

			NewNode = malloc(sizeof(POKEMON));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->height = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->weight = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->gender = *token;
			
			token = strtok(NULL, "|");
			NewNode->category = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->category, token);

			token = strtok(NULL, "|");
			NewNode->abilities = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->abilities, token);

			token = strtok(NULL, "|");
			NewNode->evolution = atoi(token);
			
			token = strtok(NULL, "|");
			NewNode->national_pokedex_number = atoi(token);

			AddNode(NewNode, Pokedex);

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
	POKEMON *Pokedex[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Pokedex);
 
	do
	{
		printf("\n\nPokedex Menu\n\n"
			   "1. Show all Pokemon in Pokedex for a given letter\n"
			   "2. Look up Pokemon by name\n"
			   "3. How many Pokemon are in the Pokedex?\n"
			   "4. Display the Pokedex\n"
			   "5. Add a new Pokemon\n"
			   "6. Delete a Pokemon from the Pokedex\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Pokedex);
				break;
			case SHOWBYNAME:
				ShowByName(Pokedex);
				break;
			case COUNT:
				printf("Your Pokedex contains %d Pokemon\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Pokedex);
				break;
			case ADD:
				AddNewPokemon(Pokedex);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Pokedex))
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
	
	FreeDynamicMemory(Pokedex);

	return 0;
}			  
