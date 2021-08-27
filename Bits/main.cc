//The following is a sample main.cc.  Modify it to test your program.
//Make sure to test thoroughly.  All the pieces below have to be included.

#include <stdio.h>

//These are called prototypes and they have to be here.
//Any function in assign1.cc that you also call from main must be listed here. 
//For now, make sure you include the following 3 lines in main.cc
int getMask(int, int, int);
int getSubInt(int, int, int);
void printDashHex(int);

//This function will run when you run your program from the command line.
int main(void)
{
	unsigned int mask;
	unsigned int subInt;
	
	//Test getMask.  Note that this only prints tests that fail.
	//Put an else in if you want to see tests that pass also.
	mask = getMask(2, 6, 1); 
	if (mask != 124)
		printf("Fail getMask(2,6,1) should return 124.\n");
	//Put more getMask tests here


	//Test getSubInt. Note that this only prints tests that fail.
	//Put an else in if you want to see tests that pass also.
	subInt = getSubInt(4, 6, 210);
	if (subInt != 5)
		printf("Fail getSubInt(4,6,210) should return 5.\n"); 
	//Put more getSubInt tests here


	//Test printDashHex
	//String tests will be a little tricky until we learn more.
	//The below will look like this if the result is correct.
	//
	//	Testing printDashHex(157)
	//	Expected: 0-0-0-0-0-0-9-D
	//	MyResult: 0-0-0-0-0-0-9-D
	//
	printf("Testing printDashHex(157)\n");
	printf("Expected: 0-0-0-0-0-0-9-D\nMyResult: ");
	printDashHex(157);

	printf("Testing printDashHex(157)\n");
	printf("Expected: 0-0-0-0-0-0-9-D\nMyResult: ");
	printDashHex(0x9d);
	
	printf("Expected: 0-0-0-0-0-0-0-1\nMyResult: ");
	printDashHex(1);

	printf("Expected: 0-0-0-0-0-0-0-2\nMyResult: ");
	printDashHex(2);

	//Add more printDashHex tests here

	return 0;
}

