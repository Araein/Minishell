/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:53:03 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 14:40:12 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_quote(char *buffer, char *str, int *i, int *j)
{
	char	quote;

	quote = buffer[(*i)];
	str[(*j)++] = buffer[(*i)++];
	while (buffer[*i] != quote)
	{
		str[*j] = buffer[*i];
		(*j)++;
		(*i)++;
	}
	str[(*j)++] = buffer[(*i)++];
}

char	*separate_redi(char *buffer, int i, int j)
{
	char	*str;

	if (!buffer)
		return (NULL);
	str = malloc((ft_strlen(buffer) * 2) + 1);
	if (!str)
		return (NULL);
	while (buffer[i])
	{
		if (buffer[i] == '\'' || buffer[i] == '\"')
			skip_quote(buffer, str, &i, &j);
		else if (buffer[i] && (buffer[i] == '<' || buffer[i] == '>'))
		{
			if (i > 0 && buffer[i - 1] != ' ')
				str[j++] = ' ';
			str[j++] = buffer[i++];
			if (buffer[i] && buffer[i] == buffer[i - 1])
				str[j++] = buffer[i++];
			if (i > 0 && buffer[i - 1] != ' ')
				str[j++] = ' ';
		}
		else
			str[j++] = buffer[i++];
	}
	return (str[j] = '\0', str);
}

void	delete_quote(char *line, char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				str[j++] = line[i++];
			if (line[i] && line[i] == quote)
				i++;
		}
		else
			str[j++] = line[i++];
	}
	str[j] = '\0';
}

char	*rm_quote(char *line, int type)
{
	char	*str;

	if (malloc_rm_quote(&str, line) == 0)
		return (NULL);
	delete_quote(line, str);
	if (type == 1)
	{
		free (line);
		line = NULL;
	}
	return (str);
}

void	remove_quote_buf(t_list *list)
{
	int			i;
	t_list		*head;

	head = list;
	if (!list)
		return ;
	while (head)
	{
		i = 0;
		if (head->clean_tab)
		{
			while (head->clean_tab[i])
			{
				if (there_is_quote(head->clean_tab[i]))
					head->clean_tab[i] = rm_quote(head->clean_tab[i], 1);
				i++;
			}
		}
		head = head->next;
	}
}
