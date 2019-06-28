/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:43:36 by guroux            #+#    #+#             */
/*   Updated: 2018/12/06 20:43:43 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*select_node(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

static void		del_node(t_list **head, int fd)
{
	t_list *tmp;

	tmp = *head;
	while ((int)(*head)->content_size != fd && *head)
	{
		tmp = *head;
		*head = (*head)->next;
	}
	if (*head && (int)(*head)->content_size == fd)
	{
		free((*head)->content);
		(*head)->content_size = 0;
		tmp->next = (*head)->next;
		(*head)->next = NULL;
		free(*head);
		*head = NULL;
	}
}

static char		*readfile(const int fd, char *str)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;
	int				i;

	i = 0;
	if ((ret = read(fd, buff, 0)) < 0)
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (!(tmp = ft_strjoin(str, buff)))
			return (NULL);
		ft_strdel(&str);
		str = tmp;
		while (buff[i] != '\0')
			if (buff[i++] == '\n')
				return (str);
		i = 0;
	}
	return (str);
}

static int		cpy_line(char **line, char **str, int i)
{
	char	*tmp;

	if (i == 0)
	{
		if (!(*line = ft_strdup("")))
			return (-1);
	}
	else
	{
		if (!(*line = ft_strsub(*str, 0, i)))
			return (-1);
	}
	if ((*str)[i])
	{
		if (!(tmp = ft_strsub(*str, (i + 1), (ft_strlen(*str) - 1))))
			return (-1);
		ft_strdel(str);
		*str = tmp;
	}
	else
	{
		if (!(*str = ft_strdup("")))
			return (-1);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list		*file;
	t_list				*curr;
	char				*str;
	char				tab[1];
	int					i;

	i = 0;
	if (fd < 0 || line == NULL || read(fd, tab, 0) < 0)
		return (-1);
	curr = select_node(&file, fd);
	if (!(curr->content = readfile(fd, curr->content)))
		return (-1);
	str = curr->content;
	if (str[0] != '\0')
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		return (cpy_line(line, (char **)&(curr->content), i));
	}
	else
		del_node(&file, fd);
	return (0);
}
