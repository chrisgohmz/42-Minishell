CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = $(addprefix srcs/, minishell.c redirection_split.c syntax_tree.c\
		check_syntax_and_transform.c check_syntax_and_transform2.c parser.c env.c\
		logical_split.c parameter_expansion.c parameter_expansion2.c wildcard_expansion.c\
		redirections.c error.c tree_utils.c exec.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

-include $(LIBFT_DIR)/Makefile.variables

NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -ltinfo

$(LIBFT): $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) libft.h)
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
