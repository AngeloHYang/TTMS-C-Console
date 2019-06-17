#include <stdio.h>
int main()
{
	printf("Hello, world!\n");
	extern void test();
	test();
	return 0;
}