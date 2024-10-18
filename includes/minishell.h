/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:45:26 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 22:04:38 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define ENV_MAX_VARS 100000

typedef enum e_token_type
{
	COMMAND,
	CMD_NAME,
	CMD_ARGUMENT,
	REDIRECTION,
	SINGLE_LEFT,
	SINGLE_RIGHT,
	DOUBLE_LEFT,
	DOUBLE_RIGHT,
	PIPE,
	T_FILE
}	t_token_type;
typedef enum e_escaped_type
{
	ESC_SPACE = -3,
	ESC_TAB = -4,
	ESC_SQUOTE = -5,
	ESC_DQUOTE = -6,
	ESC_PIPE = -7,
	ESC_LEFT = -8,
	ESC_RIGHT = -9,
	ESC_DOLLAR = -10,
	DQUOTE_DOLLAR = -11
}	t_escaped_type;
typedef struct s_syntax_tree
{
	t_token_type			type;
	char					*value;
	int						num_branches;
	struct s_syntax_tree	**branches;
}	t_syntax_tree;
void	builtin_env(char **envp);
char	**line_split(char *str, char *charset);
char	**redirection_split(char *str);
int		create_syntax_tree(t_syntax_tree **stree, char *line, char **new_envp);
int		count_split_elements(char **split);
int		create_cmd_name_args_branches(t_syntax_tree *stree, char **new_envp);
void	free_syntax_tree(t_syntax_tree *stree);
char	*revert_transform(char *token);
int		find_redirections(const char *str);
int		check_syntax_and_transform_line(char *line);
void	free_2d_malloc_array(char ***split);
char	*find_env_value(char **new_envp, char *key);
char	*find_key_value(char *env, char *key);
void	fill_expanded_str(char *old_str, char *new_str, char **new_envp, size_t expanded_size);
void	parse_tree(t_syntax_tree *stree);
char	*perform_expansions(char *str, char **new_envp);

#endif
