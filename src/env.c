/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 22:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/08/26 01:56:58 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shlvl(char *env)
{
	char	**tab;
	char	*new;
	char	*tmp;

	if (!(tab = ft_strsplit(env, '=')))
		return (NULL);
	if (!(tmp = ft_itoa(ft_atoi(tab[1]) + 1)))
		return (NULL);
	if (!(new = ft_strjoin("SHLVL=", tmp)))
		return (NULL);
	return (new);
}

char	**copyenv(char **env)
{
	char	**envcpy;
	int		i;

	i = 0;
	if (!(envcpy = (char **)malloc(sizeof(char *) * (tablen(env) + 1))))
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL", ft_strlen("SHLVL")) == 0)
		{
			if (!(envcpy[i] = shlvl(*env)))
				return (NULL);
		}
		if (ft_strncmp(*env, "SHELL", ft_strlen("SHELL")) == 0)
		{
			if (!(envcpy[i] = ft_strdup("SHELL=minishell")))
				return (NULL);

		}
		else if (!(envcpy[i] = ft_strdup(*env)))
			return (NULL);
		++i;
		++env;
	}
	envcpy[i] = NULL;
	return (envcpy);
}
