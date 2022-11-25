/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requirement_checks_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:57:43 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:57:43 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	wall_check(char *res, t_vars *vars)
{
	int	i;
	int	row_count;

	i = 0;
	row_count = 1;
	while (res[i])
	{
		while (i < vars->map_cols)
		{
			if (res[i] != '1')
				ft_error_printer("Map is not surrounded by walls!\n", vars, res);
			i++;
		}
		if (res[i] == '\n')
		{
			row_count++;
			if ((res[i - 1] != '1') || (res[i + 1] != '1'))
				ft_error_printer("Map is not surrounded by walls!\n", vars, res);
		}
		else if (row_count == vars->map_rows)
			last_row_wall_check(res, &res[i], vars);
		i++;
	}
}

void	rectangular_check(char *res, t_vars *vars)
{
	int	i;
	int	col_nb;

	i = 0;
	col_nb = 1;
	while (res[i] != '\0')
	{
		if ((res[i] == '\n') || (res[i + 1] == '\0'))
		{
			if (res[i] == '\n' && col_nb - 1 == vars->map_cols)
				col_nb = 0;
			else if (res[i + 1] == '\0' && col_nb == vars->map_cols)
				col_nb = 0;
			else
				ft_error_printer("Incorrect map size!\n", vars, res);
		}
		col_nb++;
		i++;
	}
}

void	map_ending_check(char *str, t_vars *vars)
{
	int	name_len;

	name_len = ft_strlen(str);
	if (str[name_len - 4] != '.' || str[name_len - 3] != 'b' || \
		str[name_len - 2] != 'e' || str[name_len - 1] != 'r')
		ft_error_printer("Wrong map extension (.ber)!\n", vars, NULL);
}

/*
** counter[0] - Player
** counter[1] - Collectible
** counter[2] - Exit
*/

void	last_row_wall_check(char *res, char *res_ptr, t_vars *vars)
{
	int	i;

	i = 0;
	while (res_ptr[i])
	{
		while (res_ptr[i + 1] != '\0')
		{
			if (res_ptr[i] != '1')
				ft_error_printer("Map is not surrounded by walls!\n", vars, res);
			i++;
		}
		if (res_ptr[i + 1] == '\0')
		{
			if (res_ptr[i] != '1')
				ft_error_printer("Map is not surrounded by walls!\n", vars, res);
		}
		i++;
	}
}

void	validity_check_handler(int argc, char **argv, t_vars *vars)
{
	char	*res;

	if (argc != 2)
		ft_error_printer("Incorrect number of arguments!\n", vars, NULL);
	else
		map_ending_check(argv[1], vars);
	res = ft_get_res(argv, vars);
	rowsncols(res, vars);
	rectangular_check(res, vars);
	wall_check(res, vars);
	value_check(res, 0, vars);
	character_check(res, vars);
}
