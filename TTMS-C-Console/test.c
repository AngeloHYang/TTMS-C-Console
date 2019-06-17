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
	studio_t s;

	s.ID = studio_srv_getID();
	strcpy(s.name, "a");
	s.rowsCount = 1;
	s.colsCount = 1;
	studio_srv_add(s);

	s.ID = studio_srv_getID();
	strcpy(s.name, "b");
	s.rowsCount = 2;
	s.colsCount = 2;
	studio_srv_add(s);

	s.ID = studio_srv_getID();
	strcpy(s.name, "c");
	s.rowsCount = 3;
	s.colsCount = 3;
	studio_srv_add(s);

	studio_printAll();

	extern void all_Save();
	all_Save();
}