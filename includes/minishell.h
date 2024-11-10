/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:45:26 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 16:41:07 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# define MAX_WILDCARD_EXPANSIONS 1000
# define MAX_EXEC_ARGS 1000
# define MAX_FORKS 100000

typedef enum e_token_type
{
	ROOT,
	BRACKETS,
	REDIRECTION,
	SINGLE_LEFT,
	SINGLE_RIGHT,
	DOUBLE_LEFT,
	DOUBLE_RIGHT,
	AND,
	OR,
	PIPE,
	T_FILE,
	HEREDOC_DELIMITER,
	HEREDOC_QUOTED_DELIMITER,
	WORD
}	t_token_type;
typedef enum e_escaped_type
{
	ESC_SPACE = -15,
	ESC_TAB,
	ESC_SQUOTE,
	ESC_DQUOTE,
	ESC_PIPE,
	ESC_LEFT,
	ESC_RIGHT,
	ESC_DOLLAR,
	DQUOTE_DOLLAR,
	ESC_AND,
	ESC_OPEN_BRACKET,
	ESC_CLOSE_BRACKET,
	ESC_WILDCARD
}	t_escaped_type;
typedef struct s_syntax_tree
{
	t_token_type			type;
	char					*value;
	int						num_branches;
	struct s_syntax_tree	**branches;
}	t_syntax_tree;
typedef struct s_ms_vars
{
	unsigned char	exit_value;
	char			**ep;
	char			*exec_argv[MAX_EXEC_ARGS];
	unsigned int	argv_index;
	t_token_type	redirect;
	t_syntax_tree	*stree;
	char			*line;
	pid_t			pid_arr[MAX_FORKS];
}	t_ms_vars;
char			**redirection_split(char *str);
void			create_syntax_tree(t_syntax_tree **stree, char *line, t_ms_vars *ms_vars);
int				count_split_elements(char **split);
void			free_syntax_tree(t_syntax_tree *stree);
char			*revert_transform(char *token);
int				check_syntax_and_transform_line(char *line);
void			free_2d_malloc_array(char ***split);
char			*ft_getenv(const char *name);
void			parse_tree(t_syntax_tree *stree, t_ms_vars *ms_vars);
char			*perform_parameter_expansions(char *str, t_ms_vars *ms_vars);
char			*perform_wildcard_expansions(char *str);
int				make_new_envp(t_ms_vars *ms_vars);
void			free_2d_static_arr(char **arr);
char			*remove_quotes(char *old_str);
char			**logical_split(char *str);
int				check_bracket_syntax(char *line, int bracket_level, int empty_brackets);
void			insert_exit_value(unsigned char exit_value, char *new_str, int *j);
int				perform_redirection(char *filename, t_ms_vars *ms_vars);
void			perform_heredoc(char *delimiter, t_ms_vars *ms_vars, t_token_type delim_type);
void			error_cleanup(t_ms_vars *ms_vars);
void			*allocate_new_node(size_t nmemb, size_t size, t_ms_vars *ms_vars);
void			exec_cmd(t_ms_vars *ms_vars);

#endif
