CC = cc
CFLAGS = -Wall -Wextra -Werror
-include Makefile.variables

FT_PRINTF_DIR = ft_printf
FT_PRINTF_SRCS = $(FT_PRINTF_DIR)/ft_printf.c $(FT_PRINTF_DIR)/parse_str/parse_str.c\
				$(FT_PRINTF_DIR)/print_types/print_char.c $(FT_PRINTF_DIR)/print_types/print_s.c\
				$(FT_PRINTF_DIR)/print_types/print_d.c $(FT_PRINTF_DIR)/print_types/print_p.c\
				$(FT_PRINTF_DIR)/print_types/print_u.c $(FT_PRINTF_DIR)/print_types/print_x.c\
				$(FT_PRINTF_DIR)/print_types/print_pct.c $(FT_PRINTF_DIR)/print_types/print_specifier.c

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
FT_PRINTF_DEPS = $(FT_PRINTF_SRCS:.c=.d)
GNL_OBJS = $(GNL_SRCS:.c=.o)
GNL_DEPS = $(GNL_SRCS:.c=.d)

NAME = libft.a

all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -g

-include $(LIBFT_DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

clean:
	rm -f $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS) $(LIBFT_DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
