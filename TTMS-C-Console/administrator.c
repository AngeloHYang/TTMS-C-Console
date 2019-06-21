#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"
#include "templates.h"
#include "account_UI.h"

int administratorLogin(account_list_t theUser)
{
	setBackgroundColor(7);
	setFontColor(0);
	
	char Menu[5][100] = { "Personal Profile", "Manage Accounts", "Manage Studios", "Switch Account", "Quit"};
	char* pointers[5] = { Menu[0], Menu[1], Menu[2], Menu[3], Menu[4] };

	char words[100] = "Hello, ";
	strcat(words, theUser->data.nickname);

	int selection = 0;
	int toExit = 0;
	while (toExit == 0)
	{
		selection = standardSelectMenuView(7, 0, "Administrator", words, 8 + strlen(theUser->data.nickname), pointers, 5, 100);

		if (selection == 0)
		{
			account_UI_changeProfile(theUser);
		} 
		else if (selection == 1)
		{
			
		}
		else if (selection == 2)
		{

		} 
		else if (selection == 3)
		{
			break;
		} else if (selection == 4)
		{
			toExit = exitSelect();
		}
	}

	return toExit;
}