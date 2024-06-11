/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:38:05 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 14:19:32 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	there_is_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	check_quote(char *buffer)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'' || buffer[i] == '\"')
		{
			c = buffer[i];
			++quote;
			i++;
			while (buffer[i] && buffer[i] != c)
				i++;
			if (buffer[i] == c)
				--quote;
		}
		if (quote != 0)
			return (quote);
		i++;
	}
	return (quote);
}

int	pipe_quote(char *buffer, int *i)
{
	int		text;
	char	quote_tp;

	text = 0;
	if (buffer[*i] && (buffer[*i] == '\"' || buffer[*i] == '\''))
	{
		quote_tp = buffer[*i];
		(*i)++;
		text++;
		while (buffer[*i] && buffer[*i] != quote_tp)
		{
			(*i)++;
			text++;
		}
		if (buffer[*i] && buffer[*i] == quote_tp)
		{
			(*i)++;
			text++;
		}
	}
	return (text);
}

int	error_pipe(char *buffer, int text, int i, int nb_pipe)
{
	if (!buffer || (buffer && buffer[i] && (buffer[i] == '|'
				|| ((buffer[ft_strlen(buffer) - 1]) == '|'))))
		return (0);
	while (buffer[i])
	{
		while (buffer[i] && is_whitespace(buffer[i]))
			i++;
		text = pipe_quote(buffer, &i);
		is_text(buffer, &i, &text);
		nb_pipe = 0;
		while (buffer[i] && (buffer[i] == '|' || is_whitespace(buffer[i])))
		{
			if (buffer[i] == '|')
				++nb_pipe;
			if (nb_pipe > 1)
				return (0);
			i++;
		}
		text = pipe_quote(buffer, &i);
		is_text(buffer, &i, &text);
		if (nb_pipe == 1 && !text)
			return (0);
	}
	return (1);
}

int	check_basic_error(char *buffer)
{
	if (check_quote(buffer) != 0)
	{
		write(2, "error : quote not close\n", 24);
		g_status = 2;
		return (0);
	}
	else if (error_pipe(buffer, 0, 0, 0) != 1)
	{
		write(2, "bash : syntax error near unexpected token `|'\n", 46);
		g_status = 2;
		return (0);
	}
	return (1);
}
