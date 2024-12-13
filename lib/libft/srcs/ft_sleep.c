/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:37:04 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/10 17:37:05 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_sleep(int time)
{
	int	i;

	ft_printf("\n%sSleeping... ", YELLOW);
	while (i < time)
	{
		ft_printf("\rSleeping... [%d/%ds]", i, time);
		sleep(1);
		i++;
	}
	ft_printf("\rSleeping... [%d/%ds] - DONE%s\n", i, time, RESET);
}
