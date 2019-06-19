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
	

	studio_srv_modifyByStudio_t(studio_srv_generate(3, "1144", 14, 1));
	studio_srv_printAll();

	extern void all_Save();
	all_Save();

	
}