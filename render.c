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

static void		c3_screen_coord(
	t_c3_state *stat, t_c3_vector *result, double x, double y, double z)
{
	t_c3_vector	tl;
	t_c3_vector	bl;
	t_c3_vector	tr;
	double	angle;

	angle = M_PI / 2 - stat->player.direction;
	tl.x = (1 + cos(angle)) * 0.5 * stat->renderer.resolution_x;
	tl.y = (1 + sin(angle)) * 0.5 * stat->renderer.resolution_y;
	bl.x = (1 + cos(angle + M_PI / 2.)) * 0.5 * stat->renderer.resolution_x;
	bl.y = (1 + sin(angle + M_PI / 2.)) * 0.5 * stat->renderer.resolution_y;
	tr.x = (1 + cos(angle - M_PI / 2.)) * 0.5 * stat->renderer.resolution_x;
	tr.y = (1 + sin(angle - M_PI / 2.)) * 0.5 * stat->renderer.resolution_y;

	result->x = floor(tl.x + (x / stat->map.width) * (tr.x - tl.x)
		+ (y / stat->map.height) * (bl.x - tl.x));
	result->y = floor(stat->renderer.resolution_y
		- tl.y
		- (x / stat->map.width) * (tr.y - tl.y)
		- (y / stat->map.height) * (bl.y - tl.y)
		- z);

	return ;
}

void			c3_draw_line(
	t_c3_state *stat, t_c3_vector *from, t_c3_vector *to,
	unsigned int col1, unsigned int col2)
{
	int	steps;
	int	dx;
	int	dy;

	dx = abs((int)(to->x - from->x));
	dy = abs((int)(to->y - from->y));
	if (dx > dy)
		steps = dx;
	else
		steps = dy;

	int				i;
	t_c3_vector		pos;
	unsigned int	col;

	i = 0;
	while (i < steps)
	{
		col = (col1 * i + col2 * (steps - i)) / steps;
		pos.x = (from->x * i + to->x * (steps - i)) / steps;
		pos.y = (from->y * i + to->y * (steps - i)) / steps;
		c3_render_fill_pixel(stat, pos.x, pos.y, col);
		i++;
	}
}

void			c3_render_scene(t_c3_state *stat)
{
	double			x;
	double			y;

	ft_bzero(stat->imgdata.data,
			stat->screen_height * stat->imgdata.size_line);

	x = 0;
	while (x < stat->map.width)
	{
		y = 0;
		while (y < stat->map.height)
		{
			int	height;
			t_c3_vector	coord;
			t_c3_vector	prev_coord;
			unsigned int	col1;
			unsigned int	col2;

			height = c3_query_map(stat, x, y);
			col1 = height * 20 + 0x00ff0000;
			c3_screen_coord(stat, &coord, x, y, height);
			if (x > 0)
			{
				height = c3_query_map(stat, x - 1, y);
				col2 = height * 20 + 0x00ff0000;
				c3_screen_coord(stat, &prev_coord, x - 1, y, height);
				c3_draw_line(stat, &prev_coord, &coord, col2, col1);
			}
			if (y > 0)
			{
				height = c3_query_map(stat, x, y - 1);
				col2 = height * 20 + 0x00ff0000;
				c3_screen_coord(stat, &prev_coord, x, y - 1, height);
				c3_draw_line(stat, &prev_coord, &coord, col2, col1);
			}
			if (x == 0 && y == 0)
			{
				c3_render_fill_pixel(stat, coord.x, coord.y, col1);
			}
			y++;
		}
		x++;
	}

}
