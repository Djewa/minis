/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:19:38 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/20 00:19:38 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipe(t_minishell *sh)
{
	if (sh->j % 2 == 0)
	{
		if (pipe(sh->pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		if (pipe(sh->pipefd2) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

static void	close_pipe(int i, int pipefd[2], int pipefd2[2])
{
	if (i % 2 != 0 && i > 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (i % 2 == 0 && i > 0)
	{
		close(pipefd2[0]);
		close(pipefd2[1]);
	}
}

void	child_subprocess(t_minishell sh, char **en, int *ss)
{
	pid_t	*pids;
	int		status;

	pids = malloc(sizeof(pid_t) * (sh.n + 1));
	while (sh.sep[sh.i])
	{
		sh.id_h += sh.i;
		if (sh.j < sh.n)
			create_pipe(&sh);
		edit_input(sh.sep[sh.i], sh, sh.id_h);
		pids[sh.i] = fork();
		if (pids[sh.i] < 0)
			error_func("fork error");
		else if (pids[sh.i] == 0)
			subprocess_cons(sh, en);
		close_pipe(sh.i, sh.pipefd, sh.pipefd2);
		sh.i++;
		sh.j++;
	}
	sh.j = 0;
	while (sh.j < sh.i)
		waitpid(pids[sh.j++], &status, 0);
	*ss = WEXITSTATUS(status);
	free(pids);
}
