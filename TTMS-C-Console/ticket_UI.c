#include <stdio.h>
#include "seat_srv.h"
#include "studio_srv.h"
#include "printChoices.h"
#include "inputMethod.h"
#include "schedule_srv.h"
#include "ticket_srv.h"
#include "account_srv.h"
#include "play_srv.h"

void ticket_UI_checkTicket(schedule_list_t theUser)
{
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	printTitleWithCurrentTime("Check by ID", 12);
	printf("\n\n");
	printMiddleAddjusted("Please input the ID of the ticket that you are looking for", 59);
	printf("\n\n");

	printMiddleLeft("ID:", 4, 2);
	printMultipleTimes(' ', 2);
	int number = inputInt();
	printf("\n\n");

	ticket_list_t theTicket = ticket_srv_findByID(number);

	if (theTicket == NULL || theTicket->data.status == TICKET_ERROR)
	{
		printMiddleAddjusted("The ticket doesn't exist!", 26);
		printf("\n\n");
		keyToContinue("go back!", 9);
		return;
	}

	setBackgroundColor(7);
	setFontColor(0);
	system("cls");
	schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
	play_list_t thePlay = play_srv_findByID(theSchedule->data.play_ID);
	studio_list_t theStudio = studio_srv_findByID(theSchedule->data.studio_ID);
	seat_list_t theSeat = seat_srv_findByID(theTicket->data.seat_ID);

	printTitleWithCurrentTime("Check by ID", 12);
	printf("\n\n");

	// Name
	printMiddleLeft("Name:", 6, 2);
	printf("  %s\n", thePlay->data.name);

	// Type
	printMiddleLeft("Type:", 6, 2);
	printf("  %s\n", thePlay->data.type);

	// Rating
	char ratings[6][10] = { " ", "G", "PG", "PG13", "R", "NC 17" };
	printMiddleLeft("Rating:", 8, 2);
	printf("  %s\n", ratings[thePlay->data.rating]);

	// Area
	printMiddleLeft("Area:", 6, 2);
	printf("  %s\n", thePlay->data.area);

	// Duration
	printMiddleLeft("Duration:", 10, 2);
	printf("  %d\n", thePlay->data.duration);

	// Start Date
	printMiddleLeft("Start Time:", 12, 2);
	printf("  %2d.%2d.%2d %2d:%2d:%d\n", theSchedule->data.date.year, theSchedule->data.date.month, theSchedule->data.date.day, theSchedule->data.time.hour, theSchedule->data.time.minute, 
		theSchedule->data.time.second);

	// Price
	printMiddleLeft("Price:", 7, 2);
	printf("  %d\n", thePlay->data.price);

	// Sold / Unsold
	printMiddleLeft("Status:", 8, 2);
	if (theTicket->data.status == TICKET_SOLD)
	{
		printf("  %s\n", "SOLD");
	}
	else
	{
		printf("  %s\n", "UNSOLD");
	}
	// Studio name
	printMiddleLeft("Studio Name:", 13, 2);
	printf("  %s\n", theStudio->data.name);
	printMiddleAddjusted("Seats:", 7);
	printf("\n");
	seat_UI_printSeatWithStar(50 - theStudio->data.rowsCount / 2, theSchedule, theSeat->data.column, theSeat->data.row);
	printf("\n");


	printf("\n");
	keyToContinue("continue", 8);
	printMiddleAddjusted("  ", 3);
}