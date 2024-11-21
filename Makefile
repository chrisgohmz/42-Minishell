CFLAGS = -Wall -Wextra -Werror -MMD -MP -Og -g
SPEEDFLAGS = -Wall -Wextra -Werror -Ofast
LDFLAGS = -Llibft
LDLIBS = -lft -lreadline -ltinfo

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), minishell.c redirection_split.c syntax_tree.c\
		check_syntax_and_transform.c check_syntax_and_transform2.c parser.c env.c\
		logical_split.c parameter_expansion.c parameter_expansion2.c wildcard_expansion.c\
		redirections.c error.c tree_utils.c exec.c merge_sort.c parser2.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

BUILTIN_SRCS = $(addprefix $(SRCS_DIR)builtins_lpwi/, echo.c cd.c pwd.c env.c export.c\
				unset.c exit.c)
BUILTIN_DEPS = $(BUILTIN_SRCS:.c=.d)
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

-include $(LIBFT_DIR)/Makefile.variables

NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(BUILTIN_OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIBFT): $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) libft.h)
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(DEPS) $(BUILTIN_OBJS) $(BUILTIN_DEPS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(DEPS) $(BUILTIN_OBJS) $(BUILTIN_DEPS)
	$(RM) $(NAME)

re: fclean all

vg:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --trace-children=yes --track-fds=yes ./minishell

speed: $(SRCS) $(BUILTIN_SRCS) $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS))
	$(CC) $(SPEEDFLAGS) $^ -o $(NAME) -lreadline -ltinfo

-include $(DEPS) $(BUILTIN_DEPS)

.PHONY: all clean fclean re vg
