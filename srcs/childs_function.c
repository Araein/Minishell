/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:40:48 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 11:21:57 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	startchild(t_list *list, int **pipefd, int index)
{
	list->index = index;
	if (index == 0)
	{
		if (firstchild(list, pipefd) == -1)
			return (freeandclose(list, pipefd, list->command_count, 1));
		close(pipefd[0][1]);
		index++;
	}
	else if (index > 0 && index < list->command_count - 1)
	{
		if (middlechild(list, pipefd) == -1)
			return (freeandclose(list, pipefd, list->command_count, 1));
		close(pipefd[index][1]);
		index++;
	}
	else
	{
		if (lastchild(list, pipefd) == -1)
			return (freeandclose(list, pipefd, list->command_count, -1));
		freeandclose(list, pipefd, list->command_count, 1);
		index++;
	}
	return (0);
}

int	errorpath(t_list *list, char **myenv)
{
	write(2, list->cmd[0], ft_strlen(list->cmd[0]));
	write(2, ": command not found\n", 20);
	if (myenv)
		freetab(myenv);
	g_status = 127;
	return (-1);
}

int	firstchild(t_list *list, int **pipefd)
{
	pid_t	p_pid;
	char	*paths;
	char	**myenv;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (callredirec(list, pipefd, 1) == -1)
			return (-1);
		if (!(list->cmd))
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			myenv = getmyenv(list);
			paths = getpath(list->cmd[0], getmyline(myenv));
			if (!paths)
				return (errorpath(list, myenv));
			execve(paths, list->cmd, myenv);
			free(paths);
			if (myenv)
				freetab(myenv);
		}
		return (-1);
	}
	return (0);
}

int	middlechild(t_list *list, int **pipefd)
{
	pid_t	p_pid;
	char	*paths;
	char	**myenv;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (callredirec(list, pipefd, 3) == -1)
			return (-1);
		if (!(list->cmd))
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			myenv = getmyenv(list);
			paths = getpath(list->cmd[0], getmyline(myenv));
			if (!paths)
				return (errorpath(list, myenv));
			execve(paths, list->cmd, myenv);
			free(paths);
			if (myenv)
				freetab(myenv);
		}
		return (-1);
	}
	return (0);
}

int	lastchild(t_list *list, int **pipefd)
{
	pid_t	p_pid;
	char	*paths;
	char	**myenv;

	p_pid = fork();
	if (p_pid == 0)
	{	
		if (callredirec(list, pipefd, 2) == -1)
			return (-1);
		if (!(list->cmd))
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			myenv = getmyenv(list);
			paths = getpath(list->cmd[0], getmyline(myenv));
			if (!paths)
				return (errorpath(list, myenv));
			execve(paths, list->cmd, myenv);
			free(paths);
			if (myenv)
				freetab(myenv);
		}
		return (-1);
	}
	return (0);
}
