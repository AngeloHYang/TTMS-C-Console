extern int account_UI_creatAdmin();

extern void account_UI_changeProfile(account_list_t theUser);

extern void account_UI_manageAccounts(account_list_t theUser);

// To change a basic element

extern void account_UI_changePassword(account_list_t theUser);

extern void account_UI_changePassword(account_list_t theUser);

extern void account_UI_changePhoneNumber(account_list_t theUser);

extern void account_UI_changeNickname(account_list_t theUser);

extern void account_UI_viewAccounts(account_list_t theUserNow, int howManyPerPage);

extern void printUserListOneLine(int whichOne, int selected);

extern void account_UI_modifyUser(account_list_t theUserNow, account_node_t* theUserToModify);

extern int account_UI_deleteAccount(account_list_t theUserNow, account_list_t theUserToDelete);

extern void account_UI_checkByID(account_list_t theUserNow);

extern void account_UI_checkByUsername(account_list_t theUserNow);

extern void account_UI_createAccount();