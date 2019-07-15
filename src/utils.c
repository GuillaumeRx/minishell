/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:53:11 by guroux            #+#    #+#             */
/*   Updated: 2019/07/10 15:52:00 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copyenv(char **env)
{
	char	**envcpy;
	int		i;

	i = 0;
	while (env[i] != NULL)
		++i;
	if (!(envcpy = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	i = 0;
	while (*env)
	{
		if (!(envcpy[i] = ft_strdup(*env)))
			return (NULL);
		++i;
		++env;
	}
	envcpy[i] = NULL;
	return (envcpy);
}

char **realoc_tab(char **tab, char *var)
{
	char **tmp;
	int i;

	tmp = NULL;
	i = 0;
	while (tab[i] != NULL)
		++i;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i] != NULL)
	{
		tmp[i] = tab[i];
		++i;
	}
	tmp[i] = var;
	++i;
	tmp[i] = NULL;
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