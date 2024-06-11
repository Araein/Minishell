/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/23 22:10:21 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirectthis(t_list *list)
{
	if (redirect(list, 0) == -1)
	{
		return (-1);
	}
	redirectdup(list);
	return (1);
}

int	redirect(t_list *list, int i)
{
	while (list->cmd[i])
	{
		if (ft_strcmp(list->cmd[i], "<") == 0)
		{
			if (setup_in(list->redirfd, list,
					list->cmd[i + 1], 0) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], "<<") == 0 && list->exphere != 4)
		{
			if (setup_in(list->redirfd, list,
					list->cmd[i + 1], 2) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">>") == 0)
		{
			if (setup_out(list->redirfd, list->cmd[i + 1], 1) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">") == 0)
			if (setup_out(list->redirfd, list->cmd[i + 1], 0) == -1)
				return (-1);
		i++;
	}
	return (1);
}
