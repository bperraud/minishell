
#include "minishell.h"

int	pwd()
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}
