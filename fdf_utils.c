/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzhakypo <tzhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:18:49 by tzhakypo          #+#    #+#             */
/*   Updated: 2023/08/20 00:03:22 by tzhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static int	ft_countwords(const char *str, char ceporator)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == ceporator)
			i++;
		else
		{
			words++;
			while (str[i] != '\0' && str[i] != ceporator)
				i++;
		}
	}
	return (words);
}

static char	*ft_wd(const char *str, char c)
{
	int		i;
	char	*wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = malloc(sizeof(char) * (i + 1));
	if (!wd)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		wd[i] = str[i];
		i++;
	}
	wd[i] = '\0';
	return (wd);
}

static void	ft_freeword(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**ptr_words;
	int		words;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	ptr_words = (char **)malloc(sizeof(char *) * (words + 1));
	if (!ptr_words)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		ptr_words[i] = ft_wd(s, c);
		if (ptr_words[i] == NULL)
			ft_freeword(i, ptr_words);
		while (*s && *s != c)
			s++;
		i++;
	}
	ptr_words[i] = NULL;
	return (ptr_words);
}
