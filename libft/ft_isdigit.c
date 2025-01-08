/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:25 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:05:29 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*int main(){
    printf("%d\n",isdigit('-'));
    printf("%d\n",ft_isdigit('-'));
    printf("%d\n",isdigit('3'));
    printf("%d",ft_isdigit('3'));
}*/
