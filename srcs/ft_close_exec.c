/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:02:32 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 12:42:35 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_here(t_list *list)
{
	char	*temponum;
	char	*tempoline;
	int		i;

	i = 0;
	if (list == NULL)
		return ;
	list->command_count = list->command_count - 1;
	while (i <= list->command_count)
	{
		temponum = ft_itoa(i);
		tempoline = ft_strjoin("/tmp/here_doc", temponum);
		free(temponum);
		unlink(tempoline);
		if (tempoline)
			free(tempoline);
		i++;
	}
	return ;
}

void	close_allpipe(t_list *list, int **pipefd, int type)
{
	int		i;

	i = 0;
	if (type == 1)
	{
		i = 1;
		while (i < (list->command_count - 1))
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 2)
	{
		while (i < list->command_count - 2)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 3)
		close3(list, pipefd, i);
}

int	closesaved(t_list *list, int savedout, int savedin, int type)
{
	if (type == 0)
	{
		(void)list;
		dup2(savedout, 0);
		close (savedout);
		dup2(savedin, 1);
		close(savedin);
	}
	if (type == 1)
	{
		close (savedout);
		close(savedin);
	}
	return (-1);
}

void	close3(t_list *list, int **pipefd, int i)
{
	while (i < list->command_count - 1)
	{
		if (i != list->index - 1)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		i++;
	}
}
