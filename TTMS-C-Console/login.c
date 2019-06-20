#include <stdio.h>
#include <string.h>
#include "account_srv.h"
#include "printChoices.h"
#include "color.h"
#include "account_UI.h"

void noUserLogin();

void uesrLogin();

void login()
{
	setBackgroundColor(0);
	setFontColor(7);
	setFontBackGroudColor(0);

	// Test if it's the first time 
	system("cls");
	printTitleWithCurrentTime("Welcome", 8);

	printMultipleTimes('\n', 5);

	if (account_srv_howManyInToto() == 0)
	{
		noUserLogin();
	}
	else
	{
		uesrLogin();
	}
}

void noUserLogin()
{
	printMiddleAddjusted("It looks like it's your first time lauching this APP", 54);
	printMultipleTimes('\n', 2);
	printMiddleAddjusted("So, let's set up an Administrator account", 43);
	printMultipleTimes('\n', 10);
	keyToContinue();
	account_UI_creatAdmin();


}

void uesrLogin()
{
	printMultipleTimes(' ', 5);
}