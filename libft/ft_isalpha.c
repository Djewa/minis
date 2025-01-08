/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:05 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:05:09 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*int main(){
    printf("%d\n",isalpha('-'));
    printf("%d\n",ft_isalpha('z'));
    printf("%d\n",isalpha('3'));
    printf("%d",ft_isalpha('3'));
}*/
