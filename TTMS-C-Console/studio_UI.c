#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account_srv.h"
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "studio_srv.h"
#include "templates.h"
#include "List.h"
#include "seat_UI.h"

void studio_UI_manageStudios(account_list_t theUser);

void studio_UI_viewStudiosForAdmin(int howManyPerPage);

void printStudioAdminListOneLine(int whichOne, int selected);

void studio_UI_modifyStudio(theStudioToModify);

void studio_UI_changeName(studio_list_t theStudioToModify);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void studio_UI_manageStudios(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "View Studios", "Check by ID", "Check by Name", "Create a Studio", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2], Menu[3], Menu[4] };

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Studio Management", "Add, modify, or delete a studio", 34, pointers, 5, 100);

		if (selection == 0)
		{
			 studio_UI_viewStudiosForAdmin(10);
		}
		else if (selection == 1)
		{
			//account_UI_checkByID(theUser);
		}
		else if (selection == 2)
		{
			//account_UI_checkByUsername(theUser);
		}
		else if (selection == 3)
		{
			//account_UI_createAccount();
		}
		else if (selection == 4)
		{
			toReturn = 1;
		}
	}
	free(greet);
}

void studio_UI_viewStudiosForAdmin(int howManyPerPage)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (studio_srv_howManyInToto() % howManyPerPage == 0)
	{
		pageSum = studio_srv_howManyInToto() / howManyPerPage;
	}
	else
	{
		pageSum = studio_srv_howManyInToto() / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';

	/*
	25			 51 		   24
			name ID capacity
	       1 30 1 10 1  7  1
	*/
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Studios", 14);
		printMultipleTimes('\n', 3);

		if (studio_srv_howManyInToto() == 0)
		{
			printMiddleAddjusted("No studio now!", 15);
			printf("\n\n");
			keyToContinue("Return", 6);
			break;
		}

		//if (account_srv_howManyInToto() != 0)
		//{
		printMultipleTimes(' ', 25);
		printMultipleTimes('-', 51);
		printf("\n");
		//}

		// ±íÍ·
		printMultipleTimes(' ', 25);
		printf("|");
		printf("%-30s", "Name");
		printf("|");
		printf("%-10s", "ID");
		printf("|");
		printf("%-7s", "Capacity");
		printf("|");
		printf("\n");
		printMultipleTimes(' ', 25);
		printMultipleTimes('-', 51);
		printf("\n");

		// ÄÚÈÝ
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(studio_srv_howManyInToto(), currentPage * howManyPerPage); whichOneToPrint++)
		{
			currentOne = whichOneToPrint % howManyPerPage;
			if (currentOne == 0)
			{
				currentOne = howManyPerPage;
			}

			if (currentOne == selection)
			{
				//setBackgroundColor(0);
				//setFontColor(7);

				printUserListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printUserListOneLine(whichOneToPrint, 0);
			}
		}

		// Return button
		if ((studio_srv_howManyInToto() % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (studio_srv_howManyInToto() % howManyPerPage)) * 2);
		}

		printMultipleTimes(' ', (100 - strlen("Return")) / 2);
		if (selection == howManyPerPage + 1)
		{
			setBackgroundColor(0);
			setFontColor(7);
		}
		printf("Return");
		setBackgroundColor(7);
		setFontColor(0);
		printf("\n");
		print_(100);
		printf("\n ¡ñ Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
		printMultipleTimes(' ', 28);
		printf("Page: %d/%d", currentPage, pageSum);

		// Receive
		pressedKey = _getch();
		if (pressedKey == 'w' || pressedKey == 'W')
		{
			if (currentPage == pageSum && selection == howManyPerPage + 1)
			{
				if (studio_srv_howManyInToto() % howManyPerPage != 0)
				{
					selection = (studio_srv_howManyInToto() % howManyPerPage);
				}
				else
				{
					selection = howManyPerPage;
				}
			}
			else if (selection > 1)
			{
				selection--;
			}
		}
		else if (pressedKey == 'S' || pressedKey == 's')
		{
			if (currentPage < pageSum)
			{
				if (selection <= howManyPerPage)
				{
					selection++;
				}
			}
			else
			{
				if ((studio_srv_howManyInToto() % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (studio_srv_howManyInToto() % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (studio_srv_howManyInToto() % howManyPerPage))
					{
						selection++;
					}
				}
			}
		}
		else if (pressedKey == 'a' || pressedKey == 'A')
		{
			if (currentPage > 1)
			{
				currentPage--;
			}
		}
		else if (pressedKey == 'd' || pressedKey == 'D')
		{
			if (currentPage < pageSum)
			{
				currentPage++;
				if (currentPage == pageSum && selection > (studio_srv_howManyInToto() % howManyPerPage))
				{
					selection = studio_srv_howManyInToto() % howManyPerPage;
				}
			}
		}
		else if (pressedKey == 13)
		{
			if (selection == howManyPerPage + 1)
			{
				toReturn = 1;
			}
			else
			{
				
				int theOneToModify = selection + (currentPage - 1) * howManyPerPage;
				studio_node_t* theStudioToModify = studio_srv_findByWhichOne(theOneToModify);

				studio_UI_modifyStudio(theStudioToModify);

				// Update page sum
				if (studio_srv_howManyInToto() % howManyPerPage == 0)
				{
					pageSum = studio_srv_howManyInToto() / howManyPerPage;
				}
				else
				{
					pageSum = studio_srv_howManyInToto() / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (studio_srv_howManyInToto() % howManyPerPage == 0)
		{
			pageSum = studio_srv_howManyInToto() / howManyPerPage;
		}
		else
		{
			pageSum = studio_srv_howManyInToto() / howManyPerPage + 1;
		}
	}
}

void printStudioAdminListOneLine(int whichOne, int selected)
{
	studio_node_t* thisOne = studio_srv_findByWhichOne(whichOne);

	printMultipleTimes(' ', 25);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}

	printf("|");
	printf("%-30s", thisOne->data.name);
	printf("|");
	printf("%-10d", thisOne->data.ID);
	printf("|");
	printf("%3dx%-3d", thisOne->data.rowsCount, thisOne->data.colsCount);
	printf("|");

	if (selected == 1)
	{
		setBackgroundColor(7);
		setFontColor(0);
	}
	printf("\n");
	printMultipleTimes(' ', 25);
	printMultipleTimes('-', 51);
	printf("\n");
}

void studio_UI_modifyStudio(studio_list_t theStudioToModify)
{
	int toReturn = 0;
	int navigation = 0;
	char inputChar = '\0';

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		// Unchangeable
		printTitleWithCurrentTime("Studio Modify", 15);
		printMultipleTimes('\n', 2);

		
		printf("\n");
		
		printMultipleTimes('\n', 3);

		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theStudioToModify->data.ID);

		printMultipleTimes('\n', 3);

		// Changeable
		char place1[30], place2[30];
		char menu1[][30] = {"Name:", "How Many Seats Per Row:", "How Many Seats Per Column:"};
		char menu2[][30] = {theStudioToModify->data.name, theStudioToModify->data.colsCount, _itoa(theStudioToModify->data.rowsCount, place1, 10), _itoa(theStudioToModify->data.colsCount, place2, 10)};

		// Print row and Column
		printMiddleLeft(menu1[1], strlen(menu1[1]) + 1, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", menu2[1]);
		printMiddleLeft(menu1[2], strlen(menu1[2]) + 1, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", menu2[2]);

		printf("\n\nSeat:\n");
		seat_UI_printSeatNoMovie(10, theStudioToModify->data.ID);
		printf("\n\n\n");

		// Print name
		if (navigation == 0)
		{
			printMultipleTimes(' ', (50 - strlen(menu1[0]) - 2));

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", menu1[0]);

			setFontColor(0);
			setBackgroundColor(7);
			printMultipleTimes(' ', 2);
			printf("%s\n", menu2[0]);
		}
		else
		{
			printMiddleLeft(menu1[0], strlen(menu1[0]) + 1, 2);
			printMultipleTimes(' ', 2);
			printf("%s\n", menu2[0]);
		}

		if (navigation == 1)
		{
			printMultipleTimes(' ', (100 - strlen("Change Seat")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", "Change Seat");

			setFontColor(0);
			setBackgroundColor(7);
		} else
		{
			printMultipleTimes(' ', (100 - strlen("Change Seat")) / 2);
			printf("%s", "Change Seat");
		}

		if (navigation == 2)
		{
			printMultipleTimes(' ', (100 - strlen("Delete Studio")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", "Delete Studio");

			setFontColor(0);
			setBackgroundColor(7);
		}
		else
		{
			printMultipleTimes(' ', (100 - strlen("Delete Studio")) / 2);
			printf("%s", "Delete Studio");
		}

		printf("\n\n");
		if (navigation == 3)
		{
			printMultipleTimes(' ', (100 - strlen("Return")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", "Return");

			setFontColor(0);
			setBackgroundColor(7);
		}
		else
		{
			printMiddleAddjusted("Return", 7);
		}

		anotherLine(6);
		print_(100);
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 3)
			{
				navigation++;
			}
			else if (navigation == 3)
			{
				navigation = 0;
			}
		}
		else if (inputChar == 'w' || inputChar == 'W')
		{
			if (navigation > 0)
			{
				navigation--;
			}
			else if (navigation == 0)
			{
				navigation = 3;
			}
		}
		else if (inputChar == 13)
		{

			if (navigation == 0)
			{
				studio_UI_changeName(theStudioToModify);
			}
			else if (navigation == 1)
			{
				seat_UI_changeSeat(theStudioToModify);
			}
			else if (navigation == 2)
			{
				//Delete Studio
				studio_UI_deleteStudio();
			}
			else if (navigation == 3)
			{
				break;
			}
		}
	}
}

void studio_UI_changeName(studio_list_t theStudioToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Name", 12);
	printf("\n\n");
	printMiddleAddjusted("To change the name of the studio, please input", 47);

	printMiddleLeft("New Name:", 10, 2);
	printMultipleTimes(' ', 2);

	char newName[30];
	inputAlnum(newName, 30, 1);
	printf("\n\n");
	if (areYouSure() == 1)
	{
		strcpy(theStudioToModify->data.name, newName);
		printMiddleAddjusted("Name updated!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
	} else
	{
		printMiddleAddjusted("Name not changed!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

