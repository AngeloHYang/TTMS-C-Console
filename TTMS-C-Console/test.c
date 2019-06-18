#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studio_srv.h"
#include "play_srv.h"

void test()
{
	if (chdir())

	system("cls");
	extern void all_Load();
	all_Load();
	
	ttms_date_t asd = { 1, 1, 1 };

	play_srv_add(play_srv_generate(play_srv_getID(), "a", "b", "c", 1, 123, asd, asd, 3));

	printf("delete: %d\n\n\n", play_srv_deleteByID(1));

	play_printAll();

	extern void all_Save();
	all_Save();
}