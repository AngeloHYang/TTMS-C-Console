extern int printMiddleAddjusted(char* inputThings, int maxSize);

extern int printNumberAndContentWithStartplace(int number, char* inputThings, int startPlace, int maxSize);

extern int printWithStartPlace(char* inputThings, int startPlace, int maxSize);

extern void anotherLine(int lines);

extern void printTitle(char* title, int maxSize);

extern void printMultipleTimes(char character, int times);

extern void printTitleWithCurrentTime(char* title, int maxSize);

extern void print_(int howMany);

/*
#define keyToContinue printMiddleAddjusted("Press any key to enter", 23);\
	_getch
*/

extern void keyToContinue();

extern void printMiddleLeft(char* inputThings, int maxSize, int offset);