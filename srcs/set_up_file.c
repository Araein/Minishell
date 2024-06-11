/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:21:46 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 14:30:07 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	type_out(int fd[2], char *doc, char *tempodoc)
{
	tempodoc = rm_quote(doc, 2);
	if (fd[1] > 0)
		close(fd[1]);
	fd[1] = open(tempodoc, O_TRUNC | O_CREAT | O_RDWR, 0000664);
	if (fd[1] < 0)
	{
		perror(tempodoc);
		if (tempodoc)
			free(tempodoc);
		g_status = 1;
		return (-1);
	}
	free (tempodoc);
	tempodoc = NULL;
	return (0);
}

int	setup_out(int fd[2], char *doc, int type)
{
	char	*tempodoc;

	tempodoc = NULL;
	if (type == 0)
		type_out(fd, doc, tempodoc);
	else if (type == 1)
	{
		tempodoc = rm_quote(doc, 2);
		if (fd[1] > 0)
			close(fd[1]);
		fd[1] = open(tempodoc, O_APPEND | O_CREAT | O_RDWR, 0000664);
		if (fd[1] < 0)
		{
			perror(tempodoc);
			if (tempodoc)
				free(tempodoc);
			g_status = 1;
			return (-1);
		}
		free (tempodoc);
		tempodoc = NULL;
	}
	return (1);
}

int	setup_type(t_list *list, char *tempodoc, int type, int fd[2])
{
	char	*temponum;
	char	*tempoline;
	int		resulthere;

	if (type == 2)
	{
		temponum = ft_itoa(list->index);
		tempoline = ft_strjoin("/tmp/here_doc", temponum);
		free(temponum);
		fd[0] = open(tempoline, O_RDONLY);
		free(tempoline);
	}
	else if (type == 1)
	{
		resulthere = setup_here(tempodoc, list->command_count, fd, list);
		if (resulthere < 0)
			return (resulthere);
	}
	return (0);
}

int	open_in_fd(int type, int fd[2], t_list *list, char *tempodoc)
{
	if (fd[0] > 0)
		close(fd[0]);
	if (type == 2)
		setup_type(list, tempodoc, type, fd);
	else if (type == 0)
		fd[0] = open(tempodoc, O_RDONLY);
	if (fd[0] < 0)
	{
		if (tempodoc)
			perror(tempodoc);
		if (tempodoc)
			free(tempodoc);
		return (g_status = 1, -1);
	}
	return (1);
}

int	setup_in(int fd[2], t_list *list, char *doc, int type)
{
	char	*tempodoc;
	int		resulthere;

	tempodoc = rm_quote(doc, 2);
	if (type == 1)
	{
		resulthere = setup_type(list, tempodoc, 1, fd);
		if (resulthere < 0)
		{
			if (tempodoc)
				free(tempodoc);
			return (tempodoc = NULL, resulthere);
		}
	}
	if (open_in_fd(type, fd, list, tempodoc) == -1)
		return (-1);
	if (tempodoc)
		free(tempodoc);
	return (1);
}
