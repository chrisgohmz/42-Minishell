CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -std=gnu2x
SPEEDFLAGS = -Wall -Wextra -Werror -Ofast
LDFLAGS = -Llibft
LDLIBS = -lft -lreadline -ltinfo

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), minishell.c redirection_split.c syntax_tree.c\
		check_syntax_and_transform.c check_syntax_and_transform2.c parser.c env.c\
		logical_split.c parameter_expansion.c parameter_expansion2.c wildcard_expansion.c\
		redirections.c exit_cleanup.c tree_utils.c exec.c merge_sort.c parser2.c parser3.c\
		heredocs.c signals.c heredoc_signals.c)
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
SPEED_NAME = minishell-speed

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
	$(RM) $(OBJS) $(DEPS) $(BUILTIN_OBJS) $(BUILTIN_DEPS) $(NAME) $(SPEED_NAME)

re: fclean all

vg:
	$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(PWD)/readline.supp --track-fds=yes ./$(NAME)

vg_speed:
	$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(PWD)/readline.supp --track-fds=yes ./$(SPEED_NAME)

speed: $(SPEED_NAME)

$(SPEED_NAME): $(SRCS) $(BUILTIN_SRCS) $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) $(FT_PRINTF_SRCS) $(GNL_SRCS))
	$(CC) $(SPEEDFLAGS) $^ -o $@ -lreadline -ltinfo

-include $(DEPS) $(BUILTIN_DEPS)

.PHONY: all clean fclean re vg vg_speed speed
