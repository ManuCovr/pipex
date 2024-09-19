/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:40:52 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/19 10:26:05 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*try_this(char *cargs, char **cpath)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	while (cpath[i])
	{
		temp = ft_strjoin(cpath[i], "/");
		cmd = ft_strjoin(temp, cargs);
		free(temp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	newborn(t_pip *ppx, char **argv, char **env)
{
	ppx->fd_infile = open(argv[1], O_RDONLY);
	ppx->dup_fd[0] = dup2(ppx->fd[1], STDOUT_FILENO);
	ppx->dup_fd[1] = dup2(ppx->fd_infile, STDIN_FILENO);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->fd_infile);
	if (ppx->dup_fd[0] < 0 || ppx->dup_fd[1] < 0)
		error_syntax(1);
	ppx->cargs = ft_split(argv[2], ' ');
	ppx->cmd = try_this(ppx->cargs[0], ppx->cpath);
	if (!ppx->cmd)
	{
		ft_freechild(ppx);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(ppx->cmd, ppx->cargs, env);
	ft_putendl_fd("Error executing command", 2);
	ft_freechild(ppx);
	exit (1);
}

void	second_one(t_pip *ppx, char **argv, char **env)
{
	ppx->fd_outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ppx->dup_fd[1] = dup2(ppx->fd[0], STDIN_FILENO);
	ppx->dup_fd[0] = dup2(ppx->fd_outfile, STDOUT_FILENO);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->fd_outfile);
	if (ppx->dup_fd[0] < 0 || ppx->dup_fd[1] < 0)
		error_syntax(1);
	ppx->cargs = ft_split(argv[3], ' ');
	ppx->cmd = try_this(ppx->cargs[0], ppx->cpath);
	if (!ppx->cmd)
	{
		ft_freechild(ppx);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(ppx->cmd, ppx->cargs, env);
	ft_putendl_fd("Error executing command", 2);
	ft_freechild(ppx);
	exit (1);
}
