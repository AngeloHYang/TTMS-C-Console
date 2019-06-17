#include <io.h>
#include <process.h>
#include <stdlib.h>

#include "studio_pers.h"

void all_Load()
{
	//switch working directory
	if (chdir("data") == -1)
	// fails if -1.
	// 0 if succeeds.
	{
		//printf("Data folder not exists\n");
		system("mkdir data");
		chdir("data");
	}
	else
	{
		//printf("Data folder exists\n");
	}
	studio_pers_load();
}

void all_Save()
{
	studio_pers_save();
}