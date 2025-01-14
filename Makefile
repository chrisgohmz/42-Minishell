CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
SPEEDFLAGS = -Wall -Wextra -Werror -Ofast
LDFLAGS = -Llibft
LDLIBS = -lft -lreadline -ltinfo

SRCS_DIR = srcs/
BUILTIN_DIR = $(SRCS_DIR)Built-ins/
CMD_EXEC_DIR = $(SRCS_DIR)Command_Execution/
ENV_DIR = $(SRCS_DIR)Env/
EXIT_CLEANUP_DIR = $(SRCS_DIR)Exit_Cleanup/
HEREDOCS_DIR = $(SRCS_DIR)Heredocs/
PARAMETER_EXPANSION_DIR = $(SRCS_DIR)Parameter_Expansion/
PARSER_DIR = $(SRCS_DIR)Parser/
REDIRECTIONS_DIR = $(SRCS_DIR)Redirections/
SIGNALS_DIR = $(SRCS_DIR)Signals/
SYNTAX_AND_TRANSFORMATION_DIR = $(SRCS_DIR)Syntax_and_Transformation/
SYNTAX_TREE_DIR = $(SRCS_DIR)Syntax_Tree/
WILDCARD_EXPANSION_DIR = $(SRCS_DIR)Wildcard_Expansion/

SRCS = $(addprefix $(SRCS_DIR), minishell.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR), echo.c cd.c pwd.c env.c export.c\
				unset.c exit.c)
BUILTIN_DEPS = $(BUILTIN_SRCS:.c=.d)
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

CMD_EXEC_SRCS = $(addprefix $(CMD_EXEC_DIR), exec.c exec_utils.c)
CMD_EXEC_DEPS = $(CMD_EXEC_SRCS:.c=.d)
CMD_EXEC_OBJS = $(CMD_EXEC_SRCS:.c=.o)

ENV_SRCS = $(addprefix $(ENV_DIR), env.c)
ENV_DEPS = $(ENV_SRCS:.c=.d)
ENV_OBJS = $(ENV_SRCS:.c=.o)

EXIT_CLEANUP_SRCS = $(addprefix $(EXIT_CLEANUP_DIR), exit_cleanup.c)
EXIT_CLEANUP_DEPS = $(EXIT_CLEANUP_SRCS:.c=.d)
EXIT_CLEANUP_OBJS = $(EXIT_CLEANUP_SRCS:.c=.o)

HEREDOCS_SRCS = $(addprefix $(HEREDOCS_DIR), heredocs.c)
HEREDOCS_DEPS = $(HEREDOCS_SRCS:.c=.d)
HEREDOCS_OBJS = $(HEREDOCS_SRCS:.c=.o)

PARAMETER_EXPANSION_SRCS = $(addprefix $(PARAMETER_EXPANSION_DIR), parameter_expansion.c exit_value.c)
PARAMETER_EXPANSION_DEPS = $(PARAMETER_EXPANSION_SRCS:.c=.d)
PARAMETER_EXPANSION_OBJS = $(PARAMETER_EXPANSION_SRCS:.c=.o)

PARSER_SRCS = $(addprefix $(PARSER_DIR), parser.c parse_cmd_redirects.c handle_tokens.c non_null_arg_quote_removal.c exec_args.c piped_commands.c single_command.c disable_export_word_split.c)
PARSER_DEPS = $(PARSER_SRCS:.c=.d)
PARSER_OBJS = $(PARSER_SRCS:.c=.o)

REDIRECTIONS_SRCS = $(addprefix $(REDIRECTIONS_DIR), redirections.c)
REDIRECTIONS_DEPS = $(REDIRECTIONS_SRCS:.c=.d)
REDIRECTIONS_OBJS = $(REDIRECTIONS_SRCS:.c=.o)

SIGNALS_SRCS = $(addprefix $(SIGNALS_DIR), signals.c)
SIGNALS_DEPS = $(SIGNALS_SRCS:.c=.d)
SIGNALS_OBJS = $(SIGNALS_SRCS:.c=.o)

SYNTAX_AND_TRANSFORMATION_SRCS = $(addprefix $(SYNTAX_AND_TRANSFORMATION_DIR), check_syntax_and_transform.c\
									check_syntax.c quote_removal.c transform.c transform2.c)
SYNTAX_AND_TRANSFORMATION_DEPS = $(SYNTAX_AND_TRANSFORMATION_SRCS:.c=.d)
SYNTAX_AND_TRANSFORMATION_OBJS = $(SYNTAX_AND_TRANSFORMATION_SRCS:.c=.o)

SYNTAX_TREE_SRCS = $(addprefix $(SYNTAX_TREE_DIR), logical_branches.c pipe_branches.c cmd_redirection_branches.c redirection_branches.c tree_utils.c logical_split.c logical_split2.c redirection_split.c redirection_split2.c)
SYNTAX_TREE_DEPS = $(SYNTAX_TREE_SRCS:.c=.d)
SYNTAX_TREE_OBJS = $(SYNTAX_TREE_SRCS:.c=.o)

WILDCARD_EXPANSION_SRCS = $(addprefix $(WILDCARD_EXPANSION_DIR), wildcard_expansion.c wildcard_expansion2.c wildcard_expansion3.c merge_sort.c)
WILDCARD_EXPANSION_DEPS = $(WILDCARD_EXPANSION_SRCS:.c=.d)
WILDCARD_EXPANSION_OBJS = $(WILDCARD_EXPANSION_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

-include $(LIBFT_DIR)/Makefile.variables

NAME = minishell
SPEED_NAME = minishell-speed

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(BUILTIN_OBJS) $(CMD_EXEC_OBJS) $(ENV_OBJS) $(EXIT_CLEANUP_OBJS) $(HEREDOCS_OBJS) $(PARAMETER_EXPANSION_OBJS) $(PARSER_OBJS) $(REDIRECTIONS_OBJS) $(SIGNALS_OBJS) $(SYNTAX_AND_TRANSFORMATION_OBJS) $(SYNTAX_TREE_OBJS) $(WILDCARD_EXPANSION_OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIBFT): $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) libft.h)
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(BUILTIN_OBJS) $(CMD_EXEC_OBJS) $(ENV_OBJS) $(EXIT_CLEANUP_OBJS) $(HEREDOCS_OBJS) $(PARAMETER_EXPANSION_OBJS) $(PARSER_OBJS) $(REDIRECTIONS_OBJS) $(SIGNALS_OBJS) $(SYNTAX_AND_TRANSFORMATION_OBJS) $(SYNTAX_TREE_OBJS) $(WILDCARD_EXPANSION_OBJS) $(DEPS) $(BUILTIN_DEPS) $(CMD_EXEC_DEPS) $(ENV_DEPS) $(EXIT_CLEANUP_DEPS) $(HEREDOCS_DEPS) $(PARAMETER_EXPANSION_DEPS) $(PARSER_DEPS) $(REDIRECTIONS_DEPS) $(SIGNALS_DEPS) $(SYNTAX_AND_TRANSFORMATION_DEPS) $(SYNTAX_TREE_DEPS) $(WILDCARD_EXPANSION_DEPS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(BUILTIN_OBJS) $(CMD_EXEC_OBJS) $(ENV_OBJS) $(EXIT_CLEANUP_OBJS) $(HEREDOCS_OBJS) $(PARAMETER_EXPANSION_OBJS) $(PARSER_OBJS) $(REDIRECTIONS_OBJS) $(SIGNALS_OBJS) $(SYNTAX_AND_TRANSFORMATION_OBJS) $(SYNTAX_TREE_OBJS) $(WILDCARD_EXPANSION_OBJS) $(DEPS) $(BUILTIN_DEPS) $(CMD_EXEC_DEPS) $(ENV_DEPS) $(EXIT_CLEANUP_DEPS) $(HEREDOCS_DEPS) $(PARAMETER_EXPANSION_DEPS) $(PARSER_DEPS) $(REDIRECTIONS_DEPS) $(SIGNALS_DEPS) $(SYNTAX_AND_TRANSFORMATION_DEPS) $(SYNTAX_TREE_DEPS) $(WILDCARD_EXPANSION_DEPS) $(NAME) $(SPEED_NAME)

re: fclean all

vg:
	$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(PWD)/readline.supp --track-fds=yes ./$(NAME)

vg_speed:
	$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(PWD)/readline.supp --track-fds=yes ./$(SPEED_NAME)

speed: $(SPEED_NAME)

$(SPEED_NAME): $(SRCS) $(BUILTIN_SRCS) $(CMD_EXEC_SRCS) $(ENV_SRCS) $(EXIT_CLEANUP_SRCS) $(HEREDOCS_SRCS) $(PARAMETER_EXPANSION_SRCS) $(PARSER_SRCS) $(REDIRECTIONS_SRCS) $(SIGNALS_SRCS) $(SYNTAX_AND_TRANSFORMATION_SRCS) $(SYNTAX_TREE_SRCS) $(WILDCARD_EXPANSION_SRCS) $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) $(FT_PRINTF_SRCS) $(GNL_SRCS))
	$(CC) $(SPEEDFLAGS) $^ -o $@ -lreadline -ltinfo

-include $(DEPS) $(BUILTIN_DEPS) $(CMD_EXEC_DEPS) $(ENV_DEPS) $(EXIT_CLEANUP_DEPS) $(HEREDOCS_DEPS) $(PARAMETER_EXPANSION_DEPS)\
			$(PARSER_DEPS) $(REDIRECTIONS_DEPS) $(SIGNALS_DEPS) $(SYNTAX_AND_TRANSFORMATION_DEPS) $(SYNTAX_TREE_DEPS) $(WILDCARD_EXPANSION_DEPS)

.PHONY: all clean fclean re vg vg_speed speed
