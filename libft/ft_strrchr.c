/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:09:30 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:09:33 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}

/*int main () {
   const char str[] = "https://www.tutorialspoint.com";
   const char ch = 'w';
   char *ret;
   char *ret1;

   ret = strrchr(str, ch);
   ret1 = ft_strchr(str, ch);

   printf("String after |%c| is - |%s|\n", ch, ret);
printf("String after |%c| is - |%s|\n", ch, ret1);

   return(0);
}*/