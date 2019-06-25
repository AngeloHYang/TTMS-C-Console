#include <stdio.h>
#include "play_srv.h"
#include "List.h"
#include "basicMove.h"


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
	play_t swap;

	
	type_pers_load(fp, play_head, play_unassignedID, play_node_t, play_t, play_srv_add(swap));
}

void play_pers_save()
{
	FILE* fp = fopen("play.dat", "wb+");
	play_list_t swap;

	type_pers_save(fp, play_head, play_unassignedID, play_node_t, play_t, "play.dat");
}