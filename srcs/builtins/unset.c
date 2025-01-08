/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:00:54 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/31 02:00:54 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char *input, t_minishell sh)
{
	char	**cmd;
	int		i;

	if (ft_strncmp(input, "unset", 6) == 0)
		return ;
	cmd = ft_split(input, ' ');
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
	{
		i = 0;
		while (sh.env[i])
		{
			if (ft_strncmp(sh.env[i], cmd[1], ft_strlen(cmd[1])) == 0)
				break ;
			i++;
		}
		if (!ft_strnstr(cmd[1], "=", ft_strlen(cmd[1])))
		{
			while (sh.env[i])
			{
				sh.env[i] = sh.env[i + 1];
				i++;
			}
		}
		ft_free_split(cmd);
	}
}

// void	unset_cmd(char *input, t_minishell sh)
// {
// 	int		i;
// 	char	**set;

// 	set = ft_split(input, ' ');
// 	i = 0;
// 	while (sh.env[i])
// 	{
// 		if (ft_strncmp(set[1], sh.env[i], ft_strlen(set[1])) == 0)
// 			break;
// 		i++;
// 	}
// 	if (!ft_strnstr(set[1], "=", ft_strlen(set[1])))
// 	{
// 		// sh.env[i] = ft_strjoin(set[1], "=")
// 		while (sh.env[i])
// 		{
// 			sh.env[i] = sh.env[i + 1];
// 			i++;
// 		}
// 	}
// 	ft_free_split(set);
// }
