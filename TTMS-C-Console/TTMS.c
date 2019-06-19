#include <stdio.h>
int main()
{
	extern void all_Load();
	all_Load();

	extern void test();
	test();

	extern void all_Save();
	all_Save();
	
	return 0;
}