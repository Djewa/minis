/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:23:00 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/18 22:23:00 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_func(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	msg_error(char *file, char *msg, int flag)
{
	if (flag == 1)
		write(2, "bash: ", 6);
	write(2, file, ft_strlen(file));
	write(2, msg, ft_strlen(msg));
}

void	all_error(char **command)
{
	char	**cmd;
	char	*c;

	cmd = ft_split(command[2], ' ');
	c = ft_strjoin("/bin/", cmd[0]);
	if (access(c, X_OK) == -1)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		command[2] = ft_strjoin(command[2], " 2> /dev/null");
	}
	ft_free_split(cmd);
	free(c);
}
