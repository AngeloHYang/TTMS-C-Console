#include "seat_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// ��������Seat��ID�����ز���1
int seat_srv_getID()
{
	newID(seat_unassignedID);
}

//��������һ��seat_t��ע�ⷵ��ֵ
seat_t seat_srv_generate(int ID, int roomID, int row, int column, seat_status_t status)
{
	seat_t thisOne;
	thisOne.ID = ID;
	thisOne.row = row;
	thisOne.column = column;
	thisOne.status = status;
	return thisOne;
}

//Seat�����
void seat_srv_add(seat_t inputSeat_t) 
{
	type_srv_add(seat_t, inputSeat_t, seat_node_t, seat_head);
}

//����ID���ң�����seat_list_t.û�ҵ��򷵻�NULL
seat_list_t seat_srv_findByID(int inputID)
{
	type_srv_findByID(seat_t, inputID, seat_node_t, seat_head);
}

//����seat_t���޸�
// �޸ĳɹ�����1,����0
int seat_srv_modifyBySeat_t(seat_t inputSeat_t) 
{
	type_srv_modifyByType_t(seat_t, inputSeat_t, seat_node_t, seat_srv_findByID(inputSeat_t.ID));
}

//ɾ��seat�������ɾ��seat�������������
// ɾ���ɹ�����1,����0
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
//ɾ�������������λ
extern int seat_srv_fetchById(int Id, seat_t* buf);
//����Id��ȡ������Ϣ
int seat_srv_fetchValidByRoomID(seat_list_t list, int roomId) {
	int a,b;
	a=seat_t_perst_selectByRoomId(list, roomId);
	seat_srv_sortSeatList(list);
	return a;
}
//�����ݳ�����ID�����Ч��λ
int seat_srv_fetchByRoomId(seat_list_t list, int roomId) {
	int i = 0;
	seat_list_t a = list;
	while (a != NULL) {
		if (a->data.roomID == roomId && a->data.status == 1)
			i++;
	}
	return i;
}
//�����ݳ�����ID ,��ȡ��Ч��λ����n
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
//���������кţ��кŽ�������

void seat_srv_addToSortedList(seat_list_t list, seat_node_t* node);
//��һ����λ�ڵ�������������λ������
*/