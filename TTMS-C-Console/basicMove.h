#include "List.h"

/* ��ɾ��ĵȵ� */


// ����ID��++������
#define newID(nameOfID) \
nameOfID++;\
return nameOfID - 1;

// ����type_t��Ŀ��type_node_t������
#define type_srv_add(type_t, inputType_t, type_node_t, type_head) \
	type_node_t* thisOne = (type_node_t*) malloc(sizeof(type_node_t));\
	thisOne->data = inputType_t;\
	List_AddTail(type_head, thisOne);

// ����ID���ң�����type_list_t.û�ҵ��򷵻�NULL
#define type_srv_findByID(type_t, inputID, type_node_t, type_head) \
	type_node_t* thisOne = type_head->next; \
	while (thisOne != type_head) \
	{\
		if (thisOne->data.ID == inputID)\
		{\
			return thisOne;\
		}\
		thisOne = thisOne->next;\
	}\
	return NULL;

/*
#define type_srv_modifyByType_t(type_t, inputType_t, type_node_t, inputID, type_srv_findByID)\
type_node_t* thisOne = type_
*/