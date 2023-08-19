/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:25:29 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:14:58 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	element_count(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (count);
}

int	get_row(char *map, t_fdf *data)
{
	char	*line;
	int		fd;
	int		row;

	fd = open(map, O_RDONLY);
	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		row++;
		free(line);
	}
	free(line);
	close(fd);
	if (row == 0)
	{
		ft_printf("Error: Empty map\n");
		freeall(data, 0);
		exit(1);
	}
	return (row);
}

int	get_column(char *map)
{
	int		column;
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	column = element_count(line, ' ');
	free(line);
	close(fd);
	return (column);
}

void	fill_col_matrix(t_fdf *data, int *matrix, char *line,
		int expected_columns)
{
	char	**element;
	char	**color;
	int		i;

	element = ft_split(line, ' ');
	i = 0;
	while (element[i] && i < expected_columns)
	{
		color = ft_split(element[i], ',');
		if (color[1])
			matrix[i] = ft_atoi_base(color[1] + 2, 16);
		else
			matrix[i] = DEFAULT_COLOR;
		if (color[1])
			free(color[1]);
		free(color[0]);
		free(color);
		free(element[i]);
		i++;
	}
	check_map(data, i, expected_columns);
	free(element);
}

void	check_map(t_fdf *data, int t, int expected_columns)
{
	if (t != expected_columns)
	{
		ft_printf("Error: wrong map.\n");
		freeall(data, 1);
		exit(1);
	}
}
