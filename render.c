/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:38:38 by thisai            #+#    #+#             */
/*   Updated: 2021/02/25 16:38:38 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "cub3d_int.h"

#include <stdio.h>
void			c3_render_fill_pixel(
	t_c3_state *stat, int x, int y, uint32_t col)
{
	int	screen_y;
	int	screen_x;
	int	index;

	if (x < 0
		|| x > stat->renderer.resolution_x
		|| y < 0
		|| y > stat->renderer.resolution_y)
	{
		return ;
	}

	screen_y = y * stat->screen_height / stat->renderer.resolution_y;
	while (
		screen_y < (y + 1) * stat->screen_height / stat->renderer.resolution_y)
	{
		screen_x = stat->screen_width * x / stat->renderer.resolution_x;
		while (
			screen_x <
			stat->screen_width * (x + 1) / stat->renderer.resolution_x)
		{
			index =
				screen_y * stat->imgdata.size_line +
				screen_x * stat->imgdata.bits_per_pixel / 8;
			((uint32_t*)stat->imgdata.data)[index / 4] = col;
			screen_x++;
		}
		screen_y++;
	}
}

void			c3_render_scene(t_c3_state *stat)
{
	double			x;
	double			y;
	t_c3_ray		*ray;
	unsigned int	col;
	int				wall_height;

	double	ox;
	double	oy;
	double	blx;
	double	bly;
	double	trx;
	double	try;
	double	angle;

	int	size =
		stat->screen_height *
		stat->imgdata.size_line;
	ft_bzero(stat->imgdata.data, size);

	angle = stat->player.direction + M_PI / 2;
	ox = (1 + cos(angle)) * 0.5 * stat->renderer.resolution_x;
	oy = (1 + sin(angle)) * 0.5 * stat->renderer.resolution_y;
	blx = (1 + cos(angle + M_PI / 2.)) * 0.5 * stat->renderer.resolution_x;
	bly = (1 + sin(angle + M_PI / 2.)) * 0.5 * stat->renderer.resolution_y;
	trx = (1 + cos(angle - M_PI / 2.)) * 0.5 * stat->renderer.resolution_x;
	try = (1 + sin(angle - M_PI / 2.)) * 0.5 * stat->renderer.resolution_y;

	x = 0;
	while (x < stat->map.width)
	{
		y = 0;
		while (y < stat->map.height)
		{
			int	height;

			height = c3_query_map(stat, x, y);
			col = height * 10 + 0x00ff0000;
			c3_render_fill_pixel(
				stat,
				(int)(ox + (x / stat->map.width) * (trx - ox) + (y / stat->map.height) * (blx - ox)),
				stat->renderer.resolution_y - (int)(oy + (x / stat->map.width) * (try - oy) + (y / stat->map.height) * (bly - oy)) + height,
				col);
			y++;
		}
		x++;
	}

}
