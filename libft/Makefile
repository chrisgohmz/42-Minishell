CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
		 ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c\
		 ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
		 ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
		 ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		 ft_utoa.c ft_utox.c ft_ptoa.c ft_lstnew.c ft_lstadd_front.c\
		 ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
		 ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_isint.c ft_abs.c\
		 ft_max.c ft_min.c ft_atoi_base.c ft_multi_split.c

FT_PRINTF_DIR = ft_printf
FT_PRINTF_SRCS = $(FT_PRINTF_DIR)/ft_printf.c $(FT_PRINTF_DIR)/parse_str/parse_str.c\
				$(FT_PRINTF_DIR)/print_types/print_char.c $(FT_PRINTF_DIR)/print_types/print_s.c\
				$(FT_PRINTF_DIR)/print_types/print_d.c $(FT_PRINTF_DIR)/print_types/print_p.c\
				$(FT_PRINTF_DIR)/print_types/print_u.c $(FT_PRINTF_DIR)/print_types/print_x.c\
				$(FT_PRINTF_DIR)/print_types/print_pct.c $(FT_PRINTF_DIR)/print_types/print_specifier.c

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
FT_PRINTF_DEPS = $(FT_PRINTF_SRCS:.c=.d)
GNL_OBJS = $(GNL_SRCS:.c=.o)
GNL_DEPS = $(GNL_SRCS:.c=.d)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -g

-include $(DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

clean:
	rm -f $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS) $(DEPS) $(FT_PRINTF_DEPS) $(GNL_DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
