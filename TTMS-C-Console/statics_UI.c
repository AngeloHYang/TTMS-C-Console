#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"
#include "templates.h"
#include "account_UI.h"
#include "play_UI.h"
#include "schedule_UI.h"
#include "play_srv.h"
#include "ticket_srv.h"
#include "common.h"

void statics_UI_Menu(account_list_t theUser);

void statics_UI_boxOfficeRecordsMenu();

void statics_UI_boxOfficeRecordsViewAll(int howManyPerPage);

void printPlayBoxOfficeIncomeManagerListOneLine(int whichOne, int selected);

void schedule_UI_viewPlay(play_list_t thePlayToView);

void statics_UI_checkByPlayID();

void statics_UI_salesMenu();

void statics_UI_salesMenuForReal(user_date_t startDate, user_date_t endDate);

void statics_UI_salesDateViewAll(int howManyPerPage, user_date_t startDate, user_date_t endDate);

void printSalesAccountDateManagerListOneLine(int whichOne, int selected, user_date_t startDate, user_date_t endDate);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void statics_UI_Menu(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "Box Office Records", "Sales", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2]};

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Statics", "View statics", 13, pointers, 3, 100);

		if (selection == 0)
		{
			statics_UI_boxOfficeRecordsMenu();
		}
		else if (selection == 1)
		{
			statics_UI_salesMenu();
		}
		else if (selection == 2)
		{
			toReturn = 1;
		}
	}
	free(greet);
}

void statics_UI_boxOfficeRecordsMenu()
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	

	char Menu[][100] = { "View All", "Check by Play ID", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2] };

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Box Office Records", "  ", 3, pointers, 3, 100);

		if (selection == 0)
		{
			statics_UI_boxOfficeRecordsViewAll(10);
		}
		else if (selection == 1)
		{
			statics_UI_checkByPlayID();
		}
		else if (selection == 2)
		{
			toReturn = 1;
		}
	}	
}

void statics_UI_boxOfficeRecordsViewAll(int howManyPerPage)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (play_srv_howManyInToto() % howManyPerPage == 0)
	{
		pageSum = play_srv_howManyInToto() / howManyPerPage;
	}
	else
	{
		pageSum = play_srv_howManyInToto() / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';

	/*
	8			 83 		   9
	  name ID  price  sold  total  startDate  endDate
       1 30 1   10 1    8  1   8 1   10 1  10 1
	*/
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Box Office Records", 24);
		printMultipleTimes('\n', 3);

		if (play_srv_howManyInToto() == 0)
		{
			printMiddleAddjusted("No play now!", 13);
			printf("\n\n");
			keyToContinue("Return", 6);
			break;
		}

		//if (account_srv_howManyInToto() != 0)
		//{
		printMultipleTimes(' ', 8);
		printMultipleTimes('-', 83);
		printf("\n");
		//}

		// 表头
		printMultipleTimes(' ', 8);
		printf("|");
		printf("%-30s", "Name");
		printf("|");
		printf("%-10s", "ID");
		printf("|");
		printf("%-8s", "Sold");
		printf("|");
		printf("%-8s", "Total");
		printf("|");
		printf("%-10s", "Start Date");
		printf("|");
		printf("%-10s", "End Date");  
		printf("|");
		printf("\n");
		printMultipleTimes(' ', 8);
		printMultipleTimes('-', 83);
		printf("\n");

		// 内容
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(play_srv_howManyInToto(), currentPage * howManyPerPage); whichOneToPrint++)
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

				printPlayBoxOfficeIncomeManagerListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printPlayBoxOfficeIncomeManagerListOneLine(whichOneToPrint, 0);
			}
		}

		// Return button
		if ((play_srv_howManyInToto() % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (play_srv_howManyInToto() % howManyPerPage)) * 2);
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
		printf("\n ● Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
		printMultipleTimes(' ', 28);
		printf("Page: %d/%d", currentPage, pageSum);

		// Receive
		pressedKey = _getch();
		if (pressedKey == 'w' || pressedKey == 'W')
		{
			if (currentPage == pageSum && selection == howManyPerPage + 1)
			{
				if (play_srv_howManyInToto() % howManyPerPage != 0)
				{
					selection = (play_srv_howManyInToto() % howManyPerPage);
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
				if ((play_srv_howManyInToto() % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (play_srv_howManyInToto() % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (play_srv_howManyInToto() % howManyPerPage))
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
				if (currentPage == pageSum && selection > (play_srv_howManyInToto() % howManyPerPage))
				{
					selection = play_srv_howManyInToto() % howManyPerPage;
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
				play_node_t* thePlayToView = play_srv_findByWhichOne(theOneToModify);

				schedule_UI_viewPlay(thePlayToView);

				// Update page sum
				if (play_srv_howManyInToto() % howManyPerPage == 0)
				{
					pageSum = play_srv_howManyInToto() / howManyPerPage;
				}
				else
				{
					pageSum = play_srv_howManyInToto() / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (play_srv_howManyInToto() % howManyPerPage == 0)
		{
			pageSum = play_srv_howManyInToto() / howManyPerPage;
		}
		else
		{
			pageSum = play_srv_howManyInToto() / howManyPerPage + 1;
		}
	}
}

void printPlayBoxOfficeIncomeManagerListOneLine(int whichOne, int selected)
{
	play_node_t* thisOne = play_srv_findByWhichOne(whichOne);

	printMultipleTimes(' ', 8);
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
	printf("%-8d", ticket_srv_playIDReturnSoldNumber(thisOne->data.ID));
	printf("|");
	printf("%-8d", ticket_srv_playIDReturnSoldNumber(thisOne->data.ID) * thisOne->data.price);
	printf("|");
	printf("%-4d.%-2d.%-2d", thisOne->data.start_date.year, thisOne->data.start_date.month, thisOne->data.start_date.day);
	printf("|");
	printf("%-4d.%-2d.%-2d", thisOne->data.end_date.year, thisOne->data.end_date.month, thisOne->data.end_date.day);
	printf("|");

	if (selected == 1)
	{
		setBackgroundColor(7);
		setFontColor(0);
	}
	printf("\n");
	printMultipleTimes(' ', 8);
	printMultipleTimes('-', 83);
	printf("\n");
}

void schedule_UI_viewPlay(play_list_t thePlayToView)
{
	int toReturn = 0;
	int navigation = 10;
	char inputChar = '\0';

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		// Unchangeable
		printTitleWithCurrentTime("View Play Detail", 17);
		printMultipleTimes('\n', 2);
		printf("\n");

		// ID:
		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", thePlayToView->data.ID);

		printMultipleTimes('\n', 3);

		// Load
		// Ratings result
		char ratings[6];
		if (thePlayToView->data.rating == PLAY_RATE_G)
		{
			strcpy(ratings, "G");
		}
		else if (thePlayToView->data.rating == PLAY_RATE_PG)
		{
			strcpy(ratings, "PG");
		}
		else if (thePlayToView->data.rating == PLAY_RATE_PG13)
		{
			strcpy(ratings, "PG13");
		} if (thePlayToView->data.rating == PLAY_RATE_R)
		{
			strcpy(ratings, "R");
		} if (thePlayToView->data.rating == PLAY_RATE_NC_17)
		{
			strcpy(ratings, "NC 17");
		}
		// Menu items
		char menu1[10][100] = { "Name:", "Type:" , "Area:", "Rating:", "Duration", "Start Date:", "End Date:", "Price", "Sold Out:", "Total Income"};
		// Menu results
		char menu2[10][100];
		strcpy(menu2[0], thePlayToView->data.name);
		strcpy(menu2[1], thePlayToView->data.type);
		strcpy(menu2[2], thePlayToView->data.area);
		strcpy(menu2[3], ratings);
		_itoa(thePlayToView->data.duration, menu2[4], 10);
		// start date
		memset(menu2[5], '\0', sizeof(menu2[5]));
		char swap[10];
		_itoa(thePlayToView->data.start_date.year, swap, 10);
		strcat(menu2[5], swap);
		strcat(menu2[5], ".");
		_itoa(thePlayToView->data.start_date.month, swap, 10);
		strcat(menu2[5], swap);
		strcat(menu2[5], ".");
		_itoa(thePlayToView->data.start_date.day, swap, 10);
		strcat(menu2[5], swap);
		// end date
		memset(menu2[6], '\0', sizeof(menu2[6]));
		_itoa(thePlayToView->data.end_date.year, swap, 10);
		strcat(menu2[6], swap);
		strcat(menu2[6], ".");
		_itoa(thePlayToView->data.end_date.month, swap, 10);
		strcat(menu2[6], swap);
		strcat(menu2[6], ".");
		_itoa(thePlayToView->data.end_date.day, swap, 10);
		strcat(menu2[6], swap);
		//price
		memset(menu2[7], '\0', sizeof(menu2[7]));
		_itoa(thePlayToView->data.price, menu2[7], 10);
		// Sold out
		memset(menu2[8], '\0', sizeof(menu2[8]));
		_itoa(ticket_srv_playIDReturnSoldNumber(thePlayToView->data.ID), menu2[8], 10);
		// Total income
		memset(menu2[9], '\0', sizeof(menu2[9]));
		_itoa(ticket_srv_playIDReturnSoldNumber(thePlayToView->data.ID) * thePlayToView->data.price, menu2[9], 10);
		for (int whichOne = 0; whichOne < 10; whichOne++)
		{
			if (navigation == whichOne)
			{
				printMultipleTimes(' ', 50 - strlen(menu1[whichOne]));

				setBackgroundColor(0);
				setFontColor(7);

				//printMiddleLeft(menu1[whichOne], strlen(menu1[whichOne]), 2);
				printf("%s", menu1[whichOne]);


				setBackgroundColor(7);
				setFontColor(0);

				printMultipleTimes(' ', 4);
				printf("%s\n", menu2[whichOne]);
			}
			else
			{
				printMultipleTimes(' ', 50 - strlen(menu1[whichOne]));
				printf("%s", menu1[whichOne]);
				printMultipleTimes(' ', 4);
				printf("%s\n", menu2[whichOne]);
			}
		}
		printf("\n\n");
		if (navigation == 10)
		{
			printMultipleTimes(' ', 50 - strlen("Return"));
			setBackgroundColor(0);
			setFontColor(7);
			printf("Return");
			setBackgroundColor(7);
			setFontColor(0);
		}
		else
		{
			printMultipleTimes(' ', 50 - strlen("Return"));
			printf("Return");
		}

		printf("\n\n");

		anotherLine(3);
		print_(100);
		printf("\n\n ● Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 10)
			{
				navigation++;
			}
			else if (navigation == 10)
			{
				navigation = 10;
			}
		}
		else if (inputChar == 'w' || inputChar == 'W')
		{
			if (navigation > 10)
			{
				navigation--;
			}
			else if (navigation == 10)
			{
				navigation = 10;
			}
		}
		else if (inputChar == 13)
		{
			if (navigation == 10)
			{
				break;
			}
		}
	}
}

void statics_UI_checkByPlayID()
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Check by ID", 12);
	printf("\n\n");
	printMiddleAddjusted("Please input the ID of the play that you are looking for", 57);
	printf("\n\n");

	printMiddleLeft("ID:", 4, 2);
	printMultipleTimes(' ', 2);
	int number = inputInt();

	play_list_t thePlay = play_srv_findByID(number);
	printMultipleTimes('\n', 2);
	if (thePlay == NULL)
	{
		printMiddleAddjusted("The play doesn't exist!", 24);
		printf("\n\n");
		keyToContinue("go back", 7);
	}
	else
	{
		schedule_UI_viewPlay(thePlay);
	}
}

void statics_UI_salesMenu()
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Sales", 12);
	printf("\n\n");
	printMiddleAddjusted("To check sales statics, you need to assign a time interval", 59);
	printf("\n\n");

	user_date_t startDate, endDate;
	
	char inputSpace[10];

	printMultipleTimes(' ', 20);
	printf("Start Date:");
	printMultipleTimes(' ', 2);
	printf("Year: ");
	inputNumber(inputSpace, 5, 1);
	startDate.year = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Month: ");
	inputNumber(inputSpace, 3, 1);
	startDate.month = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Day: ");
	inputNumber(inputSpace, 3, 1);
	startDate.day = atoi(inputSpace);
	printf("\n");

	printMultipleTimes(' ', 22);

	printf("End Date:");
	printMultipleTimes(' ', 2);
	printf("Year: ");
	inputNumber(inputSpace, 5, 1);
	endDate.year = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Month: ");
	inputNumber(inputSpace, 3, 1);
	endDate.month = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Day: ");
	inputNumber(inputSpace, 3, 1);
	endDate.day = atoi(inputSpace);
	printf("\n");
	

	
	printMultipleTimes('\n', 2);

	if (areYouSure() == 1)
	{
		printf("\n\n");
		if (validDate(startDate) == 1 && validDate(endDate) == 1 && DateCmp(startDate, endDate) != 1)
		{
			keyToContinue("continue", 8);
			statics_UI_salesMenuForReal(startDate, endDate);
		}
		else
		{
			printMiddleAddjusted("Invalid date!", 14);
			printf("\n\n");
			keyToContinue("go back", 8);
		}
	}
	else
	{
		printf("\n\n");
		keyToContinue("go back", 8);
	}
}

void statics_UI_salesMenuForReal(user_date_t startDate, user_date_t endDate)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';



	char Menu[][100] = { "View All", "Check by Account ID", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2] };

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Sales Statics", "  ", 3, pointers, 3, 100);

		if (selection == 0)
		{
			statics_UI_salesDateViewAll(10, startDate, endDate);
		}
		else if (selection == 1)
		{
			//statics_UI_checkByPlayID();
		}
		else if (selection == 2)
		{
			toReturn = 1;
		}
	}
}

void statics_UI_salesDateViewAll(int howManyPerPage, user_date_t startDate, user_date_t endDate)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (account_srv_howManyClerkInToto() % howManyPerPage == 0)
	{
		pageSum = account_srv_howManyClerkInToto() / howManyPerPage;
	}
	else
	{
		pageSum = account_srv_howManyClerkInToto() / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';

	/*
	8			 83 		   9
	  name    ID   sold  total price  startDate  endDate
	   1 30 1 10 1  8  1   8          1   10   1    10 1
	*/
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Sales", 11);
		printMultipleTimes('\n', 3);

		if (account_srv_howManyClerkInToto() == 0)
		{
			printMiddleAddjusted("No account now!", 16);
			printf("\n\n");
			keyToContinue("Return", 6);
			break;
		}

		//if (account_srv_howManyInToto() != 0)
		//{
		printMultipleTimes(' ', 8);
		printMultipleTimes('-', 83);
		printf("\n");
		//}

		// 表头
		printMultipleTimes(' ', 8);
		printf("|");
		printf("%-30s", "Name");
		printf("|");
		printf("%-10s", "ID");
		printf("|");
		printf("%-8s", "Sold");
		printf("|");
		printf("%-8s", "Total");
		printf("|");
		printf("%-10s", "Start Date");
		printf("|");
		printf("%-10s", "End Date");
		printf("|");
		printf("\n");
		printMultipleTimes(' ', 8);
		printMultipleTimes('-', 83);
		printf("\n");

		// 内容
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(account_srv_howManyClerkInToto(), currentPage * howManyPerPage); whichOneToPrint++)
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

				printSalesAccountDateManagerListOneLine(whichOneToPrint, 1, startDate, endDate);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printSalesAccountDateManagerListOneLine(whichOneToPrint, 0, startDate, endDate);
			}
		}

		// Return button
		if ((account_srv_howManyClerkInToto() % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (account_srv_howManyClerkInToto() % howManyPerPage)) * 2);
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
		printf("\n ● Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
		printMultipleTimes(' ', 28);
		printf("Page: %d/%d", currentPage, pageSum);

		// Receive
		pressedKey = _getch();
		if (pressedKey == 'w' || pressedKey == 'W')
		{
			if (currentPage == pageSum && selection == howManyPerPage + 1)
			{
				if (account_srv_howManyClerkInToto() % howManyPerPage != 0)
				{
					selection = (account_srv_howManyClerkInToto() % howManyPerPage);
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
				if ((account_srv_howManyClerkInToto() % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (account_srv_howManyClerkInToto() % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (account_srv_howManyClerkInToto() % howManyPerPage))
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
				if (currentPage == pageSum && selection > (account_srv_howManyClerkInToto() % howManyPerPage))
				{
					selection = account_srv_howManyClerkInToto() % howManyPerPage;
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
				//play_node_t* thePlayToView = play_srv_findByWhichOne(theOneToModify);

				//schedule_UI_viewPlay(thePlayToView);

				// Update page sum
				if (account_srv_howManyClerkInToto() % howManyPerPage == 0)
				{
					pageSum = account_srv_howManyClerkInToto() / howManyPerPage;
				}
				else
				{
					pageSum = account_srv_howManyClerkInToto() / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (account_srv_howManyClerkInToto() % howManyPerPage == 0)
		{
			pageSum = account_srv_howManyClerkInToto() / howManyPerPage;
		}
		else
		{
			pageSum = account_srv_howManyClerkInToto() / howManyPerPage + 1;
		}
	}
}

void printSalesAccountDateManagerListOneLine(int whichOne, int selected, user_date_t startDate, user_date_t endDate)
{
	//play_node_t* thisOne = play_srv_findByWhichOne(whichOne);

	account_node_t* thisOne = account_srv_findClerkByWhichOne(whichOne);

	int sold = 0, total = 0;
	ticket_srv_clerkIDAndDateToSoldNumberAndTotal(thisOne->data.ID, startDate, endDate, &sold, &total);

	printMultipleTimes(' ', 8);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}
	printf("|");
	printf("%-30s", thisOne->data.nickname);
	printf("|");
	printf("%-10d", thisOne->data.ID);
	printf("|");
	printf("%-8d", sold);
	printf("|");
	printf("%-8d", total);
	printf("|");
	printf("%-4d.%-2d.%-2d", startDate.year, startDate.month, startDate.day);
	printf("|");
	printf("%-4d.%-2d.%-2d", endDate.year, endDate.month, endDate.day);
	printf("|");

	if (selected == 1)
	{
		setBackgroundColor(7);
		setFontColor(0);
	}
	printf("\n");
	printMultipleTimes(' ', 8);
	printMultipleTimes('-', 83);
	printf("\n");
}