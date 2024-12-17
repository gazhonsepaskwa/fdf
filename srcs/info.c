/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:32:57 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 09:26:04 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_info(void *xsrv, void *win)
{
	int	col;

	col = 0xffffff;
	mlx_string_put(xsrv, win, 50, 50, col, "Keyboard :");
	mlx_string_put(xsrv, win, 50, 80, col, "    w   ");
	mlx_string_put(xsrv, win, 50, 100, col, "  a s d  => move camera");
	mlx_string_put(xsrv, win, 50, 125, col, "   ===");
	mlx_string_put(xsrv, win, 50, 150, col, " Keypad :");
	mlx_string_put(xsrv, win, 50, 180, col, "  ~ + -  => zoom");
	mlx_string_put(xsrv, win, 50, 200, col, "  ~ ~ ~");
	mlx_string_put(xsrv, win, 50, 220, col, "  < o >  => rotate");
	mlx_string_put(xsrv, win, 50, 240, col, "    |=====> front view");
}
