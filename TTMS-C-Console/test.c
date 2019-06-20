#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "studio_srv.h"
#include "play_srv.h"
#include "basicMove.h"
#include "schedule_srv.h"
#include "ticket_srv.h"
#include "seat_srv.h"
#include "inputMethod.h"

void test()
{
	system("cls");
	char something[20];
	//inputName(something, 20);
	//printf("\nYour result: %d\n", inputInt());

	/*printf("ASCII table:\n");
	for (int whichNumber = -1; whichNumber <= 128; whichNumber++)
	{
		printf("Number: %d, iscntrl: %d, char: %c\n", whichNumber, iscntrl(whichNumber), whichNumber);
	}*/
	inputPassword(something, 20);
	
}