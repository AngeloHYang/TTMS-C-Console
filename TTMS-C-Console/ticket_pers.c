#include <stdio.h>
#include "ticket_srv.h"
#include "List.h"
#include "basicMove.h"

/*
filename: ticket.dat
content:
	int ticket_ID
	studio_t * n 
	
*/

// Variables

int ticket_unassignedID;
ticket_node_t* ticket_head;

void ticket_pers_load()
{
	FILE* fp = fopen("ticket.dat", "rb+");
	ticket_t swap;

	type_pers_load(fp, ticket_head, ticket_unassignedID, ticket_node_t, ticket_t, ticket_srv_add(swap));
}

void ticket_pers_save()
{
	FILE* fp = fopen("ticket.dat", "wb+");
	ticket_list_t swap;

	type_pers_save(fp, ticket_head, ticket_unassignedID, ticket_node_t, ticket_t, "ticket.dat")
}
