/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:21:40 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 10:49:28 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

static size_t str_length(char const *str, char const *delimiters, size_t start)
{
    size_t length = start;
    while (str[length] && !strchr(delimiters, str[length]))
    {
        length++;
    }
    length = length - start;
    return length;
}

static size_t str_count(char const *s, char const *delimiters)
{
    size_t i = 0;
    size_t len;
    size_t count;

    if (!s)
        return 0;
    i = 0;
    count = 0;
    len = strlen(s);
    while (i < len)
    {
        while (strchr(delimiters, s[i]))
            i++;
        if (s[i] && s[i] != '\0')
            count++;
        i = i + str_length(s, delimiters, i);
    }
    return count;
}

char **ft_splitter(char const *s, char const *delimiters)
{
    size_t i = 0;
    size_t j = 0;
    char **split;

    i = 0;
    j = 0;
    split = (char **)calloc(sizeof(char *), (str_count(s, delimiters) + 1));
    if (!split || !s)
    {
        free((void **)split);
        return NULL;
    }
    while (j < str_count(s, delimiters))
    {
        while (strchr(delimiters, s[i]))
            i++;
        if (s[i] && s[i] != '\0')
            split[j] = ft_substr(s, i, str_length(s, delimiters, i));
        if (!split[j])
            return NULL;
        i = i + str_length(s, delimiters, i);
        j++;
    }
    return split;
}
