/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:57:39 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/17 12:32:11 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_pip
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_infile;
	int		fd_outfile;
	int		fd[2];
	int		dup_fd[2];
	char	*cmd;
	char	*path;
	char	**cargs;
	char	**cpath;
}			t_pip;

// Main PIPEX Functions

int			main(int ac, char **av, char **envp);

// Utility PIPEX Functions

void		error_syntax(int flag);
void		ft_freedad(t_pip *ppx);
char		*find_path(char **envp);
void		ft_freechild(t_pip *ppx);
void		ft_path(t_pip *ppx, char **envp);
void		newborn(t_pip *ppx, char **argv, char **env);
void		second_one(t_pip *ppx, char **argv, char **env);


#endif