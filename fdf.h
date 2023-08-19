/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:21:13 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:21:42 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_COLORS 100
# define NUM_PROJECTION_MODES 2

# define DEFAULT_COLOR 0xffffff

typedef struct s_var
{
	int		fd;
	char	*line;
	int		n_prev_line_elems;
	int		current_elems;

	float	x;
	float	y;
	float	x1;
	float	y1;
	int		z;
	int		z1;
}			t_var;

typedef struct s_float
{
	float	x;
	float	y;
}			t_float;
typedef struct s_mac
{
	float	a;
	float	b;
	int		max;
	int		x_step_abs;
	int		y_step_abs;
}			t_mac;

typedef struct s_fdf
{
	int		wid;
	int		hei;
	int		**mat;
	int		zoom;
	int		**col_matrix;
	int		row;
	int		column;
	t_float	floats;
	int		projection_mode;

	void	*mlx_ptr;
	void	*win_ptr;
	int		map_width;
	int		map_height;

}			t_fdf;

int			get_column(char *map);
void		get_color(char *map, t_fdf *data);
int			get_row(char *map, t_fdf *data);
void		freeall(t_fdf *data, int i);
int			deal_close(void *param);
int			deal_key(int key, t_fdf *data);
void		draw(t_fdf *data);
void		fill_col_matrix(t_fdf *data, int *matrix, char *line,
				int expected_columns);
int			get_map_width(char *file_path);
int			get_map_height(char *file_path);
int			**allocate_and_read_map(char *file_path, int width, int height);
void		calculate_bresenham_params(float *x, float *y, t_float *xy,
				t_fdf *data);
void		calculate_max_and_abs(float a, float b, t_mac *macros);
char		**ft_split(char const *s, char c);
int			**read_map(char *file_path, int *width, int *height);
int			count_words(const char *str, char delimiter);
int			ft_atoi(const char *str);
char		*split_str(char *str, char delimiter);
int			ft_atoi_base(const char *str, int str_base);
void		draw_bresenham_linex(t_fdf *data, float x, float y);
void		draw_bresenham_liney(t_fdf *data, float x, float y);
void		calculate_bresenham_params(float *x, float *y, t_float *xy,
				t_fdf *data);
void		isometric(float *x, float *y, int z);
void		checkarg(int ac);
void		check_map(t_fdf *data, int t, int expected_columns);

#endif
