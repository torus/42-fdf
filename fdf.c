/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:23:13 by thisai            #+#    #+#             */
/*   Updated: 2021/03/11 10:13:57 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <mlx.h>
#include <libft.h>

#include "cub3d.h"
#include "cub3d_int.h"
#include "scene.h"

void	c3_keystate_init(t_c3_keystate *keystat)
{
	keystat->w = 0;
	keystat->a = 0;
	keystat->s = 0;
	keystat->d = 0;
	keystat->left = 0;
	keystat->right = 0;
}

void	c3_texture_cache_init(t_c3_texture_cache *cache, t_c3_scene *scene)
{
	int	i;

	cache->path = scene->tex_path;
	i = 0;
	while (i < C3_OBJTYPE_NUM)
	{
		cache->cache[i].image = NULL;
		i++;
	}
}

void	c3_init(t_c3_state *stat, t_c3_scene *scene)
{
	stat->mlx = NULL;
	stat->window = NULL;
	stat->img = NULL;
	stat->renderer.rays = NULL;
	stat->texture_cache = NULL;
	stat->scene = scene;
	c3_map_init(&stat->map, scene);
	c3_keystate_init(&stat->keystate);
	c3_player_init(stat, &stat->player, &stat->map);
	stat->mlx = mlx_init();
	c3_check(!!stat->mlx, "mlx is NULL.");
	c3_init_set_screen_size(stat, scene);
	c3_renderer_init(
		&stat->renderer, scene, stat->map.width * 8,
		stat->map.height * 8);
	c3_init_render_target(stat);
	stat->is_drawing_minimap = 0;
	stat->is_benchmarking = 0;
	stat->is_showing_screen = 1;
}

int	main(int argc, char **argv)
{
	t_c3_state			stat;
	t_c3_scene			scene;

	if (argc < 2 || argc > 3
		|| (argc == 3 && ft_strncmp(argv[2], "--save", 7)))
	{
		C3_LOG("Error\nusage: cub3d scene.cub [--save]\n");
		return (1);
	}
	if (!c3_read_scene(&scene, argv[1]))
	{
		c3_scene_cleanup(&scene);
		return (1);
	}
	c3_init(&stat, &scene);
	c3_start_rendering_loop(&stat);
	return (0);
}
