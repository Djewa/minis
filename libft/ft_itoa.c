/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:44 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:05:47 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nb;
	size_t	i;
	size_t	len;

	i = get_digits(n);
	nb = n;
	len = i;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		n *= -1;
	while (i > 0)
	{
		i--;
		str[i] = (n % 10) + 48;
		n = n / 10;
	}
	if (nb < 0)
		str[0] = '-';
	str[len] = '\0';
	return (str);
}
/*int main() 
{
	int i = -123455;
	
	printf("%s\n", ft_itoa(i));

	return 0;
}*/