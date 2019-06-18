#include "account_srv.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basicMove.h"

// ��������Account��ID�����ز���1
int account_srv_getID()
{
	newID(account_unassignedID);
}

//��������һ��account_t��ע�ⷵ��ֵ
account_t account_srv_generate(int ID, account_type_t type, char username[30], char password[30])
{
	account_t thisOne;
	thisOne.ID = ID;
	strcpy(thisOne.username, username);
	strcpy(thisOne.password, password);
	thisOne.type = type;
	return thisOne;
}

void account_srv_add(account_t inputAccount_t) 
{
	type_srv_add(account_t, inputAccount_t, account_node_t, account_head);
}

//����ID���ң�����play_list_t.û�ҵ��򷵻�NULL
account_list_t account_srv_findByID(int inputID)
{
	type_srv_findByID(account_t, inputID, account_node_t, account_head);
}