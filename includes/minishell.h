#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"

/*
** shell.c
*/

int		execute(char **args, char **env);

/*
** args.c
*/

char	**getargs(void);

/*
** utils.c
*/

char	**copyenv(char **env);

/*
** builtin.c
*/

int		ft_echo(char **args, char **env);
int		ft_exit(char **args, char **env);
int		ft_env(char **args, char **env);

#endif
