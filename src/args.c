/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:34:56 by guroux            #+#    #+#             */
/*   Updated: 2019/08/14 18:59:05 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_istok(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int				count_words(char *str)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		while (*str && ft_istok(*str))
			str++;
		if (*str && !ft_istok(*str))
		{
			count++;
			while (*str && !ft_istok(*str))
				str++;
		}
	}
	return (count);
}

static char		*malloc_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !ft_istok(str[i]))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && !ft_istok(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char		**ft_split(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	if (!(arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1))))
		return (NULL);
	while (str && *str)
	{
		while (*str && ft_istok(*str))
			str++;
		if (*str && !ft_istok(*str))
		{
			if (!(arr[i] = malloc_word(str)))
				return (NULL);
			i++;
			while (*str && !ft_istok(*str))
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char			**getargs(void)
{
	char	*line;
	char	**args;

	line = NULL;
	args = NULL;
	if (get_next_line(0, &line) >= 0)
	{
		if (!line)
			exit(-1);
		if (!(args = ft_split(line)))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
		return (args);
	}
	return (NULL);
}
