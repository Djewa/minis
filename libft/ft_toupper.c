/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:10:06 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:10:09 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*int main() 
{ 
	char ch; 

	// letter to convert to uppercase
	ch = 'A'; 

	printf("%c in uppercase is represented as %c\n", 
		ch, toupper(ch));
	printf("%c in uppercase is represented as %c", 
		ch, ft_toupper(ch));

	return 0; 
}*/
