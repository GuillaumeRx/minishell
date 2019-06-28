#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"

/*
** shell.c
*/

int		execute(char **args);

/*
** args.c
*/

char	**getargs(void);

#endif