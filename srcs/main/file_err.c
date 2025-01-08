/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:53:24 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/02 23:13:38 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_string(char end)
{
	if (end == ' ' || end == '<' || end == '>')
		return (1);
	return (0);
}

static void	examine_file(char *input, int p, char *file, char mark)
{
	int	quote;
	int	i;
	char end;

	quote = 0;
	i = 0;
	end = ' ';
	while (input[p] && input[p] != end && input[p] != mark)
	{
		if ((input[p] == 34 || input[p] == 39) && quote == 0)
		{
			quote = -1;
			end = input[p];
			p++;
		}
		file[i++] = input[p++];
		if (input[p] == end && quote < 0)
		{
			end = ' ';
			quote = 0;
			p++;
		}
	}
	file[i] = '\0';
}

static int	prepare_filename(char *input, int p, int count)
{
	char	*file;
	char	mark;
	int	flag;

	file = malloc(sizeof(char) * (count + 1));
	mark = input[p - 1];
	flag = 0;
	while (input[p] && input[p] == ' ')
		p++;
	examine_file(input, p, file, mark);
	if (access(file, F_OK) == -1 && mark == '<')
	{
		msg_error(file, ": No such file or directory\n", 1);
		flag = 1;
	}
	else if (mark == '<' || mark == '>')
	{
		if (access(file, W_OK) == -1 && access(file, F_OK) == 0)
		{
			msg_error(file, ": Permission denied\n", 1);
			flag = 1;
		}
	}
	free(file);
	return (flag);
}

static int	find_filename(char *input, int p, char end, char mark)
{
	int	count;
	int	quote;

	while (input[p] && input[p] == ' ')
		p++;
	count = 0;
	quote = 0;
	while (input[p] && input[p] != end && input[p] != mark)
	{
		if ((input[p] == 34 || input[p] == 39) && quote == 0)
		{
			quote = -1;
			end = input[p];
			p++;
		}
		count++;
		p++;
		if (input[p] == end && quote < 0)
		{
			end = ' ';
			quote = 0;
			p++;
		}
	}
	return (count);
}

int	redirect_err_file(char *input)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	j = 0;
	while (input[i])
	{
		if ((input[i] == 34 || input[i] == 39) && j == 0)
		{
			j = -1;
			c = input[i++];
		}
		if (j < 0 && input[i] == c)
			j = 0;
		if ((input[i] == '<' || input[i] == '>') && j == 0)
		{
			if (input[i + 1] == '>')
				i++;
			if (prepare_filename(input, i + 1, find_filename(input, i + 1, ' ', input[i])) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
