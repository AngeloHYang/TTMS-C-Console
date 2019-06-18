#include <stdio.h>
#include "play_srv.h"
#include "List.h"



/*
filename: play.dat
content:
	int play_ID
	play_t * n

*/

int play_unassignedID;
play_node_t* play_head;

void play_pers_load()
{
	FILE* fp = fopen("play.dat", "rb+");

	play_head = NULL;

	List_Init(play_head, play_node_t);

	if (fp == NULL)
		// If the file doesn't exist
	{
		play_unassignedID = 1;
	}
	else
	{
		fread(&play_unassignedID, sizeof(int), 1, fp);

		play_t swap;
		while (fread(&swap, sizeof(play_t), 1, fp) != 0)
		{
			play_srv_add(swap);
		}
		fclose(fp);
	}
}

void play_pers_save()
{
	FILE* fp = fopen("play.dat", "wb+");

	if (fp == NULL)
		// If the file fails to create
	{
		printf("Failed to save play.dat\n");
		//system("pause");
	}
	else
	{
		//system("pause");
		fwrite(&play_unassignedID, sizeof(int), 1, fp);

		if (List_IsEmpty(play_head))
		{
			;
		}
		else
		{
			play_list_t swap = play_head->next;
			while (swap != play_head)
			{
				fwrite(&(swap->data), sizeof(play_t), 1, fp);
				swap = swap->next;
			}
		}

		fclose(fp);
	}
}