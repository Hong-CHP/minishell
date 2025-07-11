/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:43:15 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/11 15:31:19 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_command
{
	char	*cmd;
	char	**args;
	char	*infile;
	char	*outfile;
	int	 append;
	int	 here_doc;
}				t_command;

typedef struct	s_cmdlist
{
	t_command			*command;
	struct	s_cmdlist	*next;
}				t_cmdlist;

int	count_words(char *str, char c);
int ft_strcmp(char *s1, char *s2);
int if_pipex(char *input);
int		if_quote(char *str);
void	free_split(char **strs);
t_cmdlist	*create_cmds_list(t_cmdlist *head, char *input);
t_command	*tokenize_cmd(t_command *command, char *cmd);
char	**extract_cmd_args(char **cmds_split, char *content, t_command *command);
void    fill_args(char **split, t_command *cmd, char **set);
int     count_utill_charset(char **cmds_split, char **charset);
char	*find_words_in_quote(char *content, char ch);
char	*supp_quote_add_space(char *str);
char	*supp_last_quote(char *str);

#endif