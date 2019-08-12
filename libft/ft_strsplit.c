/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:03:11 by guroux            #+#    #+#             */
/*   Updated: 2019/08/12 16:04:51 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_istok(char c, const char h)
{
	return (c == h);
}

static int			count_words(const char *s, const char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_istok(*s, c))
			s++;
		if (*s && !ft_istok(*s, c))
		{
			count++;
			while (*s && !ft_istok(*s, c))
				s++;
		}
	}
	return (count);
}

static char			*malloc_word(const char *s, const char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !ft_istok(s[i], c))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && !ft_istok(s[i], c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char				**ft_strsplit(const char *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (!(arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		while (*s && ft_istok(*s, c))
			s++;
		if (*s && !ft_istok(*s, c))
		{
			if (!(arr[i] = malloc_word(s, c)))
				return (NULL);
			i++;
			while (*s && !ft_istok(*s, c))
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
