/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:11:32 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 11:07:51 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sigaexec(void)
{
	struct sigaction	saq;

	saq.sa_handler = &handle_sig;
	sigemptyset(&saq.sa_mask);
	sigaddset(&saq.sa_mask, SIGQUIT);
	saq.sa_flags = 0;
	if (sigaction(SIGQUIT, &saq, NULL) == -1)
		return (-1);
	return (1);
}

int	execloop(t_list *list)
{
	int					index;
	int					i;
	int					**pipefd;

	index = 0;
	i = 0;
	pipefd = mallocandpipe(list->command_count);
	if (pipefd == NULL)
		return (-1);
	while (i < list->command_count)
	{
		if (startchild(list, pipefd, index) == -1)
			return (-1);
		index++;
		i++;
		list = transferlistdata(list, index, list->command_count);
	}
	waitfunc(list->command_count, list);
	return (1);
}

int	command_countfunc(t_list *list)
{
	int		i;
	int		hereresult;
	int		command_count;

	command_count = 0;
	while (list)
	{
		list->exit = 0;
		i = 0;
		while (list->cmd[i])
		{
			list->command_count = command_count;
			if (ft_strcmp(list->cmd[i], "<<") == 0)
			{
				hereresult = setup_in(list->redirfd, list, list->cmd[i + 1], 1);
				if (hereresult < 0)
					return (hereresult);
			}
			i++;
		}
		command_count++;
		list = list->next;
	}
	return (command_count);
}

int	exec(t_list *list)
{
	list->command_count = command_countfunc(list);
	if (list->command_count == -1)
		return (1);
	if (list->command_count == -2)
		return (-1);
	if (sigaexec() == -1)
		return (close_here(list), -1);
	if (list->command_count > 1)
	{
		if (execloop(list) == -1)
			return (-1);
	}
	else if (onecommand(list) == -1)
		return (close_here(list), -1);
	return (close_here(list), 1);
}
