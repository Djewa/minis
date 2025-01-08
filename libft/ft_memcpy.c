/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:06:34 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:06:37 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*q;

	p = (char *)dest;
	q = (char *)src;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (p);
}
/*int main () {
   char dest[] = "oldstring";
   const char src[]  = "12345678";
   
  
   memcpy(dest, src, 5);
   printf("After memcpy dest = %s, src = %s\n", dest, src);
   ft_memcpy(dest, src, 5);
   printf("After ft_memcpy dest = %s, src = %s\n", dest, src);

   return(0);
}*/