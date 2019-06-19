#include "play_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// 生成新增Play的ID，返回并加1
int play_srv_getID()
{
	newID(play_unassignedID);
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
	type_srv_add(play_t, inputPlay_t, play_node_t, play_head);
}

//按照ID查找，返回play_list_t.没找到则返回NULL
play_list_t play_srv_findByID(int inputID)
{
	type_srv_findByID(play_t, inputID, play_node_t, play_head);
}

//删除play，不解决删除play引起的其他问题
// 删除成功返回1,否则0
int play_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(play_node_t, play_srv_findByID(inputID));
}

//输入play_t以修改
// 修改成功返回1,否则0
int play_srv_modifyByPlay_t(play_t inputPlay_t)
{
	type_srv_modifyByType_t(play_t, inputPlay_t, play_node_t, play_srv_findByID(inputPlay_t.ID));
}

void play_srv_printAll()
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
