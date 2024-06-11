/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:14:44 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/23 22:51:41 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dostr(char *str, char *buf, char *tmp, int type)
{
	if (type == 1)
	{
		tmp = ft_strjoin(str, buf);
		free(str);
		str = NULL;
		return (tmp);
	}
	else
	{
		free(str);
		str = NULL;
		if (tmp == NULL)
			return (NULL);
		else
			return (tmp);
	}
}

char	*read_line(char *str, int fd, int *r, char *tmp)
{
	char	buf[BUFFER_SIZE + 1];

	*r = read(fd, &buf, BUFFER_SIZE);
	while (*r > 0)
	{
		if (test(&r, buf) == 0)
			return (str);
		if (str)
		{
			tmp = dostr(str, buf, tmp, 1);
			if (!tmp)
				return (NULL);
			str = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
		}
		else
			str = ft_strdup(buf);
		if (str == NULL)
			return (NULL);
		if (test2(&r, buf, str, fd) == 0)
			return (str);
	}
	return (str);
}

char	*minifree(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char	*get_line(char *str, char **line, int r, int i)
{
	char	*tmp;

	while (str[i] && str[i] != '\n')
		i++;
	if (i < ft_strlen(str))
	{
		if (i == 0)
			i++;
		*line = ft_substr(str, 0, i);
		i--;
		if (*line == NULL)
			return (minifree(str));
		tmp = ft_substr(str, i + 1, ft_strlen(str));
		if (dostr(str, NULL, tmp, 2) == NULL)
			return (NULL);
		str = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	else if (r == 0)
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char		*str;
	int				r;
	char			*tmp;

	tmp = NULL;
	if (fd < 0 || !line)
		return (-1);
	if (BUFFER_SIZE < 1)
		return (-1);
	str = read_line(str, fd, &r, tmp);
	if (str == NULL || r == -1)
		return (-1);
	str = get_line(str, line, r, 0);
	if (r <= 0 && !str)
		return (r);
	return (1);
}
