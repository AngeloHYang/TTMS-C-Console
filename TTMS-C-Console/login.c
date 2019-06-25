#include <stdio.h>
#include <string.h>
#include "account_srv.h"
#include "printChoices.h"
#include "inputMethod.h"
#include "color.h"
#include "account_UI.h"
#include "templates.h"

void noUserLogin();

void uesrLogin();

void login()
{
	setBackgroundColor(0);
	setFontColor(7);

	// Test if it's the first time 
	while (account_srv_howManyInToto() == 0)
	{
		noUserLogin();
	}
	uesrLogin();
}

void noUserLogin()
{
	system("cls");
	printTitleWithCurrentTime("Welcome", 8);

	printMultipleTimes('\n', 5);
	printMiddleAddjusted("It looks like it's your first time lauching this APP", 54);
	printMultipleTimes('\n', 2);
	printMiddleAddjusted("So, let's set up an Administrator account", 43);
	printMultipleTimes('\n', 10);
	keyToContinue("Enter", 5);
	while (account_UI_creatAdmin() == 0)
	{
		setBackgroundColor(0);
		setFontColor(7);
		system("cls");				 
		printTitleWithCurrentTime("Welcome", 8);
		printMultipleTimes('\n', 5);
		printMiddleAddjusted("You have to create an Administrator account", 44);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}

}

void uesrLogin()
{
	account_list_t result = NULL;
	int toExit = 0;
	while (toExit == 0)
	{
		setBackgroundColor(0);
		setFontColor(7);
		system("cls");
		printTitleWithCurrentTime("Welcome", 8);

		printMultipleTimes('\n', 5);

		printMiddleAddjusted("Please tell me who you are", 27);
		printf("\n\n");

		char usernameReceive[30];
		char passwordReceive[30];

		printMiddleLeft("Username:", 10, 2);
		printMultipleTimes(' ', 2);
		inputAlnum(usernameReceive, 30, 6);
		printf("\n");

		printMiddleLeft("Password:", 10, 2);
		printMultipleTimes(' ', 2);
		inputPassword(passwordReceive, 30, 6);
		printf("\n\n");

		result = account_srv_findByUsername(usernameReceive);

		// varification
		int invalid = 0;
		if (result == NULL)
		{
			invalid = 1;
		}
		else if (strcmp(result->data.password, passwordReceive) != 0)
		{
			invalid = 1;
		}

		// If not to login
		if (invalid == 1)
		{
			setFontColor(1);
			printMiddleAddjusted("Invalid username or password", 29);
			printf("\n\n");
			keyToContinue("Continue", 8);
			toExit = exitSelect();
		}

		// If to login
		if (invalid == 0)
		{
			if (result->data.type == USER_ADMIN)
			{
				extern int administratorLogin(account_list_t theUser);
				toExit = administratorLogin(result);
			}
			else if (result->data.type == USER_MANAGER)
			{
				extern int managerLogin(account_list_t theUser);
				toExit = managerLogin(result);
			}
			else if (result->data.type == USER_CLERK)
			{
				extern int clerkLogin(account_list_t theUser);
				toExit = clerkLogin(result);
			}
		}
	}
}