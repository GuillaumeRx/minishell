/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:53:11 by guroux            #+#    #+#             */
/*   Updated: 2019/08/21 22:15:57 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realoc_tab(char **tab, char *var)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 2))))
		return (NULL);
	while (tab[i] != NULL)
	{
		tmp[i] = tab[i];
		++i;
	}
	tmp[i] = var;
	++i;
	tmp[i] = NULL;
	free(tab);
	return (tmp);
}

int		tablen(char **tab)
{
	int i;

	i = 0;
	if (tab && *tab)
	{
		while (tab[i] != NULL)
			++i;
		return (i);
	}
	return (0);
}

char	**remenv(int index, char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(env)))))
		return (NULL);
	while (env[i] != NULL)
	{
		if (i != index)
		{
			tmp[j] = env[i];
			++j;
		}
		else
			ft_strdel(&env[i]);
		++i;
	}
	tmp[j] = NULL;
	free(env);
	return (tmp);
}

void	deltab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		++i;
	}
	free(tab);
}
