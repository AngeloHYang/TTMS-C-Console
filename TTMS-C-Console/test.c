#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studio_srv.h"
#include "play_srv.h"
#include "basicMove.h"

#define doSomething(function)\
(*funtion)();

void printHello()
{
	printf("Hello\n");
}

void printBye()
{
	printf("Bye\n");
}

int test()
{
	system("cls");
	
	
	extern void all_Load();
	all_Load();
	
	doSomething(printHello);
	doSomething(printBye);
	extern void all_Save();
	all_Save();

	
}