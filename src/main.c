/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:02:20 by guroux            #+#    #+#             */
/*   Updated: 2019/08/12 14:03:46 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(char ***env)
{
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr("$> ");
		args = getargs();
		status = execute(args, env);
		deltab(args);
	}
	deltab(*env);
}

int		main(int ac, char **av, char **envp)
{
	char **env;

	(void)ac;
	(void)av;
	env = copyenv(envp);
	loop(&env);
	return (0);
}
