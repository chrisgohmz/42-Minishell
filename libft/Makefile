CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
ARFLAGS = rcs
-include Makefile.variables

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

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
