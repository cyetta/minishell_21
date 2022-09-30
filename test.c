#include <stdio.h>

int	main(int argc, char **argv, char **argp)
{
	int		i;

	i = -1;
	while (++i < argc)
	{
		printf("%s\n", argv[i]);
	}
	return(argc - 1);
}
