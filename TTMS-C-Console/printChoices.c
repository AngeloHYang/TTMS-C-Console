#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "timeRelated.h"
#include "inputMethod.h"

void printMultipleTimes(char character, int times)
{
	for (long long int whichTime = 1; whichTime <= times; whichTime++)
	{
		printf("%c", character);
	}
}

int printMiddleAddjusted(char* inputThings, int maxSize)
// Return 1 if successfully printed
{
	char* toDeal = (char*)malloc(sizeof(char) * maxSize);
	if (toDeal != NULL)
	{
		// Receive the array
		int sizeofToDeal = sizeof(char) * maxSize;
		memset(toDeal, '\0', sizeofToDeal);
		strcpy_s(toDeal, maxSize, inputThings);

		// Print
		int startPlace = (100 - strlen(toDeal)) / 2;
		
		printMultipleTimes(' ', startPlace);

		printf("%s", toDeal);
		free(toDeal);
		return 1;
	}
	else
	{
		printf("Failed!\n");
		return 0;
	}
}

int printNumberAndContentWithStartplace(int number, char* inputThings, int startPlace, int maxSize)
// Return 1 if successfully printed
{
	char* toDeal = (char*)malloc(sizeof(char) * maxSize);
	if (toDeal != NULL)
	{
		// Receive the array
		int sizeofToDeal = sizeof(char) * maxSize;
		memset(toDeal, '\0', sizeofToDeal);
		strcpy_s(toDeal, maxSize, inputThings);

		// Print
		for (int whichCharacter = 1; whichCharacter < startPlace; whichCharacter++)
		{
			printf(" ");
		}
		printf("%d) ", number);
		printf("%s", toDeal);
		free(toDeal);
		return 1;
	}
	else
	{
		printf("Failed!\n");
		return 0;
	}
}

int printWithStartPlace(char* inputThings, int startPlace, int maxSize)
// Return 1 if successfully printed
{
	char* toDeal = (char*)malloc(sizeof(char) * maxSize);
	if (toDeal != NULL)
	{
		// Receive the array
		int sizeofToDeal = sizeof(char) * maxSize;
		memset(toDeal, '\0', sizeofToDeal);
		strcpy_s(toDeal, maxSize, inputThings);

		// Print
		for (int whichCharacter = 1; whichCharacter < startPlace; whichCharacter++)
		{
			printf(" ");
		}
		printf("%s", toDeal);
		free(toDeal);
		return 1;
	}
	else
	{
		printf("Failed!\n");
		return 0;
	}
}

void anotherLine(int lines)
{
	for (long long int whichOne = 1; whichOne <= lines; whichOne++)
	printf("\n");
}

void printTitle(char* title, int maxSize)
// This takes three lines with no wordwarp
{
	int size = (int)strlen(title);
	if (size > maxSize)
	{
		size = maxSize;
	}
	for (long long int whichOne = 1; whichOne <= size + 6; whichOne++)
	{
		printf("-");
	}
	printf("\n");
	printf("-| ");
	printf("%s", title);
	printf(" |-\n");
	for (long long int whichOne = 1; whichOne <= size + 6; whichOne++)
	{
		printf("-");
	}
}

void printTitleWithCurrentTime(char* title, int maxSize)
// This takes three lines with no wordwarp when it's over
{
	int size = (int)strlen(title);
	if (size > maxSize)
	{
		size = maxSize;
	}
	for (long long int whichOne = 1; whichOne <= size + 6; whichOne++)
	{
		printf("-");
	}
	printf("\n");
	printf("-| ");
	printf("%s", title);
	printf(" |-");
	printMultipleTimes(' ', 100 - timeStringLength(currentSecond()) - strlen(title) - 6);
	printTimeStringUpToMinute(currentSecond());
	printf("\n");
	for (long long int whichOne = 1; whichOne <= strlen(title) + 6; whichOne++)
	{
		printf("-");
	}
}

void print_(int howMany)
{
	for (long long int whichOne = 1; whichOne <= howMany; whichOne++)
	{
		printf("_");
	}
}

void keyToContinue(char* inputString, int length)
{
	char* final = (char*)malloc(sizeof(char) * (18 + length));
	strcpy(final, "Press any key to ");
	//char final[18 + length] = "Press any key to ";
	strcat(final, inputString);
	printMiddleAddjusted(final, 18 + length);
	printf("\n");
	printMiddleAddjusted("", 1);
	free(final);
	_getch();
}

void printMiddleLeft(char* inputThings, int maxSize, int offset)
{
	char* toDeal = (char*)malloc(sizeof(char) * maxSize);
	if (toDeal != NULL)
	{
		// Receive the array
		int sizeofToDeal = sizeof(char) * maxSize;
		memset(toDeal, '\0', sizeofToDeal);
		strcpy_s(toDeal, maxSize, inputThings);

		// Print
		int startPlace = 50 - offset - strlen(toDeal);

		printMultipleTimes(' ', startPlace);

		printf("%s", toDeal);
		free(toDeal);
		return 1;
	}
	else
	{
		printf("Failed!\n");
		return 0;
	}
}

int areYouSure()
// 1 for yes
// 0 for no
{
	printMiddleAddjusted("Are you sure?(y/n): ", 23);
	char userInput[100];
	memset(userInput, '\0', sizeof(userInput));
	inputAlnum(userInput, 100, 1);
	if (userInput[0] == 'y' || userInput[0] == 'Y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}