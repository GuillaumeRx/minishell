/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:25:54 by guroux            #+#    #+#             */
/*   Updated: 2019/09/02 19:10:09 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include "get_next_line.h"

/*
** shell.c
*/

int		execute(char **args, char ***env);
char	*repvar(char *arg, char ***env);

/*
** args.c
*/

char	**getargs(void);

/*
** utils.c
*/

char	**realoc_tab(char **tab, char *var);
int		tablen(char **tab);
char	**remenv(int index, char **env);
void	deltab(char **tab);

/*
** builtin.c
*/

int		ft_env(char **args, char ***env);
int		ft_setenv(char **args, char ***env);

/*
** builtin_2.c
*/

int		ft_unsetenv(char **args, char ***env);
int		ft_exit(char **args, char ***env);
int		ft_echo(char **args, char ***env);

/*
** cd.c
*/

int		ft_cd(char **args, char ***env);

/*
** misc.c
*/
int		findenv(char ***env, char *var);
int		reppwd(char ***env, char *pwd, int i);
char	*testpath(char *arg, char *path);

/*
** var.c
*/

char	*repvar(char *arg, char ***env);

/*
** env.c
*/

char	**copyenv(char **env);

#endif
