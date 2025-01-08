/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:07:46 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:07:48 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	cc;

	cc = (char) c;
	while (*str)
	{
		if (*str == cc)
			return ((char *)str);
		str++;
	}
	if (cc == '\0')
		return ((char *)str);
	return (NULL);
}
/*int main () {
   const char str[] = "https://www.tutorialspoint.com";
   const char ch = '.';
   char *ret;
   char *ret1;

   ret = strchr(str, ch);
   ret1 = ft_strchr(str, ch);

   printf("String after |%c| is - |%s|\n", ch, ret);
printf("String after |%c| is - |%s|\n", ch, ret1);

   return(0);
}*/