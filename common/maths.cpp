#include "maths.hpp"

int compare(long double n1, long double n2)
{
	return (n1 - n2) < PRECISION;
}
