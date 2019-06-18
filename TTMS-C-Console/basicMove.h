#include "List.h"

/* 增删查改等等 */


// 返回ID后++的作用
#define newID(nameOfID) \
nameOfID++;\
return nameOfID - 1;

// 增加type_t项目到type_node_t的链表
#define type_srv_add(type_t, inputType_t, type_node_t, type_head) \
	type_node_t* thisOne = (type_node_t*) malloc(sizeof(type_node_t));\
	thisOne->data = inputType_t;\
	List_AddTail(type_head, thisOne);

// 按照ID查找，返回type_list_t.没找到则返回NULL
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