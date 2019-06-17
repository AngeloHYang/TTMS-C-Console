#include "studio_srv.h"
#include <stdio.h>
#include "List.h"

/*
filename: studio.dat
content:
	int studio_ID
	studio_t * n

*/

// Variables

int studio_unassignedID;
studio_list_t studio_head;

void studio_pers_load()
{
	FILE* fp = fopen("studio.dat", "rb+");

	studio_head = NULL;
	
	List_Init(studio_head, studio_node_t);

	if (fp == NULL)
	// If the file doesn't exist
	{
		studio_unassignedID = 1;
	}
	else
	{
		fread(&studio_unassignedID, sizeof(int), 1, fp);

		studio_t swap;
		while (fread(&swap, sizeof(studio_t), 1, fp) != 0)
		{
			studio_srv_add(swap);
		}
		fclose(fp);
	}
}

void studio_pers_save()
{
	FILE* fp = fopen("studio.dat", "wb+");

	if (fp == NULL)
		// If the file fails to create
	{
		printf("Failed to save studio.dat\n");
		system("pause");
	}
	else
	{
		system("pause");
		fwrite(&studio_unassignedID, sizeof(int), 1, fp);
	
		if (List_IsEmpty(studio_head))
		{
			;
		}
		else
		{
			studio_list_t swap = studio_head ->next;
			while (swap != studio_head)
			{
				fwrite(&(swap->data), sizeof(studio_t), 1, fp);
				swap = swap->next;
			}
		}
		
		fclose(fp);
	}
}