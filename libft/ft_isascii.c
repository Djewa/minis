/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:15 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:05:19 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*int main(){
    printf("%d\n",isascii(-1));
    printf("%d\n",ft_isascii(-1));
    printf("%d\n",isascii(128));
    printf("%d",ft_isascii(128));
}*/
