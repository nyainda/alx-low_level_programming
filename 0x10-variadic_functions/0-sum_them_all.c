#include "variadic_functions.h"
#include <stdarg.h>

/**
 * sum_them_all - function that returns the sum of all its parameters
 * @n: number of parameters
 * Return: Sum of all parameters
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list list;
	int sum =0;
	unsigned int a;

	if (n == 0)
        {

		return (0);
        }
	
	va_start(list, n);
	
	for (a = 0; a < n; a++)
        {
		sum += va_arg(list, int);

        }
	
	va_end(list);
	
	return (sum);
}
