#include <stdio.h>
#include "schedule_srv.h"
#include "List.h"
#include "basicMove.h"
/*
filename: schedule.dat
content:
	int schedule_ID
	schedule_t * n
*/

int schedule_unassignedID;
schedule_node_t* schedule_head;

void schedule_pers_load()
{
	FILE* fp = fopen("schedule.dat", "rb+");
	schedule_t swap;


	type_pers_load(fp, schedule_head, schedule_unassignedID, schedule_node_t, schedule_t, schedule_srv_add(swap));
}

void schedule_pers_save()
{
	FILE* fp = fopen("schedule.dat", "wb+");
	schedule_list_t swap;

	type_pers_save(fp, schedule_head, schedule_unassignedID, schedule_node_t, schedule_t, "schedule.dat");
}