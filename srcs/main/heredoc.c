/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:24:12 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/18 19:24:12 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	receive_input(char *eof, char *file)
{
	int		fd;
	size_t	len;
	char	*text;
	char	*input;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		error_func("can not open file.");
	len = ft_strlen(eof);
	while (1)
	{
		input = readline("> ");
		if (ft_strlen(input) > len)
			len = ft_strlen(input);
		if (ft_strncmp(input, eof, len) == 0)
		{
			free(input);
			break ;
		}
		text = ft_strjoin(input, "\n");
		write(fd, text, ft_strlen(text));
		free(text);
		free(input);
	}
	close(fd);
}

static void	manage_files(char **eof, char **file)
{
	int	i;

	i = 0;
	while (eof[i])
	{
		receive_input(eof[i], file[i]);
		i++;
	}
}

void	build_hd(char *input, int c, char **eof, char **file)
{
	char	*n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			eof[j] = get_end(input, count_end(input, i + 2), i + 2);
			n = ft_itoa(j);
			file[j] = ft_strjoin("/tmp/heredoc", n);
			free(n);
			j++;
			if (j == c)
				break;
		}
		i++;
	}
	eof[j] = NULL;
	file[j] = NULL;
	manage_files(eof, file);
}
