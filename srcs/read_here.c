/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:31:57 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/22 15:56:00 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sigread(void)
{
	struct sigaction	sb;

	sb.sa_handler = SIG_IGN;
	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;
	if (sigaction(SIGQUIT, &sb, NULL) == -1)
		return (-1);
	return (1);
}

int	writeerrorbuf(int ret, char *doc, char *buf, int fd)
{
	char	*itoanum;

	if (fd == -1)
	{
		write(2, "bash: warning: here-document at line ", 37);
		itoanum = ft_itoa(ret);
		write(2, itoanum, ft_strlen(itoanum));
		write(2, " delimited by end-of-file (wanted `", 35);
		free(itoanum);
		itoanum = ft_strjoin(doc, "')\n");
		write(2, itoanum, ft_strlen(itoanum));
		free(itoanum);
		return (0);
	}
	else
	{
		ret++;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		return (ret);
	}
}

void	readloop(int ret, char *doc, int fd[2])
{
	char	*buf;

	while (ret)
	{
		buf = readline("> ");
		if (g_status == 130 || g_status == 131)
		{
			free(buf);
			break ;
		}
		if (!buf)
			ret = writeerrorbuf(ret, doc, buf, -1);
		else if (!(ft_strcmp(buf, doc)))
			ret = 0;
		else
			ret = writeerrorbuf(ret, doc, buf, fd[0]);
		if (g_status == 130 || g_status == 131)
			ret = 0;
		free(buf);
		buf = NULL;
	}
}

int	readfunc(char *doc, int fd[2])
{
	int		ret;
	int		p_id;
	int		status;

	p_id = fork();
	if (p_id == 0)
	{
		ret = sigread();
		if (ret == -1)
			return (-1);
		readloop(ret, doc, fd);
		return (close (fd[0]), -2);
	}
	return (waitpid(-1, &status, 0), 0);
}
