/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:45:26 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/19 19:30:53 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef _FORTIFY_SOURCE
#  define _FORTIFY_SOURCE 2
# endif
# define _GNU_SOURCE
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# define PROMPT_START "\001\e[1;95m\002LynetteChriShell:"
# define PROMPT_END "> \001\e[0m\002"
# define SYNTAX_ERROR 2

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
	ESC_SPACE = -30,
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
	ESC_WILDCARD,
	DQUOTE,
	SQUOTE
}	t_escaped_type;
typedef enum e_process_type
{
	PARENT,
	CHILD
}	t_process_type;
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
	size_t			env_size;
	char			**exec_argv;
	unsigned int	argv_index;
	t_token_type	redirect;
	t_syntax_tree	*stree;
	char			*line;
	pid_t			*pid_arr;
	char			prompt[PATH_MAX + sizeof(PROMPT_START) + sizeof(PROMPT_END) - 2];
	t_process_type	proc_type;
	int				stdout_fd;
	int				stdin_fd;
}	t_ms_vars;
typedef struct s_mergesort_vars
{
	int	start;
	int	middle;
	int	end;
}	t_mergesort_vars;
char	**redirection_split(char *str);
void	create_syntax_tree(t_syntax_tree **stree, char *line, t_ms_vars *ms_vars);
int		count_split_elements(char **split);
void	free_syntax_tree(t_syntax_tree *stree);
char	*revert_transform(char *token);
int		check_syntax_and_transform_line(char *line);
void	free_2d_malloc_array(char ***split);
char	*ft_getenv(char *name);
void	parse_tree(t_syntax_tree *stree, t_ms_vars *ms_vars);
char	*perform_parameter_expansions(char *str, t_ms_vars *ms_vars);
char	**perform_wildcard_expansions(char *str);
int		make_new_envp(t_ms_vars *ms_vars);
char	*remove_quotes(char *old_str);
char	**logical_split(char *str);
int		check_bracket_syntax(char *line, int bracket_level, int empty_brackets);
void	insert_exit_value(unsigned char exit_value, char *new_str, int *j);
int		perform_redirection(char **filename, t_ms_vars *ms_vars);
void	perform_heredoc(char *delimiter, t_ms_vars *ms_vars, t_token_type delim_type);
void	error_cleanup(t_ms_vars *ms_vars);
void	*allocate_new_node(size_t nmemb, size_t size, t_ms_vars *ms_vars);
void	exec_cmd(t_ms_vars *ms_vars);
char	**mergesort_expansions(char **expansions, int expansions_count);
int		check_cmd_is_builtin(t_ms_vars *ms_vars);
void	echo_builtin(t_ms_vars *ms_vars);
void	cd_builtin(t_ms_vars *ms_vars);
void	pwd_builtin(t_ms_vars *ms_vars);
void	export_builtin(t_ms_vars *ms_vars);
void	unset_builtin(t_ms_vars *ms_vars);
void	env_builtin(t_ms_vars *ms_vars);
void	exit_builtin(t_ms_vars *ms_vars);
int		fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars);
void	wait_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars);
void	fork_wait_single_process(t_ms_vars *ms_vars);
void	parse_cmd_redirects(t_syntax_tree *stree, t_ms_vars *ms_vars);
void	modify_expansions_if_export(t_syntax_tree *stree);
void	disable_value_word_splitting(char *str);

#endif
