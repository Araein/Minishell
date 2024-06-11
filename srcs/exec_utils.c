/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:01:17 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 11:01:32 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**returnandfree(int i, int **pipefd)
{
	while (i > 0)
	{
		i--;
		free(pipefd[i]);
	}
	free(pipefd);
	return (NULL);
}

int	**mallocandpipe(int command_count)
{
	int	i;
	int	**pipefd;

	pipefd = (int **)malloc((command_count - 1) * sizeof(int *));
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < (command_count - 1))
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		if (pipefd[i] == NULL)
			return (returnandfree(i, pipefd));
		i++;
	}
	i = 0;
	while (i < command_count - 1)
	{
		if (pipe(pipefd[i]) == -1)
			perror ("Error");
		i++;
	}
	return (pipefd);
}

t_list	*transferlistdata(t_list *list, int index, int command_count)
{
	if (index < command_count)
	{
		list = list->next;
		list->index = index;
		list->command_count = command_count;
	}
	return (list);
}

void	waitfunc(int command_count, t_list *list)
{
	int	status;
	int	i;
	int	error;

	(void)list;
	i = 0;
	while (i < command_count)
	{
		error = waitpid (-1, &status, 0);
		if (error != -1)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_status = WTERMSIG(status);
				g_status += 128;
				if (WCOREDUMP(status) && g_status != 130 && g_status != 131)
					write(2, "Aborted (core dumped)\n", 22);
			}
		}
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
