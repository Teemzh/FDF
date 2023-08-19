/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:34:12 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:11:34 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	allocate_color_matrix(t_fdf *data)
{
	int	i;
	int	j;

	data->col_matrix = (int **)malloc(sizeof(int *) * data->row);
	i = 0;
	while (i < data->row)
	{
		data->col_matrix[i] = (int *)malloc(sizeof(int) * data->column);
		if (data->col_matrix[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(data->col_matrix[j]);
				j++;
			}
			free(data->col_matrix);
			return ;
		}
		i++;
	}
	data->col_matrix[i] = NULL;
}

void	fill_color_matrix(t_fdf *data, char *map)
{
	int		i;
	t_var	var;

	i = 0;
	var.fd = open(map, O_RDONLY);
	while (data->col_matrix[i] != NULL)
	{
		var.line = get_next_line(var.fd);
		if (!var.line)
		{
			free(var.line);
			break ;
		}
		fill_col_matrix(data, data->col_matrix[i], var.line, data->column);
		free(var.line);
		i++;
	}
	close(var.fd);
}

void	get_color(char *map, t_fdf *data)
{
	allocate_color_matrix(data);
	fill_color_matrix(data, map);
}

int	**read_map(char *file_path, int *width, int *height)
{
	int		_width;
	int		_height;
	char	*file_extension;

	file_extension = strrchr(file_path, '.');
	if (file_extension == NULL || strcmp(file_extension, ".fdf") != 0)
	{
		ft_printf("Please provide a .fdf file.\n");
		exit(0);
	}
	_width = get_map_width(file_path);
	_height = get_map_height(file_path);
	if (_width <= 0 || _height <= 0)
	{
		return (0);
	}
	*width = _width;
	*height = _height;
	return (allocate_and_read_map(file_path, _width, _height));
}
