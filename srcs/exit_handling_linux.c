/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:50:24 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:50:24 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	double_free_array(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map_rows)
	{
		if (vars->arr[i])
			free(vars->arr[i]);
		i++;
	}
}

void	memory_release2(t_vars *vars)
{
	if (vars->floor)
		free(vars->floor);
	if (vars->wall)
		free(vars->wall);
	if (vars->player)
		free(vars->player);
	if (vars->collect)
		free(vars->collect);
	if (vars->exit)
		free(vars->exit);
	if (vars->enemy)
		free(vars->enemy);
	if (vars->sized)
		free(vars->sized);
	if (vars->arr)
		free(vars->arr);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
}

void	memory_release(t_vars *vars)
{
	if (vars->arr)
	{
		double_free_array(vars);
		if (vars->floor->img)
			mlx_destroy_image(vars->mlx, vars->floor->img);
		if (vars->wall->img)
			mlx_destroy_image(vars->mlx, vars->wall->img);
		if (vars->player->img)
			mlx_destroy_image(vars->mlx, vars->player->img);
		if (vars->collect->img)
			mlx_destroy_image(vars->mlx, vars->collect->img);
		if (vars->exit->img)
			mlx_destroy_image(vars->mlx, vars->exit->img);
		if (vars->enemy->img)
			mlx_destroy_image(vars->mlx, vars->enemy->img);
		if (vars->sized->img)
			mlx_destroy_image(vars->mlx, vars->sized->img);
		memory_release2(vars);
	}
	free(vars);
}

int	exit_game(t_vars *vars)
{
	if (vars)
		memory_release(vars);
	exit(1);
}
