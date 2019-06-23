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
#include "ticket_srv.h"
#include "seat_srv.h"
#include "timeRelated.h"
#include "schedule_srv.h"

void studio_UI_manageStudios(account_list_t theUser);

void studio_UI_viewStudiosForAdmin(int howManyPerPage);

void printStudioAdminListOneLine(int whichOne, int selected);

void studio_UI_modifyStudio(theStudioToModify);

void studio_UI_changeName(studio_list_t theStudioToModify);

int studio_UI_deleteStudio(studio_list_t theStudioToModify);

void studio_UI_checkByID();

void studio_UI_checkByName();

void studio_UI_createAStudio();

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
			studio_UI_checkByID();
		}
		else if (selection == 2)
		{
			studio_UI_checkByName();
		}
		else if (selection == 3)
		{
			studio_UI_createAStudio();
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

				printStudioAdminListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printStudioAdminListOneLine(whichOneToPrint, 0);
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

		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theStudioToModify->data.ID);

		printMultipleTimes('\n', 3);

		// Changeable
		char menu1[][30] = {"Name:", "How Many Seats Per Row:", "How Many Seats Per Column:"};

		// Print row and Column
		printMiddleLeft(menu1[1], strlen(menu1[1]) + 1, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theStudioToModify->data.rowsCount);
		printMiddleLeft(menu1[2], strlen(menu1[2]) + 1, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theStudioToModify->data.colsCount);

		printf("\n\n");
		printMiddleAddjusted("Seats:", 7);
		printf("\n");
		seat_UI_printSeatNoMovie(50 - theStudioToModify->data.colsCount / 2, theStudioToModify->data.ID);
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
			printf("%s\n\n", theStudioToModify->data.name);
		}
		else
		{
			printMiddleLeft(menu1[0], strlen(menu1[0]) + 1, 2);
			printMultipleTimes(' ', 2);
			printf("%s\n\n", theStudioToModify->data.name);
		}

		if (navigation == 1)
		{
			printMultipleTimes(' ', (100 - strlen("Change Seat")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s\n", "Change Seat");

			setFontColor(0);
			setBackgroundColor(7);
		} else
		{
			printMultipleTimes(' ', (100 - strlen("Change Seat")) / 2);
			printf("%s\n", "Change Seat");
		}

		if (navigation == 2)
		{
			printMultipleTimes(' ', (100 - strlen("Delete Studio")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s\n", "Delete Studio");

			setFontColor(0);
			setBackgroundColor(7);
		}
		else
		{
			printMultipleTimes(' ', (100 - strlen("Delete Studio")) / 2);
			printf("%s\n", "Delete Studio");
		}

		printf("\n\n");
		if (navigation == 3)
		{
			printMultipleTimes(' ', (100 - strlen("Return")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s\n", "Return");

			setFontColor(0);
			setBackgroundColor(7);
		}
		else
		{
			printMiddleAddjusted("Return", 7);
			printf("\n");
		}

		anotherLine(3);
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
				if (studio_UI_deleteStudio(theStudioToModify) == 1)
				{
					break;
				}
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

	printf("\n\n");
	printMiddleLeft("New Name:", 10, 2);
	printMultipleTimes(' ', 2);

	char newName[30];
	inputAlnum(newName, 30, 1);
	printf("\n\n");

	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(theStudioToModify->data.name, newName);
		printMiddleAddjusted("Name updated!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
	} else
	{
		printf("\n\n");
		printMiddleAddjusted("Name not changed!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

int studio_UI_deleteStudio(studio_list_t theStudioToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Delete Studio", 14);
	printf("\n\n");
	printMiddleAddjusted("The studio will be deleted, relavant tickets and schedules will be forcedly returned.", 86);
	printf("\n\n");
	if (areYouSure() == 1)
	{
		printf("\n\n");
		for (int whichRow = 1; whichRow <= theStudioToModify->data.rowsCount; whichRow++)
		{
			for (int whichColumn = 1; whichColumn <= theStudioToModify->data.colsCount; whichColumn++)
			{
				// Return every ticket afterwards
				seat_node_t* theSeat = seat_srv_findByRoomAndPlace(theStudioToModify->data.ID, whichRow, whichColumn);
				if (theSeat != NULL)
				{
					ticket_srv_makeTicketERROR_byEndTimeAndSeat(theSeat->data.ID, currentSecond());
					// Remove seat
					seat_srv_deleteByID(theSeat->data.ID);
				}

				
			}
		}
		// Delete schedules
		schedule_srv_makeScheduleERROR_byEndTimeAndStudio(theStudioToModify->data.ID, currentSecond());

		studio_srv_deleteByID(theStudioToModify->data.ID);
		printMiddleAddjusted("Studio deleted!", 16);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 1;
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Studio not deleted!", 20);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 0;
	}
}

void studio_UI_checkByID()
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Check by ID", 12);
	printf("\n\n");
	printMiddleAddjusted("Please input the ID of the studio that you are looking for", 59);
	printf("\n\n");

	printMiddleLeft("ID:", 4, 2);
	printMultipleTimes(' ', 2);
	int number = inputInt();

	studio_list_t theStudio = studio_srv_findByID(number);
	printMultipleTimes('\n', 2);
	if (theStudio == NULL)
	{
		printMiddleAddjusted("The studio doesn't exist!", 26);
		printf("\n\n");
		keyToContinue("go back", 7);
	}
	else
	{
		studio_UI_modifyStudio(theStudio);
	}
}

void studio_UI_checkByName()
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Check by Name", 14);
	printf("\n\n");
	printMiddleAddjusted("Please input the name of the studio that you are looking for", 61);
	printf("\n\n");

	printMiddleLeft("Name:", 6, 2);
	printMultipleTimes(' ', 2);
	char name[30];
	inputAlnum(name, 30, 1);

	studio_list_t theStudio = studio_srv_findByUsername(name);
	printMultipleTimes('\n', 2);
	if (theStudio == NULL)
	{
		printMiddleAddjusted("The studio doesn't exist!", 26);
		printf("\n\n");
		keyToContinue("go back", 7);
	}
	else
	{
		studio_UI_modifyStudio(theStudio);
	}
}

void studio_UI_createAStudio()
{
	studio_t inputStudio;
	int nameOK = 0;
	int rowsCountOK = 0;
	int colsCountOK = 0;

	while (1)
	{
		setBackgroundColor(7);
		setFontColor(0);

		system("cls");

		printTitleWithCurrentTime("Create a studio", 19);
		printMultipleTimes('\n', 2);
		printMiddleAddjusted("Please fill in these information:", 34);
		printMultipleTimes('\n', 3);

		printMiddleLeft("Name:", 6, 2);
		printMultipleTimes(' ', 2);
		if (nameOK == 0)
			inputAlnum(inputStudio.name, 30, 1);
		else
			printf("%s", inputStudio.name);
		printf("\n");
		studio_node_t* otherStudio = studio_srv_findByUsername(inputStudio.name);
		if (otherStudio != NULL)
		{
			printMiddleAddjusted("Please choose another name!", 28);
			printf("\n");
			keyToContinue("Continue", 8);
			continue;
		}
		else
		{
			nameOK = 1;
		}
		printf("\n");

		printMiddleLeft("How many seats per Row:", 24, 2);
		printMultipleTimes(' ', 2);
		if (rowsCountOK == 0)
			inputStudio.rowsCount = inputInt();
		else
			printf("%d", inputStudio.rowsCount);
		printf("\n");
		if (inputStudio.rowsCount <= 0 || inputStudio.rowsCount > 10)
		{
			printMiddleAddjusted("Number out of range!", 21);
			printf("\n\n");
			keyToContinue("Continue", 8);
			continue;
		}
		else
		{
			rowsCountOK = 1;
		}
		

		printMiddleLeft("How many seats per Column:", 27, 2);
		printMultipleTimes(' ', 2);
		if (colsCountOK == 0)
			inputStudio.colsCount = inputInt();
		else
			printf("%d", inputStudio.colsCount);
		printf("\n");
		if (inputStudio.colsCount <= 0 || inputStudio.colsCount > 10)
		{
			printMiddleAddjusted("Number out of range!", 21);
			printf("\n\n");
			keyToContinue("Continue", 8);
			continue;
		}
		else
		{
			colsCountOK = 1;
		}
		printf("\n\n\n");

		if (areYouSure() == 1)
		{
			printf("\n");
			inputStudio.ID = studio_srv_getID();
			studio_srv_add(inputStudio);
			
			// Generate seats
			seat_srv_generateSeatsForNewStudio(inputStudio.ID);

			printMiddleAddjusted("Studio added!", 14);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
		else
		{
			printf("\n"); 
			printMiddleAddjusted("Studio not added!", 18);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
	}
}