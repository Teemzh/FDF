/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:07:03 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/19 19:39:38 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_and_deallocate(int **map, int rows)
{
	while (rows > 0)
	{
		rows--;
		free(map[rows]);
	}
	free(map);
}

int	*allocate_row_memory(int width)
{
	int	*row;

	row = (int *)malloc(width * sizeof(int));
	if (row == NULL)
	{
		ft_printf("error\n");
	}
	return (row);
}

int	*read_row_data(char *line, int width)
{
	int		col;
	int		*row;
	char	**tokens;

	col = 0;
	row = allocate_row_memory(width);
	if (row)
	{
		tokens = ft_split(line, ' ');
		while (tokens[col] != NULL)
		{
			row[col] = ft_atoi(tokens[col]) * 8;
			free(tokens[col]);
			col++;
		}
		free(tokens);
	}
	return (row);
}

int	**read_and_fill_map(char *file_path, int **map, int width, int height)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(file_path, O_RDONLY);
	row = 0;
	while (row < height)
	{
		line = get_next_line(fd);
		if (!line && row != height)
			break ;
		map[row] = read_row_data(line, width);
		free(line);
		if (!map[row] && (close_and_deallocate(map, row), 1))
			return (NULL);
		row++;
	}
	close(fd);
	if (row != height && (ft_printf("Ошибка\n"), 1))
		close_and_deallocate(map, row);
	return (map);
}

int	**allocate_and_read_map(char *file_path, int width, int height)
{
	int	**map;

	map = (int **)malloc(height * sizeof(int *));
	if (map == NULL)
	{
		ft_printf("error\n");
		return (NULL);
	}
	map = read_and_fill_map(file_path, map, width, height);
	if (map == NULL)
	{
		ft_printf("error\n");
		return (NULL);
	}
	return (map);
}
