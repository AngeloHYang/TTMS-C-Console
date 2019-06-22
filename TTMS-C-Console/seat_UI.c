#include <stdio.h>
#include "seat_srv.h"
#include "studio_srv.h"
#include "printChoices.h"
#include "inputMethod.h"

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
					printf(" ");
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

		printf("\n\n\nSeat:\n");
		seat_UI_printSeatNoMovie(10, theStudioToModify->data.ID);
		printf("\n\n");

		printf("The seat     ");
		int column;
		int row;
		printf("column: ");
		column = inputInt();
		printf("    row: ");
		row = inputInt();
		printf("\n");

		seat_node_t* theSeat = seat_srv_findByRoomAndPlace(theStudioToModify->data.ID, row, column);
		seat_status_t old = theSeat->data.status;

		if (theSeat == NULL)
		{
			printf("Invalid input\n\n");
			keyToContinue("Continue", 8);
			continue;
		}

		printf("Is this seat broken, good, or nonexistent?(b/g/n): ");
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
			printf("\nInvalid input\n");
			printf("Failed to change the seat\n");
			keyToContinue("Continue", 8);
			break;
		}
		printf("\n\nPreview: \n");
		seat_UI_printSeatNoMovie(10, theSeat->data.roomID);
		printf("\n");
		if (areYouSure() == 1)
		{
			// Forcedly return tickets
			if (old == SEAT_GOOD && (theSeat->data.status == SEAT_NONE) || (theSeat->data.status == SEAT_BROKEN))
			{
				printf("Returning tickets...");
				ticket_srv_makeTicketERROR_byEndTimeAndSeat(theSeat->data.ID, currentSecond());
				printf("Done!\n");
			}
			printf("Status changed!\n");

			keyToContinue("Continue", 8);
			break;
		}
		else
		{
			printf("Status not changed!\n");
			theSeat->data.status = old;
			keyToContinue("Continue", 8);
			break;
		}
	}
}