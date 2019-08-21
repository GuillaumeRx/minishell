/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:02:20 by guroux            #+#    #+#             */
/*   Updated: 2019/08/21 19:15:28 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		loop(char ***env)
{
	char	**args;
	int		status;
	int		excode;

	status = 1;
	excode = 1;
	while (status)
	{
		ft_putstr("$> ");
		if (!(args = getargs()))
		{
			deltab(*env);
			exit(-1);
		}
		status = execute(args, env);
		if (args[1])
			excode = ft_atoi(args[1]);
		deltab(args);
		args = NULL;
	}
	deltab(*env);
	return (excode);
}

int		main(int ac, char **av, char **envp)
{
	char	**env;
	int		ret;

	(void)ac;
	(void)av;
	env = copyenv(envp);
	ret = loop(&env);
	exit(ret);
	return (0);
}
