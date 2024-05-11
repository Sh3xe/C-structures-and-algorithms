#include "list.h"
#include "hash_table.h"
#include <stdio.h>

void lst_print( lst_t *list )
{
	for(uint32_t i = 0; i < lst_size(list); ++i)
	{
		printf("%d ", lst_nth(list, i));
	}
	printf("\n");
}

int main()
{
	ht_t al;
	ht_create(&al, 8);

	ht_push(&al, "arnaud", 21);
	ht_push(&al, "pierre", 22);

	int a = 0, b = 0, c = 0, d = 0, e = 0;
	bool got_a = ht_get(&al, "arnaud", &a);
	bool got_b = ht_get(&al, "arnauaad", &b);
	bool got_c = ht_get(&al, "pierre", &c);

	ht_remove(&al, "pierre");

	bool got_d = ht_get(&al, "pierre", &d);


	printf("a: %d %d\n", a, got_a);
	printf("b: %d %d\n", b, got_b);
	printf("c: %d %d\n", c, got_c);
	printf("d: %d %d\n", d, got_d);

	ht_destroy(&al);
	return 0;
}