/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Ashwin Anand                            */
/*  Student number: 152042206                     */
/*                                                */
/**************************************************/



typedef unsigned long long ull;  // creating an alias to represent the fundamental type "unsigned long long"

unsigned long long factorial(unsigned int n)
{
	ull result = 1;				
	for (ull i = n; i > 1; i--) 
		result *= i;                     
	return result;				
}


unsigned long long power(unsigned int base, unsigned int n)
{
	ull result = 1;                  
	for (ull i = n; i > 0; i--)       
		result = base * result;      
	return result;					
}

unsigned long long fibonacci(unsigned int n)
{
	ull newFib = 0;								
	ull previousFib = 0, currentFib = 1;		


	if (n < 2)								    
		newFib = n;								
	else
	{
		for (unsigned int i = 1; i < n; i++)	
		{
			newFib = previousFib + currentFib;  
			previousFib = currentFib;			
			currentFib = newFib;				
		}
	}
	return newFib;								
}