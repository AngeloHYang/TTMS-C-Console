#include "play_srv.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// 生成新增Play的ID，返回并加1
int play_srv_getID()
{
	play_unassignedID++;
	return play_unassignedID - 1;
}

//用于生成一个play_t，注意返回值
play_t play_srv_generate(int ID, char name[51], char type[21], char area[11], play_rating_t rating, int duration, ttms_date_t start_date, ttms_date_t end_date, int price)
{
	play_t thisOne;
	thisOne.ID = ID;
	strcpy(thisOne.name, name);
	strcpy(thisOne.type, type);
	strcpy(thisOne.area, area);
	thisOne.rating = rating;
	thisOne.duration = duration;
	thisOne.start_date = start_date;
	thisOne.end_date = end_date;
	thisOne.price = price;
	return thisOne;
}

void play_srv_add(play_t inputPlay_t) //影片的添加
{
	play_node_t* thisOne = (play_node_t*)malloc(sizeof(play_node_t));
	thisOne->data = inputPlay_t;
	List_AddTail(play_head, thisOne);
}

//按照ID查找，返回play_list_t.没找到则返回NULL
play_list_t play_srv_findByID(int inputID)
{
	play_list_t thisOne = play_head->next;
	while (thisOne != play_head)
	{
		if (thisOne->data.ID == inputID)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
	}
	return NULL;
}

//删除play，不解决删除play引起的其他问题
// 删除成功返回1,否则0
int play_srv_deleteByID(int inputID)
{
	play_list_t thisOne = play_srv_findByID(inputID);
	if (thisOne == NULL)
	{
		return 0;
	}
	else
	{
		List_DelNode(thisOne);
		return 1;
	}
}

//输入play_t以修改
// 修改成功返回1,否则0
int play_srv_modifyByPlay_t(play_t inputPlay_t)
{
	play_list_t thisOne = play_srv_findByID(inputPlay_t.ID);
	if (thisOne == NULL)
	{
		return 0;
	}
	else
	{
		thisOne->data = inputPlay_t;
		return 1;
	}
}

void play_printAll()
{
	play_list_t swap = play_head->next;
	int counter = 1;
	while (swap != play_head)
	{
		printf("Counter: %d\n", counter);
		printf("Name: %s\n", swap->data.name);
		printf("ID: %d\n", swap->data.ID);
		printf("Type: %s\n", swap->data.type);
		printf("Area: %s\n", swap->data.area);
		printf("Rating: %d\n", swap->data.rating);
		printf("Duration: %d\n", swap->data.duration);
		printf("start_date: %d\n", swap->data.start_date.year);
		printf("end_date: %d\n", swap->data.end_date.year);
		printf("\n");

		counter++;
		swap = swap->next;
	}
}
