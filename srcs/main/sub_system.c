/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:28:48 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/20 00:28:48 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_pipe(int fd[2], int flag)
{
	if (flag == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd[1]);
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd[1]);
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
	}
}

static void	redirect_pipe2(int fd[2], int fd2[2], int flag)
{
	if (flag == 0)
	{
		redirect_pipe(fd, 1);
		redirect_pipe(fd2, 0);
	}
	else
	{
		redirect_pipe(fd2, 0);
		redirect_pipe(fd, 1);
	}
}

static void	pipe_subprocess(t_minishell sh, int flag, char **en)
{
	char	**command;
	char	*program;

	if (flag == 0)
		redirect_pipe2(sh.pipefd, sh.pipefd2, flag);
	else
		redirect_pipe2(sh.pipefd2, sh.pipefd, flag);
	command = select_builtins(sh.sub, sh, &sh.cmd);
	// printf("%s\n", sh.cmd);
	program = select_program(command, en);//ในนี้ ทำการแยก echo ออกมาใส่ /bin/sh/echo เอา envมาอยู่ในนี้
	program = check_program(program, command[2], sh);
	// printf("%s\n", program);
	if (execve(program, command, en) == -1)
	{
		perror("ee");
		free(program);//free **command ด้วย
		exit(127);
	}
}

static void	pipe_process(int fd[2], int flag, char **en, t_minishell sh)
{
	char	**command;
	char	*program;

	redirect_pipe(fd, flag);
	command = select_builtins(sh.sub, sh, &sh.cmd);
	// printf("%s\n", sh.cmd);
	program = select_program(command, en);//ในนี้ ทำการแยก echo ออกมาใส่ /bin/sh/echo เอา envมาอยู่ในนี้
	program = check_program(program, command[2], sh);
	// printf("%s\n", program);
	if (execve(program, command, en) == -1)
	{
		perror("ee");
		free(program);//free **command ด้วย
		exit(127);
	}
}

void	subprocess_cons(t_minishell sh, char **en)
{
	sh.sub = sh.sep[sh.i];
	if (sh.i == 0)
		pipe_process(sh.pipefd, 0, en, sh);// start
	else if (sh.i % 2 != 0 && sh.i > 0 && sh.i < sh.n)
		pipe_subprocess(sh, 0, en);// mid odd
	else if (sh.i % 2 == 0 && sh.i > 0 && sh.i < sh.n)
		pipe_subprocess(sh, 1, en);// mid even
	else if (sh.i == sh.n && sh.i % 2 != 0)
		pipe_process(sh.pipefd, 1, en, sh);// end odd
	else if (sh.i == sh.n && sh.i % 2 == 0)
		pipe_process(sh.pipefd2, 1, en, sh);// end even
}
