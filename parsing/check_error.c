/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:07:57 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 15:24:32 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_redi_pipe_nwl(t_list *list)
{
	if (list == NULL)
		write(2, "bash : syntax error near unexpected token `newline'\n", 52);
	else
		write(2, "bash : syntax error near unexpected token `|'\n", 46);
	g_status = 2;
}

void	error_redi(char *cmd)
{
	write(2, "bash : syntax error near unexpected token `", 43);
	write(2, cmd, ft_strlen(cmd));
	write(2, "'\n", 2);
	g_status = 2;
}

int	check_erreur_redi_func(char **cmd, t_list *next)
{
	int	i;
	int	redi_1;
	int	redi_2;

	i = 0;
	while (cmd[i])
	{
		redi_1 = is_redi(cmd[i], 0);
		if (redi_1)
			i++;
		if (redi_1 && cmd[i])
		{
			redi_2 = is_redi(cmd[i], 0);
			if (redi_1 && redi_2)
				return (error_redi(cmd[i]), 1);
		}
		else if (!(cmd[i]) && redi_1)
			return (error_redi_pipe_nwl(next), 1);
		if (cmd[i])
			i++;
	}
	return (0);
}

int	check_error_redi(t_list *list)
{
	t_list	*head;

	if (!list)
		return (1);
	head = list;
	while (head)
	{
		if (head->cmd)
		{
			if (check_erreur_redi_func(head->cmd, head->next) == 1)
				return (1);
		}
		head = head->next;
	}
	return (0);
}

int	malloc_rm_quote(char **str, char *line)
{
	if (!line)
		return (0);
	*str = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!str)
		return (0);
	return (1);
}
