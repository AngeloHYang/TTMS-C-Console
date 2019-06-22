#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "printChoices.h"
#include "color.h"
#include "inputMethod.h"
#include "account_srv.h"
#include "templates.h"
#include "List.h"

void account_UI_changePassword(account_list_t theUser);

void account_UI_changePhoneNumber(account_list_t theUser);

void account_UI_changeNickname(account_list_t theUser);

void account_UI_viewAccounts(account_list_t theUserNow, int howManyPerPage);

void printUserListOneLine(int whichOne, int selected);

void account_UI_modifyUser(account_list_t theUserNow, account_node_t* theUserToModify);

int account_UI_deleteAccount(account_list_t theUserNow, account_list_t theUserToDelete);

void account_UI_checkByID(account_list_t theUserNow);

void account_UI_checkByUsername(account_list_t theUserNow);

void account_UI_createAccount();

//////////////////////////////////////////////////////////////////////////////////////////

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
}

void account_UI_changeProfile(account_list_t theUser)
{
	int toReturn = 0;
	int navigation = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

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
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
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
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Select with \"Enter\".\n");
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
				account_UI_changeNickname(theUser);
			}
			else if (navigation == 3)
			{
				break;
			}
		}
	}
	free(greet);


}

void account_UI_manageAccounts(account_list_t theUser)
{
	int toReturn = 0;
	int selection = 0;
	char inputChar = '\0';

	char* greet = (char*)malloc(sizeof(char) * 100);

	char Menu[][100] = { "View Accounts", "Check by ID", "Check by Username", "Create an Account", "Return"};

	char* pointers[] = { Menu[0], Menu[1], Menu[2], Menu[3], Menu[4] };

	while (toReturn == 0)
	{
		memset(greet, '\0', sizeof(char) * 100);
		strcat(greet, "Hello, ");
		strcat(greet, theUser->data.nickname);
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		selection = standardSelectMenuView(7, 0, "Account Management", "Add, modify, or delete an account", 34, pointers, 5, 100);

		if (selection == 0)
		{
			account_UI_viewAccounts(theUser, 10);
		} else if (selection == 1)
		{
			account_UI_checkByID(theUser);
		}
		else if (selection == 2)
		{
			account_UI_checkByUsername(theUser);
		} else if (selection == 3)
		{
			account_UI_createAccount();
		}
		else if (selection == 4)
		{
			toReturn = 1;
		}
	}
	free(greet);
}

// To change a basic element

	// personal profile
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

void account_UI_changeNickname(account_list_t theUser)
{
	int goBack = 0;
	int match = 0;

	match = 0;
	char newName[30];
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Changing Nickname", 18);
	printMultipleTimes('\n', 2);
	char input[100] = "Let's set up a new nickname for ";
	strcat(input, theUser->data.username);

	printMiddleAddjusted(input, strlen(input) + 1);

	printf("\n\n");

	setFontColor(1);
	printMiddleLeft("Letters and \"-\", 1-29)", 23, 2);
	setFontColor(0);
	printf("\n");
	printMiddleLeft("Nickname:", 10, 2);
	printf("  ");
	inputName(newName, 30, 1);
	printf("\n\n");

	if (areYouSure() == 1)
	{
		printf("\n\n");
		strcpy(theUser->data.nickname, newName);
		printMiddleAddjusted("Nickname updated!", 22);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		printf("\n\n");
		printMiddleAddjusted("Failed to change the nickname!", 31);
		printf("\n\n");
		keyToContinue("Continue", 8);
	}
}

	// viewAccounts
void account_UI_viewAccounts(account_list_t theUserNow, int howManyPerPage)
{
	//howManyPerPage = 3;

	// Page sum
	int pageSum;
	if (account_srv_howManyInToto() % howManyPerPage == 0)
	{
		pageSum = account_srv_howManyInToto() / howManyPerPage;
	}
	else
	{
		pageSum = account_srv_howManyInToto() / howManyPerPage + 1;
	}

	int currentPage = 1;
	int currentOne = 1;
	int selection = 1;

	int toReturn = 0;
	char pressedKey = '\0';
	
	/*
	3			 95 			2
	            username ID phone nickname
		1   30   1 10 1 20 1 30 1
	*/
	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");

		printTitleWithCurrentTime("View Accounts", 14);
		printMultipleTimes('\n', 3);
		//if (account_srv_howManyInToto() != 0)
		//{
			printMultipleTimes(' ', 3);
			printMultipleTimes('-', 95);
			printf("\n");
		//}
		// ±íÍ·
			printMultipleTimes(' ', 3);
			printf("|");
			printf("%-30s", "Username");
			printf("|");
			printf("%-10s", "ID");
			printf("|");
			printf("%-20s", "Phone Number");
			printf("|");
			printf("%-30s", "Nickname");
			printf("|");
			printf("\n");
			printMultipleTimes(' ', 3);
			printMultipleTimes('-', 95);
			printf("\n");

		// ÄÚÈÝ
		for (int whichOneToPrint = (currentPage - 1) * howManyPerPage + 1; whichOneToPrint <= min(account_srv_howManyInToto(), currentPage * howManyPerPage); whichOneToPrint++)
		{
			currentOne = whichOneToPrint % howManyPerPage;
			if (currentOne == 0)
			{
				currentOne = howManyPerPage;
			}

			if (currentOne == selection)
			{
				//setBackgroundColor(0);
				//setFontColor(7);

				printUserListOneLine(whichOneToPrint, 1);

				//setBackgroundColor(7);
				//setFontColor(0);
			}
			else
			{
				printUserListOneLine(whichOneToPrint, 0);
			}
		}

		// Return button
		if ((account_srv_howManyInToto() % howManyPerPage) == 0)
		{
			//printf("Zero!\n");
		}
		else
		{
			printMultipleTimes('\n', (howManyPerPage - (account_srv_howManyInToto() % howManyPerPage)) * 2);
		}

		printMultipleTimes(' ', (100 - strlen("Return")) / 2);
		if (selection == howManyPerPage + 1)
		{
			setBackgroundColor(0);
			setFontColor(7);
		}
		printf("Return");
		setBackgroundColor(7);
		setFontColor(0);
		printf("\n");
		print_(100);
		printf("\n ¡ñ Switch with \"W\", \"S\", \"A\", \"D\". Select with \"Enter\".");
		printMultipleTimes(' ', 28);
		printf("Page: %d/%d", currentPage, pageSum);

		// Receive
		pressedKey = _getch();
		if (pressedKey == 'w' || pressedKey == 'W')
		{
			if (currentPage == pageSum && selection == howManyPerPage + 1)
			{
				if (account_srv_howManyInToto() % howManyPerPage != 0)
				{
					selection = (account_srv_howManyInToto() % howManyPerPage);
				}
				else
				{
					selection = howManyPerPage;
				}
			}
			else if (selection > 1)
			{
				selection--;
			}
		}
		else if (pressedKey == 'S' || pressedKey == 's')
		{
			if (currentPage < pageSum)
			{
				if (selection <= howManyPerPage)
				{
					selection++;
				}
			}
			else 
			{
				if ((account_srv_howManyInToto() % howManyPerPage) == 0)
				{
					if (selection <= howManyPerPage)
					{
						selection++;
					}
				}
				else
				{
					if (selection == (account_srv_howManyInToto() % howManyPerPage))
					{
						selection = howManyPerPage + 1;
					}
					else if (selection < (account_srv_howManyInToto() % howManyPerPage))
					{
						selection++;
					}
				}
			}
		}
		else if (pressedKey == 'a' || pressedKey == 'A')
		{
			if (currentPage > 1)
			{
				currentPage--;
			}
		}
		else if (pressedKey == 'd' || pressedKey == 'D')
		{
			if (currentPage < pageSum)
			{
				currentPage++;
				if (currentPage == pageSum && selection >(account_srv_howManyInToto() % howManyPerPage))
				{
					selection = account_srv_howManyInToto() % howManyPerPage;
				}
			}
		}
		else if (pressedKey == 13)
		{
			if (selection == howManyPerPage + 1)
			{
				toReturn = 1;
			}
			else
			{
				int theOneToModify = selection + (currentPage - 1) * howManyPerPage;
				account_node_t* theUserToModify = account_srv_findByWhichOne(theOneToModify);
				account_UI_modifyUser(theUserNow, theUserToModify);

				// Update page sum
				if (account_srv_howManyInToto() % howManyPerPage == 0)
				{
					pageSum = account_srv_howManyInToto() / howManyPerPage;
				}
				else
				{
					pageSum = account_srv_howManyInToto() / howManyPerPage + 1;
				}

				if (currentPage > pageSum)
				{
					currentPage--;
				}
				selection = howManyPerPage + 1;
			}
		}
		// Update page sum
		if (account_srv_howManyInToto() % howManyPerPage == 0)
		{
			pageSum = account_srv_howManyInToto() / howManyPerPage;
		}
		else
		{
			pageSum = account_srv_howManyInToto() / howManyPerPage + 1;
		}
	}
}

void printUserListOneLine(int whichOne, int selected)
{
	account_node_t* thisOne = account_srv_findByWhichOne(whichOne);

	printMultipleTimes(' ', 3);
	if (selected == 1)
	{
		setBackgroundColor(0);
		setFontColor(7);
	}
	printf("|");
	printf("%-30s", thisOne->data.username);
	printf("|");
	printf("%-10d", thisOne->data.ID);
	printf("|");
	printf("%-20s", thisOne->data.phone);
	printf("|");
	printf("%-30s", thisOne->data.nickname);
	printf("|");
	if (selected == 1)
	{
		setBackgroundColor(7);
		setFontColor(0);
	}
	printf("\n");
	printMultipleTimes(' ', 3);
	printMultipleTimes('-', 95);
	printf("\n");
}

	// changeUser
void account_UI_modifyUser(account_list_t theUserNow, account_node_t* theUserToModify)
{

	int toReturn = 0;
	int navigation = 0;
	char inputChar = '\0';

	char type[20];

	if (theUserToModify->data.type == USER_CLERK)
	{
		strcpy(type, "Clerk");
	}
	else if (theUserToModify->data.type == USER_MANAGER)
	{
		strcpy(type, "Manager");
	}
	else if (theUserToModify->data.type == USER_ADMIN)
	{
		strcpy(type, "Administrator");
	}

	while (toReturn == 0)
	{
		setBackgroundColor(7);
		setFontColor(0);
		system("cls");
		char menu1[][30] = { "Password:"};
		char menu2[][30] = { "******" };

		// Unchangeable
		printTitleWithCurrentTime("Account Modify", 15);
		printMultipleTimes('\n', 2);

		
		printf("\n");
		
		printMultipleTimes('\n', 3);

		printMiddleLeft("Username:", 10, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", theUserToModify->data.username);

		printMiddleLeft("ID:", 4, 2);
		printMultipleTimes(' ', 2);
		printf("%d\n", theUserToModify->data.ID);

		printMiddleLeft("Type:", 6, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", type);

		printMiddleLeft("Nickname:", 10, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", theUserToModify->data.nickname);

		printMiddleLeft("Phone number:", 14, 2);
		printMultipleTimes(' ', 2);
		printf("%s\n", theUserToModify->data.phone);

		printMultipleTimes('\n', 3);

		// Changeable
		for (int whichOne = 0; whichOne <= 0; whichOne++)
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

		if (navigation == 1)
		{
			printMultipleTimes(' ', (100 - strlen("Delete Account")) / 2);

			setFontColor(7);
			setBackgroundColor(0);

			printf("%s", "Delete Account");

			setFontColor(0);
			setBackgroundColor(7);
		} else
		{
			printMultipleTimes(' ', (100 - strlen("Delete Account")) / 2);
			printf("%s", "Delete Account");
		}

		printf("\n\n");
		if (navigation == 2)
		{
			printMultipleTimes(' ', (100 - strlen("Return")) / 2);

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
		printf("\n\n ¡ñ Switch with \"W\", \"S\". Select with \"Enter\".\n");
		printMiddleAddjusted("", 1);
		inputChar = _getch();

		if (inputChar == 's' || inputChar == 'S')
		{

			if (navigation < 2)
			{
				navigation++;
			}
			else if (navigation == 2)
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
				navigation = 2;
			}
		}
		else if (inputChar == 13)
		{

			if (navigation == 0)
			{
				account_UI_changePassword(theUserToModify);
			}
			else if (navigation == 1)
			{
				if (account_UI_deleteAccount(theUserNow, theUserToModify) == 1)
				{
					break;
				}
			}
			else if (navigation == 2)
			{
				break;
			}
		}
	}
}

int account_UI_deleteAccount(account_list_t theUserNow, account_list_t theUserToDelete)
// If deleted, return 1
{
	int goBack = 0;
	
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Delete Account", 18);
	printMultipleTimes('\n', 2);

	if (theUserToDelete == theUserNow)
	{
		printMiddleAddjusted("You cannot delete yourself!", 28);
		printf("\n\n");
		keyToContinue("Continue", 8);
	} else
	{
		char input[100] = "The account ";
		strcat(input, theUserToDelete->data.username);
		strcat(input, " shall be deleted and cannot be restored!");

		printf("\n\n");
		if (areYouSure() == 1)
		{
			printf("\n\n");
			account_srv_deleteByID(theUserToDelete->data.ID);
			printMiddleAddjusted("Account deleted!", 17);
			printf("\n\n");
			keyToContinue("Continue", 8);
			return 1;
		} else
		{
			printf("\n\n");
			printMiddleAddjusted("Account not deleted!", 21);
			printf("\n\n");
			keyToContinue("Continue", 8);
			return 0;
		}
		
	}
	
}

	// Check By ID and username
void account_UI_checkByID(account_list_t theUserNow)
{
	int goBack = 0;
	
	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Check by ID", 18);
	printMultipleTimes('\n', 2);

	printMiddleAddjusted("Please input the ID of the account that you are looking for", 60);
	printf("\n\n\n");
	printMiddleLeft("ID:", 4, 2);
	printf("  ");
	int inputID = inputInt();

	printf("\n\n");
	account_list_t theUserLookingFor = account_srv_findByID(inputID);
	if (theUserLookingFor == NULL)
	{
		printMiddleAddjusted("The user you are looking for doesn't exist!", 44);
		printf("\n");
		keyToContinue("Continue", 8);
	} else
	{
		account_UI_modifyUser(theUserNow, theUserLookingFor);
	}
}

void account_UI_checkByUsername(account_list_t theUserNow)
{
	int goBack = 0;

	setBackgroundColor(7);
	setFontColor(0);
	system("cls");

	printTitleWithCurrentTime("Check by Username", 18);
	printMultipleTimes('\n', 2);

	printMiddleAddjusted("Please input the username of the account that you are looking for(not nickname)", 80);
	printf("\n\n\n");
	printMiddleLeft("Username:", 10, 2);
	printf("  ");
	char inputUsername[30];
	inputAlnum(inputUsername, 30, 6);

	printf("\n\n");
	account_list_t theUserLookingFor = account_srv_findByUsername(inputUsername);
	if (theUserLookingFor == NULL)
	{
		printMiddleAddjusted("The user you are looking for doesn't exist!", 44);
		printf("\n");
		keyToContinue("Continue", 8);
	}
	else
	{
		account_UI_modifyUser(theUserNow, theUserLookingFor);
	}
}

	// Create an account
void account_UI_createAccount()
{
	account_t inputAccount;
	while (1)
	// Check if the username is not used before
	{
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

		inputAlnum(inputAccount.username, 30, 6);
		if (account_srv_findByUsername(inputAccount.username) == NULL)
		{
			printf("\n\n");
			break;
		}
		else
		{
			printf("\n\n");
			setFontColor(1);
			printMiddleAddjusted("The username has been used. Please choose another one!", 55);
			setFontColor(0);
			printf("\n");
			keyToContinue("Continue", 8);
		}
	}

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
	int navigation = 0;
	char inputChar = '\0';
	while (1)
	{	
		// Reload
		setBackgroundColor(7);
		setFontColor(0);

		system("cls");
		//printf("NAvigation: %d\n", navigation);
		//printf("Just input: %c\n", inputChar);

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

		// Password
		setFontColor(1);
		printMiddleLeft("(6-29)", 7, 2);
		printf("\n");
		setFontColor(0);
		printMiddleLeft("Password:", 10, 2);
		printMultipleTimes(' ', 2);
		
		printMultipleTimes('*', strlen(inputAccount.password));
		printf("\n");
		printMiddleLeft("Once again:", 12, 2);
		printMultipleTimes(' ', 2);
		printMultipleTimes('*', strlen(inputAccount.password));
		printf("\n\n");


		printMiddleLeft("Account Type:", 14, 2);
		printMultipleTimes(' ', 1);

		char options[][15] = { "Clerk", "Manager", "Administrator" };

		for (int whichOne = 0; whichOne < 3; whichOne++)
		{
			if (navigation == whichOne)
			{
				printf(" ");
				setFontColor(7);
				setBackgroundColor(0);

				printf("%s", options[whichOne]);

				setFontColor(0);
				setBackgroundColor(7);
			}
			else
			{
				printf(" ");
				printf("%s", options[whichOne]);
			}
		}
		printf("\n\n");
		inputChar = _getch();
		
		if (inputChar == 'a' || inputChar == 'A')
		{
			if (navigation > 0)
			{
				navigation--;
			}
			else
			{
				navigation = 2;
			}
		}
		else if (inputChar == 'D' || inputChar == 'd')
		{
			if (navigation < 2)
			{
				navigation++;
			}
			else
			{
				navigation = 0;
			}
		}
		else if (inputChar == 13)
		{
			break;
		}
	}

	if (navigation == 0)
	{
		inputAccount.type = USER_CLERK;
	}
	else if (navigation == 1)
	{
		inputAccount.type = USER_MANAGER;
	}
	else if (navigation == 2)
	{
		inputAccount.type = USER_ADMIN;
	}

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
}