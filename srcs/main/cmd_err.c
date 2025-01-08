/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:56:08 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/02 01:56:08 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmd(char *input, int p)
{
	int	count;
	int	flag;
	char	quote;
	int	end;

	count = 0;
	flag = 0;
	end = 0;
	while (input[p]  && end == 0)
	{
		if ((input[p] == 34 || input[p] == 39) && flag == 0)
		{
			flag = -1;
			quote = input[p];
			p++;
		}
		if (input[p] == quote)
			flag = 0;
		else
			count++;
		p++;
		if (flag == 0)
			end = last_string(input[p]);
	}
	return (count);
}

static void	get_command(char *cmd, char *input, int p)
{
	int	i;
	int	flag;
	char	quote;
	int	end;

	i = 0;
	flag = 0;
	end = 0;
	while (input[p]  && end == 0)
	{
		if ((input[p] == 34 || input[p] == 39) && flag == 0)
		{
			flag = -1;
			quote = input[p];
			p++;
		}
		if (input[p] == quote)
			flag = 0;
		else
			cmd[i++] = input[p];
		p++;
		if (flag == 0)
			end = last_string(input[p]);
	}
	cmd[i] = '\0';
}

static char	*get_position(char *input, int pos)
{
	int	i;
	int	skip;
	char	*cmd;

	i = 0;
	skip = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			skip++;
		if (skip == pos)
			break;
		i++;
	}
	pos = count_cmd(input, i) + 1;
	cmd = malloc(sizeof(char) * pos);
	get_command(cmd, input, i);
	return (cmd);
}

static int	position_command(char **sep)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (sep[i])
	{
		if (sep[i][0] != '<' && sep[i][0] != '>')
			return (count + 1);
		if (sep[i][0] == '<' || sep[i][0] == '>')
		{
			count += ft_strlen(sep[i]);
			if (!sep[i][1])
				count += ft_strlen(sep[++i]);
		}
		i++;
	}
	return (0);
}

char	*find_command(char *input)
{
	char	**sep;
	char	*cmd;
	int		pos;

	sep = ft_split(input, ' ');
	pos = position_command(sep);
	cmd = get_position(input, pos);
	filter_cmd(cmd);
	ft_free_split(sep);
	return (cmd);
}
