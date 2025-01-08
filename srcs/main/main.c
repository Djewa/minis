/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:19:11 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/18 16:19:11 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ss;

void	get_shell_data(t_minishell *sh, char **en)
{
	int i;

	// sh = (t_minishell *)malloc(sizeof(t_minishell));
	sh->i = 0;
	sh->j = 0;
	sh->n = 0;
	sh->id_h = 0;
	sh->h_ok = -1;
	sh->exit = 0;
	sh->pipefd[0] = 0;
	sh->pipefd[1] = 0;
	sh->pipefd2[0] = 0;
	sh->pipefd2[1] = 0;
	sh->sub = NULL;
	sh->cmd = NULL;
	sh->eof = NULL;
	sh->hd = NULL;
	sh->sep = NULL;
	sh->env = malloc(sizeof(char *) * (ft_strlen2d(en) + 1));
	i = 0;
	while (en[i])
	{
		sh->env[i] = ft_strdup(en[i]);
		i++;
	}
	sh->env[i] = NULL;
}

int	find_heredoc(char *input)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i];
			i++;
			while (input[i] != c)
				i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
			j++;
		i++;
	}
	return (j);
}

void	start_hd(char *input, int c, t_minishell *sh)
{
	sh->h_ok = 1;
	sh->eof = malloc(sizeof(char *) * (c + 1));
	if (!sh->eof)
		error_func("The memmory can't allocate");
	sh->hd = malloc(sizeof(char *) * (c + 1));
	if (!sh->hd)
		error_func("The memmory can't allocate");
	build_hd(input, c, sh->eof, sh->hd);
}

void	start_process(char *input, char **en, t_minishell sh, int *ss)
{
	int			i;
	DIR			*dir;
	// static int	ss = 0;
	if (check_syntax(input, 0, 0, NULL) > 0)
		*ss = g_ss;
	else
	{
		i = find_heredoc(input);
		dir = NULL;
		if (i > 0)
		{
			start_hd(input, i, &sh);
			dir = opendir("/tmp/");
		}
		sep_process(input, en, sh, ss);
		if (sh.eof)// เอา if ออกแล้วลองดูว่าจะเอาunlinkไว้ใน loop มั้ย
		{
			i = 0;
			while (sh.eof[i])
			{
				unlink(sh.eof[i]);
				unlink(sh.hd[i]);
				i++;
			}
			ft_free_split(sh.eof);
			ft_free_split(sh.hd);
		}
		if (dir)
			closedir(dir);
	}
}

int	main(int ac, char **av, char **en)
{
	char		*input;
	t_minishell	sh;
	static int	ss;
	int	n;

	(void)ac;
	(void)av;
	ss = 0;
	get_shell_data(&sh, en);
	signal_init(1);
	while (1)
	{
		input = readline("\1\e[1;36m\2minishell > \1\e[0m\2");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			ft_free_split(sh.env);
			// ft_free_split(sh.envp);
			printf("exit\n");
			break ;
		}
		if (input && *input)
		{
			n = handle_exit(input, 0, 0, 0);
			if (g_ss > 0)
				ss = g_ss;
			add_history(input);
			if (check_quote(input, 0, 0, 0) == 0 && n == 0)
				start_process(input, sh.env, sh, &ss);
			else if (n == 1)
			{
				free (input);
				exit (g_ss);
			}
		}
		free(input);
	}
}
