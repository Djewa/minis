/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:13:25 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/18 19:13:25 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_file(char *hd, char *eof)
{
	int		rd;
	int		fd;
	int		b;
	char	buf[10];

	rd = open(hd, O_RDONLY);
	fd = open(eof, O_CREAT | O_RDWR | O_TRUNC, 0644);
	b = 1;
	while (b > 0)
	{
		b = read(rd, buf, sizeof(buf));
		write(fd, buf, b);
	}
	close(rd);
	close(fd);
}

void	edit_input(char *input, t_minishell sh, int round)
{
	int			i;
	static int	j = 0;

	if (sh.h_ok < 0)
		return ;
	i = 0;
	if (round == 0)
		j = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			input[++i] = ' ';
			redirect_file(sh.hd[j], sh.eof[j]);
			j++;
			sh.id_h = j;
		}
		i++;
	}
}

static void	main_process(char *input, char **en, t_minishell sh, int *ss)
{
	pid_t	pid;
	int		status;
	char	**command;
	char	*program;

	edit_input(input, sh, sh.id_h);
	status = 0;
	pid = fork();
	signal_init(2);
	if (pid < 0)
		error_func("fork error");
	else if (pid == 0)
	{
		sh.exit = *ss;
		command = select_builtins(input, sh, &sh.cmd);
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
	else
	{
		waitpid(pid, &status, 0);
		signal_init(1);
		if (g_ss > 0)
			*ss = g_ss;
		else
			*ss = WEXITSTATUS(status);
		// printf("%d\n", *ss);
	}
	// dprintf(2, "status : %d\n", *ss);
	// *ss = WEXITSTATUS(status);
	// printf("%s\n", input);
}

void	sep_process(char *input, char **en, t_minishell sh, int *ss)
{
	sh.n = count_imp(input, '|');
	sh.sep = ft_split(input, '|');
	if (sh.n + 1 == ft_strlen2d(sh.sep) && sh.n > 0)
	{
		child_subprocess(sh, en, ss);
	}
	else if (ft_strnstr(input, "cd", ft_strlen(input)) != 0)
	{
		while (*input == ' ')
			input++;
		if (ft_strncmp(input, "cd ", 3) == 0 || ft_strncmp(input, "cd", 3) == 0)
		{
			cd_command(input, sh);
			*ss = g_ss;
		}
	}

	else
	{
		if (sh.n > 0)
			sh.n = -1;
		main_process(input, en, sh, ss);
		unset_cmd(input, sh);
	}
	ft_free_split(sh.sep);
}
