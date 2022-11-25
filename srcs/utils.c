/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:58:56 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:58:56 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

char	*ft_strjoin_free(char *s1, char s2)
{
	char	*return_s;
	int		len_s1;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	return_s = ft_calloc(sizeof(char) * (len_s1 + 1) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	while (i < len_s1 + 1)
	{
		if (i < len_s1)
			return_s[i] = s1[i];
		else
			return_s[i] = s2;
		i++;
	}
	free(s1);
	return (return_s);
}

void	ft_error_printer(char *s, t_vars *vars, char *res)
{
	write(2, "Error!\n", 7);
	while (*s)
	{
		write(2, s, 1);
		s++;
	}
	if (res)
		free(res);
	exit_game(vars);
	exit(EXIT_FAILURE);
}

void	player_movement(t_vars *vars, int x_diff, int y_diff)
{
	if ((vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff]) != '1')
	{
		if ((vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff]) == 'C')
			vars->collect_nbr--;
		if (((vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff]) == 'E') && vars->collect_nbr == 0)
			exit_game(vars);
		else if (((vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff]) == 'E') && vars->collect_nbr > 0)
			return ;
		if ((vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff]) == 'X')
			exit_game(vars);
		vars->arr[(vars->player->y / SIZE)][(vars->player->x / SIZE)] = '0';
		vars->arr[(vars->player->y / SIZE) + x_diff] \
		[(vars->player->x / SIZE) + y_diff] = 'P';
		vars->move_nbr++;
		draw_enemy(vars);
		draw_player(vars, y_diff);
		print_movement(vars);
	}
}

int	key_hook(int key_code, t_vars *vars)
{
	if (key_code == 65307)
		exit_game(vars);
	else if ((key_code == 119) || (key_code == 65362))
		player_movement(vars, -1, 0);
	else if (key_code == 97 || key_code == 65361)
		player_movement(vars, 0, -1);
	else if (key_code == 115 || key_code == 65364)
		player_movement(vars, 1, 0);
	else if (key_code == 100 || key_code == 65363)
		player_movement(vars, 0, 1);
	return (0);
}
