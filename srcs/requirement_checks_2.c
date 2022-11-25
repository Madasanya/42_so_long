/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requirement_checks_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:56:45 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:56:45 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	character_check(char *res, t_vars *vars)
{
	int	i;

	i = 0;
	while (res[i] != '\0')
	{
		if (!((res[i] == '1') || (res[i] == '0') || (res[i] == 'P') || \
			(res[i] == 'C') || (res[i] == 'E') || (res[i] == 'X') || \
			(res[i] == '\n') || (res[i] == '\0')))
			ft_error_printer("Map must contain only valid chars!\n", vars, res);
		i++;
	}
	free(res);
}

void	value_check(char *res, int counter, t_vars *vars)
{
	int	count[3];

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (res[counter])
	{
		if (res[counter] == 'P')
			count[0]++;
		else if (res[counter] == 'C')
			count[1]++;
		else if (res[counter] == 'E')
			count[2]++;
		counter++;
	}
	vars->collect_nbr = count[1];
	if (count[0] <= 0)
		ft_error_printer("No (P)layer starting position.\n", vars, res);
	else if (count[0] > 1)
		ft_error_printer("More than one (P)layer in map.\n", vars, res);
	if (count[1] <= 0)
		ft_error_printer("No (C)ollectibles found on map.\n", vars, res);
	if (count[2] <= 0)
		ft_error_printer("No (E)xits found on map.\n", vars, res);
}
