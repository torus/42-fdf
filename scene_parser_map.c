/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:47:55 by thisai            #+#    #+#             */
/*   Updated: 2021/02/19 17:47:55 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <libft.h>
#include "scene.h"
#include "scene_int.h"

#include <stdio.h>
t_c3_parse_result	c3_scene_parse_map(
	t_c3_scene *scene, t_c3_scene_parser *buf)
{
	t_c3_map_rows	*rows;
	t_c3_map_cells	*cells;
	t_c3_token		tok;
	int				width;
	int				height;

	rows = NULL;
	height = 0;
	while (1)
	{
		tok = c3_scene_get_token(buf);
		cells = NULL;
		width = 0;
		while (tok == C3_SCENE_TOKEN_NUM)
		{
			int				val;
			t_c3_map_cells	*new_cell;

			new_cell = malloc(sizeof(t_c3_map_cells));
			if (!new_cell)
				return (C3_PARSE_FAIL);
			new_cell->next = cells;
			cells = new_cell;
			val = c3_scene_get_int(buf);
			tok = c3_scene_get_token(buf);
			new_cell->value = val;
			width++;
			printf(" %d", val);
		}
		if (scene->map_width < width)
			scene->map_width = width;
		height++;
		printf("\n");
		if (tok == C3_SCENE_TOKEN_EOF)
			break ;
		if (tok != C3_SCENE_TOKEN_NEWLINE)
			return (C3_PARSE_FAIL);
		t_c3_map_rows	*new_row;
		new_row = malloc(sizeof(t_c3_map_rows));
		if (!new_row)
			return (C3_PARSE_FAIL);
		new_row->next = rows;
		new_row->cells = cells;
		rows = new_row;
	}
	if (!height)
		return (C3_PARSE_FAIL);
	scene->map_height = height;
	scene->map_rows = rows;
	return (C3_PARSE_SUCCESS);
}
