#include "scop.h"

int		flag(int64_t *f, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!strcmp(argv[i], "-void"))
			*f |= 0;
		else
			return (i);
		i++;
	}
	return (i);
}
