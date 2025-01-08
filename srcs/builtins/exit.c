/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:28:41 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/23 15:28:41 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg_error(int i, char *str)
{
	(void)str;
	// write (2, "exit:", 6);
	if (i == 1)
	{
		// write (2, " ", 1);
		// write (2, str, ft_strlen(str));
		// write (2, ":", 1);
		write (2, " numeric argument required", 26);
		g_ss = 2;
	}
	else if (i == 2)
	{
		write (2, " too many arguments", 19);
		g_ss = 1;
	}
	write (2, "\n", 1);
}

void	check_alpha_digit(char *input, int *alpha, int *digit, int i)
{
	while (input[i])
	{
		if (ft_isalpha(input[i]) == 1)
		{
			(*alpha)++;
			return ;
		}
		else if (ft_isdigit(input[i]) == 1 && *digit == 0)
			(*digit)++;
		i++;
	}
}

static int	do_num_dollar(char *cmd, char *num, int i, int j)
{
	int	n;

	n = 0;
	if (ft_strnstr(cmd, "\"", ft_strlen(cmd)) != 0
		|| ft_strnstr(cmd, "\'", ft_strlen(cmd)) != 0)
	{
		if (ft_strnstr(cmd, "+", ft_strlen(cmd)) != 0
			|| ft_strnstr(cmd, "-", ft_strlen(cmd)) != 0)
			num = (char *)malloc(sizeof(char) * (ft_strlen(cmd)));
		else
			num = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - 1));
		while (cmd[i])
		{
			if (cmd[i] == '"' || cmd[i] == '\'')
				i++;
			else if (cmd[i] == '-' || cmd[i] == '+')
			{
				num[0] = cmd[i];
				j++;
				i++;
			}
			else
				num[j++] = cmd[i++];
		}
		num[j] = '\0';
		n = ft_atoi(num);
		free (num);
	}
	else
		n = ft_atoi(cmd);
	return (n);
}

static int	get_n_value(int n)
{
	if (n > 256)
	{
		while (n > 256)
			n = n - 256;
	}
	else if (n < 0)
	{
		while (n < 0)
			n = n + 256;
	}
	else
		n = n;
	return (n);
}



int	handle_exit(char *input, int alpha, int digit, int n)
{
	char	**cmd;
	// int n = 0;

	cmd = ft_split(input, ' ');
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) != 0)
	{
		ft_free_split(cmd);
		return (0);
	}
	printf("exit\n");
	check_alpha_digit(cmd[1], &alpha, &digit, 0);
	if (alpha == 1)
	{
		exit_msg_error(1, cmd[1]);
		ft_free_split(cmd);
		return (1);
	}
	else if (digit == 1 && alpha == 0 && cmd[2])
	{
		exit_msg_error(2, "");
		ft_free_split(cmd);
		return (2);
	}
	else if (digit == 1 && alpha == 0 && !cmd[2])
	{
		n = do_num_dollar(cmd[1], NULL, 0, 0);
		g_ss = get_n_value(n);
		ft_free_split(cmd);
		return (1);
	}
	return (0);
}
