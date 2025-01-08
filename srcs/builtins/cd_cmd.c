#include "minishell.h"

int	ms_cd_error(char *path, int i)
{
	if (i == 1)
	{
		write (2, "cd:", 3);
		write (2, " too many arguments", 19);
		write (2, "\n", 1);
	}
	else if (i == 2)
	{
		write (2, "Command \'", 9);
		write (2, path, ft_strlen(path));
		write (2, "' not found\n", 12);
	}
	else if (i == 3)
		write (2, "cd: syntax error near unexpected token \" or \'\n", 46);
	else if (i == 4)
	{
		write (2, " No such file or directory", 26);
		// write (2, " ", 1);
		// write (2, path, ft_strlen(path));
		write (2, "\n", 1); 
	}
	g_ss = 1;
	// printf ("ss = %d\n", *ss);
	return (1);
}

// void	sep_cd(char **path, char *oldpwd, char *en, char *str)
// {
// 	if (ft_strncmp(path[1], "/", 2) == 0)
// 		do_chdir("/", 0);
// 	else if (ft_strncmp(path[1], "~", 2) == 0 || ((ft_strncmp(path[0], "cd", 3) == 0 || ft_strncmp(path[0], "cd", 3) == 32) && path[1] == NULL))
// 	{
// 		en = getenv("HOME");
// 		do_chdir(en, 0);
// 	}
// 	else if (en != NULL)
// 		do_chdir(en, 0);
// 	else if (ft_strncmp(path[1], "-", 2) == 0)
// 	{
// 		printf("%s\n", oldpwd);
// 		do_chdir(oldpwd, 0);
// 	}
// 	else if (path[2] != NULL && str != NULL)
// 	{
// 		do_chdir(str, 0);
// 		free (str);
// 	}
// 	else if (path[1] != NULL && path[2] == NULL)
// 		do_chdir(path[1], 0);
// 	else
// 		ms_cd_error("", 4, 0);

// }

void	do_chdir(char *input)
{
	if (chdir(input) == -1)
		ms_cd_error(input, 4);
}

int check_space_cd(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i++;
			while (input[i] != input[i - 1] && input[i])
				i++;
		}
		else if (input[i] == ' ' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			ms_cd_error("", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_cd_command(char *input, char *str, char *en)
{
	// int	i;

	// i = 0;
	(void)str;
	(void)en;
	if (check_space_cd(input, 3) == 1)
		return (1);
	if (ft_strnstr(input, "/", ft_strlen(input)) != 0 && check_slash_cd(input, 0, 0) == 1)
		return (1);
	return (0);
}

int	check_slash_cd(char *input, int i, char c)
{
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i];
			i++;
			while (input[i] != c && input[i])
				i++;
		}
		else if (input[i] == '/' && (input[i + 1] == ' ' || input[i - 1] == ' ') && (ft_strncmp(input, "cd /", 5) != 0) && (input[i - 3] != 'c' && input[i - 2] != 'd'))
		{
			ms_cd_error("", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*do_en_cd(char *input, int i, char *en)
{
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			if (input[i] == '\0')
			{
				ms_cd_error("", 4);
				return (NULL);
			}
		}
		else if (input[i] == '$')
		{
			i++;
			j = i;
			while (input[j] && input[j] != ' ' && input[j] != '"')
				j++;
			str = (char *)malloc(sizeof(char) * ((j - i) + 1));
			j = 0;
			while (input[i] && input[i] != ' ' && input[i] != '"')
				str[j++] = input[i++];
			if (input[i] != '\0')
			{
				ms_cd_error("", 1);
				return (NULL);
			}
			str[j] = '\0';
			en = getenv(str);
			ft_strdup(str);
			free (str);
			break ;
		}
		i++;
	}
	return (en);
}

static int count_len_path(char **path, int i, int len)
{
	while (path[i])
	{
		len = len + ft_strlen(path[i]);
		i++;
	}
	return (len);
}

char	*space_fol_cd(char **path, char *str, int *i)
{
	int		j;
	int		len;
	char	c;
	int		count;

	len = 0;
	count = 0;
	while (path[*i])
	{
		j = 0;
		while (path[*i][j])
		{
			if ((path[*i][j] == '\"' || path[*i][j] == '\'') && path[*i][j + 1] == '$')
				return (0);
			else if ((path[*i][j] == '\"' || path[*i][j] == '\'') && count == 0)
			{
				c = path[*i][j];
				count++;
				j++;
			}
			else if (path[*i][j] == c && count > 0)
			{
				count = 0;
				j++;
			}
			else
				str[len++] = path[*i][j++];
		}
		if (path[*i + 1] != NULL)
		{
			str[len] = ' ';
			len++;
		}
		(*i)++;
	}
	str[len] = '\0';
	return (str);
}

void	cd_command(char *input, t_minishell sh)
{
	static char	*oldpwd;
	char		*newpwd;
	char		*en;
	char		**path;
	int			i;
	char		*str;
	int			len;

	// g_ss = 0;
	(void)sh;
	en = NULL;
	str = NULL;
	i = 0;
	while (*input == ' ')
		input++;
	if (oldpwd == NULL)
		oldpwd = getcwd(NULL, 0);
	newpwd = getcwd(NULL, 0);
	// if (check_space_cd(input, 3, ss) == 1)
	// 	return ;
	// if (ft_strnstr(input, "/", ft_strlen(input)) != 0 && check_slash_cd(input, 0, ss, 0) == 1)
	// 	return ;
	if (check_cd_command(input, str, en) == 1)
		return ;
	if (ft_strnstr(input, "$", ft_strlen(input)) != 0)
	{
		en = do_en_cd(input, i, en);
		if (en == NULL)
			return ;
	}
	path = ft_split(input, ' ');
	if ((ft_strnstr(input, "\"", ft_strlen(input)) != 0 || ft_strnstr(input, "\'", ft_strlen(input)) != 0) && !en)
	{
		len = count_len_path(path, 1, 0);
		str = (char *)malloc(sizeof(char) * (len + 1));
		i = 1;
		if (space_fol_cd(path, str, &i) == 0)
		{
			free (str);
			return ;
		}
	}
	// if (ft_strncmp(input, "cd /", 5) == 0)
	// 	do_chdir("/");
	if (ft_strncmp(input, "cd ~", 5) == 0 || ((ft_strncmp(input, "cd", 3) == 0 || ft_strncmp(input, "cd ", 3) == 0) && path[1] == NULL))
	{
		en = getenv("HOME");
		do_chdir(en);
		// free (en);
	}
	else if (en != NULL)
	{
		do_chdir(en);
		// free (en);
	}
	else if (ft_strncmp(input, "cd -", 5) == 0)
	{
		printf("%s\n", oldpwd);
		do_chdir(oldpwd);
	}
	else if (path[2] != NULL && str != NULL && g_ss == 0)
	{
		do_chdir(str);
		free (str);
	}
	else if (path[1] != NULL && path[2] == NULL)
		do_chdir(path[1]);
	else
	{
		ms_cd_error("", 4);
	}
		// perror("cd");
	if (oldpwd != NULL)
	{
		free (oldpwd);
		oldpwd = newpwd;
	}
	ft_free_split(path);
}
