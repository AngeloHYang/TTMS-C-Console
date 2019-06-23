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

void schedule_UI_manageSchedules(account_list_t theUser);

void schedule_UI_viewSchedulesForManager(int howManyPerPage);

void printScheduleManagerListOneLine(int whichOne, int selected);

void schedule_UI_modifySchedule(schedule_list_t theScheduleToModify);

int schedule_UI_deletePlay(schedule_list_t theScheduleToModify);
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
			//schedule_UI_checkByID();
		}
		else if (selection == 2)
		{
			//schedule_UI_AddASchedule();
		}
		else if (selection == 3)
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

	/*
	6			 89 		   5
	   playname  studioname  startDate startTime min
	   1  30  1      30    1    10    1   10    1 3  1    
	*/
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

		// ±íÍ·
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

		// ÄÚÈÝ
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
		printf("\n ¡ñ Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
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

				//schedule_UI_modifySchedule(theScheduleToModify);

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
	printf("%-4d.%-2d.%-2d", thisOne->data.date.year, thisOne->data.date.month, thisOne->data.date.day);
	printf("|");
	printf(" %-2d.%-2d.%-2d ", thisOne->data.time.hour, thisOne->data.time.minute, thisOne->data.time.second);
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
		printMultipleTimes('\n', 2);
		printf("\n");

		// ID:
		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theScheduleToModify->data.ID);
		printMultipleTimes('\n', 3);

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
		seat_UI_printSeat(50 - theStudio->data.colsCount / 2, theScheduleToModify);
		printf("\n\n");

		char result[100] = { "" };

		strcat(result, "Start time: ");
		strcat(result, theScheduleToModify->data.date.year);
		strcat(result, ".");
		strcat(result, theScheduleToModify->data.date.month);
		strcat(result, ".");
		strcat(result, theScheduleToModify->data.date.day);
		strcat(result, " ");
		strcat(result, theScheduleToModify->data.time.hour);
		strcat(result, ":");
		strcat(result, theScheduleToModify->data.time.minute);
		strcat(result, ":");
		strcat(result, theScheduleToModify->data.time.second);
		

		printMiddleAddjusted(result, strlen(result) + 1);
		printf("\n");


		if (navigation == 0)
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
		if (navigation == 1)
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
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 0)
			{
				navigation++;
			}
			else if (navigation == 1)
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
				navigation = 1;
			}
		}
		else if (inputChar == 13)
		{
			if (navigation == 0)
			{
				//Delete play
				if (schedule_UI_deletePlay(theScheduleToModify) == 1)
				{
					break;
				}
			}
			else if (navigation == 1)
			{
				break;
			}
		}
	}
}

int schedule_UI_deletePlay(schedule_list_t theScheduleToModify)
{
	;
}
