/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:28:58 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 11:27:23 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *str, int tsearched)
{
	int		i;
	char	searched;

	searched = (char)tsearched;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[ft_strlen(str) - i] == searched)
			return ((char *)&str[ft_strlen(str) - i]);
		i++;
	}
	if (str[ft_strlen(str) - i] == searched)
		return ((char *)&str[ft_strlen(str) - i]);
	return (0);
}

void	unset_line3(t_envlist *envlist, t_envlist *gl, t_envlist *temp)
{
	while (envlist->next && envlist->next != gl)
		envlist = envlist->next;
	if (envlist->next == gl)
	{
		temp = envlist->next;
		if (envlist->next->created == 1)
		{
			free(envlist->next->line);
			envlist->next->line = NULL;
		}
		envlist->next = envlist->next->next;
		free(temp);
		temp = NULL;
	}
}

t_envlist	*unset_line2(t_envlist *envlist, t_envlist *gl, t_envlist *first)
{
	t_envlist	*tempolist;

	tempolist = NULL;
	if (envlist && envlist == gl)
	{
		tempolist = envlist;
		if (envlist->created == 1)
		{
			free(envlist->line);
			envlist->line = NULL;
		}
		envlist = envlist->next;
		free(tempolist);
		tempolist = NULL;
		first = envlist;
	}
	else if (envlist)
		unset_line3(envlist, gl, tempolist);
	return (first);
}

t_envlist	*unset_line(char **buffer, t_envlist *envlist, int type)
{
	char		*tempo;
	int			i;
	char		**args;
	t_envlist	*goodlist;
	t_envlist	*firstlist;

	i = type;
	args = buffer;
	firstlist = envlist;
	while (args[i])
	{
		tempo = ft_strjoin ("$", args[i]);
		goodlist = findline(envlist, tempo);
		free(tempo);
		if (goodlist)
		{
			firstlist = unset_line2(envlist, goodlist, firstlist);
			envlist = firstlist;
		}
		i++;
	}
	return (firstlist);
}
