/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:04:39 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:04:44 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*int main(){
    printf("%d\n",isalnum('@'));
    printf("%d\n",ft_isalnum('@'));
    printf("%d\n",isalnum('A'));
    printf("%d",ft_isalnum('A'));
}*/
