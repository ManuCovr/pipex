/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:57:30 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/19 10:25:40 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pipe(t_pip ppx, char **argv, char **env)
{
	if (pipe(ppx.fd) == 0)
	{
		ppx.pid1 = fork();
		if (ppx.pid1 < 0)
			error_syntax(2);
		else if (ppx.pid1 == 0)
			newborn(&ppx, argv, env);
		close(ppx.fd[1]);
		ppx.pid2 = fork();
		if (ppx.pid2 < 0)
			error_syntax(2);
		else if (ppx.pid2 == 0)
			second_one(&ppx, argv, env);
		close (ppx.fd[0]);
		waitpid(ppx.pid1, NULL, 0);
		waitpid(ppx.pid2, NULL, 0);
	}
	else
	{
		ft_putendl_fd("Something went wrong with Pipe.", 2);
		ft_freedad(&ppx);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	ppx;

	if (argc == 5)
	{
		ft_path(&ppx, env);
		ft_pipe(ppx, argv, env);
		ft_freedad(&ppx);
	}
	else
		ft_putendl_fd("Error with the number of arguments", 2);
	return (0);
}
