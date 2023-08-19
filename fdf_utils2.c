/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:34:22 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/15 21:41:57 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_max_and_abs(float a, float b, t_mac *macros)
{
	if (a < 0)
		macros->x_step_abs = -a;
	else
		macros->x_step_abs = a;
	if (b < 0)
	{
		macros->y_step_abs = -b;
	}
	else
	{
		macros->y_step_abs = b;
	}
	if (macros->x_step_abs > macros->y_step_abs)
	{
		macros->max = macros->x_step_abs;
	}
	else
	{
		macros->max = macros->y_step_abs;
	}
	if (macros->max == 0)
	{
		macros->max = 1;
	}
}

void	draw_bresenham_linex(t_fdf *data, float x, float y)
{
	float	x_step;
	float	y_step;
	int		cc;
	t_float	xy;
	t_mac	macros;

	xy.x = data->floats.x + 1;
	xy.y = data->floats.y;
	cc = data->col_matrix[(int)y][(int)x];
	calculate_bresenham_params(&x, &y, &xy, data);
	x_step = xy.x - x;
	y_step = xy.y - y;
	calculate_max_and_abs(x_step, y_step, &macros);
	x_step /= macros.max;
	y_step /= macros.max;
	while ((int)(x - xy.x) || (int)(y - xy.y))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, cc);
		x += x_step;
		y += y_step;
	}
}

void	draw_bresenham_liney(t_fdf *data, float x, float y)
{
	float	x_step;
	float	y_step;
	int		cc;
	t_float	xy;
	t_mac	macros;

	xy.x = data->floats.x;
	xy.y = data->floats.y + 1;
	cc = data->col_matrix[(int)y][(int)x];
	calculate_bresenham_params(&x, &y, &xy, data);
	x_step = xy.x - x;
	y_step = xy.y - y;
	calculate_max_and_abs(x_step, y_step, &macros);
	x_step /= macros.max;
	y_step /= macros.max;
	while ((int)(x - xy.x) || (int)(y - xy.y))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, cc);
		x += x_step;
		y += y_step;
	}
}
