#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"
#include "ticket_srv.h"
#include "basicMove.h"
#include "common.h"
#include "schedule_srv.h"
#include "timeRelated.h"
#include "play_srv.h"
#include "seat_srv.h"
#include "studio_srv.h"
#include "account_srv.h"

// 生成新增Ticket的ID，返回并加1
int ticket_srv_getID()
{
	newID(ticket_unassignedID);
}

//用于生成一个ticket_t，注意返回值
ticket_t ticket_srv_generate(int ID, int schedule_ID, int seat_ID, int soldBy, ticket_status_t status)
{
	ticket_t thisOne;
	thisOne.ID = ID;
	thisOne.schedule_ID = schedule_ID;
	thisOne.seat_ID = seat_ID;
	//thisOne.price = price;
	thisOne.soldBy = soldBy;
	thisOne.status = status;
	return thisOne;
}


void ticket_srv_add(ticket_t inputTicket_t) //ticket的添加
{
	type_srv_add(ticket_t, inputTicket_t, ticket_node_t, ticket_head);
}

//按照ID查找，返回ticket_list_t.没找到则返回NULL
ticket_list_t ticket_srv_findByID(int inputID)
{
	//type_srv_findByID(ticket_t, inputID, ticket_node_t, ticket_head);
	ticket_node_t* thisOne = ticket_head->next;
	while (thisOne != ticket_head)
	{
		if (thisOne->data.ID == inputID && thisOne->data.status != TICKET_ERROR)
		{
			return thisOne; 
		}
		thisOne = thisOne->next; 
	}
	return NULL;
}

//删除ticket，不解决删除ticket引起的其他问题
// 删除成功返回1,否则0
int ticket_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(ticket_node_t, ticket_srv_findByID(inputID));
}

//输入ticket_t以修改
// 修改成功返回1,否则0
int ticket_srv_modifyByTicket_t(ticket_t inputTicket_t)
{
	type_srv_modifyByType_t(ticket_t, inputTicket_t, ticket_node_t, ticket_srv_findByID(inputTicket_t.ID));
}

void ticket_srv_printAll()
{
	ticket_list_t swap = ticket_head->next;
	int counter = 1;
	while (swap != ticket_head)
	{
		printf("ID: %d\n", swap->data.ID);
			//printf("Price: %d\n", swap->data.price);
		counter++;
		swap = swap->next;
	}
}

void ticket_srv_makeTicketERROR_byEndTimeAndSeat(int seatID, int currentSecond)
{
	ticket_list_t theTicket = ticket_head->next;
	
	while (theTicket != ticket_head)
	{
		schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
		if (theSchedule != NULL && theTicket->data.seat_ID == seatID)
		{
			int startSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);
			play_list_t thePlay = play_srv_findByID(theSchedule->data.play_ID);
			if (startSecond + thePlay->data.duration * 60 > currentSecond)
			{
				theTicket->data.status = TICKET_ERROR;
			}
		}
		theTicket = theTicket->next;
	}
}

void ticket_srv_makeTicketInvalidAfterDate(user_date_t byDateAfter, int playID)
{
	ticket_node_t* theTicket = ticket_head->next;
	while (theTicket != ticket_head)
	{
		schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
		if (theSchedule != NULL && theSchedule->data.play_ID == playID)
		{
			int scheduleStartSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);

			user_time_t swapTime = { 23, 59, 59 };
			int targetSecond = user_date_t_And_user_time_t_ToSecond(byDateAfter, swapTime);
			if (scheduleStartSecond > targetSecond)
			{
				theTicket->data.status = TICKET_ERROR;
			}
		}
		theTicket = theTicket->next;
	}
}

void ticket_srv_makeTicketInvalidBeforeDate(user_date_t byDateBefore, int playID)
{
	ticket_node_t* theTicket = ticket_head->next;
	while (theTicket != ticket_head)
	{
		schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
		if (theSchedule != NULL && theSchedule->data.play_ID == playID)
		{
			int scheduleStartSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);

			user_time_t swapTime = { 0, 0, 0 };
			int targetSecond = user_date_t_And_user_time_t_ToSecond(byDateBefore, swapTime);
			if (scheduleStartSecond < targetSecond)
			{
				theTicket->data.status = TICKET_ERROR;
			}
		}
		theTicket = theTicket->next;
	}
}

void ticket_srv_deleteTicketByPlayID(int playID)
{
	ticket_list_t theTicket = ticket_head->next;
	while (theTicket != ticket_head)
	{
		schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
		if (theSchedule != NULL && theSchedule->data.play_ID == playID)
		{
			theTicket->data.status = TICKET_ERROR;
		}
		theTicket = theTicket->next;
	}
}

ticket_list_t ticket_srv_findTicketByScheduleAndSeat(schedule_list_t theSchedule, int whichRow, int whichColumn)
{
	ticket_list_t theTicket = ticket_head->next;
	while (theTicket != ticket_head)
	{
		if (theTicket->data.schedule_ID == theSchedule->data.ID && theTicket->data.status != TICKET_ERROR)
		{
			seat_list_t theSeat = seat_srv_findByID(theTicket->data.seat_ID);
			if (theSeat->data.row == whichRow && theSeat->data.column == whichColumn)
			{
				return theTicket;
			}
		}
		theTicket = theTicket->next;
	}
	return NULL;
}

void ticket_srv_deleteTicketBySchedule(int scheduleID)
{
	schedule_list_t theSchedule = schedule_srv_findByID(scheduleID);

	studio_list_t theStudio = studio_srv_findByID(theSchedule->data.studio_ID);

	for (int whichRow = 1; whichRow <= theStudio->data.rowsCount; whichRow++ )
	{
		for (int whichColumn = 1; whichColumn <= theStudio->data.colsCount; whichColumn++)
		{
			ticket_list_t theTicket = ticket_srv_findTicketByScheduleAndSeat(theSchedule, whichRow, whichColumn);
			if (theTicket != NULL)
			{
				theTicket->data.status = TICKET_ERROR;
			}
		}
	}
}

int ticket_srv_playIDReturnSoldNumber(int playID)
{
	int counter = 0;
	ticket_list_t theTicket = ticket_head->next;
	while (theTicket != ticket_head)
	{
		schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
		if (theTicket->data.status == TICKET_SOLD)
		{
			if (theSchedule != NULL && theSchedule->data.play_ID == playID)
			{
				counter++;
			}
		}
		theTicket = theTicket->next;
	}
	return counter;
}

void ticket_srv_clerkIDAndDateToSoldNumberAndTotal(int clerkID, user_date_t startDate, user_date_t endDate, int* sold, int* total)
{
	account_node_t* theAccount = account_srv_findByID(clerkID);
	ticket_list_t theTicket = ticket_head->next;
	*sold = 0;
	*total = 0;

	while (theTicket != ticket_head)
	{
		if (theTicket->data.soldBy == clerkID && theTicket->data.status == TICKET_SOLD)
		{
			schedule_list_t theSchedule = schedule_srv_findByID(theTicket->data.schedule_ID);
			if ( DateCmp(theSchedule->data.date, startDate) != -1 && DateCmp(theSchedule->data.date, endDate) != 1)
			{
				(*sold)++;
				play_list_t thePlay = play_srv_findByID(theSchedule->data.play_ID);
				(*total) = (*total) + thePlay->data.price;
			}
		}

		theTicket = theTicket->next;
	}
}
