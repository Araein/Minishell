/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:17 by dabey             #+#    #+#             */
/*   Updated: 2023/02/23 20:48:08 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**to_return_or_not(char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((ft_count_word(s, c, 0) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	return (tab);
}

char	*get_s(char *s, int type)
{
	if (type == 1)
	{
		while (*s && *s == ' ' && *(s - 1) == ' ')
			s++;
	}
	else
	{
		while (*s && *s == ' ' && *(s - 1) == ' ')
			s++;
	}
	return (s);
}

char	**returntab(char **tab, int i, int j)
{
	while (j != i - 1)
	{
		free(tab[j]);
		tab[j] = NULL;
		j++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char *s, char c, int i, int j)
{
	char	**tab;
	int		count;

	count = ft_count_word(s, c, 0);
	tab = to_return_or_not(s, c);
	if (!tab)
		return (NULL);
	while (i < count)
	{
		j = 0;
		while (*s == ' ' || *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_word(s, c) + 1));
		if (!tab[i])
			return (returntab(tab, i, j));
		while (*s != c && *s != '\0')
		{
			s = get_s(s, 1);
			tab[i][j++] = *s++;
			s = get_s(s, 2);
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
