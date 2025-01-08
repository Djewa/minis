#include "minishell.h"

int	check_space(char *input, int i)
{
	i++;
	if (input[i] == ' ')
	{
		while (input[i] == ' ')
			i++;
		return (i);
	}
	return (i);
}

int	count_sign(char *input, int *i, int count, char c)
{
	while (input[*i] == c)
	{
		count++;
		(*i)++;
	}
	return (count);
}

char	*copy_str(char *input, int *i, char *str, int *j)
{
	int	len;

	len = 0;
	*j = 0;
	while (input[len] != '"')
		len++;
	if (len > 0)
		str = (char *)malloc(sizeof(char) * (len + 1));
	else
		return (NULL);
	while (input[*i] != '"' && input[*i])
		str[(*j)++] = input[(*i)++];
	str[*j] = '\0';
	return (str);
}


int	syntax_builtins_outside(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
