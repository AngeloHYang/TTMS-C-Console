#include "account_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// 生成新增Account的ID，返回并加1
int account_srv_getID()
{
	newID(account_unassignedID);
}

//用于生成一个account_t，注意返回值
account_t account_srv_generate(int ID, account_type_t type, char username[30], char password[30], char phone[20], char nickname[30])
{
	account_t thisOne;
	thisOne.ID = ID;
	strcpy(thisOne.username, username);
	strcpy(thisOne.password, password);
	thisOne.type = type;
	strcpy(thisOne.phone, phone);
	strcpy(thisOne.nickname, phone);
	return thisOne;
}

void account_srv_add(account_t inputAccount_t) 
{
	type_srv_add(account_t, inputAccount_t, account_node_t, account_head);
}

//按照ID查找，返回account_list_t.没找到则返回NULL
account_list_t account_srv_findByID(int inputID)
{
	type_srv_findByID(account_t, inputID, account_node_t, account_head);
}

//输入account_t以修改
// 修改成功返回1,否则0
int accout_srv_modifyByPlay_t(account_t inputAccount_t)
{
	type_srv_modifyByType_t(account_t, inputAccount_t, account_node_t, account_srv_findByID(inputAccount_t.ID));
}

//删除account，不解决删除account引起的其他问题
// 删除成功返回1,否则0
int account_srv_deleteByID(int inputID)
{
	type_srv_deleteByID(account_node_t, account_srv_findByID(inputID));
}

// 查询总共有多少用户
int account_srv_howManyInToto()
{
	type_srv_howManyInToto(account_node_t, account_head);
}

int account_srv_howManyClerkInToto()
{
	account_node_t* thisOne = account_head->next;
	int counter = 0;
	while (thisOne != account_head)
	{
		if (thisOne->data.type == USER_CLERK)
		{
			counter++;
		}
		thisOne = thisOne->next;
	}
	return counter;
}

// 根据username查找,失败返回NULL
account_list_t account_srv_findByUsername(char input[30])
{
	account_list_t thisOne = account_head ->next;

	while (thisOne != account_head)
	{
		if (strcmp(thisOne->data.username, input) == 0)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
	}

	return NULL;
}


//在inputSpace中描述类型
// Don't make it too small
void account_srv_tellType(account_t inputAccount_t, char* inputSpace)
{
	if (inputAccount_t.type == USER_CLERK)
	{
		strcpy(inputSpace, "Clerk");
	}
	else if (inputAccount_t.type == USER_MANAGER)
	{
		strcpy(inputSpace, "Manager");
	}
	else if (inputAccount_t.type == USER_ADMIN)
	{
		strcpy(inputSpace, "Administrator");
	}
}

// 不存在则为NULL
account_list_t account_srv_findByWhichOne(int whichOne)
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
	type_srv_findByWhichOne(account_node_t, account_head, whichOne);
}

// 不存在则为NULL
account_list_t account_srv_findClerkByWhichOne(int whichOne)
{
	int counter = 0;
	account_node_t* thisOne = account_head -> next;
	if (thisOne != account_head && thisOne->data.type == USER_CLERK)
	{
		counter++;
	}

	while (thisOne != account_head)
	{
		if (counter == whichOne && thisOne->data.type == USER_CLERK)
		{
			return thisOne;
		}
		thisOne = thisOne->next;
		if (thisOne->data.type == USER_CLERK)
			counter++;
	}
	return NULL;
}