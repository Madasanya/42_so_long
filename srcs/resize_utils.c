/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:52:28 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 13:52:28 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

int	ft_get_pixel(t_data *img, int x, int y)
{
	if (img->bits_per_pixel == 0)
		return (*(int *)(img->addr + x * 4 + img->line_length * y));
	else
		return (*(int *)(img->addr + ((y * img->line_length) + x \
		* (img->bits_per_pixel / 8))));
}

void	ft_set_pixel(t_data *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length + x \
	* (img->bits_per_pixel / 8))) = color;
}

void	ft_draw_on_img(t_data *img, t_data *upp_img)
{
	int		x;
	int		y;
	float	r_x;
	float	r_y;
	int		color;

	x = 0;
	while (x < SIZE)
	{
		y = 0;
		while (y < SIZE)
		{
			r_x = (float)x / (float)SIZE;
			r_y = (float)y / (float)SIZE;
			color = ft_get_pixel(upp_img, r_x * (upp_img->line_length / 4), \
			r_y * (upp_img->line_length / 4));
			ft_set_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}
