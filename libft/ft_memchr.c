/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:06:15 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:06:18 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	cc;
	size_t			i;

	p = (unsigned char *)str;
	cc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (p[i] == cc)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}
/*int main () {
   const char str[] = "https://www.tutorialspoint.com";
   const char ch = 'p';
   char *ret;
      char *ret1;

   ret = memchr(str, ch, 3);
     ret1 = ft_memchr(str, ch, 3);

  printf("String after |%c| is - |%s|\n", ch, ret);
      printf("String after |%c| is - |%s|\n", ch, ret1);

   return(0);
}*/
