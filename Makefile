NAME			=	minishell

SRCS			=	srcs/minishell.c \
					srcs/utils.c \
					srcs/env_management.c \
					srcs/export.c \
					srcs/dollars.c \
					srcs/unset.c \
					srcs/command.c \
					srcs/execution.c \
					srcs/itoa.c \
					srcs/builtin_management.c \
					srcs/echo.c \
					srcs/redirect.c \
					srcs/utils2.c \
					srcs/redirectdup.c \
					srcs/set_up_file.c \
					srcs/env_utils.c \
					srcs/childs_function.c\
					srcs/function_childs_need.c\
					srcs/ft_close_exec.c\
					srcs/func_exec_need.c \
					srcs/print_env.c \
					srcs/do_shlvl.c \
					srcs/gnl.c \
					srcs/gnl_utils.c \
					srcs/read_here.c \
					parsing/add_list_free.c\
					parsing/split_pipe.c\
					parsing/split_space.c \
					parsing/clean_string.c \
					parsing/separator_buffer.c \
					parsing/check_error.c \
					parsing/expand_dollars.c \
					parsing/func_expand_dlr.c\
					parsing/pars_quote.c \
					parsing/funct_env_dlr.c \
					srcs/exec_start.c \
					srcs/setup_here.c \
					srcs/exec_utils.c \
					srcs/signals.c

OBJS			=	${SRCS:.c=.o}

CC				=	clang -g

CFLAGS			= -Wall -Werror -Wextra

.c.o			:
					 ${CC}  ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${OBJS} -o ${NAME} -lreadline

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
