
extern void studio_UI_manageStudios(account_list_t theUser);

extern void studio_UI_viewStudiosForAdmin(int howManyPerPage);

extern void printStudioAdminListOneLine(int whichOne, int selected);

extern void studio_UI_modifyStudio(theStudioToModify);

extern void studio_UI_changeName(studio_list_t theStudioToModify);

extern int studio_UI_deleteStudio(studio_list_t theStudioToModify);

extern void studio_UI_checkByID();

extern void studio_UI_checkByName();

extern void studio_UI_createAStudio();