#include "list.h"
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
	lst_t list;
	lst_create(&list, 4);

	for(int i = 0; i < 5; ++i)
	{
		lst_push_back(&list, 2*i);
		lst_push_front(&list, -i);
	}

	lst_print(&list);

	for(int i = 0; i < 3; ++i)
	{
		lst_pop_front(&list);
	}

	lst_print(&list);

	lst_destroy(&list);
	return 0;
}