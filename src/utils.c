/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:53:11 by guroux            #+#    #+#             */
/*   Updated: 2019/07/03 13:10:18 by guroux           ###   ########.fr       */
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
