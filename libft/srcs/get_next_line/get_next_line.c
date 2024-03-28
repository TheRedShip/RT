/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:09:05 by rgramati          #+#    #+#             */
/*   Updated: 2023/12/17 18:44:42 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isfull(t_slist *lst)
{
	int	i;

	if (!lst)
		return (1);
	while (lst->next)
		lst = lst->next;
	while (lst && lst->str)
	{
		i = 0;
		while (*((lst->str) + i))
		{
			if (*((lst->str) + i) == '\n')
				return (0);
			i++;
		}
		lst = lst->next;
	}
	return (i != 0);
}

void	fill_list(t_slist **lst, int fd)
{
	char	*buffer;
	int		rchars;

	while (isfull(*lst))
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		rchars = read(fd, buffer, BUFFER_SIZE);
		if (rchars <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[rchars] = 0;
		ft_slstadd_back(lst, ft_slstnew(buffer));
	}
}

char	*offset(t_slist *lst)
{
	char	*newstr;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = 0;
	while ((lst->str)[i] && (lst->str)[i] != '\n')
		i++;
	if ((lst->str)[i] == '\n')
		i++;
	j = i;
	while ((lst->str)[j++])
		len++;
	newstr = ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	j = -1;
	while (++j < len && (lst->str)[i + j])
		*(newstr + j) = (lst->str)[i + j];
	*(newstr + j) = 0;
	return (newstr);
}

char	*line_from_list(t_slist **lst)
{
	t_slist	*newstart;
	t_slist	*start;
	char	*newline;
	int		i;
	int		j;

	start = *lst;
	newline = ft_calloc((ft_slstcsize(*lst) + 2), sizeof(char));
	i = 0;
	while (newline && *lst)
	{
		j = -1;
		while (((*lst)->str)[++j] && ((*lst)->str)[j] != '\n')
			newline[i++] = ((*lst)->str)[j];
		newline[i] = ((*lst)->str)[j];
		if (!(*lst)->next)
			newstart = ft_slstnew(offset(*lst));
		*lst = (*lst)->next;
	}
	ft_slstclear(&start);
	if (newline && newstart && *newstart->str)
		(*lst) = newstart;
	else if (newline)
		ft_slstclear(&newstart);
	return (newline);
}

char	*get_next_line(int fd)
{
	static t_slist	*lst[1024];
	char			*line;

	if (!lst[fd])
		lst[fd] = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fill_list(&(lst[fd]), fd);
	if (lst[fd] && !*(lst[fd]->str))
	{
		ft_slstclear(&(lst[fd]));
		return (NULL);
	}
	if (!lst[fd])
		return (NULL);
	line = line_from_list(&(lst[fd]));
	return (line);
}
