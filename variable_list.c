/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:48:11 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/15 18:11:14 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	clean_var_list(t_varlist **head)
{
    t_varlist   *cur;
    t_varlist   *next;
    
    cur = *head;
    while (cur)
    {
        next = cur->next;
        free(cur->var_data);
        free(cur);
        cur = next;
    }
    *head = NULL;
}

void	add_var_lst_front(t_varlist **head, t_varlist *var_node)
{
	if (*head && var_node)
		var_node->next = *head;
	*head = var_node;
}

void	create_var_list(t_varlist **head, char *input)
{
	t_varlist	*var_node;
	t_varlist	*cur;

	var_node = malloc(sizeof(t_varlist));
	if (!var_node)
		return ;
	var_node->var_data = init_registre_variable(input);
	var_node->next = NULL;
	add_var_lst_front(head, var_node);
    cur = *head;
    while (cur)
    {
        printf("var_node data are: %s, %s, %d\n", cur->var_data->var,  cur->var_data->val,  cur->var_data->exported);
        cur = cur->next;
    }
}