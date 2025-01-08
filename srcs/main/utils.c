/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:15:49 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/19 22:15:49 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_imp(char *input, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	ft_strlen2d(char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
		i++;
	return (i);
}

int	count_end(char *input, int p)
{
	int	count;

	count = 0;
	while (input[p] == ' '&& input[p])
		p++;
	while (input[p] != ' ' && input[p] != '|' && input[p] != ';' && input[p])
	{
		p++;
		count++;
	}
	return (count);
}

char	*get_end(char *input, int j, int start)
{
	char	*end;
	int		c;

	while (input[start] == ' ' && input[start])
		start++;
	end = malloc(sizeof(char) * (j + 1));
	c = 0;
	while (c < j)
		end[c++] = input[start++];
	end[c] = '\0';
	return (end);
}