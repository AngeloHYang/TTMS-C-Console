#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studio_srv.h"
#include "play_srv.h"
#include "basicMove.h"

int test()
{
	system("cls");
	
	
	extern void all_Load();
	all_Load();
	

	/*studio_srv_modifyByStudio_t(studio_srv_generate(3, "1144", 14, 1));*/
	studio_srv_printAll();

	ttms_date_t a = { 1, 2, 3 };

	play_srv_add(play_srv_generate(play_srv_getID(), "you", "23", "US", 3, 132, a, a, 32));

	play_srv_printAll();

	extern void all_Save();
	all_Save();

	
}