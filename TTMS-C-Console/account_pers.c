#include <stdio.h>
#include "account_srv.h"
#include "List.h"
#include "basicMove.h"
/*
filename: account.dat
content:
	int account_ID
	account_t * n
*/

int account_unassignedID;
account_node_t* account_head;

void account_pers_load()
{
	FILE* fp = fopen("account.dat", "rb+");
	account_t swap;
	
	type_pers_load(fp, account_head, account_unassignedID, account_node_t, account_t, account_srv_add(swap));
}

void account_pers_save()
{
	FILE* fp = fopen("account.dat", "wb+");
	account_list_t swap;

	/*
	if (fp == NULL)
		// If the file fails to create
	{
		printf("Failed to save account.dat\n");
		//system("pause");
	}
	else
	{
		//system("pause");
		fwrite(&account_unassignedID, sizeof(int), 1, fp);

		if (List_IsEmpty(account_head))
		{
			;
		}
		else
		{
			swap = account_head->next;
			while (swap != account_head)
			{
				fwrite(&(swap->data), sizeof(account_t), 1, fp);
				swap = swap->next;
			}
		}

		fclose(fp);
	}*/
	type_pers_save(fp, account_head, account_unassignedID, account_node_t, account_t, "accout.dat");
}