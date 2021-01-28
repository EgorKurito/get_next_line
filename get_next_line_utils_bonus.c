/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguy <hanguy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:30:15 by hanguy            #+#    #+#             */
/*   Updated: 2020/06/02 12:30:17 by hanguy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(t_list **list, int fd)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->tail = NULL;
	new->next = NULL;
	new->fd = fd;
	if (!(*list))
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (*list);
}

int		ft_lstdel(t_list **list, int fd)
{
	t_list	*prev;
	t_list	*curr;

	prev = *list;
	curr = *list;
	while (curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev->next != curr->next)
		prev->next = curr->next;
	else
		*list = (*list)->next;
	free(curr);
	return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strchr(s1, '\0') - s1;
	j = ft_strchr(s2, '\0') - s2;
	if ((str = malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	str[i + j] = '\0';
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char *str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}
