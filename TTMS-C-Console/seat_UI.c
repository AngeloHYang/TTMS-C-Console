#include <stdio.h>
#include "seat_srv.h"
#include "studio_srv.h"
#include "printChoices.h"
#include "inputMethod.h"
#include "schedule_srv.h"
#include "ticket_srv.h"
#include "account_srv.h"

// Invalid studio return -1, else 0;
int seat_UI_printSeatNoMovie(int howManySpace, int studioID)
{
	studio_list_t thisOne = studio_srv_findByID(studioID);
	seat_list_t theSeat;
	if (thisOne != NULL)
	{
		for (int whichRow = 1; whichRow <= thisOne->data.rowsCount; whichRow++)
		{
			printMultipleTimes(' ', howManySpace);
			for (int whichColumn = 1; whichColumn <= thisOne->data.colsCount; whichColumn++)
			{
				theSeat = seat_srv_findByRoomAndPlace(studioID, whichRow, whichColumn);
				if (theSeat->data.status == SEAT_NONE)
				{
					printf("  ");
				}
				else if (theSeat->data.status == SEAT_GOOD)
				{
					printf("¨€");
				}
				else if (theSeat->data.status == SEAT_BROKEN)
				{
					printf("¢ú");
				}
			}
			printf("\n");
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

void seat_UI_changeSeat(studio_list_t theStudioToModify)
{


	int timeToExit = 0;
	int navigation = 0;
	while (timeToExit == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("Change Seat", 12);
		printf("\n\n");
		printMiddleAddjusted("If a seat has been booked, it will be forcedly returned", 56);
		printf("\n");
		printMiddleAddjusted("Seats:", 7);
		printf("\n");
		seat_UI_printSeatNoMovie(50 - theStudioToModify->data.colsCount / 2, theStudioToModify->data.ID);
		printf("\n\n");


		printf("     The seat     ");
		int column;
		int row;
		printf("column: ");
		column = inputInt();
		printf("    row: ");
		row = inputInt();
		printf("\n");

		if (row < 0 || row > theStudioToModify->data.rowsCount || column < 0 || column > theStudioToModify->data.colsCount)
		{
			printMiddleAddjusted("Invalid input", 14);
			printf("\n\n\n");
			keyToContinue("Continue", 8);
			continue;
		}

		seat_node_t* theSeat = seat_srv_findByRoomAndPlace(theStudioToModify->data.ID, row, column);
		seat_status_t old = theSeat->data.status;

		if (theSeat == NULL)
		{
			printMiddleAddjusted("Invalid input", 14);
			printf("\n\n\n");
			keyToContinue("Continue", 8);
			continue;
		}

		printMiddleAddjusted("Is this seat broken, good, or nonexistent?(b/g/n):      \b\b\b\b", 61);
		char inputOperation[30];
		inputAlnum(inputOperation, 30, 0);
		if (inputOperation[0] == 'b' || inputOperation[0] == 'B')
		{
			theSeat->data.status = SEAT_BROKEN;
		}
		else if (inputOperation[0] == 'n' || inputOperation[0] == 'N')
		{
			theSeat->data.status = SEAT_NONE;
		}
		else if (inputOperation[0] == 'g' || inputOperation[0] == 'G')
		{
			theSeat->data.status = SEAT_GOOD;
		}
		else
		{
			printf("\n");
			printMiddleAddjusted("Invalid input", 14);
			printf("\n\n\n");
			printMiddleAddjusted("Failed to change the seat\n", 27);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
		printf("\n\n");
		printMiddleAddjusted("Preview:", 9);
		printf("\n");
		seat_UI_printSeatNoMovie(50 - theStudioToModify->data.colsCount / 2, theSeat->data.roomID);
		printf("\n\n");
		if (areYouSure() == 1)
		{
			// Forcedly return tickets
			if (old == SEAT_GOOD && (theSeat->data.status == SEAT_NONE) || (theSeat->data.status == SEAT_BROKEN))
			{
				printf("\n\n");
				printMiddleAddjusted("Returning tickets...     \b\b\b\b\b", 31);
				ticket_srv_makeTicketERROR_byEndTimeAndSeat(theSeat->data.ID, currentSecond());
				printf("Done!\n");
			}
			printf("\n");
			printMiddleAddjusted("Status changed!", 16);
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
		else
		{
			printf("\n\n");
			printMiddleAddjusted("Status not changed!", 20);
			theSeat->data.status = old;
			printf("\n");
			keyToContinue("Continue", 8);
			break;
		}
	}
}

void seat_UI_printSeat(int howManySpace, schedule_list_t theSchedule)
{
	studio_list_t theStudio = studio_srv_findByID(theSchedule->data.studio_ID);
	seat_list_t theSeat;

	if (theStudio != NULL)
	{
		for (int whichRow = 1; whichRow <= theStudio->data.rowsCount; whichRow++)
		{
			printMultipleTimes(' ', howManySpace);
			for (int whichColumn = 1; whichColumn <= theStudio->data.colsCount; whichColumn++)
			{
				theSeat = seat_srv_findByRoomAndPlace(theStudio->data.ID, whichRow, whichColumn);
				if (theSeat->data.status == SEAT_NONE)
				{
					printf("  ");
				}
				else if (theSeat->data.status == SEAT_GOOD)
				{
					// Make sure if the seat is taken
					ticket_list_t theTicket = ticket_srv_findTicketByScheduleAndSeat(theSchedule, whichRow, whichColumn);
					if (theTicket->data.status == TICKET_SOLD)
						printf("¨€");
					else
						printf("¡õ");
				}
				else if (theSeat->data.status == SEAT_BROKEN)
				{
					printf("¢ú");
				}
			}
			printf("\n");
		}
	}
}

void ticket_UI_sell(schedule_list_t theSchedule, int secondNow, account_list_t theUser)
{
	int timeToExit = 0;
	
	while (timeToExit == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("Sell a ticket", 14);
		printf("\n\n");
		printMiddleAddjusted("You can't book if it's out of date", 35);

		printf("\n\n");

		int scheduleStartSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);
		if (scheduleStartSecond <= secondNow)
		{
			printMiddleAddjusted("It's out of date", 17);
			printf("\n\n");
			keyToContinue("go back", 8);
			timeToExit = 1;
			break;
		}

		printMiddleAddjusted("Seats:", 7);
		printf("\n");
		studio_list_t theStudioToModify = studio_srv_findByID(theSchedule->data.studio_ID);

		seat_UI_printSeat(50 - theStudioToModify->data.colsCount / 2, theSchedule);
		printf("\n\n");

		printMultipleTimes(' ', 20);
		printf("The seat     ");
		int column;
		int row;
		printf("column: ");
		column = inputInt();
		printf("    row: ");
		row = inputInt();
		printf("\n");
		printf("\n");
		if (areYouSure() == 1)
		{
			printf("\n\n");
			if (column < 1 || column > theStudioToModify->data.colsCount || row < 1 || row > theStudioToModify->data.rowsCount)
			{
				printMiddleAddjusted("Invalid seat!", 14);
				printf("\n\n");
				keyToContinue("go back", 8);
				break;
			}
			else
			{
				seat_list_t theSeat = seat_srv_findByRoomAndPlace(theSchedule->data.studio_ID, row, column);
				if (theSeat->data.status != SEAT_GOOD)
				{
					printMiddleAddjusted("Invalid seat!", 14);
					printf("\n\n");
					keyToContinue("go back", 8);
					break;
				}
				else
				{
					ticket_list_t theTicket = ticket_srv_findTicketByScheduleAndSeat(theSchedule, row, column);
					if (theTicket->data.status == TICKET_SOLD)
					{
						printMiddleAddjusted("Seat taken!", 12);
						printf("\n\n");
						keyToContinue("go back", 8);
						break;
					}
					else
					{
						theTicket->data.status = TICKET_SOLD;
						theTicket->data.soldBy = theUser->data.ID;
						printMiddleAddjusted("Ticket sold!", 13);
						printf("\n\n");
						keyToContinue("go back", 8);
						break;
					}
				}
			}
		}
		else
		{
			printf("\n\n");
			printMiddleAddjusted("Ticket not sold!", 17);
			printf("\n\n");
			keyToContinue("go back", 8);
			timeToExit = 1;
		}
	}
}

void ticket_UI_return(schedule_list_t theSchedule, int secondNow, account_list_t theUser)
{

}