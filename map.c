/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:37:36 by thisai            #+#    #+#             */
/*   Updated: 2021/02/25 17:37:36 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "cub3d_int.h"
#include "scene.h"

void	c3_map_init(t_c3_map *map, t_c3_scene *scene)
{
	map->width = scene->map_width;
	map->height = scene->map_height;
	printf("init width height: %d %d\n", map->width, map->height);
	map->map = malloc(sizeof(int) * map->width * map->height);
	if (!map->map)
	{
		c3_scene_cleanup(scene);
		exit(1);
	}
	ft_bzero(map->map, sizeof(int) * map->width * map->height);

	t_c3_map_rows	*row;
	t_c3_map_cells	*cell;
	int				i;
	int				j;

	i = 0;
	row = scene->map_rows;
	while(row)
	{
		j = 0;
		cell = row->cells;
		while(cell)
		{
			map->map[(map->height - i - 1) * map->width + map->width - j - 1] = cell->value;
			cell = cell->next;
			j++;
		}
		row = row->next;
		i++;
	}
}

#include <math.h>
int		c3_query_map(t_c3_state *stat, int x, int y)
{
	int	dx;
	int	dy;
	int	height;

	height = stat->map.map[y * stat->map.width + x];

	return (height);
}
