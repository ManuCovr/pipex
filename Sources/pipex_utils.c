/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:11:22 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/17 11:36:21 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_syntax(int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("Error with the input/output files.\n", 2);
		ft_putstr_fd("Usage: ./pipex [infile] [cmd1] [cmd2] [outfile]\n", 2);
	}
	if (flag == 2)
		ft_putstr_fd("Something went wrong with Fork.", 2);
	exit (0);
}


void	ft_path(t_pip *ppx, char **envp)
{
	ppx->path = find_path(envp);
	if (!ppx->path)
		exit(1);
	ppx->cpath = ft_split(ppx->path, ':');
}

void	ft_freechild(t_pip *ppx)
{
	int	i;

	i = 0;
	while (ppx->cargs[i])
	{
		free(ppx->cargs[i]);
		i++;
	}
	i = -1;
	while (ppx->cpath[++i])
		free(ppx->cpath[i]);
	free(ppx->cpath);
	free(ppx->cargs);
	free(ppx->cmd);
}

void	ft_freedad(t_pip *ppx)
{
	int	i;

	i = 0;
	while (ppx->cpath[i])
	{
		free(ppx->cpath[i]);
		i++;
	}
	free(ppx->cpath);
}

char	*find_path(char **envp)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			res = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (res == NULL)
	{
		ft_putendl_fd("Path not found", 2);
		return (NULL);
	}
	return (res);
}
