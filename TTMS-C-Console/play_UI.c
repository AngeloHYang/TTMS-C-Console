#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account_srv.h"
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "templates.h"
#include "List.h"
#include "timeRelated.h"
#include "common.h"
#include "play_srv.h"
#include "ticket_srv.h"
#include "schedule_srv.h"

void play_UI_managePlays(account_list_t theUser);

void play_UI_viewPlaysForManager(int howManyPerPage);

void printPlayManagerListOneLine(int whichOne, int selected);

void play_UI_modifyPlay(play_list_t thePlayToModify);

void play_UI_changeName(play_list_t thePlayToModify);

void play_UI_changeType(play_list_t thePlayToModify);

void play_UI_changeArea(play_list_t thePlayToModify);

void play_UI_changeRating(play_list_t thePlayToModify);

void play_UI_changeDuration(play_list_t thePlayToModify);

void play_UI_changeStartAndEndDate(play_list_t thePlayToModify);

void play_UI_changePrice(play_list_t thePlayToModify);

int play_UI_deletePlay(play_list_t thePlayToModify);

void play_UI_checkByID();

void play_UI_AddAPlay();

//////////////////////////////////////////////////////////////////
void play_UI_managePlays(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "View Plays", "Check by ID", "Add a Play", "Return"};

	char* pointers[] = { Menu[0], Menu[1], Menu[2], Menu[3]};

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Play Management", "Add, modify, or delete a play", 30, pointers, 4, 100);

		if (selection == 0)
		{
			play_UI_viewPlaysForManager(10);
		}
		else if (selection == 1)
		{
			play_UI_checkByID();
		}
		else if (selection == 2)
		{
			play_UI_AddAPlay();
		}
		else if (selection == 3)
		{
			toReturn = 1;
		}
	}
	free(greet);
}

void play_UI_viewPlaysForManager(int howManyPerPage)
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
	6			 89 		   5
			name  ID   type  area rating duration price
		   1 30 1 10 1  20  1 10   1 5     1 3 1    3   1
	*/
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Plays", 11);
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
		printMultipleTimes(' ', 6);
		printMultipleTimes('-', 89);
		printf("\n");
		//}

		// ±íÍ·
		printMultipleTimes(' ', 6);
		printf("|");
		printf("%-30s", "Name");
		printf("|");
		printf("%-10s", "ID");
		printf("|");
		printf("%-20s", "Type");
		printf("|");
		printf("%-10s", "Area");
		printf("|");
		printf("%-5s", "FRS");  // Ratings
		printf("|");
		printf("%-3s", "Min");  // Duration
		printf("|");
		printf("%-3s", " $ ");  // Price
		printf("|");
		printf("\n");
		printMultipleTimes(' ', 6);
		printMultipleTimes('-', 89);
		printf("\n");

		// ÄÚÈÝ
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

				printPlayManagerListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printPlayManagerListOneLine(whichOneToPrint, 0);
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
		printf("\n ¡ñ Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
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
				play_node_t* thePlayToModify = play_srv_findByWhichOne(theOneToModify);

				//play_UI_modifyPlay(thePlayToModify);

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

void printPlayManagerListOneLine(int whichOne, int selected)
{
	play_node_t* thisOne = play_srv_findByWhichOne(whichOne);

	// Ratings;
	char ratings[6];
	if (thisOne->data.rating == PLAY_RATE_G)
	{
		strcpy(ratings, "G");
	} else if (thisOne->data.rating == PLAY_RATE_PG)
	{
		strcpy(ratings, "PG");
	} else if (thisOne->data.rating == PLAY_RATE_PG13)
	{
		strcpy(ratings, "PG13");
	} if (thisOne->data.rating == PLAY_RATE_R)
	{
		strcpy(ratings, "R");
	} if (thisOne->data.rating == PLAY_RATE_NC_17)
	{
		strcpy(ratings, "NC 17");
	} 


	printMultipleTimes(' ', 6);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}

	printMultipleTimes(' ', 6);
	printf("|");
	printf("%-30s", thisOne->data.name);
	printf("|");
	printf("%-10d", thisOne->data.ID);
	printf("|");
	printf("%-20s", thisOne->data.type);
	printf("|");
	printf("%-10s", thisOne->data.area);
	printf("|");
	printf("%-5s", ratings);  // Ratings
	printf("|");
	printf("%-3d", thisOne->data.duration);  // Duration
	printf("|");
	printf("%-3d", thisOne->data.price);  // Price
	printf("|");

	if (selected == 1)
	{
		setBackgroundColor(7);
		setFontColor(0);
	}
	printf("\n");
	printMultipleTimes(' ', 6);
	printMultipleTimes('-', 89);
	printf("\n");
}

void play_UI_modifyPlay(play_list_t thePlayToModify)
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
		printTitleWithCurrentTime("Play Modify", 15);
		printMultipleTimes('\n', 2);
		printf("\n");

		// ID:
		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", thePlayToModify->data.ID);

		printMultipleTimes('\n', 3);

		// Load
		// Ratings result
		char ratings[6];
		if (thePlayToModify->data.rating == PLAY_RATE_G)
		{
			strcpy(ratings, "G");
		}
		else if (thePlayToModify->data.rating == PLAY_RATE_PG)
		{
			strcpy(ratings, "PG");
		}
		else if (thePlayToModify->data.rating == PLAY_RATE_PG13)
		{
			strcpy(ratings, "PG13");
		} if (thePlayToModify->data.rating == PLAY_RATE_R)
		{
			strcpy(ratings, "R");
		} if (thePlayToModify->data.rating == PLAY_RATE_NC_17)
		{
			strcpy(ratings, "NC 17");
		}
		// Menu items
		char menu1[8][100] = { "Name:", "Type:" , "Area:", "Rating:", "Duration", "Start Date:", "End Date:", "Price" };
		// Menu results
		char menu2[8][100];
		strcpy(menu2[0], thePlayToModify->data.name);
		strcpy(menu2[1], thePlayToModify->data.type);
		strcpy(menu2[2], thePlayToModify->data.area);
		strcpy(menu2[3], ratings);
		_itoa(menu2[4], thePlayToModify->data.duration, 10);
			// start date
		memset(menu2[5], '\0', sizeof(menu2[5]));
		char swap[10];
		_itoa(thePlayToModify->data.start_date.year, swap, 10);
		strcat(menu2[5], swap);
		strcat(menu2[5], ".");
		_itoa(thePlayToModify->data.start_date.month, swap, 10);
		strcat(menu2[5], swap);
		strcat(menu2[5], ".");
		_itoa(thePlayToModify->data.start_date.day, swap, 10);
		strcat(menu2[5], swap);
			// end date
		memset(menu2[6], '\0', sizeof(menu2[6]));
		_itoa(thePlayToModify->data.end_date.year, swap, 10);
		strcat(menu2[6], swap);
		strcat(menu2[6], ".");
		_itoa(thePlayToModify->data.end_date.month, swap, 10);
		strcat(menu2[6], swap);
		strcat(menu2[6], ".");
		_itoa(thePlayToModify->data.end_date.day, swap, 10);
		strcat(menu2[6], swap);
			//price
		memset(menu2[7], '\0', sizeof(menu2[7]));
		_itoa(thePlayToModify->data.price, menu2[7], 10);

		for (int whichOne = 0; whichOne < 8; whichOne++)
		{
			if (navigation == whichOne)
			{
				printMultipleTimes(' ', (100 - strlen(menu1[whichOne])) / 2);

				setBackgroundColor(0);
				setFontColor(7);

				//printMiddleLeft(menu1[whichOne], strlen(menu1[whichOne]), 2);
				printf("%s", menu1[whichOne]);
				

				setBackgroundColor(7);
				setFontColor(0);

				printMultipleTimes(' ', 2);
				printf("%s\n", menu2[whichOne]);
			}
			else
			{
				printMiddleLeft(menu1[whichOne], strlen(menu1[whichOne]), 2);
				printMultipleTimes(' ', 2);
				printf("%s\n", menu2[whichOne]);
			}
		}
		if (navigation == 8)
		{
			printMultipleTimes(' ', (100 - strlen("Delete")) / 2);
			setBackgroundColor(0);
			setFontColor(7);
			printf("Delete");
			setBackgroundColor(7);
			setFontColor(0);
		}
		printf("\n\n");
		if (navigation == 9)
		{
			printMultipleTimes(' ', (100 - strlen("Return")) / 2);
			setBackgroundColor(0);
			setFontColor(7);
			printf("Return");
			setBackgroundColor(7);
			setFontColor(0);
		}
		else
		{
			printMultipleTimes(' ', (100 - strlen("Return")) / 2);
			printf("Return");
		}

		printf("\n\n");

		anotherLine(3);
		print_(100);
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 9)
			{
				navigation++;
			}
			else if (navigation == 9)
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
				navigation = 9;
			}
		}
		else if (inputChar == 13)
		{

			if (navigation == 0)
			{
				play_UI_changeName(thePlayToModify);
			}
			else if (navigation == 1)
			{
				play_UI_changeType(thePlayToModify);
			}
			else if (navigation == 2)
			{
				play_UI_changeArea(thePlayToModify);
			}
			else if (navigation == 3)
			{
				play_UI_changeRating(thePlayToModify);
			}
			else if (navigation == 4)
			{
				play_UI_changeDuration(thePlayToModify);
			}
			else if (navigation == 5 || navigation == 6)
			{
				play_UI_changeStartAndEndDate(thePlayToModify);
			}
			else if (navigation == 7)
			{
				play_UI_changePrice(thePlayToModify);
			}
			else if (navigation == 8)
			{
				//Delete play
				if (play_UI_deletePlay(thePlayToModify) == 1)
				{
					break;
				}
			}
			else if (navigation == 9)
			{
				break;
			}
		}
	}
}

void play_UI_changeName(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Name", 12);
	printf("\n\n");
	printMiddleAddjusted("To change the name of the play, please input", 45);

	printf("\n\n");
	printMiddleLeft("New Name:", 10, 2);
	printMultipleTimes(' ', 2);

	char newName[31];
	inputAlnum(newName, 31, 1);
	printf("\n\n");

	/*
	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}*/

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(thePlayToModify->data.name, newName);
		printMiddleAddjusted("Name updated!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Name not changed!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

void play_UI_changeType(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Type", 12);
	printf("\n\n");
	printMiddleAddjusted("To change the type of the play, please input", 45);

	printf("\n\n");
	printMiddleLeft("New Type:", 10, 2);
	printMultipleTimes(' ', 2);

	char newType[21];
	inputAlnum(newType, 21, 1);
	printf("\n\n");

	/*
	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}*/

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(thePlayToModify->data.type, newType);
		printMiddleAddjusted("Type updated!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Type not changed!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

void play_UI_changeArea(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Area", 12);
	printf("\n\n");
	printMiddleAddjusted("To change the area of the play, please input", 45);

	printf("\n\n");
	printMiddleLeft("New Area:", 10, 2);
	printMultipleTimes(' ', 2);

	char newArea[11];
	inputAlnum(newArea, 11, 1);
	printf("\n\n");

	/*
	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}*/

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(thePlayToModify->data.area, newArea);
		printMiddleAddjusted("Area updated!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Area not changed!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

void play_UI_changeRating(play_list_t thePlayToModify)
{
	
	int navigation = 0;
	char menu[][6] = { "G", "PG", "PG-13", "R", "NC 17"};
	char inputChar = '\0';
	while (1)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("Change Rating", 14);
		printf("\n\n");

		printMiddleAddjusted("To change the rating of the play, please choose:", 49);

		printf("\n\n");
		printMiddleLeft("New Rating:", 12, 2);
		printf("  ");

		for (int whichOne = 0; whichOne < 5; whichOne++)
		{
			if (whichOne == navigation)
			{
				setBackgroundColor(0);
				setFontColor(7);
				printf("%s", menu[whichOne]);
				setBackgroundColor(7);
				setFontColor(0);
				printf(" "); 
			}
			else
			{
				printf("%s", menu[whichOne]);
				printf(" ");
			}
		}

		inputChar = _getch();

		if (inputChar == 'a' || inputChar == 'A')
		{
			if (navigation > 0)
			{
				navigation--;
			}
			else
			{
				navigation = 4;
			}
		}
		else if (inputChar == 'd' || inputChar == 'D')
		{
			if (navigation < 4)
			{
				navigation++;
			}
			else
			{
				navigation = 0;
			}
		}
		else if (inputChar == 13)
		{
			break;
		}
	}
	printf("\n\n");
	if (areYouSure() == 1)
	{
		printf("\n");
		thePlayToModify->data.rating = (play_rating_t)(navigation + 1);
		printMiddleAddjusted("Play rating changed!", 21);
		printf("\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n");
		printMiddleAddjusted("Play rating not changed!", 25);
		printf("\n");
		keyToContinue("Continue", 8);
	}
}

void play_UI_changeDuration(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Duration", 16);
	printf("\n\n");
	printMiddleAddjusted("To change the duration of the play, please input", 49);

	printf("\n\n");
	printMiddleLeft("New Duration:", 14, 2);
	printMultipleTimes(' ', 2);

	int newDuration = inputInt();
	printf("\n\n");

	/*
	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}*/

	if (areYouSure() == 1 && newDuration > 0 && newDuration < 1000)
	{
		printf("\n\n");
		thePlayToModify->data.duration = newDuration;
		printMiddleAddjusted("Duration updated!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		if (newDuration <= 0 || newDuration >= 1000)
		{
			printMiddleAddjusted("Invalid new duration!", 22);
			printf("\n");
		}
		printMiddleAddjusted("Duration not changed!", 22);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

void play_UI_changeStartAndEndDate(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Date", 12);
	printf("\n\n");
	printMiddleAddjusted("Please input the new start date and end date of the play", 57);
	printf("\n");
	printMiddleAddjusted("Relevant tickets and schedules will be modified!", 49);
	printf("\n\n");

	char inputSpace[10];

	user_date_t inputStart;
	user_date_t inputEnd;

	printMultipleTimes(' ', 24);
	printf("Start Date:");
	printMultipleTimes(' ', 6);
	printf("Year: ");
	inputNumber(inputSpace, 4, 1);
	inputStart.year = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Month: ");
	inputNumber(inputSpace, 2, 1);
	inputStart.month = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Day: ");
	inputNumber(inputSpace, 2, 1);
	inputStart.day = atoi(inputSpace);

	printMultipleTimes(' ', 24);
	printf("  End Date:");
	printMultipleTimes(' ', 6);
	printf("Year: ");
	inputNumber(inputSpace, 4, 1);
	inputEnd.year = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Month: ");
	inputNumber(inputSpace, 2, 1);
	inputEnd.month = atoi(inputSpace);
	printMultipleTimes(' ', 1);
	printf("Day: ");
	inputNumber(inputSpace, 2, 1);
	inputEnd.day = atoi(inputSpace);

	printf("\n\n\n");
	if (areYouSure() == 1 && validDate(inputStart) == 1 && validDate(inputEnd) == 1 && DateCmp(inputStart, inputEnd) <= 0)
	{
		printf("\n\n");

		// Return tickets
		ticket_srv_makeTicketInvalidAfterDate(inputEnd, thePlayToModify->data.ID);
		ticket_srv_makeTicketInvalidBeforeDate(inputStart, thePlayToModify->data.ID);

		// Reset schedules
		schedule_srv_makeScheduleInvalidAfterDate(inputEnd, thePlayToModify->data.ID);
		schedule_srv_makeScheduleInvalidBeforeDate(inputStart, thePlayToModify->data.ID);

		printMiddleAddjusted("Start time and end time changed!", 33);
		keyToContinue("Continue", 8);
	}
	else
	{
		if (validDate(inputStart) == 0 || validDate(inputEnd) == 0)
		{
			printMiddleAddjusted("Invalid date!", 14);
		}
		else if (DateCmp(inputStart, inputEnd) <= 0)
		{
			printMiddleAddjusted("Invalid start time or end time!", 32);
		}
		
		printMiddleAddjusted("Start time and end time not changed!", 37);
		keyToContinue("Continue", 8);
	}
}

void play_UI_changePrice(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Change Price", 13);
	printf("\n\n");
	printMiddleAddjusted("To change the price of the play, please input", 46);

	printf("\n\n");
	printMiddleLeft("New Price:", 11, 2);
	printMultipleTimes(' ', 2);

	int newPrice = inputInt();
	printf("\n\n");

	/*
	if (studio_srv_findByUsername(newName) != NULL && studio_srv_findByUsername(newName) != theStudioToModify)
	{
		printMiddleAddjusted("The name has been used! Please choose another one!", 51);
	}*/

	if (areYouSure() == 1 && newPrice > 0 && newPrice < 1000)
	{
		printf("\n\n");
		thePlayToModify->data.price = newPrice;
		printMiddleAddjusted("Price updated!", 15);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		if (newPrice <= 0 || newPrice >= 1000)
		{
			printMiddleAddjusted("Invalid new price!", 19);
			printf("\n");
		}
		printMiddleAddjusted("Pirce not changed!", 19);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

int play_UI_deletePlay(play_list_t thePlayToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Delete Play", 12);
	printf("\n\n");
	printMiddleAddjusted("The play will be deleted, relavant tickets and schedules will be forcedly returned.", 84);
	printf("\n\n");
	if (areYouSure() == 1)
	{
		printf("\n\n");
		
		// Delete tickets
		ticket_srv_deleteTicketByPlayID(thePlayToModify->data.ID);

		// Delete schedules
		schedule_srv_deleteScheduleByPlayID(thePlayToModify->data.ID);

		printMiddleAddjusted("Play deleted!", 14);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 1;
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Play not deleted!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 0;
	}
}

void play_UI_checkByID()
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
		play_UI_modifyPlay(thePlay);
	}
}

void play_UI_AddAPlay()
{
	play_t inputPlay;

	int navigation = 0;
	char inputChar = '\0';

	int nameOK = 0;
	int typeOK = 0;
	int areaOK = 0;
	int ratingOK = 0;
	int durationOK = 0;
	int dateOK = 0;
	int priceOK = 0;

	while (1)
	{
		setBackgroundColor(7);
		setFontColor(0);

		system("cls");

		printTitleWithCurrentTime("Add a Play", 11);
		printMultipleTimes('\n', 2);
		printMiddleAddjusted("Please fill in these information:", 34);
		printMultipleTimes('\n', 3);

		// Name
		printMiddleLeft("Name:", 6, 2);
		printMultipleTimes(' ', 2);
		if (nameOK == 0)
			inputAlnum(inputPlay.name, 31, 1);
		else
			printf("%s", inputPlay.name);
		printf("\n");
		nameOK = 1;
		printf("\n");

		// Type
		printMiddleLeft("Type:", 6, 2);
		printMultipleTimes(' ', 2);
		if (typeOK == 0)
			inputAlnum(inputPlay.type, 21, 1);
		else
			printf("%s", inputPlay.type);
		printf("\n");
		typeOK = 1;
		printf("\n");

		// Area
		printMiddleLeft("Area:", 6, 2);
		printMultipleTimes(' ', 2);
		if (areaOK == 0)
			inputAlnum(inputPlay.area, 11, 1);
		else
			printf("%s", inputPlay.area);
		printf("\n");
		areaOK = 1;
		printf("\n");

		// Rating
		printMiddleLeft("Rating:", 6, 2);
		printMultipleTimes(' ', 2);
		char menu[][6] = { "G", "PG", "PG-13", "R", "NC 17" };
		if (ratingOK == 0)
		{
			//inputAlnum(inputPlay.ratin, 31, 1);
			for (int whichOne = 0; whichOne < 5; whichOne++)
			{
				if (whichOne == navigation)
				{
					setBackgroundColor(0);
					setFontColor(7);
					printf("%s", menu[whichOne]);
					setBackgroundColor(7);
					setFontColor(0);
					printf(" ");
				}
				else
				{
					printf("%s", menu[whichOne]);
					printf(" ");
				}
			}

			inputChar = _getch();

			if (inputChar == 'a' || inputChar == 'A')
			{
				if (navigation > 0)
				{
					navigation--;
				}
				else
				{
					navigation = 4;
				}
			}
			else if (inputChar == 'd' || inputChar == 'D')
			{
				if (navigation < 4)
				{
					navigation++;
				}
				else
				{
					navigation = 0;
				}
			}
			else if (inputChar == 13)
			{
				ratingOK = 1;
				inputPlay.rating = navigation + 1;
			}
		}
		else
			printf("%s", menu[inputPlay.rating - 1]);
		printf("\n");

		// Duration
		printMiddleLeft("Duration:", 10, 2);
		printMultipleTimes(' ', 2);
		if (durationOK == 0)
		{
			inputPlay.duration = inputInt();
			if (inputPlay.duration > 0 && inputPlay.duration < 1000)
			{
				durationOK = 1;
			}
			else
			{
				printf("\n");
				printMiddleAddjusted("Invalid duration!", 18);
				printf("\n");
				keyToContinue("Continue", 8);
				continue;
			}
		}
		else
			printf("%d", inputPlay.duration);
		printf("\n");
		printf("\n");

		// Start date and end date
		if (dateOK == 0)
		{
			user_date_t inputStart;
			user_date_t inputEnd;

			char inputSpace[10];
			printMultipleTimes(' ', 24);
			printf("Start Date:");
			printMultipleTimes(' ', 6);
			printf("Year: ");
			inputNumber(inputSpace, 4, 1);
			inputStart.year = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			inputNumber(inputSpace, 2, 1);
			inputStart.month = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			inputNumber(inputSpace, 2, 1);
			inputStart.day = atoi(inputSpace);

			printMultipleTimes(' ', 24);
			printf("  End Date:");
			printMultipleTimes(' ', 6);
			printf("Year: ");
			inputNumber(inputSpace, 4, 1);
			inputEnd.year = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			inputNumber(inputSpace, 2, 1);
			inputEnd.month = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			inputNumber(inputSpace, 2, 1);
			inputEnd.day = atoi(inputSpace);

			printf("\n\n");
			if (validDate(inputStart) == 1 && validDate(inputEnd) == 1 && DateCmp(inputStart, inputEnd) <= 0)
			{
				inputPlay.start_date = inputStart;
				inputPlay.end_date = inputEnd;
				dateOK = 1;
			}
			else
			{
				printMiddleAddjusted("Invalid date!", 14);
				printf("\n");
				keyToContinue("Continue", 8);
				continue;
			}
		}
		else
		{
			char inputSpace[10];
			printMultipleTimes(' ', 24);
			printf("Start Date:");
			printMultipleTimes(' ', 6);
			printf("Year: ");
			printf("%d", inputPlay.start_date.year);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			printf("%d", inputPlay.start_date.month);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			printf("%d", inputPlay.start_date.day);

			printMultipleTimes(' ', 24);
			printf("  End Date:");
			printMultipleTimes(' ', 6);
			printf("Year: ");
			printf("%d", inputPlay.end_date.year);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			printf("%d", inputPlay.end_date.month);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			printf("%d", inputPlay.end_date.day);

			printf("\n\n");
		}
		

		// Price
		printMiddleLeft("Price:", 7, 2);
		printMultipleTimes(' ', 2);
		if (priceOK == 0)
		{
			inputPlay.price = inputInt();
			if (inputPlay.price > 0 && inputPlay.price < 1000)
			{
				priceOK = 1;
			}
			else
			{
				printf("\n");
				printMiddleAddjusted("Invalid price!", 15);
				printf("\n");
				keyToContinue("Continue", 8);
				continue;
			}
		}
		else
			printf("%d", inputPlay.price);
		printf("\n");
		printf("\n");
		
		printf("\n\n\n");

		if (areYouSure() == 1)
		{
			printf("\n");
			inputPlay.ID = play_srv_getID();
			inputPlay.exist = 1;
			play_srv_add(inputPlay);
			printMiddleAddjusted("Play added!", 12);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
		else
		{
			printf("\n");
			printMiddleAddjusted("Play not added!", 16);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
	}
}