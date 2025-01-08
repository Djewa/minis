/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:09:09 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:09:14 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*int main () {
	char str1[15];
	char str2[15];
	int ret;
	int ret1;

	strcpy(str1, "hello world");
	strcpy(str2, "helLo world");

	ret = strncmp(str1, str2, 3);
	ret1 = ft_strncmp(str1, str2, 3);
	
	printf("%d\n", ret);
	printf("%d\n", ret1);
	
	return(0);
}*/