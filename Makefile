CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix srcs/, minishell.c redirection_split.c syntax_tree.c syntax_tree2.c\
		check_syntax_and_transform.c check_syntax_and_transform2.c parser.c env.c\
		logical_split.c parameter_expansion.c parameter_expansion2.c wildcard_expansion.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -g -lreadline -ltinfo

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -g

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
