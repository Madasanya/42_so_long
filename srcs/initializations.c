/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:59:45 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:59:45 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

char	*ft_get_res(char **argv, t_vars *vars)
{
	int		fd;
	char	str;
	char	*res;

	res = (char *)ft_calloc(sizeof(char), 1);
	if (res == NULL)
		exit_game(vars);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0))
		ft_error_printer("File doesn't exist!\n", vars, res);
	while (read(fd, &str, 1))
	{
		res = ft_strjoin_free(res, str);
		if (res == NULL)
			exit_game(vars);
	}
	close(fd);
	return (res);
}

t_data	*init_tile(t_vars *vars, char *path)
{
	t_data	*tile;
	int		height;
	int		width;

	tile = ft_calloc(sizeof(t_data), 1);
	if (tile == NULL)
		exit_game(vars);
	tile->height = SIZE;
	tile->width = SIZE;
	if (path != 0)
	{
		tile->img = mlx_xpm_file_to_image(vars->mlx, path, &height, &width);
		tile->addr = mlx_get_data_addr(tile->img, &tile->bits_per_pixel + 1, \
		&tile->line_length, &tile->endian);
	}
	else
	{
		tile->img = mlx_new_image(vars->mlx, SIZE, SIZE);
		tile->addr = mlx_get_data_addr(tile->img,
				&tile->bits_per_pixel,
				&tile->line_length, &tile->endian);
	}
	tile->x = 0;
	tile->y = 0;
	return (tile);
}

char	**init_map(t_vars *vars, char **argv)
{
	int		i;
	int		j;
	int		fd1;
	char	**arr;

	i = 0;
	arr = malloc(vars->map_rows * sizeof(char *));
	if (arr == NULL)
		exit_game(vars);
	fd1 = open(argv[1], O_RDONLY);
	while (i < vars->map_rows)
	{
		arr[i] = ft_calloc(vars->map_cols * sizeof(char), 1);
		if (arr[i] == NULL)
			exit_game(vars);
		j = 0;
		while (j < vars->map_cols)
		{
			read(fd1, &arr[i][j], 1);
			j++;
		}
		i++;
	}
	close(fd1);
	return (arr);
}

void	game_init(t_vars *vars, char **argv)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, (vars->map_cols) * SIZE, \
	vars->map_rows * SIZE, "so_long");
	vars->map_cols = vars->map_cols + 1;
	vars->move_nbr = 0;
	vars->floor = init_tile(vars, FLOORPATH);
	vars->player = init_tile(vars, PLAYERPATH_L);
	vars->wall = init_tile(vars, WALLPATH);
	vars->collect = init_tile(vars, COLLPATH);
	vars->exit = init_tile(vars, EXITPATH);
	vars->enemy = init_tile(vars, ENEMYPATH_L);
	vars->sized = init_tile(vars, 0);
	vars->arr = init_map(vars, argv);
	if (!vars->mlx || !vars->win || !vars->floor || !vars->player \
	|| !vars->wall || !vars->collect || !vars->exit || !vars->enemy \
	|| !vars->sized || !vars->arr)
		exit_game(vars);
}

void	rowsncols(char *res, t_vars *vars)
{
	int	i;
	int	j;
	int	rowlen;

	i = 0;
	j = 0;
	rowlen = 1;
	while (res[i] != '\0')
	{
		if (res[i] == '\n')
			rowlen++;
		i++;
	}
	while (res[j] != '\n')
		j++;
	vars->map_cols = j;
	vars->map_rows = rowlen;
}
