/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:09:40 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:09:42 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*trim;

	trim = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		trim = (char *)malloc(sizeof(char) * (j - i + 1));
		if (trim)
			ft_strlcpy(trim, &s1[i], j - i + 1);
	}
	return (trim);
}
/*int main()
{
    printf("%s\n", ft_strtrim("abqbc", "abc"));
  //  printf("%s\n", ft_strtrim("xavocadoyz", "xyz"));
    return 0;
}*/