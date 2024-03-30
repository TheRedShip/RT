/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:15:22 by rgramati          #+#    #+#             */
/*   Updated: 2023/12/17 19:27:26 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_slist	*ft_slstnew(char *str)
{
	t_slist	*new;

	new = malloc(sizeof(t_slist));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	ft_slstclear(t_slist **lst)
{
	if (!lst || !(*lst))
		return ;
	ft_slstclear(&((*lst)->next));
	if ((*lst)->str)
		free((*lst)->str);
	free(*lst);
	*lst = NULL;
}

void	ft_slstadd_back(t_slist **lst, t_slist *new)
{
	t_slist	*curr;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	curr = (*lst);
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

int	ft_slstcsize(t_slist *lst)
{
	int	total;
	int	i;

	if (!lst)
		return (0);
	total = 0;
	while (lst)
	{
		i = 0;
		while (*((lst->str) + i) != '\n' && *((lst->str) + i))
			i++;
		if (*((lst->str) + i) == '\n')
			i++;
		lst = lst->next;
		total += i;
	}
	return (total);
}
