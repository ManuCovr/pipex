/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:57:30 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/17 14:35:54 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void ft_pipe (t_pip ppx, char **argv, char **env)
{
	if(pipe(ppx.fd) == 0)
	{
		ppx.pid1 = fork();
		if(ppx.pid1 < 0)
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
	{
		ft_putendl_fd("Error with the number of arguments", 2);
	}
	return (0);
}










/*

ACCESS: Checks file accessibility (e.g., read/write permissions). Use it to ensure file1 exists and is readable and that file2 is writable.

DUP: Duplicates a file descriptor. Not essential here since dup2 is more flexible for redirection, but can be used if needed.

DUP2: Duplicates a file descriptor to a specific file descriptor (e.g., redirecting standard input/output).

EXECVE: Executes a program (like a shell command). Use this to run cmd1 and cmd2.

EXIT: Terminates a process with a status code. Use this to exit child processes.

FORK: Creates a new process (child). Use it to run cmd1 and cmd2 in separate processes.

PIPE: Creates a unidirectional data channel that can be used for inter-process communication. Use it to pass the output of cmd1 to the input of cmd2.

UNLINK: Deletes a name and possibly the file it refers to. If needed, use it to remove file2 before creating it.

WAIT: Waits for a child process to change state (e.g., to finish).

WAITPID: Waits for a specific child process to change state. Use it to handle the termination of child processes.

 */