/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:22:49 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 11:22:27 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	size_t	j;
	size_t	p;

	p = ft_strlen(s2);
	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ((ft_strlen(s1) + p + 1)));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < p)
	{
		dest[i] = s2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	lenght_of_word(char *s, char sep)
{
	int		len_w;
	char	quote_tp;

	len_w = 0;
	while (*s && *s != sep)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			s = loop_word_quote(&len_w, s, quote_tp);
			s++;
			len_w++;
		}
		else if (*s && *s != sep)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != sep)
			{
				len_w++;
				s++;
			}
		}
	}
	return (len_w);
}
