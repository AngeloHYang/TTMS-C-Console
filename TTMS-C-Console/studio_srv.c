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

void studio_srv_add(studio_t inputStudio_t)
{
	// 基本struct封装成带next和prev
	studio_list_t thisOne = (studio_list_t)malloc(sizeof(studio_node_t));
	thisOne->data = inputStudio_t;
	List_AddTail(studio_head, thisOne);
	printf("You just added %d %s %d %d\n", thisOne->data.ID, thisOne->data.name, thisOne->data.rowsCount, thisOne->data.colsCount);
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

	printf("new ID: %d\n", studio_srv_getID());
	printf("new ID: %d\n", studio_srv_getID());
	printf("new ID: %d\n", studio_srv_getID());
}