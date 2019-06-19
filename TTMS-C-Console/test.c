#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studio_srv.h"
#include "play_srv.h"
#include "basicMove.h"
#include "schedule_srv.h"

int test()
{
	system("cls");
	
	
	extern void all_Load();
	all_Load();
	

	user_date_t d = { 1, 2, 3 };
	user_time_t t = { 3, 2, 1 };

	schedule_srv_add(schedule_srv_generate(schedule_srv_getID(), play_srv_getID(), studio_srv_getID(), d, t));

	schedule_srv_printAll();

	extern void all_Save();
	all_Save();

	
}