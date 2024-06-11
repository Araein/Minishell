/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 14:33:28 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	g_status;

int	ft_prompt(char **buffer)
{
	*buffer = readline("Minishell$> ");
	if (!(*buffer))
	{
		write (2, "exit\n", 5);
		return (1);
	}
	add_history(*buffer);
	return (0);
}

t_list	*else_while(t_list_prov *l_p, t_list *list, char *buf, int *er_redi)
{	
	int	i;

	i = 0;
	buf = separate_redi(buf, 0, 0);
	l_p->str_cmd = ft_split_pipe(buf, '|', 0);
	l_p->str_cmd = expand_dollar(l_p->envlist,
			l_p->str_cmd);
	while (l_p->str_cmd[i] != 0)
	{
		list = ft_add_node(list, l_p->str_cmd[i], buf,
				l_p->envlist);
		i++;
	}
	if (check_error_redi(list))
		return (freetab(l_p->str_cmd), free(buf), *er_redi = -1, list);
	if (list && list->envlist)
		l_p->envlist = list->envlist;
	freetab(l_p->str_cmd);
	free(buf);
	get_clean_string(list, 0, 0);
	remove_quote_buf(list);
	return (list);
}

void	loop(t_list_prov *list_prov, t_list *list, char *buffer, int er_redi)
{
	while (1)
	{
		if (ft_prompt(&buffer))
			break ;
		if (check_basic_error(buffer) != 1)
			free_first_check(list);
		else
		{
			er_redi = 0;
			list = else_while(list_prov, list, buffer, &er_redi);
			list->statushandle = list_prov->statushandle;
			if (er_redi == 0)
			{
				if ((list->cmd[0] != NULL && exec(list) == -1))
				{
					free_list(list);
					list = NULL;
					break ;
				}
			}
			list = minifreeprov(list_prov, list, 2);
		}
		if (loop_signal() == -1)
			return ;
	}
}

t_list_prov	*ft_init_list_prov(t_list_prov *list_prov, char **argv)
{
	(void)argv;
	g_status = 0;
	list_prov = malloc(sizeof(t_list_prov));
	if (!list_prov)
		return (NULL);
	list_prov->str_cmd = NULL;
	list_prov->statushandle = 0;
	return (list_prov);
}

int	main(int argc, char **argv, char **env)
{
	t_list				*list;
	t_list_prov			*list_prov;

	list = NULL;
	list_prov = NULL;
	if (argc != 1)
	{
		write(2, "error : too many arguments\n", 27);
		exit(1);
	}
	list_prov = ft_init_list_prov(list_prov, argv);
	using_history();
	list_prov->envlist = make_env(env);
	execute_signals(list_prov);
	loop(list_prov, list, NULL, 0);
	if (list_prov && list_prov->envlist && list_prov->envlist->shlvl_line)
		free(list_prov->envlist->shlvl_line);
	if (list_prov)
		free_list_env(list_prov->envlist);
	free(list_prov);
	exit(g_status);
	return (0);
}
