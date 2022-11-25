/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:50:47 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:50:47 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	draw_enemy(t_vars *vars)
{
	if (vars->enemy->img)
		mlx_destroy_image(vars->mlx, vars->enemy->img);
	if (vars->enemy)
		free(vars->enemy);
	if (vars->move_nbr % 2 == 0)
		vars->enemy = init_tile(vars, ENEMYPATH_L);
	else
		vars->enemy = init_tile(vars, ENEMYPATH_R);
}

void	draw_player(t_vars *vars, int direction)
{
	if (direction != 0)
	{
		if (vars->player->img)
			mlx_destroy_image(vars->mlx, vars->player->img);
		if (vars->player)
			free(vars->player);
		if (direction == -1)
			vars->player = init_tile(vars, PLAYERPATH_L);
		else if (direction == 1)
			vars->player = init_tile(vars, PLAYERPATH_R);
	}
}

void	char_ident(t_vars *vars, int i, int j)
{
	if (vars->arr[i][j] == '0')
		ft_draw_on_img(vars->sized, vars->floor);
	else if (vars->arr[i][j] == '1')
		ft_draw_on_img(vars->sized, vars->wall);
	else if (vars->arr[i][j] == 'P')
	{
		vars->player->x = j * SIZE;
		vars->player->y = i * SIZE;
		ft_draw_on_img(vars->sized, vars->player);
	}
	else if (vars->arr[i][j] == 'C')
		ft_draw_on_img(vars->sized, vars->collect);
	else if (vars->arr[i][j] == 'E')
		ft_draw_on_img(vars->sized, vars->exit);
	else if (vars->arr[i][j] == 'X')
		ft_draw_on_img(vars->sized, vars->enemy);
	mlx_put_image_to_window(vars->mlx, vars->win, \
		vars->sized->img, j * SIZE, i * SIZE);
}

int	put_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->map_rows)
	{
		j = 0;
		while (j < vars->map_cols)
		{
			char_ident(vars, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int	print_movement(t_vars *vars)
{
	char	*moves;

	moves = ft_itoa(vars->move_nbr);
	put_map(vars);
	mlx_string_put(vars->mlx, vars->win, 10, 10, 123456, moves);
	free(moves);
	return (0);
}
