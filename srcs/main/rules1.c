/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:17:33 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/23 15:17:33 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	put_exit_ss2(char *new, char *old, char *status)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (old[i])
// 	{
// 		if (old[i] == '$' && old[++i] == '?')
// 		{
// 			j = 0;
// 			while (status[j])
// 			{
// 				new[k++] = status[j];
// 				j++;
// 			}
// 			k--;
// 		}
// 		else
// 			new[k] = old[i];
// 		k++;
// 		i++;
// 	}
// 	new[k] = '\0';
// }

// static int	find_exit_imp(char *input)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && input[i + 1] == '?')
// 			j++;
// 		i++;
// 	}
// 	return (j);
// }

// static void	handle_exit_ss(char *input, t_minishell sh)
// {
// 	char	*status;
// 	char	*old;

// 	if (sh.exit == 0)
// 		return ;
// 	status = ft_itoa(sh.exit);
// 	old = ft_strdup(input);
// 	if (sh.exit > 9 && sh.exit < 100)
// 		put_exit_ss2(input, old, status);
// 	else if (sh.exit < 10)
// 	{
// 		// free(input);
// 		ft_strdup(input);
// 		input = malloc(sizeof(char) * (ft_strlen(old) + find_exit_imp(input) + 1));
// 		put_exit_ss2(input, old, status);
// 	}
// 	else if (sh.exit > 99)
// 	{
// 		// free(input);
// 		ft_strdup(input);
// 		input = malloc(sizeof(char) * (ft_strlen(old) + find_exit_imp(input) + 1));
// 		put_exit_ss2(input, old, status);
// 	}
// 	free(status);
// 	free(old);
// }


static void	put_exit_ss(char *input, t_minishell sh, int p)
{
	char	*status;
	// int		i;
	
	// i = 0;
	status = ft_itoa(sh.exit);
	if (sh.exit < 10)
	{
		input[p] = status[0];
		input[p + 1] = ' ';
	}
	else if (sh.exit < 100)
	{
		input[p] = status[0];
		input[p + 1] = status[1];
	}
	// else
	// exit_ss_more(input, status);
	free(status);
}

static void	handle_exit_ss(char *input, t_minishell sh)
{
	int	i;
	int	j;
	// int	k;

	i = 0;
	j = 0;
	// k = 0;
	while (input[i])
	{
		if (input[i] == '$')
			j++;
		if (input[i + 1] == '?')
		{
			if (j % 2 > 0)
			{
				put_exit_ss(input, sh, i);
				j = 0;
				// k++;
			}
		}
		i++;
	}
	// if (sh.exit > 99)
	// 	exit_ss_more(input, sh, k);
	// printf("k = %d\n", k);
}

static int	buitins_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

char	*check_program(char *program, char *input, t_minishell sh)
{
	if (program)
	{
		env_cmd(input, sh);
		free(sh.cmd);
		return (program);
	}
	else
	{
		if (buitins_cmd(sh.cmd) == 1)
		{
			free(sh.cmd);
			return ("/bin/sh");
		}
		free(sh.cmd);
		return (NULL);
	}
}

char	*select_program(char **command, char **en)
{
	char **path;
	char	*program;
	char	*tmp;
	int	i;

	while (*en && ft_strncmp(*en, "PATH=", 5) != 0)
		en++;
	if (!*en)
		return (NULL);
	path = ft_split(*en + 5, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		program = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(program, X_OK) == 0)
		{
			ft_free_split(path);
			return (program);
		}
		free(program);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}


//////////////////////////


char	**select_builtins(char *input, t_minishell sh, char **cmd)
{
	char	**command;

	if (ft_strnstr(input, "<", sizeof(input)) || ft_strnstr(input, ">", sizeof(input)))
	{
		if (redirect_err_file(input) == 1)// not include envariable ( $HOME $$ $? )
		{
			free(input);
			input = ft_strdup("cp 2> /dev/null");
		}
	}
	*cmd = find_command(input);
	if (ft_strnstr(input, "echo", ft_strlen(input)))
		handle_exit_ss(input, sh);
	command = (char **)malloc(sizeof(char *) * 4);
	command[0] = "sh";
	command[1] = "-c";
	command[2] = input;
	command[3] = NULL;
	return (command);
}
