#include "studio_srv.h"
#include <stdio.h>
#include "List.h"

#include "basicMove.h"

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
	studio_t swap;

	/*
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

		
		while (fread(&swap, sizeof(studio_t), 1, fp) != 0)
		{
			studio_srv_add(swap);
		}
		fclose(fp);
	}*/
	type_pers_load(fp, studio_head, studio_unassignedID, studio_node_t, studio_t, studio_srv_add(swap));
}

void studio_pers_save()
{
	FILE* fp = fopen("studio.dat", "wb+");
	studio_list_t swap;

	type_pers_save(fp, studio_head, studio_unassignedID, studio_node_t, studio_t, "studio.dat")
}