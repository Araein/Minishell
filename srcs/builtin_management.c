/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:30:17 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/20 17:51:09 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launchpwd(t_list *list, char *tempoline)
{
	redirectthis(list);
	tempoline = NULL;
	tempoline = built_in_pwd(list);
	if (tempoline != NULL)
	{
		printf("%s\n", tempoline);
		free (tempoline);
		g_status = 0;
	}
	else
		g_status = 1;
}

int	firstbuiltin(t_list *list, char *tempoline)
{
	if (ft_strcmp(list->cmd[0], "env") == 0)
	{
		redirectthis(list);
		printlist(list->envlist, 0);
		g_status = 0;
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "pwd") == 0)
	{
		launchpwd(list, tempoline);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "exit") == 0)
	{
		redirectthis(list);
		built_in_exit(list, 0);
		return (1);
	}
	return (0);
}

int	checkbuiltin(t_list *list)
{
	if (firstbuiltin(list, NULL) == 1)
		return (1);
	else if (ft_strcmp(list->cmd[0], "unset") == 0)
	{
		redirectthis(list);
		list->envlist = unset_line(list->cmd, list->envlist, 1);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "export") == 0)
	{
		redirectthis(list);
		list->envlist = built_in_export(list->envlist, list->cmd);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "cd") == 0)
	{
		redirectthis(list);
		list->envlist = built_in_cd(list->envlist, list->cmd, 0);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "echo") == 0)
		return (built_in_echo(list->cmd, list, 0));
	return (0);
}
