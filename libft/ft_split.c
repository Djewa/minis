/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:07:38 by tchaloei          #+#    #+#             */
/*   Updated: 2024/02/28 18:07:40 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (*s)
	{
		if (*s != c)
		{
			res += 1;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (res);
}

static int	ft_free(char **res, size_t index)
{
	if (!res || !res[index - 1])
	{
		while (index > 0)
			free(res[--index]);
		free(res);
		return (1);
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	size_t	len;

	i = 0;
	res = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!res || !s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			res[i++] = ft_substr(s - len, 0, len);
			if (ft_free(res, i))
				return (NULL);
		}
		else
			++s;
	}
	res[i] = 0;
	return (res);
}
/*int main()
{
	char months[] = "JAN,FEB,asdhht";
	char** tokens;

	printf("months=[%s]\n\n", months);

	tokens = ft_split(months, ',');

	if (tokens)
	{
		int i;
		for (i = 0; *(tokens + i); i++)
		{
			printf("month=[%s]\n", *(tokens + i));
			free(*(tokens + i));
		}
		printf("\n");
		free(tokens);
	}

	return 0;
}*/