#include "seat_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// 生成新增Seat的ID，返回并加1
int seat_srv_getID()
{
	newID(seat_unassignedID);
}

//用于生成一个seat_t，注意返回值
seat_t seat_srv_generate(int ID, int roomID, int row, int column, seat_status_t status)
{
	seat_t thisOne;
	thisOne.ID = ID;
	thisOne.row = row;
	thisOne.column = column;
	thisOne.status = status;
	return thisOne;
}

//Seat的添加
void seat_srv_add(seat_t inputSeat_t) 
{
	type_srv_add(seat_t, inputSeat_t, seat_node_t, seat_head);
}

//按照ID查找，返回seat_list_t.没找到则返回NULL
seat_list_t seat_srv_findByID(int inputID)
{
	type_srv_findByID(seat_t, inputID, seat_node_t, seat_head);
}

//输入seat_t以修改
// 修改成功返回1,否则0
int seat_srv_modifyBySeat_t(seat_t inputSeat_t) 
{
	type_srv_modifyByType_t(seat_t, inputSeat_t, seat_node_t, seat_srv_findByID(inputSeat_t.ID));
}

//删除seat，不解决删除seat引起的其他问题
// 删除成功返回1,否则0
int seat_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(seat_node_t, seat_srv_findByID(inputID));
}

void seat_srv_printAll()
{
	seat_list_t swap = seat_head->next;
	int counter = 1;
	while (swap != seat_head)
	{
		printf("ID: %d\n", swap->data.ID);
		swap = swap->next;
	}
}
/*
extern int seat_srv_deleteAllByRoomId(int roomId) {
	seat_list_t a, b;
	while (a) {
		if (a->data.roomID == roomId) {
			b = a;
			List_DelNode(a);
			a = b->next;
		}
	}
}
//删除整个房间的座位
extern int seat_srv_fetchById(int Id, seat_t* buf);
//根据Id获取数据信息
int seat_srv_fetchValidByRoomID(seat_list_t list, int roomId) {
	int a,b;
	a=seat_t_perst_selectByRoomId(list, roomId);
	seat_srv_sortSeatList(list);
	return a;
}
//根据演出厅的ID获得有效座位
int seat_srv_fetchByRoomId(seat_list_t list, int roomId) {
	int i = 0;
	seat_list_t a = list;
	while (a != NULL) {
		if (a->data.roomID == roomId && a->data.status == 1)
			i++;
	}
	return i;
}
//根据演出厅的ID ,获取有效座位个数n
seat_node_t* Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
	seat_node_t *a;
	seat_list_t b;
	while (b != NULL) {
		if (b->data.row == row && b->data.column == column) {
			a = b;
		}
	}
}

void seat_srv_sortSeatList(seat_list_t list) {

}
//对链表按照行号，列号进行排序

void seat_srv_addToSortedList(seat_list_t list, seat_node_t* node);
//将一个座位节点加入已排序的座位链表中
*/