/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:50:55 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/24 12:51:43 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_signal(void)
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

void	signal_display(void)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig(int sig)
{
	int					status;

	status = 0;
	waitpid(-1, &status, 0);
	if (!status && g_status != 42)
		signal_display();
	else if (!status && g_status == 42)
	{
		if (sig == SIGINT)
			exit(130);
		else
			exit(131);
	}
	else if (sig != SIGQUIT)
		write(2, "\n", 1);
	if (sig == SIGINT)
		g_status = 130;
	else if (sig == SIGQUIT)
	{
		g_status = 131;
		write(2, "Quit (core dumped)\n", 19);
	}
	if (loop_signal() == -1)
		return ;
}

t_list	*minifreeprov(t_list_prov *prov, t_list *list, int type)
{
	if (type == 1)
	{
		if (prov)
			free_list_env(prov->envlist);
		free(prov);
		exit(g_status);
	}
	else if (type == 2)
	{
		prov->statushandle = list->statushandle;
		prov->envlist = list->envlist;
		free_list(list);
		list = NULL;
		return (NULL);
	}
	return (NULL);
}

void	execute_signals(t_list_prov *prov)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = 0;
	sb.sa_handler = SIG_IGN;
	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		if (prov && prov->envlist && prov->envlist->shlvl_line)
			free(prov->envlist->shlvl_line);
		minifreeprov(prov, NULL, 1);
	}
	if (sigaction(SIGQUIT, &sb, NULL) == -1)
	{
		if (prov && prov->envlist && prov->envlist->shlvl_line)
			free(prov->envlist->shlvl_line);
		minifreeprov(prov, NULL, 1);
	}
}
