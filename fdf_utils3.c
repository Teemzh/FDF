/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:13:56 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/18 17:50:13 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map(int **map, int width, int height, char *file_path)
{
	int		fd;
	char	*line;
	int		row;
	int		col;
	char	*token;

	line = NULL;
	fd = open(file_path, O_RDONLY);
	row = 0;
	while (row < height)
	{
		col = 0;
		token = split_str(line, ' ');
		while (token != NULL && col < width)
		{
			map[row][col] = ft_atoi(token);
			token = split_str(NULL, ' ');
			col++;
		}
		free(line);
		row++;
	}
	close(fd);
}

char	*split_str(char *str, char delimiter)
{
	static char	*next_token;
	char		*token;

	next_token = NULL;
	if (str != NULL)
	{
		next_token = str;
	}
	if (next_token == NULL || *next_token == '\0')
	{
		return (NULL);
	}
	token = next_token;
	while (*next_token != '\0' && *next_token != delimiter)
	{
		next_token++;
	}
	if (*next_token == delimiter)
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}
