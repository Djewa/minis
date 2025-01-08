/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:06:24 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:06:27 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	i = 0;
	p = (unsigned char *)str1;
	q = (unsigned char *)str2;
	while (i < n)
	{
		if (p[i] != q[i])
			return (p[i] - q[i]);
		i++;
	}
	return (0);
}
/*int main () {
   char str1[15] = "ABCDefl";
   char str2[15] = "ABCD666662";
   int ret;
   int ret1;

   ret = memcmp(str1, str2, 2);
   ret1 = ft_memcmp(str1, str2, 2);

   printf("%d\n", ret);
  printf("%d", ret1);
   
   return(0);
}*/