/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 02:17:16 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/30 02:17:16 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char *input, t_minishell sh)
{
	int		i;
	char	**sep;

	if (ft_strnstr(input, "env", sizeof(input)))
	{
		sep = ft_split(input, ' ');
		i = 0;
		while (sep[i])
		{
			if (ft_strncmp(sep[i], "env", 3) != 0)
			{
				ft_free_split(sep);
				return ;
			}
			i++;
		}
		ft_free_split(sep);
		input = "env > /dev/null";
		i = 0;
		while (sh.env[i])
		{
			printf("%s\n", sh.env[i]);
			i++;
		}
	}
}
