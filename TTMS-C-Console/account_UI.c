#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"

void account_UI_creatAdmin()
{
	setBackgroundColor(6);
	setFontColor(7);
	setFontBackGroudColor(6);

	system("cls");

	printTitleWithCurrentTime("Create an account", 19);
	printMultipleTimes('\n', 2);
	printMiddleAddjusted("Please fill in these information:", 34);
	printMultipleTimes('\n', 3);

	account_t inputAccount;

	// Username
	setFontColor(1);
	printMiddleLeft("(6-29)(al+num)", 15, 2);
	printf("\n");
	setFontColor(7);
	printMiddleLeft("Username:", 10, 2);
	printMultipleTimes(' ', 2);
	inputAlnum(inputAccount.username, 30, 6);
	printf("\n\n");

	// password
	int match = 0;
	while (match == 0)
	{
		setFontColor(1);
		printMiddleLeft("(6-29)", 7, 2);
		printf("\n");
		setFontColor(7);
		printMiddleLeft("Password:", 10, 2);
		printMultipleTimes(' ', 2);
		char one[30], two[30];
		inputPassword(one, 30, 6);
		printf("\n");
		printMiddleLeft("Once again:", 12, 2);
		printMultipleTimes(' ', 2);
		inputPassword(two, 30, 6);
		printf("\n\n");

		if (strcmp(one, two) == 0)
		{
			match = 1;
			strcpy(inputAccount.password, one);
			break;
		}
		else
		{
			setFontColor(1);
			printf("\n\n");
			printMiddleAddjusted("Two passwords don't match!", 27);
			printf("\n");
			keyToContinue();

			// Reload page
			setBackgroundColor(6);
			setFontColor(7);
			setFontBackGroudColor(6);

			system("cls");

			printTitleWithCurrentTime("Create an account", 19);
			printMultipleTimes('\n', 2);
			printMiddleAddjusted("Please fill in these information:", 34);
			printMultipleTimes('\n', 3);

			// Username
			setFontColor(1);
			printMiddleLeft("(6-29)(al+num)", 15, 2);
			printf("\n");
			setFontColor(7);
			printMiddleLeft("Username:", 10, 2);
			printMultipleTimes(' ', 2);
			//inputAlnum(inputAccount.username, 30, 6);
			printf("%s", inputAccount.username);
			printf("\n\n");
		}
	}

	// User Type
	inputAccount.type = USER_ADMIN;
	printMiddleLeft("Account Type:", 14, 2);
	printMultipleTimes(' ', 2);
	printf("Administrator\n\n\n");

	// Nickname
	setFontColor(1);
	printMiddleLeft("Letters and \"-\", 6-29)", 23, 2);
	setFontColor(7);
	printf("\n");
	printMiddleLeft("Nickname:", 10, 2);
	printMultipleTimes(' ', 2);
	inputName(inputAccount.nickname, 30, 6);
	printf("\n\n");

	// Phone number
	printMiddleLeft("Phone number:", 14, 2);
	printf("  ");
	inputNumber(inputAccount.phone, 20, 0);
	printf("\n\n");

	system("pause");
}