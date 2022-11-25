/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:28:19 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 12:28:19 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = ft_calloc(sizeof(t_vars), 1);
	if (vars == NULL)
		return (0);
	validity_check_handler(argc, argv, vars);
	game_init(vars, argv);
	put_map(vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, 33, (1L << 17), exit_game, vars);
	mlx_hook(vars->win, 12, (1L << 15), print_movement, vars);
	mlx_loop(vars->mlx);
	exit_game(vars);
	return (1);
}

// gcc -Wall -Wextra -Werror -g *.c so_long.h mlx/libmlx_Linux.a 
//-L /usr/include/X11/extensions/ -lXext -lX11 -lm
// export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | 
//awk '{print $2}'):0.0