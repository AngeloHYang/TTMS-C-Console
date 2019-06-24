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
#include "studio_srv.h"
#include "seat_UI.h"
#include "seat_srv.h"

void schedule_UI_manageSchedules(account_list_t theUser);
void schedule_UI_clerkSchedules(account_list_t theUser);

void schedule_UI_viewSchedulesForManager(int howManyPerPage);
void schedule_UI_viewSchedulesForClerk(int howManyPerPage, int secondNow, account_list_t theUser);

void printScheduleManagerListOneLine(int whichOne, int selected);
void printScheduleClerkListOneLine(int whichOne, int selected, int secondNow);

void schedule_UI_modifySchedule(schedule_list_t theScheduleToModify);
void schedule_UI_modifyScheduleClerk(schedule_list_t theScheduleToModify, int secondNow, account_list_t theUser);

void schedule_UI_changeStartTime(schedule_list_t theScheduleToModify);

int schedule_UI_deleteSchedule(schedule_list_t theScheduleToModify);

void schedule_UI_checkByID();

void schedule_UI_AddASchedule();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void schedule_UI_manageSchedules(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "View Schedules", "Check by ID", "Add a Schedule", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2], Menu[3] };

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Schedule Management", "Add, modify, or delete a schedule", 34, pointers, 4, 100);

		if (selection == 0)
		{
			schedule_UI_viewSchedulesForManager(10);
		}
		else if (selection == 1)
		{
			schedule_UI_checkByID();
		}
		else if (selection == 2)
		{
			schedule_UI_AddASchedule();
		}
		else if (selection == 3)
		{
			toReturn = 1;
		}
	}
	free(greet);
}

void schedule_UI_clerkSchedules(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "View Schedules", "Check by ID", "Return" };

	char* pointers[] = { Menu[0], Menu[1], Menu[2] };

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Check Schedules", "Check a schedule, sell or return a ticket", 42, pointers, 3, 100);

		if (selection == 0)
		{
			schedule_UI_viewSchedulesForClerk(10, currentSecond(), theUser);
		}
		else if (selection == 1)
		{
			//schedule_UI_checkByIDClerk(currentSecond());
		}
		else if (selection == 2)
		{
			toReturn = 1;
		}
	}
	free(greet);
}


void schedule_UI_viewSchedulesForManager(int howManyPerPage)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (schedule_srv_howManyInToto() % howManyPerPage == 0)
	{
		pageSum = schedule_srv_howManyInToto() / howManyPerPage;
	}
	else
	{
		pageSum = schedule_srv_howManyInToto() / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';

	//
	//6			 89 		   5
	//	playname  studioname  startDate startTime min
	//   1  30  1      30    1    10    1   10    1 3  1    
	//
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Schedules", 15);
		printMultipleTimes('\n', 3);

		if (schedule_srv_howManyInToto() == 0)
		{
			printMiddleAddjusted("No schedules now!", 18);
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

		// 表头
		printMultipleTimes(' ', 6);
		printf("|");
		printf("%-30s", "Play Name");
		printf("|");
		printf("%-30s", "Studio Name");
		printf("|");
		printf("%-10s", "Date");
		printf("|");
		printf("%-10s", "Time");
		printf("|");
		printf("%-3s", "Min");  // Duration
		printf("|");

		printf("\n");
		printMultipleTimes(' ', 6);
		printMultipleTimes('-', 89);
		printf("\n");

		// 内容
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(schedule_srv_howManyInToto(), currentPage * howManyPerPage); whichOneToPrint++)
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

				printScheduleManagerListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printScheduleManagerListOneLine(whichOneToPrint, 0);
			}
		}

		// Return button
		if ((schedule_srv_howManyInToto() % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (schedule_srv_howManyInToto() % howManyPerPage)) * 2);
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
				if (schedule_srv_howManyInToto() % howManyPerPage != 0)
				{
					selection = (schedule_srv_howManyInToto() % howManyPerPage);
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
				if ((schedule_srv_howManyInToto() % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (schedule_srv_howManyInToto() % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (schedule_srv_howManyInToto() % howManyPerPage))
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
				if (currentPage == pageSum && selection > (schedule_srv_howManyInToto() % howManyPerPage))
				{
					selection = schedule_srv_howManyInToto() % howManyPerPage;
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
				schedule_node_t* theScheduleToModify = schedule_srv_findByWhichOne(theOneToModify);

				schedule_UI_modifySchedule(theScheduleToModify);

				// Update page sum
				if (schedule_srv_howManyInToto() % howManyPerPage == 0)
				{
					pageSum = schedule_srv_howManyInToto() / howManyPerPage;
				}
				else
				{
					pageSum = schedule_srv_howManyInToto() / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (schedule_srv_howManyInToto() % howManyPerPage == 0)
		{
			pageSum = schedule_srv_howManyInToto() / howManyPerPage;
		}
		else
		{
			pageSum = schedule_srv_howManyInToto() / howManyPerPage + 1;
		}
	}
}

void schedule_UI_viewSchedulesForClerk(int howManyPerPage, int secondNow, account_list_t theUser)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (schedule_srv_howManyAvailable(secondNow) % howManyPerPage == 0)
	{
		pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage;
	}
	else
	{
		pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';

	//
	//6			 89 		   5
	//	playname  studioname  startDate startTime min
	//   1  30  1      30    1    10    1   10    1 3  1    
	//
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Schedules", 15);
		printMultipleTimes('\n', 3);

		if (schedule_srv_howManyAvailable(secondNow) == 0)
		{
			printMiddleAddjusted("No schedules now!", 18);
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

		// 表头
		printMultipleTimes(' ', 6);
		printf("|");
		printf("%-30s", "Play Name");
		printf("|");
		printf("%-30s", "Studio Name");
		printf("|");
		printf("%-10s", "Date");
		printf("|");
		printf("%-10s", "Time");
		printf("|");
		printf("%-3s", "Min");  // Duration
		printf("|");

		printf("\n");
		printMultipleTimes(' ', 6);
		printMultipleTimes('-', 89);
		printf("\n");

		// 内容
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(schedule_srv_howManyAvailable(secondNow), currentPage * howManyPerPage); whichOneToPrint++)
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

				printScheduleClerkListOneLine(whichOneToPrint, 1, TimeNow);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printScheduleClerkListOneLine(whichOneToPrint, 0, TimeNow);
			}
		}

		// Return button
		if ((schedule_srv_howManyAvailable(secondNow) % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (schedule_srv_howManyAvailable(secondNow) % howManyPerPage)) * 2);
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
				if (schedule_srv_howManyAvailable(secondNow) % howManyPerPage != 0)
				{
					selection = (schedule_srv_howManyAvailable(secondNow) % howManyPerPage);
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
				if ((schedule_srv_howManyAvailable(secondNow) % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (schedule_srv_howManyAvailable(secondNow) % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (schedule_srv_howManyAvailable(secondNow) % howManyPerPage))
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
				if (currentPage == pageSum && selection > (schedule_srv_howManyAvailable(secondNow) % howManyPerPage))
				{
					selection = schedule_srv_howManyAvailable(secondNow) % howManyPerPage;
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
				schedule_node_t* theScheduleToModify = schedule_srv_findByWhichOneAvailable(theOneToModify, secondNow);

				schedule_UI_modifyScheduleClerk(theScheduleToModify, secondNow, theUser);

				// Update page sum
				if (schedule_srv_howManyAvailable(secondNow) % howManyPerPage == 0)
				{
					pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage;
				}
				else
				{
					pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (schedule_srv_howManyAvailable(secondNow) % howManyPerPage == 0)
		{
			pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage;
		}
		else
		{
			pageSum = schedule_srv_howManyAvailable(secondNow) / howManyPerPage + 1;
		}
	}
}


void printScheduleManagerListOneLine(int whichOne, int selected)
{
	schedule_node_t* thisOne = schedule_srv_findByWhichOne(whichOne);
	

	printMultipleTimes(' ', 6);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}
	printf("|");
	printf("%-30s", play_srv_findByID(thisOne->data.play_ID)->data.name);
	printf("|");
	printf("%-30s", studio_srv_findByID(thisOne->data.studio_ID)->data.name);
	printf("|");
	printf("%4d.%2d.%2d", thisOne->data.date.year, thisOne->data.date.month, thisOne->data.date.day);
	printf("|");
	printf(" %-2d:%-2d:%-2d ", thisOne->data.time.hour, thisOne->data.time.minute, thisOne->data.time.second);
	printf("|");
	printf("%-3d", play_srv_findByID(thisOne->data.play_ID)->data.duration);
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

void printScheduleClerkListOneLine(int whichOne, int selected, int secondNow)
{
	schedule_node_t* thisOne = schedule_srv_findByWhichOneAvailable(whichOne, secondNow);


	printMultipleTimes(' ', 6);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}
	printf("|");
	printf("%-30s", play_srv_findByID(thisOne->data.play_ID)->data.name);
	printf("|");
	printf("%-30s", studio_srv_findByID(thisOne->data.studio_ID)->data.name);
	printf("|");
	printf("%4d.%2d.%2d", thisOne->data.date.year, thisOne->data.date.month, thisOne->data.date.day);
	printf("|");
	printf(" %-2d:%-2d:%-2d ", thisOne->data.time.hour, thisOne->data.time.minute, thisOne->data.time.second);
	printf("|");
	printf("%-3d", play_srv_findByID(thisOne->data.play_ID)->data.duration);
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

void schedule_UI_modifySchedule(schedule_list_t theScheduleToModify)
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
		printTitleWithCurrentTime("Modify Schedule", 16);
		printf("\n");

		// ID:
		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theScheduleToModify->data.ID);
		printMultipleTimes('\n', 1);

		// Play:
		play_list_t thePlay = play_srv_findByID(theScheduleToModify->data.play_ID);
		printMiddleLeft("Play Name:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.name);
		printMiddleLeft("Play Type:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.type);
		printMiddleLeft("Play Area:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.area);
		printMiddleLeft("Play Rating:", 13, 2);
		// Ratings result
		char ratings[6];
		if (thePlay->data.rating == PLAY_RATE_G)
		{
			strcpy(ratings, "G");
		}
		else if (thePlay->data.rating == PLAY_RATE_PG)
		{
			strcpy(ratings, "PG");
		}
		else if (thePlay->data.rating == PLAY_RATE_PG13)
		{
			strcpy(ratings, "PG13");
		} if (thePlay->data.rating == PLAY_RATE_R)
		{
			strcpy(ratings, "R");
		} if (thePlay->data.rating == PLAY_RATE_NC_17)
		{
			strcpy(ratings, "NC 17");
		}
		printf("  ");
		printf("%s\n", ratings);
		printMiddleLeft("Play Duration:", 15, 2);
		printf("  ");
		printf("%d\n", thePlay->data.duration);
		printMiddleLeft("Play Price:", 12, 2);
		printf("  ");
		printf("%d\n", thePlay->data.price);
		printf("\n");

		// Studio
		studio_list_t theStudio = studio_srv_findByID(theScheduleToModify->data.studio_ID);
		printMiddleLeft("Studio ID:", 11, 2);
		printf("  %d\n", theStudio->data.ID);
		printMiddleLeft("Studio Name:", 13, 2);
		printf("  %s\n", theStudio->data.name);
		printMiddleAddjusted("Seat:", 6);
		printf("\n");
		seat_UI_printSeat((100 - theStudio->data.colsCount) / 2, theScheduleToModify);
		printf("\n\n");

		char result[100] = { "" };
		char swapArea[100];

		if (navigation == 0)
		{
			setBackgroundColor(0);
			setFontColor(7);
			setBackgroundColor(7);
			setFontColor(0);
			strcat(result, "Start time: ");
			_itoa(theScheduleToModify->data.date.year, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ".");
			_itoa(theScheduleToModify->data.date.month, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ".");
			_itoa(theScheduleToModify->data.date.day, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, " ");
			_itoa(theScheduleToModify->data.time.hour, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ":");
			_itoa(theScheduleToModify->data.time.minute, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ":");
			_itoa(theScheduleToModify->data.time.second, swapArea, 10);
			strcat(result, swapArea);
			printMultipleTimes(' ', 50 - strlen(result) / 2);
			setBackgroundColor(0);
			setFontColor(7);
			printf("%s", result);
			//printMiddleAddjusted(result, strlen(result) + 1);
			setBackgroundColor(7);
			setFontColor(0);
			printf("\n");
		}
		else
		{
			strcat(result, "Start time: ");
			_itoa(theScheduleToModify->data.date.year, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ".");
			_itoa(theScheduleToModify->data.date.month, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ".");
			_itoa(theScheduleToModify->data.date.day, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, " ");
			_itoa(theScheduleToModify->data.time.hour, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ":");
			_itoa(theScheduleToModify->data.time.minute, swapArea, 10);
			strcat(result, swapArea);
			strcat(result, ":");
			_itoa(theScheduleToModify->data.time.second, swapArea, 10);
			strcat(result, swapArea);
			//printMiddleAddjusted(result, strlen(result) + 1);
			printMultipleTimes(' ', 50 - strlen(result) / 2);
			printf("%s", result);
			printf("\n");
		}


		

		if (navigation == 1)
		{
			printMultipleTimes(' ', 50 - strlen("Delete"));
			setBackgroundColor(0);
			setFontColor(7);
			printf("Delete");
			setBackgroundColor(7);
			setFontColor(0);
		}
		else
		{
			printMultipleTimes(' ', 50 - strlen("Delete"));

			printf("Delete");

		}
		printf("\n\n");
		if (navigation == 2)
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

		print_(100);
		printf("\n\n ● Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 2)
			{
				navigation++;
			}
			else if (navigation == 2)
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
				navigation = 2;
			}
		}
		else if (inputChar == 13)
		{
			if (navigation == 0)
			{
				schedule_UI_changeStartTime(theScheduleToModify);
			}
			else if (navigation == 1)
			{
				//Delete schedule
				if (schedule_UI_deleteSchedule(theScheduleToModify) == 1)
				{
					break;
				}
			}
			else if (navigation == 2)
			{
				break;
			}
		}
	}
}

void schedule_UI_modifyScheduleClerk(schedule_list_t theScheduleToModify, int secondNow, account_list_t theUser)
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
		printTitleWithCurrentTime("View Schedule", 14);
		printf("\n");

		// ID:
		printMiddleLeft("Schedule ID:", 13, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theScheduleToModify->data.ID);
		printMultipleTimes('\n', 1);

		// Play:
		play_list_t thePlay = play_srv_findByID(theScheduleToModify->data.play_ID);
		printMiddleLeft("Play Name:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.name);
		printMiddleLeft("Play Type:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.type);
		printMiddleLeft("Play Area:", 11, 2);
		printf("  ");
		printf("%s\n", thePlay->data.area);
		printMiddleLeft("Play Rating:", 13, 2);
		// Ratings result
		char ratings[6];
		if (thePlay->data.rating == PLAY_RATE_G)
		{
			strcpy(ratings, "G");
		}
		else if (thePlay->data.rating == PLAY_RATE_PG)
		{
			strcpy(ratings, "PG");
		}
		else if (thePlay->data.rating == PLAY_RATE_PG13)
		{
			strcpy(ratings, "PG13");
		} if (thePlay->data.rating == PLAY_RATE_R)
		{
			strcpy(ratings, "R");
		} if (thePlay->data.rating == PLAY_RATE_NC_17)
		{
			strcpy(ratings, "NC 17");
		}
		printf("  ");
		printf("%s\n", ratings);
		printMiddleLeft("Play Duration:", 15, 2);
		printf("  ");
		printf("%d\n", thePlay->data.duration);
		printMiddleLeft("Play Price:", 12, 2);
		printf("  ");
		printf("%d\n", thePlay->data.price);
		printf("\n");

		// Studio
		studio_list_t theStudio = studio_srv_findByID(theScheduleToModify->data.studio_ID);
		printMiddleLeft("Studio ID:", 11, 2);
		printf("  %d\n", theStudio->data.ID);
		printMiddleLeft("Studio Name:", 13, 2);
		printf("  %s\n", theStudio->data.name);
		printMiddleAddjusted("Seat:", 6);
		printf("\n");
		seat_UI_printSeat((100 - theStudio->data.colsCount) / 2, theScheduleToModify);
		printf("\n\n");

		char result[100] = { "" };
		char swapArea[100];

		
		strcat(result, "Start time: ");
		_itoa(theScheduleToModify->data.date.year, swapArea, 10);
		strcat(result, swapArea);
		strcat(result, ".");
		_itoa(theScheduleToModify->data.date.month, swapArea, 10);
		strcat(result, swapArea);
		strcat(result, ".");
		_itoa(theScheduleToModify->data.date.day, swapArea, 10);
		strcat(result, swapArea);
		strcat(result, " ");
		_itoa(theScheduleToModify->data.time.hour, swapArea, 10);
		strcat(result, swapArea);
		strcat(result, ":");
		_itoa(theScheduleToModify->data.time.minute, swapArea, 10);
		strcat(result, swapArea);
		strcat(result, ":");
		_itoa(theScheduleToModify->data.time.second, swapArea, 10);
		strcat(result, swapArea);
		//printMiddleAddjusted(result, strlen(result) + 1);
		printMultipleTimes(' ', 50 - (strlen(result) / 2));
		printf("%s", result);
		printf("\n\n");
	

		if (navigation == 0)
		{
			printMultipleTimes(' ', 50 - strlen("Sell a Ticket")/2);
			setBackgroundColor(0);
			setFontColor(7);
			printf("Sell a Ticket");
			setBackgroundColor(7);
			setFontColor(0);
		}
		else
		{
			printMultipleTimes(' ', 50 - strlen("Sell a Ticket")/2);

			printf("Sell a Ticket");

		}
		printf("\n\n");

		if (navigation == 1)
		{
			printMultipleTimes(' ', 50 - strlen("Return a Ticket")/2);
			setBackgroundColor(0);
			setFontColor(7);
			printf("Return a Ticket");
			setBackgroundColor(7);
			setFontColor(0);
		}
		else
		{
			printMultipleTimes(' ', 50 - strlen("Return a Ticket")/2);

			printf("Return a Ticket");

		}
		printf("\n\n");

		if (navigation == 2)
		{
			printMultipleTimes(' ', 50 - strlen("Return")/2);
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

		print_(100);
		printf("\n\n ● Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 2)
			{
				navigation++;
			}
			else if (navigation == 2)
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
				navigation = 2;
			}
		}
		else if (inputChar == 13)
		{
			if (navigation == 0)
			{
				// Sell a ticket
				ticket_UI_sell(theScheduleToModify, secondNow, theUser);
			}
			else if (navigation == 1)
			{
				ticket_UI_return(theScheduleToModify, secondNow, theUser);
			}
			else if (navigation == 2)
			{
				break;
			}
		}
	}
}

int schedule_UI_deleteSchedule(schedule_list_t theScheduleToModify)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Delete Schedule", 16);
	printf("\n\n");
	printMiddleAddjusted("The scheulde will be deleted, all relevant tickets will be returned.", 69);
	printf("\n\n");
	if (areYouSure() == 1)
	{
		printf("\n\n");

		// Delete tickets
		
		ticket_srv_deleteTicketBySchedule(theScheduleToModify->data.ID);

		// Delete schedules
		theScheduleToModify->data.exist = 0;

		printMiddleAddjusted("Schedule deleted!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 1;
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Schedule not deleted!", 22);
		printf("\n\n");
		keyToContinue("Continue", 8);
		return 0;
	}
}

void schedule_UI_changeStartTime(schedule_list_t theScheduleToModify)
{
	// Time
	int timeAndDateOK = 0;
	while (1)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("Change Start Time", 18);
		printf("\n\n");
		printMiddleAddjusted("Please input the new start date and time of the schedule", 57);
		printf("\n\n");

		printMultipleTimes(' ', 20);
		printf("Schedule Date:");
		printMultipleTimes(' ', 2);
		user_date_t inputDate;
		user_time_t inputTime;
		if (timeAndDateOK == 0)
		{

			char inputSpace[10];
			printf("Year: ");
			inputNumber(inputSpace, 5, 1);
			inputDate.year = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			inputNumber(inputSpace, 3, 1);
			inputDate.month = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			inputNumber(inputSpace, 3, 1);
			inputDate.day = atoi(inputSpace);
			printf("\n");

			printMultipleTimes(' ', 36);

			printf("Hour: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.hour = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Minute: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.minute = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Second: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.second = atoi(inputSpace);
			printf("\n");

			timeAndDateOK = 1;
		}

		printf("\n\n\n");

		if (areYouSure() == 1)
		{
			printf("\n");

			user_time_t a = { 0, 0, 0 };
			user_time_t b = { 23, 59, 59 };

			// Preparation
			play_list_t thePlay = play_srv_findByID(theScheduleToModify->data.play_ID);
			schedule_t aNewSchedule = schedule_srv_generate(theScheduleToModify->data.ID, theScheduleToModify->data.play_ID, theScheduleToModify->data.studio_ID, inputDate, inputTime);

			// Check Date
			if (validDate(inputDate) == 0 || validTime(inputTime) == 0 || DateAndTimeCmp(inputDate, inputTime, thePlay->data.start_date, a) == -1 || DateAndTimeCmp(inputDate, inputTime, thePlay->data.end_date, b) == 1)
			{
				printMiddleAddjusted("Invalid time or date!", 22);
				printf("\n");

				keyToContinue("Continue", 8);
				timeAndDateOK = 0;
				continue;
			}
			// Check oterh schedules
			else if (schedule_srv_checkIfConflictsWithOtherSchedules(aNewSchedule) == 0)
			{
				printMiddleAddjusted("Date or time conflicts!", 24);
				printf("\n");
				keyToContinue("Continue", 8);
				timeAndDateOK = 0;
				continue;
			}
			else
			{
				theScheduleToModify->data.date = inputDate;
				theScheduleToModify->data.time = inputTime;
				printMiddleAddjusted("Time and date modified!", 24);
				printf("\n");
				keyToContinue("Continue", 8);
				break;
			}
		}
		else
		{
			printf("\n");
			printMiddleAddjusted("Time and date not modified!", 28);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
	}
}

void schedule_UI_checkByID()
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Check by ID", 12);
	printf("\n\n");
	printMiddleAddjusted("Please input the ID of the schedule that you are looking for", 61);
	printf("\n\n");

	printMiddleLeft("ID:", 4, 2);
	printMultipleTimes(' ', 2);
	int number = inputInt();

	schedule_list_t theSchedule = schedule_srv_findByID(number);
	printMultipleTimes('\n', 2);
	if (theSchedule == NULL)
	{
		printMiddleAddjusted("The schedule doesn't exist!", 28);
		printf("\n\n");
		keyToContinue("go back", 7);
	}
	else
	{
		schedule_UI_modifySchedule(theSchedule);
	}
}

void schedule_UI_AddASchedule()
{
	schedule_t inputSchedule;

	int navigation = 0;
	char inputChar = '\0';

	int playOK = 0;
	int studioOK = 0;
	int timeAndDateOK = 0;

	play_list_t thePlay;
	studio_list_t theStudio;

	
	while (1)
	{
		setBackgroundColor(7);
		setFontColor(0);

		system("cls");

		printTitleWithCurrentTime("Add a Schedule", 15);
		printMultipleTimes('\n', 2);
		printMiddleAddjusted("Please fill in these information:", 34);
		printMultipleTimes('\n', 3);

		// Play ID
		printMiddleLeft("Play ID:", 9, 2);
		printMultipleTimes(' ', 2);
		if (playOK == 0)
		{
			inputSchedule.play_ID = inputInt();
			thePlay = play_srv_findByID(inputSchedule.play_ID);
			if (thePlay != NULL)
			{
				playOK = 1;
				printf("\n");
				printMiddleLeft("Play Name:", 11, 2);
				printf("  ");
				printf("%s\n", thePlay->data.name);
				printMiddleLeft("Date:", 6, 2);
				printf("  ");
				printf("%4d.%2d.%2d to %4d.%2d.%2d\n", thePlay->data.start_date.year, thePlay->data.start_date.month, thePlay->data.start_date.day, thePlay->data.end_date.year, thePlay->data.end_date.month, thePlay->data.end_date.day);
				printf("\n");
			}
			else
			{
				printf("\n");
				printMiddleAddjusted("Invalid play!", 14);
				printf("\n");
				keyToContinue("Continue", 8);
				continue;
			}
		}
		else
		{
			thePlay = play_srv_findByID(inputSchedule.play_ID);
			printf("%d", thePlay->data.ID);
			printf("\n");
			printMiddleLeft("Play Name:", 11, 2);
			printf("  ");
			printf("%s\n", thePlay->data.name);
			printMiddleLeft("Date:", 6, 2);
			printf("  ");
			printf("%4d.%2d.%2d to %4d.%2d.%2d\n", thePlay->data.start_date.year, thePlay->data.start_date.month, thePlay->data.start_date.day, thePlay->data.end_date.year, thePlay->data.end_date.month, thePlay->data.end_date.day);
			printf("\n");
		}
		printf("\n");
		printf("\n");

		// Studio ID
		printMiddleLeft("Studio ID:", 11, 2);
		printMultipleTimes(' ', 2);
		if (studioOK == 0)
		{
			inputSchedule.studio_ID = inputInt();
			theStudio = studio_srv_findByID(inputSchedule.studio_ID);
			if (theStudio != NULL)
			{
				studioOK = 1;
				printf("\n");
				printMiddleLeft("Studio Name:", 13, 2);
				printf("  ");
				printf("%s\n", theStudio->data.name);
				printMiddleAddjusted("Seats:", 7);
				printf("\n");
				seat_UI_printSeatNoMovie(50 - theStudio->data.colsCount / 2, theStudio->data.ID);
				printf("\n");
			}
			else
			{
				printf("\n");
				printMiddleAddjusted("Invalid studio!", 16);
				printf("\n");
				keyToContinue("Continue", 8);
				continue;
			}
		}
		else
		{
			theStudio = studio_srv_findByID(inputSchedule.studio_ID);
			printf("%d", theStudio->data.ID);
			printf("\n");
			printMiddleLeft("Studio Name:", 13, 2);
			printf("  ");
			printf("%s\n", theStudio->data.name);
			printMiddleAddjusted("Seats:", 7);
			printf("\n");
			seat_UI_printSeatNoMovie(50 - theStudio->data.colsCount / 2, theStudio->data.ID);
			printf("\n");
		}
		printf("\n");
		printf("\n");

		// Time
		printMultipleTimes(' ', 20);
		printf("Schedule Date:");
		printMultipleTimes(' ', 2);
		if (timeAndDateOK == 0)
		{
			user_date_t inputDate;
			user_time_t inputTime;

			char inputSpace[10];
			printf("Year: ");
			inputNumber(inputSpace, 5, 1);
			inputDate.year = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Month: ");
			inputNumber(inputSpace, 3, 1);
			inputDate.month = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Day: ");
			inputNumber(inputSpace, 3, 1);
			inputDate.day = atoi(inputSpace);
			printf("\n");

			printMultipleTimes(' ', 36);

			printf("Hour: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.hour = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Minute: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.minute = atoi(inputSpace);
			printMultipleTimes(' ', 1);
			printf("Second: ");
			inputNumber(inputSpace, 3, 1);
			inputTime.second = atoi(inputSpace);
			printf("\n");

			timeAndDateOK = 1;

			inputSchedule.date = inputDate;
			inputSchedule.time = inputTime;
		}

		printf("\n\n\n");

		if (areYouSure() == 1)
		{
			printf("\n");
			
			user_time_t a = { 0, 0, 0 };
			user_time_t b = { 23, 59, 59 };
			// Check Date
			if (validDate(inputSchedule.date) == 0 || validTime(inputSchedule.time) == 0 || DateAndTimeCmp(inputSchedule.date, inputSchedule.time, thePlay->data.start_date, a) == -1 || DateAndTimeCmp(inputSchedule.date, inputSchedule.time, thePlay->data.end_date, b) == 1)
			{
				printMiddleAddjusted("Invalid time or date!", 22);
				printf("\n");
				
				keyToContinue("Continue", 8);
				timeAndDateOK = 0;
				continue;
			}
			// Check oterh schedules
			else if (schedule_srv_checkIfConflictsWithOtherSchedules(inputSchedule) == 0)
			{
				printMiddleAddjusted("Date or time conflicts!", 24);
				printf("\n");
				keyToContinue("Continue", 8);
				timeAndDateOK = 0;
				continue;
			}
			else
			{
				inputSchedule.ID = schedule_srv_getID();
				inputSchedule.exist = 1;
				schedule_srv_add(inputSchedule);

				// Generate tickets
				for (int whichRow = 1; whichRow <= theStudio->data.rowsCount; whichRow++)
				{
					for (int whichColumn = 1; whichColumn <= theStudio->data.colsCount; whichColumn++)
					{
						seat_list_t theSeat = seat_srv_findByRoomAndPlace(theStudio->data.ID, whichRow, whichColumn);
						if (theSeat->data.status != SEAT_BROKEN)
						{
							ticket_t aTicket = ticket_srv_generate(ticket_srv_getID(), inputSchedule.ID, theSeat->data.ID, -1, TICKET_UNSOLD);
							ticket_srv_add(aTicket);
						}
					}
				}

				printMiddleAddjusted("Schedule added!", 16);
				printf("\n");
				keyToContinue("Continue", 8);
				break;
			}
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
