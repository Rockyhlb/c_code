#include "hash.h"
#include <stdlib.h>

int main()
{
	HASH hash;
	init_hash(&hash);

	int i = 100;
	while(i--)
		insert_hash(&hash, rand()%100);

	show_hash(&hash);
}