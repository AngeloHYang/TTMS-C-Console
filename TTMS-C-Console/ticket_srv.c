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

// 生成新增Ticket的ID，返回并加1
int ticket_srv_getID()
{
	newID(ticket_unassignedID);
}

//用于生成一个ticket_t，注意返回值
ticket_t ticket_srv_generate(int ID, int schedule_ID, int seat_ID, int price, int soldBy, ticket_status_t status)
{
	ticket_t thisOne;
	thisOne.ID = ID;
	thisOne.schedule_ID = schedule_ID;
	thisOne.seat_ID = seat_ID;
	thisOne.price = price;
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
	type_srv_findByID(ticket_t, inputID, ticket_node_t, ticket_head);
}

//删除ticket，不解决删除ticket引起的其他问题
// 删除成功返回1,否则0
int ticket_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(ticket_node_t, ticket_srv_findByID(inputID));
}

//输入ticket_t以修改
// 修改成功返回1,否则0
int ticket_srv_modifyByPlay_t(ticket_t inputTicket_t)
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
			printf("Price: %d\n", swap->data.price);
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
		if (theTicket->data.seat_ID == seatID)
		{
			int startSecond = user_date_t___And___user_time_t___ToSecond(theSchedule->data.date, theSchedule->data.time);
			play_list_t thePlay = play_srv_findByID(theSchedule->data.play_ID);
			if (startSecond + thePlay->data.duration * 60 > currentSecond)
			{
				theTicket->data.status = TICKET_ERROR;
			}
		}
		theTicket = theTicket->next;
	}
}