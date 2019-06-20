// 各种输入函数
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>

void yes()
{
	char space[100];
	char a;
	while ( a=_getch())
	{
		printf("You just input: %c %d\n", a, a);
	}
	// 8 for backspace
	// 13 for enter
}

#define inputStringMacro(inputSpace, length, condition)\
int counter = 0;\
while ((aChar = _getch()) != 13)\
{\
	if (aChar >= 0 && aChar < 128)\
	{\
		if (aChar == 8)\
		{\
			if (counter > 0)\
			{\
				counter--; \
				inputSpace[counter] = '\0'; \
				printf("\b \b"); \
			}\
		}\
		else if (counter < length - 1 && (condition))\
		{\
			printf("%c", aChar); \
			inputSpace[counter] = aChar; \
			counter++; \
		}\
	}\
}\
inputSpace[counter] = '\0';


void inputAlnum(char* inputSpace, int length)
// Length includes '\0'
{
	char aChar;
	inputStringMacro(inputSpace, length, isalnum(aChar));
	//printf("\nyou just input: *%s*\n", inputSpace);
}

void inputName(char* inputSpace, int length)
// Length includes '\0'
{
	char aChar;
	inputStringMacro(inputSpace, length, isalpha(aChar) || aChar == '-' || aChar == 32);
	//printf("\nyou just input: *%s*\n", inputSpace);
}

int inputInt()
// Length includes '\0'
{
	int length = 10;
	length = (int)((int)log10(pow(2, sizeof(int) * 8)) + 1);
	char* numberArray = (char*)malloc(sizeof(char) *(length + 1));
	
	char aChar;
	inputStringMacro(numberArray, length - 1, isdigit(aChar));

	int result = atoi(numberArray);
	free(numberArray);
	return result;
}

void inputPassword(char* inputSpace, int length)
{
	char aChar;
	
	int counter = 0; 
	while ((aChar = _getch()) != 13)
	{
		if (aChar > 0 && aChar < 128)
		{
			if (aChar == 8)
			{
				if (counter > 0)
				{
					counter--; 
					inputSpace[counter] = '\0'; 
					printf("\b \b"); 
				}
			}
			else if (counter < length - 1 && (iscntrl(aChar) == 0))
			{
				printf("%c", '*'); 
				inputSpace[counter] = aChar; 
				counter++; 
			}
		}
	}
	inputSpace[counter] = '\0';


	//printf("\nyou just input: *%s*\n", inputSpace);
}