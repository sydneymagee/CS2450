#include <stdio.h>

//Prototypes the following six lines must 
//be here or the program will not compile
double findCloseToZero(double * , int);
double findFarFromZero(double *, int); 
int countDivisible(int *, int, int); 
double sumFractions(double *, int);
int countAbsoluteRangeValues(double *, int, double);
 
void test1();

int main()
{
	test1();

	return 0;
}

void test1()
{
  //Temporary storage
  double dv = 0;
  int iv = 0;

  //Generate an array then run student functions
	double myArray[] = {2.1,3.2,0.6,1.3,2.5,5.11,6.2,6.0,5.2,4.2};
  int myIntArray[] = {2,3,0,16,20,5,6,6,5,4,8};
    
  //Test findCloseToZero
  dv = findCloseToZero(myArray, 10);
  if (dv != 0.6) printf("FAIL in findCloseToZero().  Expected 0.6.\n");
  //printf("value=%f\n", dv);
  
  //Test findFarFromZero  
  dv = findFarFromZero(myArray, 10);
  if (dv != 6.2) printf("FAIL in findFarFromZero().  Expected 6.2.\n");
  //printf("value=%f\n", dv);
  
  //Test countDivisible  
  iv = countDivisible(myIntArray, 11, 4);
  if (iv != 5) printf("FAIL in countDivisible().  Expected 5.\n");
  //printf("value=%d\n", iv);
  
  //Test sumFractions
  dv = sumFractions(myArray, 10);
  //Math is tricky with doubles.  Answer should be 2.41, but will actually be "very close" to 2.41
  //Assume 6 decimal places.
  //Low is 2.409999
  //High is 2.410001
  if (dv < 2.409999 || dv > 2.410001) printf("FAIL in sumFractions().  Expected 2.41.\n");
  //printf("value=%.20f\n", dv);

  double myArray2[] = {-5.0, -3.6, -3.1, -2.7, -2.6, -1.2, 0.1, 1.5, 1.8, 2.7, 3.0, 3.5, 3.6, 4.0 };
  iv = countAbsoluteRangeValues(myArray2, 14, 3.1);
  if (iv != 5) printf("FAIL in countAbsoluteRangeValues().  Expected 5.\n");
  //printf("value=%d\n", iv);
}
