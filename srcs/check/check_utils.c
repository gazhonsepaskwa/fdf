#include "check.h"

int	getnlen(char *str)
{
	int	i;
	int	count;

	count = 1;
	i = 1;
	while (str[++i])
		if (ft_isdigit(str[i]) && (str[i - 1] == 32
				|| str[i - 1] == '-'))
			count++;
	return (count);
}
