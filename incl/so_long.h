/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:15:20 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/12 15:15:20 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PLAYERPATH_L "./imgs/player1.xpm"
# define PLAYERPATH_R "./imgs/player2.xpm"
# define FLOORPATH "./imgs/floor.xpm"
# define EXITPATH "./imgs/exit.xpm"
# define COLLPATH "./imgs/collect.xpm"
# define WALLPATH "./imgs/wall.xpm"
# define ENEMYPATH_L "./imgs/enemy1.xpm"
# define ENEMYPATH_R "./imgs/enemy2.xpm"
# define SIZE 64
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include "../mlx_linux/mlx.h"
# include "../libft/incl/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		width;
	int		height;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*player;
	t_data	*floor;
	t_data	*wall;
	t_data	*collect;
	t_data	*exit;
	t_data	*enemy;
	t_data	*sized;
	char	**arr;
	int		map_rows;
	int		map_cols;
	int		collect_nbr;
	int		move_nbr;
}			t_vars;

/* resize_utils.c */
int		ft_get_pixel(t_data *img, int x, int y);
void	ft_set_pixel(t_data *img, int x, int y, int color);
void	ft_draw_on_img(t_data *img, t_data *upp_img);

/* utils.c */
char	*ft_strjoin_free(char *s1, char s2);
void	ft_error_printer(char *s, t_vars *vars, char *res);
void	player_movement(t_vars *vars, int x_diff, int y_diff);
int		key_hook(int key_code, t_vars *vars);

/* requirements_check_1.c */
void	validity_check_handler(int argc, char **argv, t_vars *vars);
void	wall_check(char *res, t_vars *vars);
void	rectangular_check(char *res, t_vars *vars);
void	map_ending_check(char *str, t_vars *vars);
void	last_row_wall_check(char *res, char *res_ptr, t_vars *vars);

/* requirements_check_2.c */
void	character_check(char *res, t_vars *vars);
void	value_check(char *res, int counter, t_vars *vars);

/* initialization.c */
char	*ft_get_res(char **argv, t_vars *vars);
t_data	*init_tile(t_vars *vars, char *path);
char	**init_map(t_vars *vars, char **argv);
void	game_init(t_vars *vars, char **argv);
void	rowsncols(char *res, t_vars *vars);

/* draw_game.c */
void	draw_enemy(t_vars *vars);
void	draw_player(t_vars *vars, int direction);
void	char_ident(t_vars *vars, int i, int j);
int		put_map(t_vars *vars);
int		print_movement(t_vars *vars);

/* exit_handling.c */
void	double_free_array(t_vars *vars);
void	memory_release2(t_vars *vars);
void	memory_release(t_vars *vars);
int		exit_game(t_vars *vars);

#endif
