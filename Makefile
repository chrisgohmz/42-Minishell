CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), minishell.c redirection_split.c syntax_tree.c\
		check_syntax_and_transform.c check_syntax_and_transform2.c parser.c env.c\
		logical_split.c parameter_expansion.c parameter_expansion2.c wildcard_expansion.c\
		redirections.c error.c tree_utils.c exec.c merge_sort.c parser2.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

BUILTIN_SRCS = $(addprefix $(SRCS_DIR)/builtins_lpwi/, echo.c cd.c pwd.c env.c export.c\
				unset.c exit.c)
BUILTIN_DEPS = $(BUILTIN_SRCS:.c=.d)
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

-include $(LIBFT_DIR)/Makefile.variables

NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(BUILTIN_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(BUILTIN_OBJS) $(LIBFT) -o $(NAME) -lreadline -ltinfo

$(LIBFT): $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) libft.h)
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS) $(BUILTIN_DEPS)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPS) $(BUILTIN_OBJS) $(BUILTIN_DEPS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPS) $(BUILTIN_OBJS) $(BUILTIN_DEPS)
	rm -f $(NAME)

re: fclean all

vg:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --trace-children=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re vg
