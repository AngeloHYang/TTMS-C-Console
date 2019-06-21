#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"

void account_UI_changePassword(account_list_t theUser);

void account_UI_changePhoneNumber(account_list_t theUser);

int account_UI_creatAdmin()
{
	setBackgroundColor(7);
	setFontColor(0);

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
	setFontColor(0);
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
		setFontColor(0);
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
			keyToContinue("Continue", 8);

			// Reload page
			setBackgroundColor(7);
			setFontColor(0);

			system("cls");

			printTitleWithCurrentTime("Create an account", 19);
			printMultipleTimes('\n', 2);
			printMiddleAddjusted("Please fill in these information:", 34);
			printMultipleTimes('\n', 3);

			// Username
			setFontColor(1);
			printMiddleLeft("(6-29)(al+num)", 15, 2);
			printf("\n");
			setFontColor(0);
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
	printMiddleLeft("Letters and \"-\", 1-29)", 23, 2);
	setFontColor(0);
	printf("\n");
	printMiddleLeft("Nickname:", 10, 2);
	printMultipleTimes(' ', 2);
	inputName(inputAccount.nickname, 30, 1);
	printf("\n\n");

	// Phone number
	printMiddleLeft("Phone number:", 14, 2);
	printf("  ");
	inputNumber(inputAccount.phone, 20, 0);
	printf("\n\n");

	if (areYouSure() == 1)
	{
		inputAccount.ID = account_srv_getID();
		account_srv_add(inputAccount);
		printf("\n\n");
		printMiddleAddjusted("Added successfully!", 20);
		printf("\n");
		extern void all_Save();
		void all_Save();
		keyToContinue("Continue", 8);
		return 1;
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Failed to add!", 15);
		printf("\n");
		keyToContinue("Continue", 8);
		return 0;
	}
	
	system("pause");
}

void account_UI_changeProfile(account_list_t theUser)
{
	int toReturn = 0;
	int navigation = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);
	memset(greet, '\0', sizeof(char) * 100);
	strcat(greet, "Hello, ");
	strcat(greet, theUser->data.nickname);

	char type[20];

	if (theUser->data.type == USER_CLERK)
	{
		strcpy(type, "Clerk");
	}
	else if (theUser->data.type == USER_MANAGER)
	{
		strcpy(type, "Manager");
	}
	else if (theUser->data.type == USER_ADMIN)
	{
		strcpy(type, "Administrator");
	}

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");
		char menu1[][30] = { "Password:", "Phone Number:", "Nickname:" };
		char menu2[3][30] = { "******" };
		strcpy(menu2[1], theUser->data.phone);
		strcpy(menu2[2], theUser->data.nickname);

		// Unchangeable
		printTitleWithCurrentTime("Personal Profile", 17);
		printMultipleTimes('\n', 2);
		
		printMiddleAddjusted(greet, 100);
		printf("\n");
		printMiddleAddjusted("You can view and configure your profile here", 100);
		printMultipleTimes('\n', 3);

		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theUser->data.ID);

		printMiddleLeft("Username:", 10, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", theUser->data.username);

		printMiddleLeft("Type:", 6, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", type);
		printMultipleTimes('\n', 3);

		// Changeable
		for (int whichOne = 0; whichOne <= 2; whichOne++)
		{
			if (navigation == whichOne)
			{
				printMultipleTimes(' ', (50 - strlen(menu1[whichOne]) - 2));

				setFontColor(7);
				setBackgroundColor(0);

				printf("%s", menu1[whichOne]);

				setFontColor(0);
				setBackgroundColor(7);
				printMultipleTimes(' ', 2);
				printf("%s\n", menu2[whichOne]);
			}
			else
			{
				printMiddleLeft(menu1[whichOne], strlen(menu1[whichOne]) + 1, 2);
				printMultipleTimes(' ', 2);
				printf("%s\n", menu2[whichOne]);
			}
		}

		printf("\n\n");
		if (navigation == 3)
		{
			printMultipleTimes(' ', (100 - strlen("Return")) /2 );

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", "Return");

			setFontColor(0);
			setBackgroundColor(7);
		}
		else
		{
			printMiddleAddjusted("Return", 7);
		}
		
		anotherLine(6);
		print_(100);
		printf("\n\n �� Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{
			if (navigation < 3)
			{
				navigation++;
			}
			else if (navigation == 3)
			{
				navigation = 0;
			}
		}
		else if (inputChar == 'w' || inputChar == 'W')
		{
			if (navigation > 0)
			{
				navigation--;
			}
			else if (navigation == 0)
			{
				navigation = 3;
			}
		}
		else if (inputChar == 13)
		{

			if (navigation == 0)
			{
				account_UI_changePassword(theUser);
			} 
			else if (navigation == 1)
			{
				account_UI_changePhoneNumber(theUser);
			}
			else if (navigation == 2)
			{

			}
			else if (navigation == 3)
			{
				break;
			}
		}
	}
	free(greet);


}

void account_UI_changePassword(account_list_t theUser)
{
	int goBack = 0;
	int match = 0;

	match = 0;
	char one[30], two[30];
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Changing Password", 19);
	printMultipleTimes('\n', 2);
	char input[100] = "Let's set up a new password for ";
	strcat(input, theUser->data.username);

	printMiddleAddjusted(input, strlen(input) + 1);

	printf("\n\n");
	setFontColor(1);
	printMiddleLeft("(6-29)", 7, 2);
	printf("\n");
	setFontColor(0);
	printMiddleLeft("New password:", 14, 2);
	printMultipleTimes(' ', 2);
	inputPassword(one, 30, 6);
	printf("\n");
	printMiddleLeft("Once again:", 12, 2);
	printMultipleTimes(' ', 2);
	inputPassword(two, 30, 6);
	printf("\n\n");

	if (strcmp(one, two) == 0)
	{
		match = 1;
		strcpy(theUser->data.password, one);
		printMiddleAddjusted("Password updated!", 18);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		setFontColor(1);
		printf("\n\n");
		printMiddleAddjusted("Two passwords don't match!", 27);
		printf("\n\n");
		setFontColor(0);
		printMiddleAddjusted("Failed to reset the password!", 30);
		printf("\n\n");
		keyToContinue("Continue", 8);

	}
}

void account_UI_changePhoneNumber(account_list_t theUser)
{
	int goBack = 0;
	int match = 0;

	match = 0;
	char inputPhone[20];
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Changing Phone Number", 22);
	printMultipleTimes('\n', 2);
	char input[100] = "Let's set up a new phone number for ";
	strcat(input, theUser->data.username);

	printMiddleAddjusted(input, strlen(input) + 1);

	printf("\n\n");
	
	
	printMiddleLeft("Phone number:", 14, 2);
	printf("  ");
	inputNumber(inputPhone, 20, 0);
	printf("\n\n");

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(theUser->data.phone, inputPhone);
		printMiddleAddjusted("Phone number updated!", 22);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Failed to change the phone number!", 35);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}