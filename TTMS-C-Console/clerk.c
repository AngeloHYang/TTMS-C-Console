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
#include "common.h"

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
			ticket_UI_checkTicket(theUser);
		}
		else if (selection == 3)
		{
			while (1)
			{
				char Menu[3][100] = { "Today", "This Month", "Return" };
				char* pointers[3] = { Menu[0], Menu[1], Menu[2] };
				char words[42] = "How would you like to check your statics?";
				int selection = standardSelectMenuView(7, 0, "Check Statics", words, 42, pointers, 3, 100);
				if (selection == 0)
				{
					user_date_t a = DateNow();
					statics_UI_viewClerk(theUser, a, a);
				}
				else if (selection == 1)
				{
					user_date_t a = DateNow();
					a.day = 1;
					user_date_t b = DateNow();
					statics_UI_viewClerk(theUser, a, b);
				}
				else
				{
					break;
				}
			}
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