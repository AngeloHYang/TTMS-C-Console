#include <stdio.h>
#include "account_srv.h"
#include "List.h"

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

	account_head = NULL;

	List_Init(account_head, account_node_t);

	if (fp == NULL)
		// If the file doesn't exist
	{
		account_unassignedID = 1;
	}
	else
	{
		fread(&account_unassignedID, sizeof(int), 1, fp);

		account_t swap;
		while (fread(&swap, sizeof(account_t), 1, fp) != 0)
		{
			account_srv_add(swap);
		}
		fclose(fp);
	}
}

void account_pers_save()
{
	FILE* fp = fopen("account.dat", "wb+");

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
			account_list_t swap = account_head->next;
			while (swap != account_head)
			{
				fwrite(&(swap->data), sizeof(account_t), 1, fp);
				swap = swap->next;
			}
		}

		fclose(fp);
	}
}