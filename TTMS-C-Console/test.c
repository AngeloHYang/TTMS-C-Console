#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studio_srv.h"
#include "studio_pers.h"

void test()
{
	if (chdir())

	system("cls");
	extern void all_Load();
	all_Load();
	

	studio_srv_add(studio_srv_generate(studio_srv_getID(), "a", 3, 3));
	studio_srv_add(studio_srv_generate(studio_srv_getID(), "b", 4, 4));
	studio_srv_add(studio_srv_generate(studio_srv_getID(), "del", 3, 3));
	studio_srv_deleteByID(3);
	printf("new ID: %d\n", studio_srv_getID());
	printf("new ID: %d\n", studio_srv_getID());
	printf("new ID: %d\n", studio_srv_getID());

	studio_printAll();

	extern void all_Save();
	all_Save();
}