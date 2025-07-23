/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:28:28 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 17:23:54 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char    *fill_multi_vars(char *str, int i)
{
    int len;
    int dollar_pos;
    int j;
    char    *var;

    len = 0;
    dollar_pos = i;
    j = i + 1;
    while (str[j] && str[j] >= 'A' && str[j] <='Z')
    {
        len++;
        j++;
    }
    var = ft_substr(str, dollar_pos + 1, len);
    return (var);
}

char    **find_dollar_sign(char *str, int nb_var)
{
    int i;
    int k;
    char    **vars;

    vars = malloc(sizeof(char *) * (nb_var + 1));
    if (!vars)
        return (NULL);
    i = 0;
    k = 0;
    while(str[i])
    {
        if (str[i] == '$')
        {
            vars[k] = fill_multi_vars(str, i);
            printf("vars after dollar sign is %s\n", vars[k]);
            k++;
        }
        i++;
    }
    vars[k] = NULL;
    return (vars);
}

char *check_same_var_in_varlist(char *var, t_cmdlist *cmd_node)
{
    t_varlist *cur;
    char      *tmp;
    
    if (!var || !cmd_node || !cmd_node->var_list)
    {
        printf("Error: cmd_node or var_list is NULL!\n");
        return NULL;
    }
    tmp = NULL;
    cur = cmd_node->var_list;
    while (cur)
    {
        if (ft_strcmp(var, cur->var_data->var) == 0)
        {
            tmp = ft_strdup(cur->var_data->val);
            return (tmp);
        }
        cur = cur->next;
    }
    return (NULL);
}

int    get_vals_and_tot_len(char *str, char **vals, char **vars, t_cmdlist *cmd_node)
{
    int i;
    int len;
    int t_len;

    i = 0;
    len = 0;
    while (vars[i])
    {
        vals[i] = check_same_var_in_varlist(vars[i], cmd_node);
        printf("vals is %s\n", vals[i]);
        len += ft_strlen(vals[i]);
        i++;
    }
    vals[i] = NULL;
    t_len = real_length_of_word(str, len);
    printf("vals length totally is %d\n", len);
    return (t_len);
}

void    fill_word_with_real_vals(char *word, char *str, char **vars, char **vals, int t_len)
{
    int i;
    int j;
    int k;
    int o;
    
    i = 0;
    k = 0;
    j = 0;
    while(j < t_len)
    {
        if (str[i] == '\'' || str[i] == '\"')
			i++;
        if (str[i] == '$')
        {
            i++;
            o = 0;
            while(vals[k][o])
            {
                word[j] = vals[k][o];
                j++;
                o++;
            }
            i += ft_strlen(vars[k]);
            k++;
        }
        else
        {
            word[j] = str[i];
            j++;
            i++;
        }
    }
    word[j] = '\0';
}

char    *reg_dollar(char *str, t_cmdlist *cmd_node)
{
    char    **vars;
    int     nb_vars;
    char    **vals;
    int t_len;
    char    *word;

    printf("6.head var ptr is %p\n", cmd_node->var_list);
    nb_vars = if_dollar_sign(str);
    vars = find_dollar_sign(str, nb_vars);
    printf("total nb of vars is %d\n", nb_vars);
    vals = malloc(sizeof(char *) * (nb_vars + 1));
    if (!vals)
    {
        free_vars_vals(vars, vals);
        return (NULL);
    }
    t_len = get_vals_and_tot_len(str, vals, vars, cmd_node);
    word = malloc(sizeof(char) * (t_len + 1));
    if (!word)
    {
        free_vars_vals(vars, vals);
        return (NULL);
    }
    fill_word_with_real_vals(word, str, vars, vals, t_len);
    printf("real word after replace is %s\n", word);
    free_vars_vals(vars, vals);
    return (word);
}
