/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name:  Ashwin Anand                           */
/*  Student number:  152042206                    */
/*                                                */
/**************************************************/

/* Recursively */

typedef unsigned long long ull; // an alias to the unsigned long long type


unsigned long long factorial(unsigned int n)
{
	ull result = 1;							
	if (n > 1)								
		result = n * factorial(n - 1);		
	return result;
}

unsigned long long power (unsigned int base, unsigned int n){
	ull result = 1;										
	if (n >= 1)											
		result = base * power(base, n - 1);				
	return result;

}
unsigned long long fibonacci (unsigned int n){
	ull result = 0;									
	if (n < 2)									
		result = n;									
	else
	{
		result = fibonacci(n - 1) + fibonacci(n - 2);
	}

	return result;
}