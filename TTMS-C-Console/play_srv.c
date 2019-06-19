#include "play_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// ��������Play��ID�����ز���1
int play_srv_getID()
{
	newID(play_unassignedID);
}

//��������һ��play_t��ע�ⷵ��ֵ
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

void play_srv_add(play_t inputPlay_t) //ӰƬ�����
{
	type_srv_add(play_t, inputPlay_t, play_node_t, play_head);
}

//����ID���ң�����play_list_t.û�ҵ��򷵻�NULL
play_list_t play_srv_findByID(int inputID)
{
	type_srv_findByID(play_t, inputID, play_node_t, play_head);
}

//ɾ��play�������ɾ��play�������������
// ɾ���ɹ�����1,����0
int play_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(play_node_t, play_srv_findByID(inputID));
}

//����play_t���޸�
// �޸ĳɹ�����1,����0
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
