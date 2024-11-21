CFLAGS = -Wall -Wextra -Werror -MMD -MP -Og -g
ARFLAGS = rcs
-include Makefile.variables

FT_PRINTF_DIR = ft_printf/
FT_PRINTF_SRCS = $(addprefix $(FT_PRINTF_DIR), ft_printf.c parse_str/parse_str.c\
				print_types/print_char.c print_types/print_s.c\
				print_types/print_d.c print_types/print_p.c\
				print_types/print_u.c print_types/print_x.c\
				print_types/print_pct.c print_types/print_specifier.c)

GNL_DIR = get_next_line/
GNL_SRCS = $(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c)

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
FT_PRINTF_DEPS = $(FT_PRINTF_SRCS:.c=.d)
GNL_OBJS = $(GNL_SRCS:.c=.o)
GNL_DEPS = $(GNL_SRCS:.c=.d)

NAME = libft.a

all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)

-include $(LIBFT_DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

clean:
	$(RM) $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS) $(LIBFT_DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
