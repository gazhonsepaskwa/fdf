#include "../libft.h"

void ft_sleep(int time)
{
	int i;

	ft_printf("\n%sSleeping... ", YELLOW);
	while (i < time)
	{
		ft_printf("\rSleeping... [%d/%ds]", i, time);
		sleep(1);
		i++;
	}
		ft_printf("\rSleeping... [%d/%ds] - DONE%s\n", i, time, RESET);
}
