/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:43:15 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 17:15:40 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_variable
{
	char	*var;
	char	*val;
	int		exported;
	struct s_variable *next;
}				t_variable;

typedef struct	s_varlist
{
	t_variable			*var_data;
	struct s_varlist	*next;
}				t_varlist;

typedef struct	s_command
{
	char	*cmd;
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	int		here_doc;
}				t_command;

typedef struct	s_cmdlist
{
	t_command			*command;
	t_varlist			*var_list;
	struct	s_cmdlist	*next;
}				t_cmdlist;

// ft_split.c
int		count_words(char *str, char c);
// utils_str.c 
int 	ft_strcmp(char *s1, char *s2);
void	free_split(char **strs);
// pipex_utils.c
int 	if_pipex(char *input);
// tokenize_utils.c 
int		if_quote(char *str);
int		if_equal(char *str);
//command_list.c
void	clean_cmdlist(t_cmdlist **head);
t_cmdlist	*create_cmds_list(t_cmdlist *head, char *input, t_varlist **head_var);
//tokenize.c
t_command	*tokenize_cmd(t_cmdlist *cmd_node, char *content);
//extract_cmd_args.c
char	**extract_cmd_args(char **cmds_split, char *content, t_cmdlist *cmd_node);
// extract_cmd_args_by_quote.c
void	fill_args(char **split, t_cmdlist *cmd_node, char **set);
int     count_utill_charset(char **cmds_split, char **charset);
char	*find_words_in_quote(char *content, char ch);
char	*supp_quote_add_space(char *str);
char	*supp_last_quote(char *str);
//variable_value.c
void 	init_registre_variable(t_variable *v_content, char *content);
//variable_list.c
void	clean_var_list(t_varlist **head);
void    create_var_list_or_find_node(t_varlist **head, char *input, t_variable *var_node);
//variable_utils.c 
int		if_export_variable(char *content);
int		no_quote_no_space(char *str);
char	*if_variable_val(char *content);
char	*if_variable_var(char *content);
int		check_input_var_val(char *input);
// dollar_sign.c
char    *reg_dollar(char *str, t_cmdlist *cmd_node);
char    **find_dollar_sign(char *str, int nb_var);
// dollar_sign_utils.c
int		if_dollar_sign(char *str);
void    free_vars_vals(char **vars, char **vals);
int	real_length_of_word(char *str, int vals_len);

#endif