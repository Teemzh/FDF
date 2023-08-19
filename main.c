/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:53:12 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:08:12 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	freeall(t_fdf *data, int i)
{
	free(data->mat);
	if (i == 1)
		free(data->col_matrix);
}

int	deal_key(int key, t_fdf *data)
{
	if (key == 34)
	{
		data->projection_mode = (data->projection_mode + 1)
			% NUM_PROJECTION_MODES;
		draw(data);
	}
	if (key == 53)
	{
		freeall(data, 1);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

int	deal_close(void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	freeall(data, 1);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	find_scale_zoom(t_fdf *data)
{
	while ((data->column * data->zoom) < 3000 / 2 && (data->row
			* data->zoom) < 3000 / 2)
		data->zoom++;
	ft_printf("data->zoom = %i\n", data->zoom);
	return (data->zoom);
}

int	main(int ac, char **av)
{
	int		width;
	int		height;
	int		**map;
	t_fdf	data;

	checkarg(ac);
	width = 0;
	height = 0;
	map = read_map(av[1], &width, &height);
	data.mat = map;
	data.hei = height;
	data.wid = width;
	data.row = get_row(av[1], &data);
	data.column = get_column(av[1]);
	get_color(av[1], &data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 3000, 3000, "FDF");
	mlx_hook(data.win_ptr, 17, 0, deal_close, &data);
	data.zoom = find_scale_zoom(&data);
	data.projection_mode = 0;
	draw(&data);
	mlx_key_hook(data.win_ptr, deal_key, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
