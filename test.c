#include <stdio.h>

int	main(int argc, char **argv, char **argp)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		printf("%s\n", argv[i]);
	}
}
