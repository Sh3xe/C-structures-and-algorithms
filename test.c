#include "list.h"

bool lst_test()
{
	bool condition = true;

	lst_t lst;
	lst_create(&lst, 4);

	for(int i = 0; i < 10; ++i)
	{
		lst_push_back(&lst, i);
	}

	



	return true;
}