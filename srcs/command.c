/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:46:23 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/23 20:34:02 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd2(t_list *list, char *buffer)
{
	int		l;
	int		equal;
	char	*tempoline;
	char	*result;

	l = ft_strlen(list->envlist->line);
	equal = searchequal(list->envlist->line) - 1;
	buffer = ft_substr(list->envlist->line, 11, l - (l - equal) - 9);
	tempoline = ft_substr(list->envlist->line,
			equal + 3, l - (equal + 4));
	result = ft_strjoin(buffer, tempoline);
	free(buffer);
	free(tempoline);
	tempoline = ft_substr(result, 4, ft_strlen(result) - 4);
	free(result);
	return (tempoline);
}

char	*built_in_pwd(t_list *list)
{
	char	*buffer;
	size_t	allocsize;

	buffer = NULL;
	allocsize = sizeof(char) * FILENAME_MAX;
	buffer = (char *)malloc(sizeof(char) * allocsize);
	if (buffer == NULL)
		return (NULL);
	if (getcwd(buffer, allocsize) == NULL)
	{
		free(buffer);
		buffer = ft_strjoin ("$", "PWD");
		if (list)
			list->envlist = findline(list->envlist, buffer);
		free (buffer);
		if (list && list->envlist)
			return (pwd2(list, buffer));
		else
			return (NULL);
	}
	return (buffer);
}

// char	*ft_strdup(const char *str)
// {
// 	int		i;
// 	char	*dest;

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	dest = (char *)malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		dest[i] = str[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

void	exec_cd(t_envlist *envlist, char *tempo, char *oldpwd)
{
	char	*tempo2;
	char	**tempotab;

	tempo = built_in_pwd(NULL);
	tempo2 = ft_strjoin("cut PWD=", tempo);
	tempotab = ft_split(tempo2, ' ', 0, 0);
	envlist = built_in_export(envlist, tempotab);
	freetab(tempotab);
	free (tempo);
	free (tempo2);
	tempo = NULL;
	tempo2 = NULL;
	if (oldpwd)
	{
		tempo = oldpwd;
		tempo2 = ft_strjoin("cut OLDPWD=", tempo);
		tempotab = ft_split(tempo2, ' ', 0, 0);
		built_in_export(envlist, tempotab);
		freetab(tempotab);
		free (tempo);
		free (tempo2);
	}
	g_status = 0;
}

void	errorcd(char *tempo, char **buffer, int type)
{
	if (type == 1)
	{
		tempo = ft_strjoin("minishell: cd: ", buffer[1]);
		perror(tempo);
		free(tempo);
		g_status = 1;
	}
	if (type == 2)
	{
		write(2, "minishell: cd: too many arguments\n", 29);
		g_status = 1;
	}
}

t_envlist	*built_in_cd(t_envlist *envlist, char **buffer, int i)
{
	char		*oldpwd;
	t_envlist	*tempolist;

	while (buffer[i])
		i++;
	if (i == 1)
		return (envlist);
	else if (i != 2)
		errorcd(NULL, buffer, 2);
	else if (chdir(buffer[1]) == 0)
	{
		tempolist = findline(envlist, "$PWD");
		if (tempolist)
		{
			oldpwd = cutline(tempolist->line);
			oldpwd = removequote(oldpwd);
		}
		else
			oldpwd = NULL;
		exec_cd(envlist, NULL, oldpwd);
	}
	else
		errorcd(NULL, buffer, 1);
	return (envlist);
}
