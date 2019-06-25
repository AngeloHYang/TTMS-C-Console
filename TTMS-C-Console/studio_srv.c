#include "studio_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

//private:

// To convert studio_list_t into studio_node*
static struct studio_node* fakePointerToRealPointer()
{
	return studio_head;
}

//public:

// ��������Studio��ID�����ز���1
int studio_srv_getID()
{
	newID(studio_unassignedID);
}

//��������һ��studio_t��ע�ⷵ��ֵ
studio_t studio_srv_generate(int ID, char* name, int rowsCount, int colsCount)
{
	studio_t thisOne;
	thisOne.ID = ID;
	strcpy(thisOne.name, name);
	thisOne.rowsCount = rowsCount;
	thisOne.colsCount = colsCount;
	return thisOne;
}

//����������studio_t��ӵ�����
void studio_srv_add(studio_t inputStudio_t)
{
	/*
	// ����struct��װ�ɴ�next��prev
	studio_list_t thisOne = (studio_list_t)malloc(sizeof(studio_node_t));
	thisOne->data = inputStudio_t;
	List_AddTail(studio_head, thisOne);
	//printf("You just added %d %s %d %d\n", thisOne->data.ID, thisOne->data.name, thisOne->data.rowsCount, thisOne->data.colsCount);*/
	type_srv_add(studio_t, inputStudio_t, studio_node_t, studio_head);
}

void studio_srv_printAll()
{
	studio_list_t swap = studio_head->next;
	int counter = 1;
	while (swap != studio_head)
	{
		printf("Counter: %d\n", counter);
		printf("Name: %s\n", swap->data.name);
		printf("ID: %d\n", swap->data.ID);
		printf("rows: %d\n", swap->data.rowsCount);
		printf("cols: %d\n", swap->data.colsCount);
		printf("\n");
		counter++;
		swap = swap->next;
	}
}

//����ID���ң�����studio_list_t.û�ҵ��򷵻�NULL
studio_list_t studio_srv_findByID(int inputID)
{
	/*
	studio_list_t thisOne = studio_head->next;
	while (thisOne != studio_head)
	{
		if (thisOne->data.ID == inputID)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
	}
	return NULL;*/
	type_srv_findByID(studio_t, inputID, studio_node_t, studio_head);
}

//ɾ��studio�������ɾ��studio�������������
// ɾ���ɹ�����1,����0
int studio_srv_deleteByID(int inputID)
{
	/*
	studio_list_t thisOne = studio_srv_findByID(inputID);
	if (thisOne == NULL)
	{
		return 0;
	}
	else
	{
		List_DelNode(thisOne);
		return 1;
	}*/
	type_srv_deleteByID(studio_node_t, studio_srv_findByID(inputID));
}

//����studio_t���޸�
// �޸ĳɹ�����1,����0
int studio_srv_modifyByStudio_t(studio_t inputStudio_t)
{
	/*
	studio_list_t thisOne = studio_srv_findByID(inputStudio_t.ID);
	if (thisOne == NULL)
	{
		return 0;
	}
	else
	{
		thisOne->data = inputStudio_t;
		return 1;
	}*/
	type_srv_modifyByType_t(studio_t, inputStudio_t, studio_node_t, studio_srv_findByID(inputStudio_t.ID));
}

// ��ѯ�ܹ��ж���studios
int studio_srv_howManyInToto()
{
	type_srv_howManyInToto(studio_node_t, studio_head);
}

// ����name����,ʧ�ܷ���NULL
studio_list_t studio_srv_findByUsername(char input[30])
{
	studio_list_t thisOne = studio_head->next;

	while (thisOne != studio_head)
	{
		if (strcmp(thisOne->data.name, input) == 0)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
	}

	return NULL;
}

// ��������ΪNULL
studio_list_t studio_srv_findByWhichOne(int whichOne)
{
	/*
	int counter = 1;
	account_node_t* thisOne = account_head -> next;
	while (thisOne != account_head)
	{
		if (counter == whichOne)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
		counter++;
	}
	return NULL;
	*/
	type_srv_findByWhichOne(studio_node_t, studio_head, whichOne);
}
