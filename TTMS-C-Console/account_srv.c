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