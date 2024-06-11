/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:34:24 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 11:55:10 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	secondgnl(int fd, char *tempoline, char **expanded)
{
	int	i;

	i = 0;
	fd = open(tempoline, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	if (fd < 0)
	{
		freetab(expanded);
		return ;
	}
	while (expanded[i])
	{
		write(fd, expanded[i], ft_strlen(expanded[i]));
		i++;
	}
	if (i > 0)
		write(fd, "\n", 1);
	freetab(expanded);
	close(fd);
}

int	firstgnl(int fd, char *tempoline)
{
	int		i;
	char	*line;

	i = 0;
	fd = open(tempoline, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
	while ((get_next_line(fd, &line)) > 0)
	{
		i++;
		free(line);
		line = NULL;
	}
	free (line);
	line = NULL;
	close (fd);
	return (i);
}

void	expand_here(int fd, t_envlist *envlist, char *tempoline, char *line)
{
	char	**expandtab;
	char	**expanded;
	int		i;

	i = firstgnl(fd, tempoline);
	if (i == -1)
		return ;
	expandtab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!expandtab)
		return ;
	fd = open(tempoline, O_RDONLY);
	i = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		expandtab[i] = line;
		i++;
	}
	if (line)
		free(line);
	close (fd);
	expandtab[i] = NULL;
	if (expandtab[i])
		free(expandtab[i]);
	expanded = expand_dollar(envlist, expandtab);
	secondgnl(fd, tempoline, expanded);
}

int	setup_here(char *doc, int command_num, int fd[2], t_list *list)
{
	char	*temponum;
	char	*tempoline;

	if (fd[0] > 0)
		close(fd[0]);
	temponum = ft_itoa(command_num);
	tempoline = ft_strjoin("/tmp/here_doc", temponum);
	free(temponum);
	fd[0] = open(tempoline, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	if (fd[0] == -1)
	{
		free(tempoline);
		perror(doc);
		return (g_status = 1, -1);
	}
	g_status = 42;
	if (readfunc(doc, fd) == -2)
		return (free(tempoline), -2);
	if (g_status == 42)
		g_status = 0;
	close(fd[0]);
	if (g_status == 131 || g_status == 130)
		return (free(tempoline), -1);
	expand_here(fd[0], list->envlist, tempoline, NULL);
	return (free(tempoline), 1);
}
