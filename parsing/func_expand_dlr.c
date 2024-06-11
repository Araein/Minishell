/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_expand_dlr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:52:08 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 15:25:15 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*funct_dollar_intero(int *i, int *j, int *k)
{
	char	*str_d;

	str_d = ft_itoa(g_status);
	*j = *i + 2;
	*k = 1;
	return (str_d);
}

int	close_quote(char *line, int i, char quote)
{
	while (line[i])
	{
		if (line[i] && line[i] != quote)
			i++;
		else if (line[i])
			return (++i);
	}
	return (i);
}

void	expand_quote(char *line, int *i)
{
	char	db_quote;

	db_quote = 0;
	if (line[*i] == '\"')
	{
		if (!db_quote)
			db_quote = 1;
		++(*i);
	}
	if (line[*i] == '\'' && db_quote == 0)
		*i = close_quote(line, ++(*i), line[(*i - 1)]);
	else if (line[*i] == '\'')
		++(*i);
}

char	*free_expand(char *str_d, char *line)
{
	free(line);
	line = str_d;
	return (line);
}

void	init_new_cmd(char **str_1, char **cmd, int *x)
{
	*x = 0;
	*cmd = NULL;
	*str_1 = NULL;
}
