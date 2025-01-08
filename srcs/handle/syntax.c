#include "minishell.h"

int	syntax_msg_error(int i, char *str)
{
	if (i == 1)
		g_ss = 2;
	else
		g_ss = 127;
	if (i == 1)
	{
		write (2, " syntax error near unexpected token `", 37);
		write (2, str, ft_strlen(str));
		write (2, "\'", 1);
	}
	else if (i == 2)
	{
		write (2, str, ft_strlen(str));
		write (2, ":", 1);
		write (2, " command not found", 18);
	}
	else if (i == 3)
	{
		write (2, str, ft_strlen(str));
		write (2, ":", 1);
		write (2, " No such file or directory", 26);
	}
	write (2, "\n", 1);
	return (g_ss);
}

static int	do_syntax_pipe(char *input, int *i, int *j, char *str)
{
	char	*bin;

	bin = NULL;
	(*i)++;
	*j = *i;
	str = copy_str(input, i, NULL, j);
	if (str == NULL)
		return (0);
	else if (input[*i + 1] == '\0' && str)
	{
		if (ft_strncmp(str, "/bin/", 5) != 0
			&& ft_strncmp(str, "/usr/bin/", 9) != 0)
			bin = ft_strjoin("/bin/", str);
		else
			*bin = ft_strlcpy(bin, str, ft_strlen(str));
		if (access(bin, X_OK) == -1 && syntax_builtins_outside(str) == 0)
		{
			if (str[ft_strlen(str) - 1] == '/')
				return (syntax_msg_error(3, str));
			else
				return (syntax_msg_error(2, str));
		}
		free (bin);
	}
	return (0);
}

void	do_syntax_sign(int i, int count_less, int count_more, int flag)
{
	if (i == 1 && count_more > 0)
	{
		if (flag == 1 && count_more > 1)
			syntax_msg_error(1, ">>");
		else if (count_more < 3 && flag == 0)
			syntax_msg_error(1, "newline");
		else if ((count_more == 3 && flag == 0)
			|| (count_more == 1 && flag == 1))
			syntax_msg_error(1, ">");
		else if (flag == 0 && count_more > 3)
			syntax_msg_error(1, ">>");
	}
	else if (i == 2 && count_less > 0)
	{
		if (count_less < 4)
			syntax_msg_error(1, "newline");
		else if (count_less == 4)
			syntax_msg_error(1, "<");
		else if (count_less == 5)
			syntax_msg_error(1, "<<");
		else
			syntax_msg_error(1, "<<<");
	}
}

int	sep_syntax_sign(char *input, int *i, int count_more, int count_less)
{
	int	flag;

	flag = 0;
	if (input[*i] == '>')
	{
		if (input[*i] == '>' && input[*i + 1] == ' ' && input[*i + 2] == '>')
		{
			*i = *i + 2;
			flag = 1;
		}
		count_more = count_sign(input, i, 0, '>');
		if (input[*i] == '\0' && count_more > 0)
			do_syntax_sign(1, 0, count_more, flag);
		(*i)--;
	}
	else if (input[*i] == '<')
	{
		count_less = count_sign(input, i, 0, '<');
		if (input[*i] == '\0' && count_less > 0)
			do_syntax_sign(2, count_less, 0, flag);
		(*i)--;
	}
	return (g_ss);
}

int	check_syntax(char *input, int i, int j, char *str)
{
	g_ss = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == '\0')
			return (syntax_msg_error(1, ";"));
		if (input[i] == '|')
		{
			if (input[0] == '|' || input[i + 1] == '\0' || input[i - 1] == '<')
				return (syntax_msg_error(1, "|"));
			else
			{
				i = check_space(input, i);
				if (input[i] == '"' && do_syntax_pipe(input, &i, &j, str) != 0)
					break ;
				free (str);
				i--;
			}
		}
		else if ((input[i] == '>' || input[i] == '<')
			&& sep_syntax_sign(input, &i, 0, 0) > 0)
			break ;
		i++;
	}
	return (g_ss);
}
