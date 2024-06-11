/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2023/02/24 14:55:29 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>

# define STDIN	0
# define STDOUT	1
# define BUFFER_SIZE 1

extern long long	g_status;

typedef struct envlist
{
	char			*line;
	int				created;
	struct envlist	*next;
	char			*shlvl_line;
}	t_envlist;

typedef struct s_list_prov
{
	t_envlist		*envlist;
	int				statushandle;
	char			**str_cmd;
}	t_list_prov;

typedef struct s_list
{
	t_envlist			*envlist;
	char				*buffer;
	char				**cmd;
	int					buf_size;
	int					redirfd[2];
	int					index;
	int					command_count;
	struct s_list		*next;
	char				*clean_string;
	char				**clean_tab;
	char				**myenv;
	struct __dirstream	*isdir;
	int					exit;
	int					exphere;
	int					statushandle;
}	t_list;

// ***********************get_next_line*******************************
int			get_next_line(int fd, char **line);

// ***********************get_next_line_utils*******************************
int			test( int **r, char *buf);
int			test2( int **r, char *buf, char *str, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, int len);
char		*ft_strdup(const char *str);

// ***********************get_clean_string*******************************
void		get_clean_string(t_list *list, int i, int j);
int			whereend(char *line);
void		is_text(char *buffer, int *i, int *text);

// ***********************ft_utils*******************************
char		**ft_split(char *s, char c, int i, int j);
int			ft_strcmp(char *s1, char *s2);
int			close_quote(char *line, int i, char quote);

// ***********************ft_utils2*******************************
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(const char *str, int n);
int			ft_strcmp(char *s1, char *s2);
int			ft_isdigit(int c);
int			lenght_of_word(char *s, char sep);

// ***********************exec_utils*******************************
int			ft_strncmp(const char *s1, const char *s2, int n);
void		waitfunc(int command_count, t_list *list);
t_list		*transferlistdata(t_list *list, int index, int command_count);
int			**mallocandpipe(int command_count);
int			**returnandfree(int i, int **pipefd);

//***********************env_management************************
t_envlist	*make_env(char **env);
t_envlist	*ft_add_env(t_envlist *list, char *line, int created);
void		printlist(t_envlist *list, int type);
void		free_list_env(t_envlist *list);

//***********************print_env.c************************
void		printlist(t_envlist *list, int type);

//***********************do_shlvl************************
t_envlist	*change_shlvl(t_envlist *envlist, char **env);

// //***********************export********************************
t_envlist	*built_in_export(t_envlist *envlist, char **line);

//****************************env_utils***************************
char		*addquote(char *line);
int			searchequal(char *line);

//**************************unset******************************
t_envlist	*unset_line(char **buffer, t_envlist *envlist, int type);
char		*ft_strrchr(const char *str, int tsearched);
int			ft_strlen(const char *s);

// //****************************dollars***************************
t_envlist	*findline(t_envlist *envlist, char *line);
char		*get_env_line(t_envlist *envlist, char *line);
char		*cutline(char *line);
int			ft_len_word(char const *s, char c);
char		*removequote(char *line);

//**********************command********************************
char		*built_in_pwd(t_list *list);
t_envlist	*built_in_cd(t_envlist *envlist, char **buffer, int i);
char		*minifreetab(char **tab, char *result);

//**********************itoa**************************************
long long	ft_atoi(const char *str);
char		*ft_itoa(long long n);

//**********************redirect**************************************
int			redirect(t_list *list, int i);
int			redirectthis(t_list *list);
int			readfunc(char *doc, int fd[2]);

//**********************redirectdup**************************************
void		dupbonus(t_list *list, int **pipefd, int type);
void		redirectdup(t_list *list);

//**********************set_up_file.c**************************************
int			is_redi(char *line, int i);
int			setup_here(char *doc, int command_num, int fd[2], t_list *list);
int			setup_out(int fd[2], char *doc, int type);
int			setup_in(int fd[2], t_list *list, char *doc, int type);

//**********************builtin_management*****************************
int			checkbuiltin(t_list *list);

// //**********************parser***********************
int			check_basic_error(char *buffer);

// //*********************************************
int			is_redi(char *line, int i);

// //**********************split_pipe***********************
char		**split2(char *s, char c, int i);
char		**expand_dollar(t_envlist *envlist, char **str_cmd);

// //**********************split_pipe.c***********************
t_envlist	*findline2(t_envlist *envlist, char *line);
int			ft_count_word(char *s, char sep, char c);
char		*loop_word_quote(int *len_w, char *s, char quote_tp);
char		**ft_split_pipe(char *buff, char c, int i);

//**********************echo**************************************
int			lineisn(char *line);
int			checkn(char **line);
int			built_in_echo(char **line, t_list *list, int linelength);
int			built_in_exit(t_list *list, int i);

//**********************execution*******************************
int			exportunset(t_list *list);
int			checkerrorcmd(t_list *list);
int			errorpathorwait(t_list *list, int type, char **myenv, char *paths);
int			cdsolo(t_list *list, int savedin, int savedout);

//***********************signals***************************************
void		handle_sig(int sig);
void		execute_signals(t_list_prov *prov);
t_list		*minifreeprov(t_list_prov *prov, t_list *list, int type);
int			loop_signal(void);

//**********************func_exec_need.c*******************************
int			onecommand(t_list *list);
char		**getmyenv(t_list *list);

// //*********************childs_function.c ***********************
int			startchild(t_list *list, int **pipefd, int index);
int			firstchild(t_list *list, int **pipefd);
int			middlechild(t_list *list, int **pipefd);
int			lastchild(t_list *list, int **pipefd);

// //**********************function_childs_need.c***********************
int			freeandclose(t_list *list, int **pipefd, int command_count,
				int type);
int			callredirec(t_list *list, int **pipefd, int type);
char		*getpath(char *pro, char *goodline);
char		*getmyline(char **env);
int			checkpro(char *pro);

// //******************exec_start.c ***************************
int			exec(t_list *list);

// //******************setup_here.c ***************************
int			setup_here(char *doc, int command_num, int fd[2], t_list *list);

// //******************ft_close_exec.c ***************************
void		close_here(t_list *tempo);
void		close_allpipe(t_list *list, int **pipefd, int type);
int			closesaved(t_list *list, int savedout, int savedin, int type);
void		close3(t_list *list, int **pipefd, int i);

// //**********************add_list_free.c ***********************
void		freetab(char **tab);
void		free_list(t_list *list);
void		free_first_check(t_list *list);
t_list		*ft_new_node(char *cmd_i, char *buffer, t_envlist *first);
t_list		*ft_add_node(t_list *list, char *cmd_i, char *buffer,
				t_envlist *env);

// //**********************expand_dollars.c***********************
char		*dollar_intero(void);
char		*find_expand_dollar(t_envlist *envlist, char *line);
char		**expand_dollar(t_envlist *envlist, char **str_cmd);

// //**********************func_expand_env_dlr.c***********************
int			ft_len_word(char const *s, char c);
char		*split2_word_quote(char *s, int *count_w);
t_envlist	*findline2(t_envlist *envlist, char *line);
char		*get_env_line_dollar(t_envlist *envlist, char *str_d);//, int *len);
void		init_new_cmd(char **str_1, char **cmd, int *x);
char		*free_expand(char *str_d, char *line);
// //**********************func_expand_dlr.c***********************
// char		*dollar_intero(void);
char		*ft_new_cmd(char *line, char *str_d, int k, int *index);
void		expand_quote(char *line, int *i);
char		*funct_dollar_intero(int *i, int *j, int *k);

// //**********************separator_buffer.c***********************
void		remove_quote_buf(t_list *list);
char		*separate_redi(char *buffer, int i, int j);
char		*rm_quote(char *line, int type);

// //**********************check_error.c****************************
int			check_error_redi(t_list *list);
int			is_whitespace(char c);
int			malloc_rm_quote(char **str, char *line);

int			there_is_quote(char *line);
int			error_pipe(char *buffer, int text, int i, int nb_pipe);

#endif
