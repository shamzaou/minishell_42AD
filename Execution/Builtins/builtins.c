/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:09:02 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 12:28:37 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     is_builtin(char *cmd)
{
    char *builtin;

    if (cmd == NULL)
        return (0);
    builtin = ft_strtolower(cmd);
    
    
    return (0);
}