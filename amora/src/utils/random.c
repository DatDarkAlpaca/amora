#include "random.h"
#include <stdlib.h>

int get_rand_int(int min, int max)
{
	return min + rand() % (max + 1 - min);
}
