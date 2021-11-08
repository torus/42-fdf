/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:14:05 by thisai            #+#    #+#             */
/*   Updated: 2021/02/08 14:14:05 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "cub3d.h"
# include "stddef.h"

# define C3_STRING_BUFFER_SIZE 1024

typedef enum		e_c3_token
{
	C3_SCENE_TOKEN_NUM,
	C3_SCENE_TOKEN_COMMA,
	C3_SCENE_TOKEN_NEWLINE,
	C3_SCENE_TOKEN_EOF,
	C3_SCENE_TOKEN_UNKNOWN,
}					t_c3_token;

typedef enum		e_c3_parse_result
{
	C3_PARSE_FAIL,
	C3_PARSE_SUCCESS,
}					t_c3_parse_result;

typedef struct		s_c3_strbuf
{
	const char	*str;
	size_t		index;
}					t_c3_strbuf;

typedef struct		s_c3_file
{
	int		fd;
	int		is_ungotten;
	char	ungotten;
	char	last_char;
}					t_c3_file;

typedef union		u_c3_scene_container
{
	t_c3_strbuf	*strbuf;
	t_c3_file	*file;
}					t_c3_scene_container;

typedef struct		s_c3_scene_parser
{
	t_c3_scene_container	container;
	int						is_beginning_of_line;
	int						int_value;
	char					string_value[C3_STRING_BUFFER_SIZE];
	int						(*getc)(t_c3_scene_container);
	void					(*ungetc)(t_c3_scene_container);
	const char				*error;
	int						is_specified[C3_SCENE_TOKEN_NUM];
}					t_c3_scene_parser;

typedef struct		s_c3_map_cells
{
	int						value;
	struct s_c3_map_cells	*next;
}					t_c3_map_cells;

typedef struct		s_c3_map_rows
{
	t_c3_map_cells			*cells;
	struct s_c3_map_rows	*next;
}					t_c3_map_rows;

typedef struct		s_c3_scene
{
	t_c3_vector		resolution;
	char			*tex_path[C3_OBJTYPE_NUM];
	unsigned int	color_floor;
	unsigned int	color_ceiling;
	int				map_width;
	int				map_height;
	t_c3_map_rows	*map_rows;
}					t_c3_scene;

int					c3_scene_parser_init_with_file(
	t_c3_scene_parser *buf, const char *path);

void				c3_scene_init(t_c3_scene *scene);
t_c3_parse_result	c3_scene_parse(t_c3_scene *scene, t_c3_scene_parser *buf);
void				c3_scene_cleanup(t_c3_scene *scene);
int					c3_read_scene(t_c3_scene *scene, const char *path);
int					c3_scene_check_textures_specified(t_c3_scene_parser *buf);
int					c3_scene_check_colors_specified(t_c3_scene_parser *buf);

#endif
