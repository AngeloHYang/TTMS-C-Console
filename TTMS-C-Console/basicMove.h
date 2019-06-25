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


#define type_srv_modifyByType_t(type_t, inputType_t, type_node_t, functionToFindByID)\
type_node_t* thisOne = functionToFindByID;\
if (thisOne == NULL)\
{\
	return 0;\
}\
else\
{\
	thisOne->data = inputType_t;\
	return 1;\
}

#define type_srv_deleteByID(type_node_t, functionToFindByID)\
type_node_t* thisOne = functionToFindByID;\
if (thisOne == NULL) \
{\
	return 0;\
}\
else\
{\
	List_DelNode(thisOne);\
	return 1;\
}

#define type_pers_load(fp, type_head, type_unassignedID, type_node_t, type_t, type_srv_addSwap)\
type_head = NULL;\
List_Init(type_head, type_node_t);\
if (fp == NULL)\
{\
	type_unassignedID = 1;\
}\
else\
{\
	fread(&type_unassignedID, sizeof(int), 1, fp);\
	while (fread(&swap, sizeof(type_t), 1, fp) != 0)\
	{\
		type_srv_addSwap; \
	}\
	fclose(fp);\
}

#define type_pers_save(fp, type_head, type_unassignedID, type_node_t, type_t, fileName)\
if (fp == NULL) \
{\
	printf("Failed to save %s\n", fileName);\
}\
else\
{\
	fwrite(&type_unassignedID, sizeof(int), 1, fp);\
	\
	if (List_IsEmpty(type_head))\
	{\
		;\
	}\
	else\
	{\
		swap = type_head->next;\
		while (swap != type_head)\
		{\
			fwrite(&(swap->data), sizeof(type_t), 1, fp);\
			swap = swap->next;\
		}\
	}\
	fclose(fp);\
}

#define type_srv_howManyInToto(type_node_t, type_head)\
type_node_t* thisOne = type_head->next;\
int counter = 0;\
while (thisOne != type_head)\
{\
	counter++;\
	thisOne = thisOne->next;\
}\
return counter;

#define type_srv_findByWhichOne(type_node_t, type_head, whichOne)\
int counter = 1;\
type_node_t* thisOne = type_head -> next;\
while (thisOne != type_head)\
{\
	if (counter == whichOne)\
		return thisOne;\
	thisOne = thisOne->next;\
	counter++;\
}\
return NULL;