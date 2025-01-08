/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:40:39 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/05 00:40:39 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buitins_outside(char *cmd)
{
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

static void	commond_name(char *name)
{
	char	*bin;

	bin = ft_strjoin("/bin/", name);
	if (access(bin, X_OK) == -1 && buitins_outside(name) == 0)
		msg_error(name, ": command not found\n", 0);
	free(bin);
}

static void	directory_name(char *name)
{
	if (access(name, X_OK) == 0)
	{
		if (ft_strncmp(name, "/bin/", 5) != 0 && ft_strncmp(name, "/usr/bin/", 9) != 0)
			msg_error(name, ": Is a directory\n", 1);
	}
	else
		msg_error(name, ": No such file or directory\n", 1);
}

static void	split_directory(char *name)
{
	if (ft_strnstr(name, "/", ft_strlen(name)))
		directory_name(name);
	else
		commond_name(name);
}

static char	*do_en_cmd(char *data, int f, char *name)
{
	char	*cv;

	if (f == 0 && name[0] != '$')
		return (data);
	cv = NULL;
	cv = getenv(data);
	if (!cv)
		return ("\0");
	return (cv);
}

void	filter_cmd(char *name)
{
	char	**sep;
	char	*en_var;
	char	*new;
	char	*tmp;
	int	i;

	if (ft_strnstr(name, "$", ft_strlen(name)))
	{
		sep = ft_split(name, '$');//พอspiltออกมาแล้วไม่รู้ว่าตำแหน่งไหนที่ต่อท้ายเครื่องหมาย $ (space เคลียร์แล้วจ้า)
		i = -1;
		new = ft_strdup("\0");
		while (sep[++i])
		{
			en_var = do_en_cmd(sep[i], i, name);
			tmp = ft_strdup(new);
			free(new);
			new = ft_strjoin(tmp, en_var);
			free(tmp);
		}
		split_directory(new);
		free(new);
		ft_free_split(sep);
	}
	else
		split_directory(name);
}
