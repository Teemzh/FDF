/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:04:37 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:04:50 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(float *x, float *y, int z)
{
	float	angle;

	angle = 0.8;
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

void	draw(t_fdf *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	data->floats.y = 0;
	while (data->floats.y < data->hei)
	{
		data->floats.x = 0;
		while (data->floats.x < data->wid)
		{
			if (data->floats.x < data->wid - 1)
				draw_bresenham_linex(data, data->floats.x, data->floats.y);
			if (data->floats.y < data->hei - 1)
				draw_bresenham_liney(data, data->floats.x, data->floats.y);
			data->floats.x++;
		}
		data->floats.y++;
	}
}

void	calculate_bresenham_params(float *x, float *y, t_float *xy, t_fdf *data)
{
	int	z;
	int	z1;

	z = data->mat[(int)*y][(int)*x];
	z1 = data->mat[(int)xy->y][(int)xy->x];
	*x *= data->zoom;
	*y *= data->zoom;
	xy->x *= data->zoom;
	xy->y *= data->zoom;
	if (data->projection_mode == 0)
	{
		isometric(x, y, z);
		isometric(&(xy->x), &(xy->y), z1);
	}
	else
	{
	}
	*x += 1000;
	*y += 200;
	xy->x += 1000;
	xy->y += 200;
}

void	checkarg(int ac)
{
	if (ac == 1)
	{
		ft_printf("Error, wrong number of arguments\n");
		exit(1);
	}
	if (ac >= 3)
	{
		ft_printf("Error, too many of arguments\n");
		exit(1);
	}
}
