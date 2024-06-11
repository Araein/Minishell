/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:15:58 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/23 22:51:59 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	test( int **r, char *buf)
{
	if (**r == -1)
		return (0);
	buf[**r] = 0;
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

int	test2( int **r, char *buf, char *str, int fd)
{
	if (ft_strchr(buf, '\n'))
		return (0);
	**r = read(fd, buf, BUFFER_SIZE);
	if (**r == -1)
	{
		free(str);
		str = NULL;
	}
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*answer;
	int		i;

	i = 0;
	if (!s || len <= 0 || start >= (unsigned int)ft_strlen(s))
		return (NULL);
	answer = malloc(sizeof(char) * len + 1);
	if (answer == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		answer[i] = s[start];
		i++;
		start++;
	}
	answer[i] = '\0';
	return (answer);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
	if (dest == NULL)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
