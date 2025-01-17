/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguy <hanguy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:30:04 by hanguy            #+#    #+#             */
/*   Updated: 2020/06/02 12:30:05 by hanguy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_tail(char **tail, char **line)
{
	char	*tmp;
	char	*tmp_line;

	tmp_line = *line;
	if ((tmp = ft_strchr(*tail, '\n')))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strjoin(*line, *tail)))
			return (-1);
		tmp++;
		*tail = ft_strcpy(*tail, tmp);
		free(tmp_line);
		return (1);
	}
	if (!(*line = ft_strjoin(*line, *tail)))
		return (-1);
	free(tmp_line);
	free(*tail);
	return (2);
}

static int	check_buf(char *buf, char **tail, char **line)
{
	char	*tmp;
	char	*tmp_line;

	tmp_line = *line;
	if ((tmp = ft_strchr(buf, '\n')))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		tmp++;
		if (!(*tail = ft_strjoin(tmp, "")))
			return (-1);
		free(tmp_line);
		free(buf);
		return (1);
	}
	if (!(*line = ft_strjoin(*line, buf)))
		return (-1);
	free(tmp_line);
	return (2);
}

int			get_line(int fd, char **line, char **tail, t_list **list)
{
	int		res;
	int		readed;
	char	*buf;

	res = 0;
	if (*tail && (res = check_tail(tail, line)) != 2)
		return ((res == -1) ? ft_lstdel(list, fd) : res);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_lstdel(list, fd) - 1);
	while ((readed = read(fd, buf, BUFFER_SIZE)))
	{
		if (readed < 0)
			return (ft_lstdel(list, fd) - 1);
		buf[readed] = '\0';
		if ((res = check_buf(buf, tail, line)) != 2)
			return (res != 1 ? ft_lstdel(list, fd) : res);
	}
	free(buf);
	return (ft_lstdel(list, fd));
}

int			get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*tmp;

	if (BUFFER_SIZE < 1 || fd < 0 || !line ||
		!(*line = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	*line[0] = 0;
	if (!list)
		if (!(list = ft_lstnew(&list, fd)))
			return (-1);
	tmp = list;
	while (tmp->next && fd != tmp->fd)
		tmp = tmp->next;
	if (fd != tmp->fd)
	{
		if (!(list = ft_lstnew(&list, fd)))
			return (-1);
		tmp = list;
	}
	return (get_line(fd, line, &(tmp->tail), &list));
}
