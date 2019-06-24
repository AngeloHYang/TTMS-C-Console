#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"
#include "templates.h"
#include "account_UI.h"
#include "play_UI.h"
#include "schedule_UI.h"

int clerkLogin(account_list_t theUser)
{
	setBackgroundColor(7);
	setFontColor(0);


	char Menu[6][100] = { "Personal Profile", "Check Schedules", "Check Tickets by ID", "Statics", "Switch Account", "Quit" };
	char* pointers[6] = { Menu[0], Menu[1], Menu[2], Menu[3], Menu[4], Menu[5] };


	char words[100];

	int selection = 0;
	int toExit = 0;

	while (toExit == 0)
	{
		memset(words, '\0', sizeof(words));
		strcat(words, "Hello, ");
		strcat(words, theUser->data.nickname);
		selection = standardSelectMenuView(7, 0, "Clerk", words, 8 + strlen(theUser->data.nickname), pointers, 6, 100);
		if (selection == 0)
		{
			account_UI_changeProfile(theUser);
		}
		else if (selection == 1)
		{
			schedule_UI_clerkSchedules(theUser);
		}
		else if (selection == 2)
		{
			//studio_UI_manageStudiosForManager(theUser);
		}
		else if (selection == 3)
		{
			//schedule_UI_manageSchedules(theUser);
		}
		else if (selection == 4)
		{
			extern void all_Save();
			void all_Save();
			break;
		}
		else if (selection == 5)
		{
			extern void all_Save();
			void all_Save();
			toExit = exitSelect();
		}
	}

	return toExit;
}