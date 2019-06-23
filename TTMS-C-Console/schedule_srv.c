#include "schedule_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"
#include "common.h"
#include "play_srv.h"

// 生成新增schedule的ID，返回并加1
int schedule_srv_getID()
{
	newID(schedule_unassignedID);
}

//用于生成一个schedule_t，注意返回值
schedule_t schedule_srv_generate(int ID, int play_ID, int studio_ID, user_date_t date, user_time_t time)
{
	schedule_t thisOne;
	thisOne.ID = ID;
	thisOne.play_ID = play_ID;
	thisOne.studio_ID = studio_ID;
	thisOne.date = date;
	thisOne.time = time;
	thisOne.exist = 1;
	return thisOne;
}

void schedule_srv_add(schedule_t inputSchedule_t) //schedule的添加
{
	type_srv_add(schedule_t, inputSchedule_t, schedule_node_t, schedule_head);
}

//按照ID查找，返回schedule_list_t.没找到则返回NULL
schedule_list_t schedule_srv_findByID(int inputID)
{
	//type_srv_findByID(schedule_t, inputID, schedule_node_t, schedule_head);
	schedule_node_t* thisOne = schedule_head->next;
	while (thisOne != schedule_head)
	{
		if (thisOne->data.ID == inputID && thisOne->data.exist == 1)
		{
			return thisOne; 
		}
		thisOne = thisOne->next; 
	}
	return NULL;
}

//删除schedule，不解决删除schedule引起的其他问题
// 删除成功返回1,否则0
int schedule_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(schedule_node_t, schedule_srv_findByID(inputID));
}

//输入schedule_t以修改
// 修改成功返回1,否则0
int schedule_srv_modifyBySchedule_t(schedule_t inputSchedule_t)
{
	type_srv_modifyByType_t(schedule_t, inputSchedule_t, schedule_node_t, schedule_srv_findByID(inputSchedule_t.ID));
}

void schedule_srv_printAll()
{
	schedule_list_t swap = schedule_head->next;
	int counter = 1;
	while (swap != schedule_head)
	{
		printf("ID: %d\n", swap->data.ID);
		printf("studio ID: %d\n", swap->data.studio_ID);
		printf("play ID: %d\n", swap->data.play_ID);
		printf("%d\n", swap->data.date.year);
		printf("%d\n", swap->data.time.hour);
		printf("\n");

		counter++;
		swap = swap->next;
	}
}

void schedule_srv_makeScheduleERROR_byEndTimeAndStudio(int studioID, int currentSecond)
{
	schedule_list_t theSchedule = schedule_head -> next;
	while (theSchedule != schedule_head)
	{
		if (theSchedule->data.studio_ID == studioID)
		{
			int endSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time) + play_srv_findByID(theSchedule->data.play_ID)->data.duration * 60;
			if (currentSecond <= endSecond)
			{
				theSchedule->data.exist = 0;
			}
		}
		theSchedule = theSchedule->next;
	}
}

void schedule_srv_makeScheduleInvalidAfterDate(user_date_t byDateAfter, int playID)
{
	schedule_list_t theSchedule = schedule_head->next;

	while (theSchedule != schedule_head)
	{
		if (theSchedule->data.play_ID == playID)
		{
			int scheduleStartSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);
			user_time_t swapTime = { 23, 59, 59 };
			int targetSecond = user_date_t_And_user_time_t_ToSecond(byDateAfter, swapTime);
			if (scheduleStartSecond > targetSecond)
			{
				theSchedule->data.exist = 0;
			}
		}
		theSchedule = theSchedule->next;
	}
}

void schedule_srv_makeScheduleInvalidBeforeDate(user_date_t byDateBefore, int playID)
{
	schedule_list_t theSchedule = schedule_head->next;

	while (theSchedule != schedule_head)
	{
		if (theSchedule->data.play_ID == playID)
		{
			int scheduleStartSecond = user_date_t_And_user_time_t_ToSecond(theSchedule->data.date, theSchedule->data.time);
			user_time_t swapTime = { 23, 59, 59 };
			int targetSecond = user_date_t_And_user_time_t_ToSecond(byDateBefore, swapTime);
			if (scheduleStartSecond < targetSecond)
			{
				theSchedule->data.exist = 0;
			}
		}
		theSchedule = theSchedule->next;
	}
}

void schedule_srv_deleteScheduleByPlayID(int playID)
{
	schedule_list_t theSchedule = schedule_head->next;
	while (theSchedule != schedule_head)
	{
		if (theSchedule->data.play_ID == playID)
		{
			theSchedule->data.exist = 0;
		}
		theSchedule = theSchedule->next;
	}
}