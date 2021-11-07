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
#include "cub3d.h"
#include "cub3d_int.h"

void			c3_render_fill_pixel(
	t_c3_state *stat, int x, int y, uint32_t col)
{
	int	screen_y;
	int	screen_x;
	int	index;

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
	int				x;
	int				y;
	t_c3_ray		*ray;
	unsigned int	col;
	int				wall_height;

	x = 0;
	while (x < ((t_c3_scene*)stat->scene)->map_width)
	{
		y = 0;
		while (y < ((t_c3_scene*)stat->scene)->map_height)
		{
			col = c3_query_map(stat, x, y);
			c3_render_fill_pixel(stat, x, y, col);
			y++;
		}
		x++;
	}

}
