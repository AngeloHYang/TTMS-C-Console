#include "studio_srv.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>


//private:

// To convert studio_list_t into studio_node*
static struct studio_node* fakePointerToRealPointer()
{
	return studio_head;
}

//public:

// 生成新增Studio的ID，返回并加1
int studio_srv_getID()
{
	studio_unassignedID++;
	return studio_unassignedID - 1;
}

//用于生成一个studio_t，注意返回值
studio_t studio_srv_generate(int ID, char* name, int rowsCount, int colsCount)
{
	studio_t thisOne;
	thisOne.ID = ID;
	strcpy(thisOne.name, name);
	thisOne.rowsCount = rowsCount;
	thisOne.colsCount = colsCount;
	return thisOne;
}

//负责将完整的studio_t添加到链表
void studio_srv_add(studio_t inputStudio_t)
{
	// 基本struct封装成带next和prev
	studio_list_t thisOne = (studio_list_t)malloc(sizeof(studio_node_t));
	thisOne->data = inputStudio_t;
	List_AddTail(studio_head, thisOne);
	//printf("You just added %d %s %d %d\n", thisOne->data.ID, thisOne->data.name, thisOne->data.rowsCount, thisOne->data.colsCount);
}

void studio_printAll()
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

//按照ID查找，返回studio_list_t.没找到则返回NULL
studio_list_t studio_srv_findByID(int inputID)
{
	studio_list_t thisOne = studio_head->next;
	while (thisOne != studio_head)
	{
		if (thisOne->data.ID == inputID)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
	}
	return NULL;
}

//删除studio，不解决删除studio引起的其他问题
// 删除成功返回1,否则0
int studio_srv_deleteByID(int inputID)
{
	studio_list_t thisOne = studio_srv_findByID(inputID);
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

//输入studio_t以修改
// 修改成功返回1,否则0
int studio_srv_modifyByStudio_t(studio_t inputStudio_t)
{
	studio_list_t thisOne = studio_srv_findByID(inputStudio_t.ID);
	if (thisOne == NULL)
	{
		return 0;
	}
	else
	{
		thisOne->data = inputStudio_t;
		return 1;
	}
}