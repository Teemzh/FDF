/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:41:57 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/19 20:28:59 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			res = res * str_base + *str - 48;
		else if (*str >= 'A' && *str <= 'F')
			res = res * str_base + *str - 55;
		else if (*str >= 'a' && *str <= 'f')
			res = res * str_base + *str - 87;
		else
		{
			break ;
		}
		str++;
	}
	return (sign * res);
}

int	count_words(const char *str, char delimiter)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (*str != '\0')
	{
		if (*str != delimiter)
		{
			if (is_word == 0)
			{
				count++;
				is_word = 1;
			}
		}
		else
		{
			is_word = 0;
		}
		str++;
	}
	return (count);
}

int	get_map_width(char *file_path)
{
	int		fd;
	char	*line;
	int		width;

	width = 0;
	if (access(file_path, F_OK) == -1)
	{
		ft_printf("ERROR: File not found\n");
		exit(1);
	}
	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	if (line[0] == '\0' || strchr(line, ' ') == NULL)
	{
		ft_printf("Error:empty or contains no elements\n");
		free(line);
		close(fd);
		exit(1);
	}
	width = count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	get_map_height(char *file_path)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}
