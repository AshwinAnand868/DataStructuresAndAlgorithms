/********************************************************************/
/*                                                                  */
/*   lab 2 timing file                                              */
/*                                                                  */
/*   To compile: g++ lab2.cpp lab2timing.cpp timer.cpp -std=c++0x   */
/*   NOTE: if you are working in windows, change the #define        */
/*   PLATFORM line in timer.h, see comments in that file            */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include "timer.h"
#include <iostream>
using namespace std;

unsigned int factorial(unsigned int n);
double power(double base, unsigned int n);
unsigned int fibonacci(unsigned int n)
{
	unsigned int result = 0;
	if (n < 2)
		result = n;
	else
	{
		result = fibonacci(n - 1) + fibonacci(n - 2);
	}

	return result;
}

int main(void)
{
	unsigned int n = 45;
	unsigned int rc;
	Timer t;
	t.start();
	rc = fibonacci(n);
	t.stop();
	cout << "fibonacci (" << n << ") = " << rc << endl;
	cout << "fibonacci (" << n << ") took " << t.currtime() << " s" << endl;
	return 0;
}
