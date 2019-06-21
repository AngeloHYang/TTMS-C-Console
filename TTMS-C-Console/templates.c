#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "printChoices.h"
#include "color.h"

int standardSelectMenuView(int currentBackGroundColor, int currentFontColor, char* title, char* words, int wordCount, char** Menu, int menuItems, int menuLength)
// It returns the selection of the user
{
	int cursorPlace = 0;
	char pressedButton = '0';
	setBackgroundColor(currentBackGroundColor);
	system("cls");

	while (pressedButton != 'q' && pressedButton != 'Q')
	{
		setBackgroundColor(currentBackGroundColor);
		setFontColor(currentFontColor);
		system("cls");
		printTitleWithCurrentTime(title, 100);
		anotherLine(5);
		printMiddleAddjusted(words, wordCount + 1);
		anotherLine(5);

		for (long long int whichOne = 0; whichOne < menuItems; whichOne++)
		{
			if (whichOne == cursorPlace)
			{
				printMultipleTimes(' ', (100 -strlen(Menu[whichOne])) / 2);

				setFontColor(currentBackGroundColor);
				setFontBackGroudColor(currentFontColor);
				//printMiddleAddjusted(Menu[whichOne], menuLength);
				printf("%s", Menu[whichOne]);
				//withDrawColor();
				//printf("\n");
				setFontColor(currentFontColor);
				setFontBackGroudColor(currentBackGroundColor);
				printf("\n");
			}
			else
			{
				printMultipleTimes(' ', (100 - strlen(Menu[whichOne])) / 2);
				
				//printMiddleAddjusted(Menu[whichOne], menuLength);
				//printf("\n");
				printf("%s\n", Menu[whichOne]);
			}
		}

		anotherLine(6);
		print_(100);
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Return with \"Q\". Select with \"Enter\".\n");

		pressedButton = _getch();
		if (pressedButton == 's' || pressedButton == 'S')
		{
			if (cursorPlace < menuItems - 1)
			{
				cursorPlace++;
			}
			else if (cursorPlace == menuItems - 1)
			{
				cursorPlace = 0;
			}
		}
		else if (pressedButton == 'w' || pressedButton == 'W')
		{
			if (cursorPlace > 0)
			{
				cursorPlace--;
			}
			else if (cursorPlace == 0)
			{
				cursorPlace = menuItems - 1;
			}
		}
		else if (pressedButton == 13)
		{
			return cursorPlace;
		}
	}

}

int exitSelect()
{
	int selection = 2;
	char receive;
	while (1)
	{
		setBackgroundColor(0);
		setFontColor(7);
		system("cls");
		printTitleWithCurrentTime("Exit", 5);
		printMultipleTimes('\n', 9);
		printMiddleAddjusted("Do you want to quit?", 21);
		printMultipleTimes('\n', 10);
		
		
		printMultipleTimes(' ', 70);
		if (selection == 1)
		{
			setFontColor(0);
			setFontBackGroudColor(7);
		}
		printf("Yes");
		setFontColor(7);
		setFontBackGroudColor(0);
		
		printMultipleTimes(' ', 10);

		if (selection == 2)
		{
			setFontColor(0);
			setFontBackGroudColor(7);
		}
		printf("No");
		setFontColor(7);
		setFontBackGroudColor(0);


		printMultipleTimes('\n', 4);


		print_(100);
		printf("\n\n ¡ñ Switch with \"A\" and \"D\". Select with \"Enter\".\n");

		receive = _getch();

		if (receive == 'd' || receive == 'D')
		{
			if (selection < 2)
			{
				selection++;
			}
			else if (selection == 2)
			{
				selection = 1;
			}
		}
		else if (receive == 'a' || receive == 'A')
		{
			if (selection > 1)
			{
				selection--;
			}
			else if (selection == 1)
			{
				selection = 2;
			}
		}
		else if (receive == 13)
		{
			if (selection == 2)
			{
				return 0;
			}
			if (selection == 1)
				return 1;
		}
	}
}