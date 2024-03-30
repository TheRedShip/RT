/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:57:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/28 18:42:07 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_word_size(char *src, char charset)
{
	int	i;

	i = 0;
	while (*(src + i) && *(src + i) != charset)
		i++;
	return (i);
}

static int	ft_count_words(char *str, char charset)
{
	int	i;
	int	wc;

	i = 1;
	wc = 0;
	if (!*str)
		return (0);
	if (*str != charset)
		wc++;
	while (str[i])
	{
		if (*(str + i - 1) == charset)
		{
			if (*(str + i) != charset)
				wc++;
		}
		i++;
	}
	return (wc);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		wsize;
	int		wc;
	int		i;

	i = -1;
	wsize = 0;
	if (!s)
		return (NULL);
	wc = ft_count_words((char *)s, c);
	split = malloc(sizeof(char *) * (wc + 1));
	if (split == NULL)
		return (NULL);
	while (++i < wc)
	{
		while (wsize-- > 0 || *(char *)s == c)
			s++;
		wsize = ft_n_word_size((char *)s, c);
		split[i] = malloc(sizeof(char) * (wsize + 1));
		if (split[i] == NULL)
			return (NULL);
		ft_strlcpy(split[i], (char *)s, wsize + 1);
	}
	split[i] = 0;
	return (split);
}
