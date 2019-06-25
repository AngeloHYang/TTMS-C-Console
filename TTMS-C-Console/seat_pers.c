#include <stdio.h>
#include "seat_srv.h"
#include "List.h"
#include "basicMove.h"


/*
filename: seat.dat
content:
	int seat_ID
	seat_t * n

*/

int seat_unassignedID;
seat_node_t* seat_head;

void seat_pers_load()
{
	FILE* fp = fopen("seat.dat", "rb+");
	seat_t swap;


	type_pers_load(fp, seat_head, seat_unassignedID, seat_node_t, seat_t, seat_srv_add(swap));
}

void seat_pers_save()
{
	FILE* fp = fopen("seat.dat", "wb+");
	seat_list_t swap;

	type_pers_save(fp, seat_head, seat_unassignedID, seat_node_t, seat_t, "seat.dat");
}