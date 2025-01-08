/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:09:57 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:10:00 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*int main() 
{ 
    char ch; 

    // letter to convert to uppercase
    ch = 'A'; 

    printf("%c in uppercase is represented as %c\n", 
        ch, tolower(ch));
    printf("%c in uppercase is represented as %c", 
        ch, ft_tolower(ch));

    return 0; 
}*/
