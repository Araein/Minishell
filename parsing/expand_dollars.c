/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:04:18 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 15:23:46 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_new_cmd(char *line, char *str_d, int k, int *index)
{
	int		x;
	char	*cmd;
	char	*str_1;

	init_new_cmd(&str_1, &cmd, &x);
	if (line)
	{
		str_1 = ft_substr(line, 0, *index);
		cmd = ft_strjoin(str_1, str_d);
		free(str_1);
		free(str_d);
		*index += k;
		x = ft_strlen(cmd);
		if (line[*index])
		{
			str_d = ft_strjoin(cmd, line + *index);
			free(cmd);
			cmd = str_d;
		}
		*index = x - 1;
	}
	return (cmd);
}

void	len_var_dollar(char *line, int *i, int *j)
{
	*j = *i + 1;
	while (line[*j] && line[*j] != ' ' && line[*j] != '\''
		&& line[*j] != '$' && line[*j] != '\"')
		(*j)++;
}

char	*expand(char *line, t_envlist *envlist, int *i, int k)
{
	int		j;
	char	*str_1;
	char	*str_2;

	j = 0;
	expand_quote(line, i);
	if (line[*i] && line[*i] == '$' && line[*i + 1] != ' '
		&& line[*i + 1] != '$'
		&& line[*i + 1] != '\0')
	{
		if (line[*i + 1] == '?')
			str_1 = funct_dollar_intero(i, &j, &k);
		else
		{
			len_var_dollar(line, i, &j);
			str_2 = ft_substr(line, *i, j - *i);
			str_1 = get_env_line_dollar(envlist, str_2);
		}
		str_2 = ft_new_cmd(line, str_1, j - *i, i);
		line = free_expand(str_2, line);
	}
	else if (line[*i])
		(*i)++;
	return (line);
}

char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\0')
		line = expand(line, envlist, &i, k);
	return (line);
}

char	**expand_dollar(t_envlist *envlist, char **str_cmd)
{
	int		i;

	if (!str_cmd)
		return (NULL);
	i = 0;
	while (str_cmd[i])
	{
		str_cmd[i] = find_expand_dollar(envlist, str_cmd[i]);
		i++;
	}
	return (str_cmd);
}
