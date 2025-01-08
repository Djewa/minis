#include "minishell.h"

static int	quote_msg_error(void)
{
	write (2, "Syntax error: Unterminated quoted string\n", 41);
	return (1);
}

void	plus_quote(int *sq, int *dq, int flag, int *i)
{
	if (flag == 0)
		(*dq)++;
	else
		(*sq)++;
	(*i)++;
}

int	check_quote(char *input, int i, int dq, int sq)
{
	char	cha;
	int		flag;

	flag = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			cha = input[i];
			if (input[i] == '\'')
				flag = 1;
			plus_quote(&sq, &dq, flag, &i);
			while (input[i] != cha && input[i])
				i++;
			if (input[i] == cha)
				plus_quote(&sq, &dq, flag, &i);
		}
		else
			i++;
	}
	if (sq % 2 != 0 || dq % 2 != 0)
		return (quote_msg_error());
	return (0);
}
