/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:53:41 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 08:54:04 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
